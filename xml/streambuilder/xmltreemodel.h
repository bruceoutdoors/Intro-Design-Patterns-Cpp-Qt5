#ifndef XMLTREEMODEL_H
#define XMLTREEMODEL_H

#include <QStandardItemModel>
#include <QXmlStreamReader>
#include <QFile>
//start
/** An example tree builder that uses QXmlStreamReader
 */
class XmlTreeModel : public QStandardItemModel {
    Q_OBJECT
public:
    enum Roles {LineStartRole = Qt::UserRole + 1,
                LineEndRole};    /* Custom roles for data() */
    explicit XmlTreeModel(QObject *parent = 0);
public slots:
    void open(QString fileName);
private:
    QXmlStreamReader m_streamReader;
    QStandardItem* m_currentItem;
};
//end
#endif // XMLTREEMODEL_H
