#ifndef PLAYLISTSVIEW_H
#define PLAYLISTSVIEW_H

#include <QListView>


/** A view for a list of playlists
    (in this case, the SourceListModel)
    Promoted from QListView in mainwindow.ui
*/
class PlaylistsView : public QListView {
public:
    PlaylistsView(QWidget* parent=0) : QListView(parent) {
        /* Initialized from MainWindow.ui as promoted widget. */
    }
    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent* event);
    void dragMoveEvent(QDragMoveEvent* event);
};

#endif // PLAYLISTSVIEW_H

