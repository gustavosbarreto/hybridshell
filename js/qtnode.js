// Wrap QtNode object
window.QtNode = {
    onLoad: { _cb: function() { }, connect: function(cb) { this._cb = cb; } }
};

// This function is invoked on QWebChannel script is loaded
function connectToWebChannel() {
    var socket = new WebSocket(getURLParam("webChannel"));
    socket.onopen = function() { initializeWebChannel(socket); }
}

// This function is invoked on WebSocket is connected
function initializeWebChannel(socket) {
    new QWebChannel(socket, function(channel) {
        // Once this callback is invoked all published objects in QWebChannel are acessible

        var QtNode = window.QtNode;
        window.QtNode = channel.objects.QtNode; // The wrapper for the QtNode is not necessary anymore

        // This function send the 'fn' code to NodeJSEvaluator which is responsible
        // for compiling the code using the v8::Script and also running it into Node.js context
        window.QtNode.exec = function(scope, fn, cb) {
            var thisArgs = JSON.stringify(scope);
            var compiledCode = compileScriptTemplate(nodeScriptTemplate, { code: fn.toString(), thisArgs: thisArgs });

            channel.objects.NodeJSEvaluator.eval(compiledCode, cb);
        }

        // This SLOT evaluates the 'code' in browser context when QWebEngineView.exec is called in the Node.js context
        channel.objects.NodeJSEvaluator.evaluateJavaScript.connect(function(uuid, code) {
            if (uuid == getURLParam("qtNodeUuid")) {
                var compiledCode = compileScriptTemplate(browserScriptTemplate, { code: code });

                eval(compiledCode);
            }
        });

        processScriptElements();

        // Finally calls onLoad callback
        QtNode.onLoad._cb();
    });
}

function getURLParam(param) {
    var regexp = new RegExp("[\\?&]" + param + "=([^&#]*)");
    return regexp.exec(decodeURIComponent(location.search))[1];
}

// Process all script elements with type of "nodejs"
function processScriptElements() {
    var scripts = document.getElementsByTagName('script');
    for (var i = 0; i < scripts.length; i++) {
        if (scripts[i].type == "nodejs") {
            var compiledCode = compileScriptTemplate(scriptElementTemplate, { code: scripts[i].innerHTML });

            window.QtNode.exec({}, compiledCode, function() { });
        }
    }
}

/*
 * Compiles a script template
 *
 * fn	A script template function
 * args	An object containing the arguments to be replaced in the compiled script template
 */
function compileScriptTemplate(fn, args) {
  var str = fn.toString();

  for (var i in args) {
    str = str.replace("#{" + i + "}", args[i]);
  }

  return str.replace(/^[^\/]+\/\*!?/, '').
             replace(/\*\/[^\/]+$/, '').trim();
}

// This script template is used to evaluate an JavaScript code in Nodejs context
var nodeScriptTemplate = function() {/*!

// Due the v8 isolation design the 'require' is not available by default
function require(mod) {
  return module.require(mod);
};

// Wraps JavaScript code in a function and pass the this arguments
(#{code}).call(JSON.parse('#{thisArgs}'));

*/}

// This script template is used to evaluate an JavaScript code in Nodejs context
var browserScriptTemplate = function() {/*!

(#{code})();

*/}

// This script template is used to evaluate script elements with type of "nodejs"
var scriptElementTemplate = function() {/*!

function() {
  #{code}
}

*/}

var script = document.createElement('script');
script.type = 'text/javascript';
script.src = 'qrc:///qtwebchannel/qwebchannel.js'; // Qt web channel script file
script.onload = connectToWebChannel;

document.getElementsByTagName('head')[0].appendChild(script);
