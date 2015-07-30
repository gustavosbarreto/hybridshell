#include "webchannel.h"
#include "webchanneltransport.h"
#include "nodejsevaluator.h"

#include <QWebSocketServer>
#include <QWebChannel>
#include <QUrl>

WebChannel::WebChannel()
{
    server = new QWebSocketServer("test", QWebSocketServer::NonSecureMode);
    server->listen(QHostAddress::LocalHost);

    QWebChannel *channel = new QWebChannel();

    channel->registerObject("QtNode", new QObject);
    channel->registerObject("NodeJSEvaluator", new NodeJSEvaluator);

    QObject::connect(server, &QWebSocketServer::newConnection, [=]() {
        WebChannelTransport *transport = new WebChannelTransport(server->nextPendingConnection());
        channel->connectTo(transport);
    });
}

QString WebChannel::url() {
    return server->serverUrl().toString();
}
