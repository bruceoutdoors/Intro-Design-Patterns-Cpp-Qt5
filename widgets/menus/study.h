#ifndef STUDY_H
#define STUDY_H

#include <QMainWindow>
class QAction;
class QActionGroup;

/**
  Demo of QActions and QActionGroups
  S. Alan Ezust (alan dot ezust at gmail dot com )
  */
//start
class Study : public QMainWindow {
    Q_OBJECT
 public:
    explicit Study(QWidget* parent=0);
 public slots:
    void actionEvent(QAction* act);
 private:
    QActionGroup* actionGroup;  /* For catching the signals */
    QToolBar* toolbar;          /* For displaying the actions as buttons */

    QAction* useTheForce;
    QAction* useTheDarkSide;
    QAction* studyWithObiWan;
    QAction* studyWithYoda;
    QAction* studyWithEmperor;
    QAction* fightYoda;
    QAction* fightDarthVader;
    QAction* fightObiWan;
    QAction* fightEmperor;
protected:
    /**
       Adds a new QAction to a toolbar and returns it.
       */
    QAction* addChoice(QString name, QString text);

};
//end
#endif


