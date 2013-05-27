#include <QtWidgets>
#include "lifemainwindow.h"
#include "ui_lifemainwindow.h"
#include "lifewidget.h"

LifeMainWindow::LifeMainWindow(QWidget* parent) 
: QMainWindow(parent), ui(new Ui::LifeMainWindow) {
    ui->setupUi(this);
    m_lifeWidget = new LifeWidget(this);
    setCentralWidget(m_lifeWidget);
    layout()->invalidate();
    QSettings s;
    QVariant bs = s.property("size");
    m_boardSize = QSize(1024, 768);
    if (!bs.isNull()) {
        m_boardSize = bs.toSize();
    }
    m_current = QImage(m_boardSize, QImage::Format_Mono);
    m_lifeWidget->setImage(m_current);
}

LifeMainWindow::~LifeMainWindow() {
    delete ui;
}

void LifeMainWindow::on_actionPopulate_Randomly_triggered() {
    qsrand(QTime::currentTime().msec());
    for (int i=0; i<10000; ++i) {
        int rx = qrand() % m_boardSize.width();
        int ry = qrand() % m_boardSize.height();
        m_current.setPixel(rx, ry, ALIVE);
    }
    m_lifeWidget->setImage(m_current);
}


void LifeMainWindow::on_actionStartStop_triggered(bool checked) {
    m_running = checked;
    if (ui->actionStartStop->isChecked() != checked) {
        ui->actionStartStop->setChecked(checked);
    }
    if (m_running) {
        m_numGenerations = 0;
        m_timer.start();
        calculate();
    } else {
        int elapsed = m_timer.elapsed();
        double fps = 1000.0 * m_numGenerations / elapsed;
        QString status = tr("Frames: %1. elapsed: %2  fps: %3")
                         .arg(m_numGenerations).arg(elapsed).arg(fps);
        statusBar()->showMessage(status);
    }
}


int LifeMainWindow::neighborCount(const QImage& img, int x, int y) {
    int retval = 0;
    for (int c = x-1; c < x+2; c++) {
        int wc = c;
        if (wc >= img.width()) wc = 0;
        if (wc < 0) wc = img.width() - 1;
        for (int r = y-1; r < y+2; ++r) {
            if ((c == x) && (r == y)) continue;    /* I am not my own neighbor */
            int wr = r;
            if (wr < 0) wr = img.height() - 1;
            if (wr >= img.height()) wr = 0;
            if (ALIVE == img.pixelIndex(wc, wr))
                retval ++;
        }
    }
    return retval;
}


void LifeMainWindow::calculate() {
    int w = m_boardSize.width();
    int h = m_boardSize.height();
    while (m_running) {
        qApp->processEvents();          /* Let the GUI process events also! */
        m_numGenerations++;
        QImage next = m_current;
        for (int x=0; x < w; ++x) {     /* The rules of the game of life */
            for (int y=0; y < h; ++y) {
                bool isAlive = (m_current.pixelIndex(x, y) == ALIVE);
                int nc = neighborCount(m_current, x, y);
                if (!isAlive && nc == 3)
                    next.setPixel(x, y, ALIVE);
                if (!isAlive) continue;
                if ((nc < 2) || (nc > 3))
                    next.setPixel(x, y, DEAD);
            }
        }
        m_current = next;
        m_lifeWidget->setImage(m_current);
    }
}

void LifeMainWindow::on_actionClear_triggered() {
    on_actionStartStop_triggered(false);
    m_current.fill(DEAD);
    m_lifeWidget->setImage(m_current);
}

void LifeMainWindow::closeEvent(QCloseEvent* evt) {
    m_running = false;
}

void LifeMainWindow::on_actionQuit_triggered() {
    m_running=false;
    qApp->quit();
}

void LifeMainWindow::on_actionAbout_Qt_triggered() {
    qApp->aboutQt();
}

void LifeMainWindow::on_actionAbout_triggered() {
    QMessageBox::information(this, tr("About %1") .arg(qApp->applicationName()),
        tr ("This is a single-threaded version of Conway's Game of Life."));
}
