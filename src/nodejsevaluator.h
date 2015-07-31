#ifndef NODEJSEVALUATOR_H
#define NODEJSEVALUATOR_H

#include <QObject>
#include <QVariant>
#include <QUuid>

class NodeJSEvaluator: public QObject
{
    Q_OBJECT

public:
    NodeJSEvaluator();

public slots:
    QVariant eval(QString str);

    void sendJavaScriptToBrowser(const QUuid &uuid, QString str);

signals:
    void evaluateJavaScript(QString uuid, QString str);
};

#endif

