#ifndef NODEJSEVALUATOR_H
#define NODEJSEVALUATOR_H

#include <QObject>
#include <QVariant>

class NodeJSEvaluator: public QObject
{
    Q_OBJECT

public:
    NodeJSEvaluator();

public slots:
    QVariant eval(QString str);

    void sendJavaScriptToBrowser(QString str);

signals:
    void evaluateJavaScript(QString str);
};

#endif

