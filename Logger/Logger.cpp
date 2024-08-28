#include "Logger.h"

QString Logger::logFileName = QDir::currentPath() + QDir::separator() + "log.txt";
bool Logger::logging = false;
static const QtMessageHandler QT_DEFAULT_MESSAGE_HANDLER = qInstallMessageHandler(nullptr);

Logger::Logger(QObject *parent)
    : QObject{parent}
{
}

void Logger::attach()
{
    Logger::logging = true;
    qInstallMessageHandler(Logger::handler);
}

void Logger::handler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    if (Logger::logging)
    {
        QString txt;

        switch (type)
        {
            case QtInfoMsg:
            {
                txt = QString("Info : %1").arg(msg);
                break;
            }

            case QtDebugMsg:
            {
                txt = QString("Debug : %1").arg(msg);
                break;
            }

            case QtWarningMsg:
            {
                txt = QString("Warning : %1").arg(msg);
                break;
            }

            case QtCriticalMsg:
            {
                txt = QString("Critical : %1").arg(msg);
                break;
            }

            case QtFatalMsg:
            {
                txt = QString("Fatal : %1").arg(msg);
                break;
            }
        }

        QFile file(Logger::logFileName);
        QLockFile locked(file.fileName() + "l");
        locked.setStaleLockTime(4000);

        if (locked.tryLock())
        {
            if (file.open(QIODevice::Append))
            {
                QTextStream textStream(&file);
                textStream  << "[*] <" << QDateTime::currentDateTime().toString()
                            << ">,<" << txt << ">,<file : " << context.file << ">,<line :" << context.line << ">\r\n";
                textStream.flush();
                file.close();
            }

            locked.unlock();
        }
        else
        {
            qInfo() << "could not lock the file !";
            qint64 pid;
            QString host;
            QString application;

            if (locked.getLockInfo(&pid, &host, &application))
            {
                qInfo() << "The file is locked by :: ";
                qInfo() << "PID :: " << pid;
                qInfo() << "Host :: " << host;
                qInfo() << "Application :: " << application;
            }
            else
            {
                qInfo() << "File is locked, but we can't get the info!";
            }
        }

        (*QT_DEFAULT_MESSAGE_HANDLER)(type, context, msg);
    }
}
