#ifndef QOBJECTBROWSERACTION_H
#define QOBJECTBROWSERACTION_H

#include "qobjectbrowser.h"
#include <QAction>
#include <QScopedPointer>

/** Toggle an initially invisible QObjectBrowser window. 
    Usage: Create and add an instance to your own tools/view/context menu.
*/
class OBJECTBROWSER_EXPORT QObjectBrowserAction : public QAction {
    Q_OBJECT
public:
    /** @param parent - the parent object (responsible for destruction of
        this instance and the toggled widget as well) */
    QObjectBrowserAction(QObject* parent=0);
    bool isChecked() const;
public slots:
    void setChecked(bool);
    void checkCheck();
private:
    QScopedPointer<QObjectBrowser> m_browser; /* A "managed" object
        that does not treat this as a parent. In a parent-like way,
        When this is deleted, the browser is also. */
};

#endif        //  #ifndef QOBJECTBROWSERACTION_H
