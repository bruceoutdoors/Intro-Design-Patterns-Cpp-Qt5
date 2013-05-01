#ifndef DATAOBJECTTABLEMODEL_H
#define DATAOBJECTTABLEMODEL_H

#include <QSharedPointer>
#include <QAbstractTableModel>
#include <QVariant>
#include <QModelIndex>
#include <QStringList>
#include <QTimer>
using namespace Qt;

#include "dataobject.h"

/**  @short An example TableModel for a QList<QSharedPointer<DataObject> >
     This class uses the metaproperties API to extract the header information
     to display in the table, and contains a QList<DataObject*> for row
     data.
*/
//start id=dotm
class DOBJS_EXPORT DataObjectTableModel : public QAbstractTableModel {
    Q_OBJECT
  public:
    /**
      @param headerModel - an example DataObject-derived class with
       properties defined, used to determine the name/type of
       the column headers.
       @see extractHeaders()
    */
    explicit DataObjectTableModel(DataObject* headerModel = 0, 
                                  QObject* parent=0);

    /** Inserts a new record into the table
       @param newRecord - a DataObject to be interpreted as
       a row.
       @param position - the row number it should be inserted
       at. If -1, it is appended to the end.
      */
    virtual bool insertRecord(QSharedPointer<DataObject> newRecord,
                              int position = -1,
                              const QModelIndex& = QModelIndex());

                              /**
       @return each DataObject as a toString()
    */
    QStringList toStringList() const;

    QString toString() const;

    virtual int fieldIndex(const QString& fieldName) const;

    /** Deletes all of the contained DataObjects which
       were added to this model. */
    virtual ~DataObjectTableModel();
//end
//start id=abstract
    /* Methods which are required to be overridden
       because of QAbstractTableModel */
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;

    /** @return data at this index.
        @param index location of data
        @param role if Qt::UserRole, then return the objectName
                of the DataObject at index.row()
    */
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section,
                        Qt::Orientation orientation = Qt::Horizontal,
                        int role = DisplayRole) const;
    ItemFlags flags(const QModelIndex& index) const;
    bool setData(const QModelIndex& index, const QVariant& value,
                 int role = EditRole);
    bool insertRows(int position, int rows,
                    const QModelIndex& index = QModelIndex());
    bool removeRows(int position, int rows,
                    const QModelIndex& index = QModelIndex());
//end
    virtual int findRow(const QString& name);
//start id=dotm
  public slots:
    void clear();
    /** Mark the corresponding row for this dataobject changed */
    void rowChanged(const QString& fileName);

  protected:
    QList<QSharedPointer<DataObject> > m_Data;
    QList<bool> m_isEditable;
    QStringList m_Headers;
    DataObject* m_Original;
    /** sets the headerModel based on property names/types. 
        TODO: Use setRoleNames(roles), a feature added to Qt 4.6,
        so it works from QML views also. 
    */
    void extractHeaders(DataObject* hmodel);
  public:

    /** A convenience function for insertRecord
    */
    DataObjectTableModel& operator<<(QSharedPointer<DataObject> newObj) {
        insertRecord(newObj);
        return *this;
    }
};
//end
#endif

