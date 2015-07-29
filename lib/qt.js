var qt = require(__dirname + '/../build/Release/qt.node');

// avoid GC'ed
global._qtApp = new qt.QApplication;

var _qtWebEngineView = qt.QWebEngineView;
var _qtWebEngineViewInstances = [];

// Push QWebEngineView instances to an array to avoid GC'ed
qt.QWebEngineView = function() {
	_qtWebEngineViewInstances.push(new _qtWebEngineView);
	return _qtWebEngineViewInstances[_qtWebEngineViewInstances.length - 1];
}

// Qt mainloop integration
setInterval(_qtApp.processEvents.bind(_qtApp), 0);

module.exports = qt;
