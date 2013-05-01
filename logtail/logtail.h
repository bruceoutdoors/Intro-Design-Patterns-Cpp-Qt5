#ifndef LogTail_H
#define LogTail_H

//start
#include <QObject>
#include <QProcess>

/**
    A simple example using QProcess and tail -f as an
    external command. 
    Executes a process and connects its output signals to a Logger.
    */
class LogTail : public QProcess {
    Q_OBJECT
  public:
    LogTail(QString fn = QString());
    ~LogTail();
  signals:
    void logString(const QString &str);
    
  public slots:
    void logOutput();
};
//end

#endif

