#ifndef _WEBSOCKETTRANSPORT_H
#define _WEBSOCKETTRANSPORT_H

#include <QWebChannelAbstractTransport>
#include <QJsonObject>

class QWebSocket;

class WebChannelTransport: public QWebChannelAbstractTransport
{
public:
    WebChannelTransport(QWebSocket *s);

    void sendMessage(const QJsonObject &message);

private:
    QWebSocket *socket;
};

#endif
