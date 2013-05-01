//start
#include <QtGui>
int main (int argc, char* argv[]) {
    QApplication app(argc, argv);
    QProgressDialog nonModal;
    nonModal.setWindowTitle("Non Modal Parent Dialog");
    nonModal.show();                    /* Returns immediately */
    nonModal.connect(&nonModal, SIGNAL(finished()), 
            &app, SLOT(quit()));        /* Termination condition */    
//end
    QProgressDialog *nonModal2 = new QProgressDialog(&nonModal);
    nonModal2->setWindowTitle("Non-modal Child Dialog");
    QProgressDialog nonModal3;
    nonModal3.setWindowTitle("Non Modal Parentless dialog 3");
    nonModal.resize(640, 480);
    nonModal2->resize(320, 200);
    nonModal3.resize(320, 200);
    nonModal2->show();
    nonModal3.show();
//start
    QFileDialog fileDialog(&nonModal, "Modal File Child Dialog");
    // 2 modal dialogs. exec() takes over all user interactions until closed. 
    fileDialog.exec();                  /* Similar to entering an event loop, returns when window closes. */
    QMessageBox::question(0, QObject::tr("Modal parentless Dialog"),
            QObject::tr("can you interact with the other dialogs now?"), 
            QMessageBox::Yes | QMessageBox::No);
    return app.exec();                  /* Quits when nonModal closes */
}
//end