#include <QtGui>
//start id=main
#include "createModel.h"

int main( int argc, char** argv ) {
  QApplication app( argc, argv );
  QStandardItemModel* model = createModel(&app);
  QSplitter vsplitter(Qt::Vertical);
  QSplitter hsplitter;                    /* By default, children layout horizontally. */
  
  QListView list;
  QTableView table;
  QTreeView tree;
  QColumnView columnView;
  //end
  list.setToolTip ("QListView");
  table.setToolTip("QTableView");
  tree.setToolTip("QTreeView");
  columnView.setToolTip("QColumnView");
  //start id=main
  list.setModel( model );
  table.setModel( model );
  tree.setModel( model );	                           /* Share the same model. */
  columnView.setModel (model);
  //end
  table.setColumnWidth(0, 200);                      /* Widen first column of table. */
  table.setColumnWidth(1, 150);
  tree.header()->resizeSection(0, 200);
  tree.header()->resizeSection(1, 150);              /* Widen the second column of the table. */
  //start id=main
  list.setSelectionModel( tree.selectionModel() );
  table.setSelectionModel( tree.selectionModel() );  /* Common selection model. */
  columnView.setSelectionModel (tree.selectionModel());
  table.setSelectionBehavior( QAbstractItemView::SelectRows );
  table.setSelectionMode( QAbstractItemView::SingleSelection );
  //end
  //start id=splitter
  hsplitter.addWidget( &list );
  hsplitter.addWidget( &table );
  vsplitter.addWidget( &hsplitter );
  vsplitter.addWidget ( &tree );
  vsplitter.addWidget ( &columnView );

  vsplitter.setGeometry(300, 300, 500, 500);
  vsplitter.setWindowTitle("Multiple Views - Editable Model");
  //end
  QObjectList kids = vsplitter.children();           /* QSplitter is a QWidget. */
  foreach(QObject* optr, kids) {                     /* Added widgets are children. */
     qDebug() << optr->metaObject()->className();
  }
  vsplitter.show();


  return app.exec();
}

