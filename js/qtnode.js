// Wrap QtNode object because the real object is loaded asynchronous
window.QtNode = {
    onLoad: { _cb: function() { }, connect: function(cb) { this._cb = cb; } }
};

window._QtNode = {
};

var script = document.createElement('script');
script.type = 'text/javascript';
script.src = 'qrc:///qtwebchannel/qwebchannel.js'; // Qt web channel script file
script.onload = function() {
	// Connect to the Web Channel
    var url = (/[?&]webChannel=([A-Za-z0-9\-:/\.]+)/.exec(decodeURIComponent(location.search))[1]);
    var socket = new WebSocket(url);

    socket.onopen = function() {
        new QWebChannel(socket, function(channel) {
            // Once this callback is invoked, the QtNode object is acessible. Thus,
            // the wrapper for the QtNode is not necessary anymore

            // First undo wrapper for the QtNode object
            var QtNode = window.QtNode;
            window.QtNode = channel.objects.QtNode;
            window._QtNode = window.QtNode;

            window.QtNode.exec = function(scope, func, cb) {
                var scopeJson = JSON.stringify(scope);

                channel.objects.NodeJSEvaluator.eval("function require(mod) { return module.require(mod); }; (" + func.toString() + ").call(JSON.parse(\'" + scopeJson + "\'))", function(result) {
                    cb(result);
                });
            }

            var scripts = document.getElementsByTagName('script');
            for (var i = 0; i < scripts.length; i++) {
                if (scripts[i].type == "nodejs") {
                    window.QtNode.exec({}, "function() { " + scripts[i].innerHTML + " }", function() { });
                }
            }

            // Finally calls onLoad callback
            QtNode.onLoad._cb();
        });
	}
}

document.getElementsByTagName('head')[0].appendChild(script);
