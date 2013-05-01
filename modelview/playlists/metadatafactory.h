#ifndef METADATAFACTORY_H
#define METADATAFACTORY_H

#include <QSharedPointer>

class MetaData;

class MetaDataFactory
{
public:
    MetaDataFactory();
    QSharedPointer<MetaData> randomSong(int playlist) const;
};

#endif // METADATAFACTORY_H

