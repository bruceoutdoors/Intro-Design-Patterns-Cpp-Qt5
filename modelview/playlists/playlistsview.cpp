#include <QtGui>
#include "playlistview.h"
#include "playlistsview.h"

void PlaylistsView::dragEnterEvent(QDragEnterEvent* event) {
    if (event->source() == this) {
        qDebug() << "Dropped on drag source.";
        return;
    }
    if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
        qDebug() << "DragEnter acceptProposed";
    }
    else {
        qDebug() << "dragEnter notAccepted";
    }
}

void PlaylistsView::dragMoveEvent(QDragMoveEvent* event) {
    static QModelIndex oldIdx;
    static QModelIndex idx;
    PlayListView* source =
            qobject_cast<PlayListView*>(event->source());
    if (source == 0) return;
    QPoint point = event->pos();
    idx = indexAt(point);
    if (idx.isValid()) {
        event->setDropAction(Qt::CopyAction);
        selectionModel()->setCurrentIndex(idx, QItemSelectionModel::SelectCurrent);
        event->accept();
    }
}

void PlaylistsView::dropEvent(QDropEvent* event) {
    QPoint point = event->pos();
    QModelIndex idx = indexAt(point);
    if (!idx.isValid()) {
        qDebug() << "invalid index";
        return;
    }
    event->accept();
}

