#include <QApplication>
#include "ObjectBrowserModel.h"
#include <QDialog>
#include "ui_test.h"
#include <QTreeView>
#include <QDebug>
#include <QModelIndex>
#ifdef MODELTEST
#include "modeltest.h"
#endif

int main( int argc, char** argv ) {
    QApplication app( argc, argv );

    QDialog* dialog = new QDialog;
    Ui::Test* ui = new Ui::Test;
    ui->setupUi( dialog );
    dialog->show();

    ObjectBrowserModel* model = new ObjectBrowserModel(dialog);
#ifdef MODELTEST
    new ModelTest(model, dialog);
#endif
    QTreeView* view = new QTreeView;
    view->setModel( model );
    view->resize( 400, 600 );
    view->show();
/*
    // First step do you get a real index from your model?
    QModelIndex top1 = model->index( 0,0, QModelIndex() );
    qDebug() << "The first topmost child: " << top1 << top1.isValid();

    QModelIndex top2 = model->index( 1,0, QModelIndex() );
    qDebug() << "The second topmost child: " << top2 << top2.isValid();

    // Does your data function work on toplevel indexes?
    qDebug() << "Class name of the first topmost child (QDialog|QTreeView)" << model->data( top1, Qt::DisplayRole );
    qDebug() << "Class name of the second topmost child (QDialog|QTreeView)" << model->data( top2, Qt::DisplayRole );

    // Does your model return the right thing for non display role roles?
    qDebug() << "Better be a null index:" << model->data( top1, Qt::ForegroundRole );
    qDebug() << "Better be a null index:" << model->data( top2, Qt::ForegroundRole );

    // Now lets see if you also are capable of handing out sub indexes.
    QModelIndex sub1 = model->index( 0,0, top1 );
    qDebug() << "First child of the first top: " << sub1;

    QModelIndex sub2 = model->index( 1,0, top1 );
    qDebug() << "Second child of the first top: " << sub2;

    // Does your data function work for these indexes??
    qDebug() << "Class name of first child"  << model->data( sub1, Qt::DisplayRole );
    qDebug() << "Class name of second child" << model->data( sub2, Qt::DisplayRole );

    // Now lets see if you also implemented the parent function correct.
    qDebug() << "parent of the top index (should be null): " << model->parent(top1);
    qDebug() << "parent of the first child (should be top) " << model->parent(sub1) << " == " << top1;
    qDebug() << "parent of the second child (should be top) " << model->parent(sub2) << " == " << top1;

    // Lets try to dig one level deeper.
    QModelIndex subsub1 = model->index( 0,0, sub1 );
    qDebug() << "Child of child: " << subsub1;
    qDebug() << "class name for subsub child: " << model->data( subsub1, Qt::DisplayRole );
    qDebug() << "parent of subsub child: " << model->parent( subsub1 ) << " == " << sub1;
*/


    return app.exec();
}
