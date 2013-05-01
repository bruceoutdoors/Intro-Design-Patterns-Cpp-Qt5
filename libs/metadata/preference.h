#ifndef _PREFERENCE_H
#define _PREFERENCE_H
#include <QVariant>
#include <QMetaType>
#include "enum.h"
#include "metadataexport.h"

/** A Preference Enum class, that defines
    preferences for mp3 tracks similar to what is in musicmatch */

class METADATAEXPORT Preference: public Enum {
 public:

    /** @param value - from 0 to 10 */
    Preference(int value=0);
    Preference(QString prefstr);

 protected:
    const NameMap& nameMap() const;
};
Q_DECLARE_METATYPE(Preference)
#endif

