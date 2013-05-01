#include <QApplication>
#include <QTreeView>
#include <QSplitter>
#include <QTextStream>
#include <cstdio>
#include "slacker.h"
#include "xmltreemodel.h"
#include <QApplication>
QTextStream cout(stdout);

QWidget* twinview(QDomNode before, QDomNode after) {

    QSplitter* hbox = new QSplitter();

    XmlTreeModel* dtm1 = new XmlTreeModel(hbox);
    XmlTreeModel* dtm2 = new XmlTreeModel(hbox);
    dtm1->setContent(before);
    dtm2->setContent(after);
    QTreeView* tv1 = new QTreeView(hbox);
    tv1->setWhatsThis("Before");
    tv1->setModel(dtm1);
    QTreeView* tv2 = new QTreeView(hbox);
    tv2->setModel(dtm2);
    tv2->setWhatsThis("After");
    return hbox;
}

//start
int main(int argc, char **argv) {
    QApplication app(argc, argv);
    QString filename;
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " filename.xml" << endl;
        filename = "samplefile.xml";
    }
    else {
        filename = argv[1];
    }
    QFile f(filename);
    QString errorMsg;
    int errorLine, errorColumn;
    QDomDocument doc("SlackerDoc");
    bool result = doc.setContent(&f, &errorMsg, 
         &errorLine, &errorColumn);             /* Parse the file into a
         DOM tree, and store tree in empty doc. */
    QDomNode before = doc.cloneNode(true);      /* Deep copy. */
    Slacker slack(doc);                         /* Send the tree to slack. */
    QDomNode after = slack.transform();         /* Start the visitation. */
    cout << QString("Before: ") << before << endl;
    cout << QString("After: ") << after << endl;
    QWidget * view = twinview(before, after);   /* Create a pair of QTreeView 
        objects separated by slider, using the QDomDocuments as models. */
    view->show();
    app.exec();
    delete view;
}
//end

