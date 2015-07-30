#include "webchannel.h"
#include "webchanneltransport.h"
#include "nodejsevaluator.h"

#include <QWebSocketServer>
#include <QWebChannel>
#include <QUrl>

static WebChannel *_instance = NULL;

WebChannel::WebChannel()
{
    server = new QWebSocketServer("test", QWebSocketServer::NonSecureMode);
    server->listen(QHostAddress::LocalHost);

    evaluator = new NodeJSEvaluator();

    QWebChannel *channel = new QWebChannel();

    channel->registerObject("QtNode", new QObject);
    channel->registerObject("NodeJSEvaluator", evaluator);

    QObject::connect(server, &QWebSocketServer::newConnection, [=]() {
        WebChannelTransport *transport = new WebChannelTransport(server->nextPendingConnection());
        channel->connectTo(transport);
    });
}

QString WebChannel::url() {
    return server->serverUrl().toString();
}

WebChannel* WebChannel::instance()
{
    if (!_instance) {
        _instance = new WebChannel();
    }

    return _instance;
}
