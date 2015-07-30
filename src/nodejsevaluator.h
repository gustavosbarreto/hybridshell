#ifndef NODEJSEVALUATOR_H
#define NODEJSEVALUATOR_H

#include <QObject>

class NodeJSEvaluator: public QObject
{
    Q_OBJECT

public:
    NodeJSEvaluator();

public slots:
    QString eval(QString str);
};

#endif

