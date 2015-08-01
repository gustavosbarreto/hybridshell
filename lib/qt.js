var qt = require(__dirname + '/../build/Release/qt.node');

var url = require('url');

// Guarantees single instance of QApplication
if (typeof _qtApp == "undefined") {
    // avoid GC'ed
    global._qtApp = new qt.QApplication;
}

var _qtWebEngineView = qt.QWebEngineView;
var _qtWebEngineViewLoad = qt.QWebEngineView.prototype.load;
var _qtWebEngineViewExec = qt.QWebEngineView.prototype.exec;
var _qtWebEngineViewInstances = [];

qt.QWebEngineView.prototype.load = function(_url) {
	// Append webChannel URL
	var parsed_url = url.parse(_url, true);
	parsed_url.search = "";
	parsed_url.query["webChannel"] = _qtApp.webChannelUrl();
	parsed_url.query["qtNodeUuid"] = this.uuid();

	_qtWebEngineViewLoad.apply(this, [ url.format(parsed_url) ]);
}

qt.QWebEngineView.prototype.exec = function(func) {
    var args = Array.prototype.slice.call(arguments);
    args[0] = args[0].toString();

    _qtWebEngineViewExec.apply(this, args);
}

// Push QWebEngineView instances to an array to avoid GC'ed
qt.QWebEngineView = function() {
	_qtWebEngineViewInstances.push(new _qtWebEngineView);
	return _qtWebEngineViewInstances[_qtWebEngineViewInstances.length - 1];
}

// Qt mainloop integration
setInterval(_qtApp.processEvents.bind(_qtApp), 0);

// Allow NodeJSEvaluator to use require
global.module = module;

module.exports = qt;
