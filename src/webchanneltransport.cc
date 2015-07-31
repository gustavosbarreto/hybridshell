#include "webchanneltransport.h"

#include <QJsonDocument>
#include <QWebSocket>

WebChannelTransport::WebChannelTransport(QWebSocket *s)
{
    socket = s;

    connect(socket, &QWebSocket::textMessageReceived, [=](const QString &message) {
        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8(), &error);

        if (error.error || !doc.isObject()) {
            return;
        }

        emit messageReceived(doc.object(), this);
    });
}

void WebChannelTransport::sendMessage(const QJsonObject &message)
{
    QJsonDocument doc(message);
    socket->sendTextMessage(QString::fromUtf8(doc.toJson(QJsonDocument::Compact)));
}
