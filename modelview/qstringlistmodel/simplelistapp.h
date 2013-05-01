#ifndef SIMPLELIST_H
#define SIMPLELIST_H

#include <QApplication>
#include <QListView>
#include <QStringListModel>
#include <QMainWindow>
#include <QPushButton>
/* Controller example */

class SimpleListApp : public QApplication {
    Q_OBJECT
    public:
    SimpleListApp(int argc, char* argv[]); 
  public slots:
    void showNewChanges();
    void addItem();
  private:
    QStringListModel m_Model;     /* created first */
    QMainWindow m_Window;
    QListView m_View;             
    QPushButton m_Button;        /* destroyed first */
};

#endif

