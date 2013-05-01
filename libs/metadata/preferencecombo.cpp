#include "preferencecombo.h"
#include <preference.h>

PreferenceCombo::PreferenceCombo(QWidget* parent)
: QComboBox(parent) {
    setObjectName("preferenceCombo");
    static Preference prefs;
    foreach (const QString &str , prefs.names()) {
        Preference pref(str);
//        QVariant v;
//        v.setValue(pref.intValue());
        addItem(str, QVariant(pref.intValue()));
    }
}

