#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include "dobjs_export.h"
//start
#include <QObject>
#include <QVariant>
#include <QMetaProperty>

/** @short Common base class for some cloneable reflectable data structures.
    Provides some convenience methods for accesing metadata, used
	by other classes such as the DataObjectTableModel.

	It is by no means necessary to derive from this class for your own
    code - QObject might be sufficient.
    
    DataObject dates back to the Qt3 days when the QObject class had
    fewer features.
*/
//end

class DOBJS_EXPORT DataObject : public QObject {
	Q_OBJECT

public:
	//start
public:
	Q_INVOKABLE explicit DataObject(QString name);
	Q_INVOKABLE explicit DataObject(QObject* parent=0);
	virtual ~DataObject();
	virtual bool readFrom(const QObject& source);

	/**
	 writes all our properties into a QObject
	 @return true if successful in setting all properties.
	 */
	virtual bool writeTo(QObject& dest) const;

	/**
	 iterates through the wayward and steals all its children,
	 reparenting them under "this"
	 @param wayward - another QObject which has children we wish to add
		  to this. The wayward loses children.
	 */
	void adoptChildren(QObject* wayward);

	/**
	  @param compareChildren if true recursively checks children
	  @return true if other has the same property values
	  as this.
	  */
	static bool equals(const QObject& left, const QObject& right, bool compareChildren=true) ;



	DataObject& operator=(const DataObject& other);


	/**
	 We can't virtually override QObject::className(), but we override
	 it anyway. In DataObject, it is virtual, so it can return something
	 else in derived classes.

	 @return the name of this object's class
	 */
	virtual QString className() const;


	/**
	 @return a list of propertyNames, so that the user of DataObject does not need to
	 use a @ref QMetaObject just to get a list of property names.
	*/
	virtual QStringList propertyNames() const;
	static QStringList propertyNames(const QObject*);

	/* public convenience functions that return the QMetaProperty for a given
		propertyname (or index)..
	*/
	virtual QMetaProperty metaProperty(const QString& propname) const;
	virtual QMetaProperty metaProperty(int i) const;

	/**
	@return number of properties.
	 @param superclass include superclass inherited properties in the count
	 (currently ignored)
	*/
	virtual uint numProperties() const;

	/**
	@return human and machine readable representation of this object (XML format)
	*/
	virtual QString toString() const;

	/** overloaded to support QString */
	virtual QVariant property( QString name ) const;
	virtual QVariant property( const char* name) const;
	/**
	  Polymorphic clone() method - its proper behavior is
	  to copy all properties from *this into the new copy.
	  @return a newly allocated copy of *this

	  Should be overridden in derived classes.

	  @param deep if true, makes clones of all the children
			 and reconstructs the tree.
	  */
	virtual DataObject* clone(bool deep=false) const;
signals:
	/** Emitted to interested models that use it
		(in particular, the DataObjectTableModel)
		*/
	void dataObjectChanged(const QString& name);
public slots:

	/**
	 * overloaded for QString
	  @param propertyName name of property to set
	  @param value value to set property
	  @return true if value satisfies the regexp constraint for
	  this property.

	  NOTE: Qt3's QObject had these as virtual, but in Qt4, they are non-virtual.
	  This means these methods will not be called if you use the QObject
	  interface. */
	virtual bool setProperty(const QString &propName, const QVariant &qv);
	virtual bool setProperty(const char* propName, const QVariant& qv);

};
//end
DOBJS_EXPORT bool operator==(const QObject& left, const QObject& right) ;


#endif        //  #ifndef DATAOBJECT_H
