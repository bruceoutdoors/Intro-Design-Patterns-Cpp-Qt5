#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QAction>
#include <QDebug>
#include <QApplication>
#include <QToolBar>
#include <QMessageBox>
#include <QActionGroup>
#include "study.h"

//start id=main
int main( int argc, char** argv ) {
    QApplication app( argc, argv );
    Study study;
    study.show();
    return app.exec();
}
//end
//start id=addchoice

// Factory function for creating QActions initialized in a uniform way
QAction* Study::addChoice(QString name, QString text) {
    QAction* retval = new QAction(text, this);
    retval->setObjectName(name);
    retval->setEnabled(false);
    retval->setCheckable(true);
    actionGroup->addAction(retval); /* Add every action 
    to a QActionGroup so we need only one 
    signal connected to one slot. */
    return retval;
}
//end
//start id=study
Study::Study(QWidget* parent) : QMainWindow(parent) {
    actionGroup = new QActionGroup(this);
    actionGroup->setExclusive(false);
    statusBar();

    QWidget::setWindowTitle( "to become a jedi, you wish?"); /* Some of the ClassName:: prefixes used here are not necessary, because the functions can be called on "this". The class names can be used to explicitly call a baser-version, or show the reader which version is called. */

    QMenu* useMenu = new QMenu("&Use", this);
    QMenu* studyMenu = new QMenu("&Study", this);
    QMenu* fightMenu = new QMenu("&Fight", this);

    useTheForce = addChoice("useTheForce", "Use The &Force");
    useTheForce->setStatusTip("This is the start of a journey...");
    useTheForce->setEnabled(true);
    useMenu->addAction(useTheForce);                         /* It's already in a QActionGroup, but we also add it to a QMenu. */
//end
    useTheDarkSide = addChoice("useTheDarkSide", "Use the &Dark Side");
    useMenu->addAction(useTheDarkSide);
    useTheDarkSide->setStatusTip("It's unavoidable, like the Apple in eden...");
//start id=study
    studyWithObiWan = addChoice("studyWithObiWan", "&Study With Obi Wan");
    studyMenu->addAction(studyWithObiWan);
    studyWithObiWan->setStatusTip("He will certainly open doors "
                                   "for you...");

    fightObiWan = addChoice("fightObiWan", "Fight &Obi Wan");
    fightMenu->addAction(fightObiWan);
    fightObiWan->setStatusTip("You'll learn some tricks from him "
                               "that way, for sure!");
//end
    studyWithYoda = addChoice("studyWithYoda", "Study with &Yoda");
    studyMenu->addAction(studyWithYoda);
    studyWithYoda->setStatusTip("He's the master, why wouldn't you?");

    fightYoda = addChoice("fightYoda", "Fight Y&oda");
    fightMenu->addAction(fightYoda);
    fightYoda->setStatusTip("What are you, nuts?");

    fightDarthVader = addChoice("fightDarthVader", "Fight Darth &Vader");
    fightMenu->addAction(fightDarthVader);

    fightEmperor = addChoice("fightEmperor", "Fight &Emperor");
    fightMenu->addAction(fightEmperor);

    studyWithEmperor = addChoice("studyWithEmperor", "Study With Empero&r");
    studyMenu->addAction(studyWithEmperor);
//start id=study
    QMainWindow::menuBar()->addMenu(useMenu);
    QMainWindow::menuBar()->addMenu(studyMenu);
    QMainWindow::menuBar()->addMenu(fightMenu);

    toolbar = new QToolBar("Choice ToolBar", this);          /* This gives
        us visible buttons in a dockable widget for each of the QActions. */
    toolbar->addActions(actionGroup->actions());

    QMainWindow::addToolBar(Qt::LeftToolBarArea, toolbar);


    QObject::connect(actionGroup, SIGNAL(triggered(QAction*)),
            this, SLOT(actionEvent(QAction*)));              /* Instead of
            connecting each individual action's signal, perform one connect to an actionGroup that contains them all. */

    QWidget::move(300, 300);
    QWidget::resize(300, 300);
}
//end

//start id=actionevent
void Study::actionEvent(QAction* act) {
   QString name = act->objectName();
   QString msg = QString();

   if (act == useTheForce ) {
       studyWithObiWan->setEnabled(true);
       fightObiWan->setEnabled(true);
       useTheDarkSide->setEnabled(true);
   }
   if (act == useTheDarkSide) {
       studyWithYoda->setEnabled(false);
       fightYoda->setEnabled(true);
       studyWithEmperor->setEnabled(true);
       fightEmperor->setEnabled(true);
       fightDarthVader->setEnabled(true);
   }
   if (act == studyWithObiWan) {
       fightObiWan->setEnabled(true);
       fightDarthVader->setEnabled(true);
       studyWithYoda->setEnabled(true);
   }
//end

   if (act == studyWithYoda) {
       fightDarthVader->setEnabled(true);
       fightEmperor->setEnabled(true);
   }
   if (act == fightYoda) {
       msg = "You Lose.";
       act->setChecked(false);
       studyWithYoda->setEnabled(false);
   }
//start id=actionevent
   if (act == fightObiWan ) {
       if (studyWithEmperor->isChecked()) {
            msg = "You are victorious!";
       }
       else {
           msg = "You lose.";
           act->setChecked(false);
           studyWithYoda->setEnabled(false);
       }
   }
//end
   if (act == fightDarthVader ) {
       if (studyWithYoda->isChecked() == false) {
           msg = "Off with your hand! Chop!";
           act->setChecked(false);
       }
       else {
           msg = "You whupped some Vader ass!";
           studyWithEmperor->setEnabled(false);
           studyWithYoda->setEnabled(true);
       }
   }
   if (act == studyWithEmperor) {
       studyWithEmperor->setChecked(true);
   }
   if (act == fightEmperor ) {
       if (fightObiWan->isChecked()) {
           msg = "You defeated the evil emperor!";
       }
       else {
           msg = "You've been burned to a crisp.";
           studyWithEmperor->setEnabled(false);
           fightEmperor->setChecked(false);
       }
   }
//start id=actionevent
   if (msg != QString()) {
      QMessageBox::information(this, "Result", msg, "ok");
   }
}
//end

