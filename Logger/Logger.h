#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>

#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <QDir>
#include <QLockFile>
#include <QTextStream>

class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QObject *parent = nullptr);

public:
    static bool logging;
    static QString logFileName;
    static void attach();
    static void handler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

signals:
};

#endif // LOGGER_H
