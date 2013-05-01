#include <QString>
#include <QMetaObject>
#include <QMetaProperty>
#include <QList>
#include <QDebug>
#include <QStringList>
#include "dataobject.h"

#include "qobjectwriter.h"

QString DataObject::toString() const {
    QObjectWriter w;
    return w.toString(this);
}


DataObject::DataObject (QString name) {
    setObjectName(name);
}


DataObject& DataObject::operator=(const DataObject& other) {
	readFrom(other);
	return (*this);
}

DataObject::~DataObject() {}
DataObject::DataObject(QObject* parent) : QObject(parent) {}

/*
QString DataObject::validInputs(QString propertyName) const {
    return propertyName + " must be " + ConstraintMgr().getConstraint(className(), propertyName)->toString();
}
*/
//start id="setproperty"
bool DataObject::setProperty(const QString& propertyName, const QVariant &value) {
    return QObject::setProperty(propertyName.toAscii(), value);
}
//end
bool DataObject::setProperty(const char* propName, const QVariant& qv) {
    return QObject::setProperty(propName, qv);
}


void DataObject::adoptChildren(QObject* wayward) {
    QObjectList children = wayward->children();
    foreach (QObject* obj, children) {
        obj->setParent(this);
    }
}

bool DataObject::equals(const QObject& left, const QObject& right, 
                        bool checkChildren)  {
    if (&left == &right)
        return true;
    if (left.objectName() != right.objectName()) return false;
    QStringList propnames = propertyNames(&left);
    foreach (const QString& propname, propnames) {
        QVariant qvOther = right.property(propname.toUtf8());
        // if propname is not one of other's properites then
        // property() returns an invalid variant.
        if (! qvOther.isValid())
            return false;
        // Temporary variables for debugging purposes
        if (left.property(propname.toUtf8()) != qvOther) {
            QString thisPropStr = left.property(propname.toUtf8()).toString();
            QString otherPropStr = qvOther.toString();
            qDebug() << QString("Prop: %1 %2 != %3").arg(propname)
                    .arg(left.property(propname.toUtf8()).toString())
                    .arg(qvOther.toString());
            return false;
        }
    }

    if (! checkChildren)
        return true;

    // Equal so far - now see if this and other have children
    // TODO: this should be fixed for QObjects:
    QList<QObject*> leftKids = left.findChildren<QObject*>(QString());
    QList<QObject*> rightKids = right.findChildren<QObject*>(QString());

    //    if (0 == thesekids  && 0 == otherkids)
    //      return true;  // no children
    if (leftKids.count() != rightKids.count())
        return false;    // different numbers of children

    // At this point both have same number of children.
    // Now iterate through them.

    QListIterator<QObject*> lit( leftKids );
    QListIterator<QObject*> rit( rightKids);
    QObject*leftChild;
    QObject*rightChild;
    while (lit.hasNext()) {
        leftChild = lit.next();
        rightChild = rit.next();
        // skip over grandchildren and greatgrandchildren
        if (leftChild->parent() != &left) continue;
        if (!equals(*leftChild,*rightChild, checkChildren))
            return false;
    }
    return true;
}

bool operator==(const QObject& left, const QObject& right) {
    return DataObject::equals(left, right, true);
}

//start id=readwrite
bool DataObject::readFrom(const QObject& source) {
    bool retval = true;
    const QMetaObject* meta = source.metaObject();
    int count = meta->propertyCount();
    for (int i=0; i<count; ++i) {
        QMetaProperty metap = meta->property(i);
        const char* pname = metap.name();
        if (metap.isWritable()) {
            retval = setProperty(pname, source.property(pname))
                     && retval;
        }
    }
    emit dataObjectChanged(objectName());
    return retval;
}


QString DataObject::className() const
{
    QVariant qv = property("className");
    if (!qv.isNull()) {
        return qv.toString();
    }
    return metaObject()->className();
}


//end

QStringList DataObject::propertyNames() const {
    return propertyNames(this);
}

QStringList DataObject::propertyNames(const QObject* that) {
    QStringList retval;
    const QMetaObject* meta = that->metaObject();
    for (int i=0; i<meta->propertyCount(); ++i) {
        retval += meta->property(i).name();
    }
    return retval;
}

uint DataObject::numProperties() const {
    return propertyNames().count();
}

QMetaProperty DataObject::metaProperty(const QString& propname) const {
    const QMetaObject* meta = this->metaObject();
    int i = meta->indexOfProperty(propname.toAscii());
    return meta->property(i);
}

QMetaProperty DataObject::metaProperty(int i) const {
    return metaObject()->property(i);
}
QVariant DataObject::property ( QString name ) const {
    return QObject::property(name.toAscii());
}

QVariant DataObject::property (const char* name ) const {
    return QObject::property(name);
}

DataObject* DataObject::clone( bool deep ) const  {
    DataObject* retval = new DataObject(); /* TODO:
        Rewrite this method to use a template to create
        a new instance of the same type */

    writeTo(*retval);
    if (deep) {
        foreach (DataObject* child, findChildren<DataObject*>()) {
            if (child->parent() == this) {
                DataObject* childClone = child->clone(deep);
                childClone->setParent(retval);
            }
        }
    }
    return retval;
}

//start id=readwrite
bool DataObject::writeTo(QObject& dest) const {
    bool result = true;
    foreach (const QString &propname, propertyNames()) {
        if (metaProperty(propname).isWritable()) {
            QVariant val = property(propname);
            result = dest.setProperty(propname.toAscii(), val) && result;
        }
    }
    return result;
}
//end
