#ifndef WEBCHANNEL_H
#define WEBCHANNEL_H

#include <QString>

class QWebChannel;
class QWebSocketServer;
class NodeJSEvaluator;

class WebChannel
{
public:
    QString url();

    inline NodeJSEvaluator* nodeJSEvaluator() { return evaluator; }

    static WebChannel* instance();

private:
    WebChannel();

    QWebSocketServer *server;
    NodeJSEvaluator *evaluator;
};

#endif

