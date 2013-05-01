#include <QtCore>
#include <dynoprops.h>
//start id=inventory
QString DynoProps::propsInventory() {
   static const QMetaObject* meta = metaObject();
   QStringList res;
   res << "Fixed Properties:";
   QString propData;
   for(int i = 0; i < meta->propertyCount(); ++i) {
      res << QString("%1\t%2").arg(QString(meta->property(i).name()))
              .arg(meta->property(i).read(this).toString());  /* We could also use property(propName) here. */
   }
   res << "Dynamic Properties:";  
   foreach(QByteArray dpname, dynamicPropertyNames()) {
      res << QString("%1\t%2").arg(QString(dpname))
              .arg(property(dpname).toString());
   }
   return res.join("\n");
}
 
//end
//start id=serial
/** This is a simplified example that assumes our class is not
 derived from another class with Properties. 
 If it were, we would use QMetaObject::propertyOffset()
 instead of 0 to begin our loop and make use of base class
 stream operators. */
 QDataStream& operator<< (QDataStream& os, const DynoProps& dp) {
   static const QMetaObject* meta = dp.metaObject();
   for(int i = 0; i < meta->propertyCount(); ++i) {
        const char* name = meta->property(i).name();
        os << QString::fromLocal8Bit(name)              /* To serialize a char* as a QString */
           << dp.property(name);
   }
   qint32 N(dp.dynamicPropertyNames().count());         /* To serialize an int */
   os << N;
   foreach(QByteArray propname, dp.dynamicPropertyNames()) {
      os << QString::fromLocal8Bit(propname) << dp.property(propname);
   }
   return os;
 }
 
 QDataStream& operator>> (QDataStream& is, DynoProps& dp) {
   static const QMetaObject* meta = dp.metaObject();
   QString propname;
   QVariant propqv;
   int propcount(meta->propertyCount());
   for(int i = 0; i < propcount; ++i) {
      is >> propname;
      is >> propqv;
      dp.setProperty(propname.toLocal8Bit(), propqv);   /* De-serialize char* using reverse QString conversion */
   }
   qint32 dpcount;
   is >> dpcount;
   for(int i = 0; i < dpcount; ++i) {
      is >> propname;
      is >> propqv;
      dp.setProperty(propname.toLocal8Bit(), propqv);
   }
   return is;
 }
//end
