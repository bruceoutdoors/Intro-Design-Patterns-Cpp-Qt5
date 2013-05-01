#include <QtGui>
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QFileSystemModel model;                
    model.setRootPath("/");           
    QTreeView tree;
    tree.setModel(&model);                 
    tree.setSortingEnabled(true);    /* Enable HeaderView sort buttons. */
    tree.header()->setResizeMode(QHeaderView::ResizeToContents);
    tree.resize(640, 480);
    tree.show();   
    return app.exec();
}
