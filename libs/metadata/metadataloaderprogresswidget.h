#ifndef METADATALOADERPROGRESSWIDGET_H
#define METADATALOADERPROGRESSWIDGET_H

#include "metadataexport.h"
#include <QWidget>
#include <metadatavalue.h>

class QToolButton;
class QProgressBar;
namespace Abstract {
    class MetaDataLoader;
}

/** A cancel button and progress widget hooked up to a MetaDataLoader.
        TODO: use Abstract interface and move to MetaData library.
*/

class METADATAEXPORT MetaDataLoaderProgressWidget : public QWidget
{
    Q_OBJECT
public:
    /** @param loader if 0, will use the Abstract::MetaDataLoader::instance() */
    
    explicit MetaDataLoaderProgressWidget(Abstract::MetaDataLoader* loader = 0, 
                                         QWidget* parent = 0);
    
    /** Hookup another MetaDataLoader to the same widgets */
    void hookup (Abstract::MetaDataLoader* mdl);
    QProgressBar* progressBar() {return m_progressBar;}
    QToolButton* cancelButton() {return m_cancelButton;}
signals:

public slots:
    void updateStatus(const MetaDataValue& mdv);
    void updateRange(int min, int max) ;
private:
    MetaDataValue lastValue;
    QProgressBar* m_progressBar;
    QToolButton* m_cancelButton;
};

#endif // METADATALOADERPROGRESSWIDGET_H
