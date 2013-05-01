#ifndef QONSOLE_H
#define QONSOLE_H

 

#include <QMainWindow>
class QLineEdit;
class QProcess;
class QTextEdit;
/**
  A simple demo application that shows how to use QProcess,
  with signals/slots providing bidirectional communication.
  */
//start
class Qonsole : public QMainWindow {
    Q_OBJECT
 public:
    Qonsole();
 public slots:
    void execute();
    void showOutput();
 private:
    QTextEdit* m_Logw;
    QLineEdit* m_InputArea;
    QProcess* m_Shell;
};
//end
#endif

