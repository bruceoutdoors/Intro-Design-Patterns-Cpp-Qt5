#include <QDataWidgetMapper>
#include <QDialogButtonBox>
#include "metadataobject.h"
#include "metadatawidget.h"
#include "preference.h"


QTextStream cout(stdout);

MetaDataWidget::MetaDataWidget(QWidget* parent) : QWidget(parent) {
    Preference pref;

    setupUi(this);
    m_model = new MetaDataObject(this);

    connect(buttonBox, SIGNAL(clicked ( QAbstractButton *  )),
        this, SLOT(processButton( QAbstractButton *  )));

    // Type-specific customizations here
    preferenceCombo->addItems(pref.names());
    QStringList props = m_model->propertyNames();

    // We are not using this yet...
    m_Mapper = new QDataWidgetMapper(this);

    m_Mapper->addMapping(genreLineEdit, props.indexOf("Genre") );
    m_Mapper->addMapping(commentLineEdit, props.indexOf("Comment"));
    m_Mapper->addMapping(titleLineEdit, props.indexOf("TrackTitle"));
    m_Mapper->addMapping(albumLineEdit, props.indexOf("AlbumTitle"));
    m_Mapper->addMapping(trackSpinBox, props.indexOf("TrackNumber"));
    m_Mapper->addMapping(preferenceCombo, props.indexOf("Preference"));
    m_Mapper->addMapping(artistLineEdit, props.indexOf("Artist"));
    m_Mapper->addMapping(timeDisplay, props.indexOf("TrackTime"));

    // connect(previousButton, SIGNAL(clicked()), m_Mapper, SLOT(toPrevious()));
    // connect(nextButton, SIGNAL(clicked()), m_Mapper, SLOT(toNext()));
    // connect(spinBox, SIGNAL(valueChanged(int)), m_Mapper, SLOT(setCurrentIndex(int)));
    // connect(m_Mapper, SIGNAL(currentIndexChanged(int)), spinBox, SLOT(setValue(int)));

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(submit()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(revert()));

}


MetaDataObject* MetaDataWidget::model() const {
    return m_model;
}

void MetaDataWidget::display(const MetaDataValue &mdv) {
    *m_model = mdv;
    revert();


}

void MetaDataWidget::processButton ( QAbstractButton * button ) {
	QDialogButtonBox::ButtonRole role = buttonBox->buttonRole(button);
	cout << role << endl;
}

void MetaDataWidget::clear() {
/*	int rows = m_Model->rowCount();
	m_Model->removeRows(0, rows); */
}

void MetaDataWidget::revert() {
	m_Mapper->revert();
    artistLineEdit->setText(m_model->artist());
    commentLineEdit->setText(m_model->comment());
    titleLineEdit->setText(m_model->trackTitle());
    albumLineEdit->setText(m_model->albumTitle());
    trackSpinBox->setValue(m_model->trackNumber().toInt());
    preferenceCombo->setCurrentIndex(m_model->preference().intValue());
    timeDisplay->setTime(m_model->trackTime());
    genreLineEdit->setText(m_model->genre());

    QImage img = m_model->image();
    if (!img.isNull()) {
        QPixmap pm = QPixmap::fromImage(img);
        imageLabel->setPixmap(pm);
    }
	cout << "revert" << endl;
}

void MetaDataWidget::submit() {
	m_Mapper->submit();
	cout << "submit" << endl;
}
