#include <QTimer>
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), 
    ui(new Ui::MainWindow), m_expInterval(0), m_durationInterval(0),
    m_trials(0), m_correctChars(0),  m_totTrials(0),
    m_totCorrectChars(0) {

    m_randStr = new RandomString(3, "canadian-english-small");
    totalLenTarget = 0;

    //initialize ui
    ui->setupUi(this);
    ui->displayLabel->hide();
    ui->responseLabel->hide();
    ui->nextButton->hide();
    m_randStr->setStringLength(5);
}

MainWindow::~MainWindow() {
    delete m_randStr;
    delete ui;
}

void MainWindow::changeEvent(QEvent* e) {
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_exposureSlider_valueChanged(int value) {
    ui->exposureLCD->display(value); 
}

void MainWindow::on_lengthSlider_valueChanged(int value) {
    ui->lengthLCD->display(value);
}

void MainWindow::on_startButton_clicked() {
    //hide start button
    ui->startButton->hide();

    //show game panel
    ui->displayLabel->show();
    ui->targetString->show();
    ui->responseLabel->show();
    ui->responseString->show();
    ui->nextButton->show();

    //disable settings
    ui->groupBox->setEnabled(false);

    m_trials = 0;
    lenTarget = 0;

    //initialize the score system
    m_correctChars = 0;

    // start trials
    processTrial();
}

//start
void MainWindow::processTrial() {
    // get user defined values
    m_expInterval = ui->exposureSlider->value();
    m_durationInterval = ui->durationSlider->value();
    m_randStr->setStringLength(ui->lengthSlider->value());

    //clear response text editor
    ui->responseString->setText("");
    //display the random string
    QString string = m_randStr->generateString();
    ui->targetString->setText(string);
    lenTarget += string.count();
    totalLenTarget += string.count();
    ui->responseString->setEnabled(false);
    ui->nextButton->setEnabled(false);
    //count the number of trials
    m_trials++;
    m_totTrials++;
    ui->nextButton->setText(QString("String %1").arg(m_trials));
    //begin exposure
    QTimer::singleShot(m_expInterval, this, SLOT(timerDisplayRandStr()));
}


void MainWindow::timerDisplayRandStr() {
    ui->targetString->setText(QString(""));
    //enable the response line editor and next button
    ui->responseString->setEnabled(true);
    ui->responseString->setFocus();
    ui->nextButton->setEnabled(true);
    clicked = false;
    QTimer::singleShot(m_durationInterval, this, SLOT(on_nextButton_clicked()));
}

//end

void MainWindow::on_responseString_returnPressed() {
    on_nextButton_clicked();  //Pressing return has same effect as clicking next.
}


void MainWindow::on_nextButton_clicked() {

    // prevents method from getting called twice, once from button and another from
    // timer
    if(clicked == false)
        clicked = true;
    else
        return;

    int goodChars(m_randStr->numCorrectChars(ui->responseString->text()));
    m_correctChars += goodChars;
    m_totCorrectChars += goodChars;
    ui->correctCharFraction->setText(QString("%1 / %2").arg(m_correctChars).arg(lenTarget));
    ui->cumulativeFraction->setText(QString("%1 / %2").arg(m_totCorrectChars).arg(totalLenTarget));

    if(m_trials == ui->trialsSpinBox->value()) {
        //hide game panel
        ui->startButton->show();
        //show start button
        ui->displayLabel->hide();
        ui->targetString->hide();
        ui->responseLabel->hide();
        ui->responseString->hide();
        ui->nextButton->hide();
        //Enble settings
        ui->groupBox->setEnabled(true);
    }
    else
        processTrial();
}



void MainWindow::on_durationSlider_valueChanged(int value) {
    ui->durationLCD->display(value);
}
