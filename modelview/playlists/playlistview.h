#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#include <QTableView>

/** A view for a list of tracks to play, implemented as a table model.
    Promoted from QTableView in MainWindow.ui
*/
class PlayListView : public QTableView {
    Q_OBJECT
public:
    explicit PlayListView(QWidget* parent=0);
    virtual void dropEvent(QDropEvent* event);
    virtual void startDrag(Qt::DropActions supportedActions);

};


#endif        //  #ifndef PLAYLISTVIEW_H

