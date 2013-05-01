#include "simplelistapp.h"
#include <QDebug>
#include <QVBoxLayout>

SimpleListApp::SimpleListApp(int argc, char* argv[]) :
    QApplication(argc, argv), m_Button("Insert") {
    QString englishDays = "Monday,Tuesday,Wednesday,Thursday,Friday,"
                   "Saturday,Sunday";
    QString frenchDays = "Lundi,Mardi,Mercredi,Jeudi,Vendredi"
                         ",Samedi,Dimanche";
    QString dutchDays = "Mandaag,Dinsdag,Wowoensdag,Dunderdag,"
                        "Vrijdag,Zaterdag,Zonedag";
    QStringList days = dutchDays.split(",");                         
    m_Model.setStringList(days);
    m_View.setModel(&m_Model);
    connect(this, SIGNAL(aboutToQuit()), 
            this, SLOT(showNewChanges()));
    QWidget* wid = new QWidget(&m_Window);
    QVBoxLayout* layout = new QVBoxLayout(wid);
    m_Window.setCentralWidget(wid);
    layout->addWidget(&m_View);
    layout->addWidget(&m_Button);
    connect (&m_Button, SIGNAL(clicked()),
             this, SLOT(addItem()));
    m_Window.setVisible(true);
}

void SimpleListApp::addItem() {
    static int itemnumber = 1;
    QString str = QString("item #%1").arg(itemnumber++);
    QStringList sl = m_Model.stringList();
    sl << str;
    m_Model.setStringList(sl);
}

void SimpleListApp::showNewChanges() {
    qDebug() << " The new days of the week: ";
    qDebug() << m_Model.stringList().join(",");
}

int main(int argc, char* argv[]) {
    SimpleListApp app(argc, argv);
    return app.exec();
}

