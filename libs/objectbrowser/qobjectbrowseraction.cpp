
#include "qobjectbrowseraction.h"

QObjectBrowserAction::QObjectBrowserAction(QObject* parent)
        : QAction(tr("Object Browser"), parent), 
        m_browser(0) {
        setObjectName(tr("ObjectBrowserAction"));
        setCheckable(true);
        connect (this, SIGNAL(triggered(bool)), this, SLOT(setChecked(bool)));
        if (parent == 0)
            connect (qApp, SIGNAL(aboutToQuit()), this, SLOT(deleteLater()));
    }

    bool QObjectBrowserAction::isChecked() const {
        if (m_browser.isNull()) return false;
        return m_browser->isVisible();
    }

    void QObjectBrowserAction::setChecked(bool checked) {
        QAction::setChecked(checked);
        if (checked && m_browser.isNull()) {
            m_browser.reset(new QObjectBrowser);
            connect (m_browser.data(), SIGNAL(hidden()),
                     this, SLOT(checkCheck()));
        }
        m_browser->setVisible(checked);
    }

    void QObjectBrowserAction::checkCheck() {
        setChecked(false);
    }
