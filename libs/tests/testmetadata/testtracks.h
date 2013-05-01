#ifndef TESTTRACKS_H
#define TESTTRACKS_H

#include <QString>
class MetaDataValue;

QString testTracksDir();
bool equal(const MetaDataValue& left, const MetaDataValue& right);

#endif // TESTTRACKS_H
