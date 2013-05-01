#include <QIcon>

#include "sourcelistmodel.h"
#include "metadatafactory.h"
#include "modeltest.h"

SourceListModel::SourceListModel(QObject* parent)
    : QAbstractListModel(parent)
{
    populateSamples();

}

int SourceListModel::rowCount(const QModelIndex &) const {
    return m_playlists.size();

}

QVariant SourceListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_playlists.size()) return QVariant();
    if (role == Qt::DisplayRole) {
        return m_playlists[index.row()]->objectName();
    }
    if (role == Qt::ToolTipRole) {
        int numTracks = m_playlists[index.row()]->rowCount();
        return tr("%1 tracks").arg(numTracks);
    }
    if (role == Qt::DecorationRole) {
        return QIcon(":/icons/playlist.png");
    }
    return QVariant();
}


MetaDataTableModel* SourceListModel::playList(int row) const {
    if (row >= m_playlists.size()) return 0;
    return m_playlists[row];
}



SourceListModel::~SourceListModel() {
    qDeleteAll(m_playlists);
}

MetaDataTableModel* SourceListModel::randomModel(int pid) {
    QList< QSharedPointer <MetaData> > songs;
    MetaDataTableModel* retval=0;
    MetaDataFactory mdf;
    int size = qrand() % 20 + 10;
    for (int i=0; i<size; ++i) {
        songs << mdf.randomSong(pid);
    }
    retval = new MetaDataTableModel(songs, this);
    return retval;
}

//start id="modeltest"
void SourceListModel::populateSamples() {
    for (int i=0; i<5; ++i) {
        QString name = QString("TestPlayList%1").arg(i);
        MetaDataTableModel *model = randomModel(i);
        new ModelTest(model, this);
        model->setObjectName(name);
        m_playlists << model;
    }
}
//end



bool SourceListModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int, const QModelIndex & ) {
    MetaDataTableModel* tableModel = m_playlists[row];
    return tableModel->dropMimeData(data, action, -1, 0, QModelIndex());
}


Qt::DropActions SourceListModel::supportedDropActions() const {
    return Qt::CopyAction ;
}
