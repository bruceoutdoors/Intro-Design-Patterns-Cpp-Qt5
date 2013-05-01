#include "qonsole.h"
#include <QDockWidget>
#include <QLineEdit>
#include <QProcess>
#include <QByteArray>
#include <QEvent>
#include <QDebug>
#include <QKeyEvent>
#include <QTextCursor>


//start id="constructor"
Qonsole::Qonsole() {
   m_Logw = new QTextEdit;
   setCentralWidget(m_Logw); 
   m_Logw->installEventFilter(this);                /* Intercept events going to the QTextEdit. */
   m_Logw->setLineWrapMode(QTextEdit::WidgetWidth);
   m_Shell = new QProcess();
   m_Shell->setReadChannelMode(QProcess::MergedChannels);
   connect (m_Shell, SIGNAL(readyReadStandardOutput()),
             this, SLOT(showOutput()));
#ifdef Q_WS_WIN
   m_Shell->start("cmd", QStringList(), QIODevice::ReadWrite);
#else
   m_Shell->start("bash", QStringList("-i"), QIODevice::ReadWrite);
#endif   
}
//end

//start id="event"
bool Qonsole::eventFilter(QObject* o, QEvent* e) {
    if (e->type() == QEvent::KeyPress) {
        QKeyEvent* k = static_cast<QKeyEvent*> (e); 
        int key = k->key();
        QString str = k->text();
        m_UserInput.append(str);
        updateCursor();
        if ((key == Qt::Key_Return) || (key == Qt::Key_Enter) ) {
#ifdef Q_WS_WIN                                     /* Windows processes need a Carriage Return + Line Feed, not just a CR. */
            m_UserInput.append(QChar(0x000A));
#endif
            execute();
            return true;                            /* We processed the event. This
            prevents other widgets from seeing it. */           
        }
        else {
            m_Logw->insertPlainText(str);
            return true;
        }
    }
    return false;                                   /* Don't touch the event. */
}
//end    

void Qonsole::showOutput() {
    QByteArray bytes = m_Shell->readAllStandardOutput();
    m_Logw->append(QString(bytes));
}
//start id="update-execute"
void Qonsole::updateCursor() {
    QTextCursor cur = m_Logw->textCursor();
    cur.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
    m_Logw->setTextCursor(cur);
}

void Qonsole::execute() {
    QByteArray bytes = m_UserInput.toUtf8();
    m_Shell->write(bytes);
    m_UserInput = "";    
}
//end
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("QonsoleKeyEvents");
    app.setOrganizationName("objectlearning.net");
    Qonsole qon;
    qon.show();
    return app.exec();
}

