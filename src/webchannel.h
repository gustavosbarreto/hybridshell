#ifndef WEBCHANNEL_H
#define WEBCHANNEL_H

#include <QString>

class QWebSocketServer;

class WebChannel
{
public:
    WebChannel();

    QString url();

private:
    QWebSocketServer *server;
};

#endif

