#include "activity.h"
#include "activityitem.h"
#include <QtWidgets>


/* Demo of spinny activity buttons */
int main (int argc, char* argv[]) {
        QApplication app(argc, argv);
        QDialog mainWin;
        mainWin.setWindowTitle("TestIcons");
        QVBoxLayout *vbox = new QVBoxLayout(&mainWin); 
        
        ActivityButton *ab = new ActivityButton("SpinnyButton");
        ab->setCheckable(true);
        ab->connect(ab, SIGNAL(toggled(bool)), ab, SLOT(setActive(bool)));
        vbox->addWidget(ab);
        QSlider* slider = new QSlider(Qt::Vertical);
        
        slider->setRange(1, 100);
        slider->setValue(100);
        slider->setToolTip("Speed of movie");
        slider->connect (slider, SIGNAL(valueChanged(int)), getMovie(), SLOT(setSpeed(int)));
        QStandardItemModel *model = new QStandardItemModel(qApp);
        for (int i=0; i<5; ++i) {
            ActivityItem *item = new ActivityItem(QString("Activity %1").arg(i));
            item->setActive(true);
            model->appendRow(item);
        }
        ActivityView *av = new ActivityView();
        QHBoxLayout *hbox = new QHBoxLayout();
        vbox->addLayout(hbox);
        hbox->addWidget(av);
        hbox->addWidget(slider);
        av->setModel(model);
        mainWin.show();
        
        return app.exec();
        
    
    
}
