#include <QtGui>
#include "lifemainwindow.h"
#include "ui_lifemainwindow.h"
#include "lifewidget.h"
#include "lifeslice.h"
enum {DEAD=0, ALIVE=1};
static QSize boardSize(1024, 768);

LifeMainWindow::LifeMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LifeMainWindow)
{
    ui->setupUi(this);
    ui->threadSpinBox->setValue(QThreadPool::globalInstance()->maxThreadCount());
    m_lifeWidget = new LifeWidget(this);
    setCentralWidget(m_lifeWidget);
    setWindowTitle(qApp->applicationName());
    QSettings s;
    QVariant bs = s.property("boardsize");
    if (!bs.isNull()) {
        boardSize = bs.toSize();
    }
    m_current = QImage(boardSize, QImage::Format_Mono);
    m_lifeWidget->setImage(m_current);
}

LifeMainWindow::~LifeMainWindow() {
    delete ui;
}

void LifeMainWindow::on_actionPopulate_Randomly_triggered() {
    qsrand(QTime::currentTime().msec());
    for (int i=0; i<10000; ++i) {
        int rx = qrand() % boardSize.width();
        int ry = qrand() % boardSize.height();
        m_current.setPixel(rx, ry, ALIVE);
    }
    m_lifeWidget->setImage(m_current);
}


void LifeMainWindow::on_actionStartStop_triggered(bool checked) {
    m_running = checked;
    if (m_running) {
        m_numGenerations = 0;
        m_timer.start();
        calculate();
    }
    else {
        int elapsed = m_timer.elapsed();
        double fps = 1000.0 * m_numGenerations / elapsed;
        QString status = tr("Frames: %1. elapsed: %2  fps: %3")
                         .arg(m_numGenerations).arg(elapsed).arg(fps);
        statusBar()->showMessage(status);
    }
}

/** Wrap-around neighbor count */
static int neighborCount(const QImage &img, int x, int y) {
    int retval = 0;
    int wid = img.width();
    int height = img.height();
    for (int c = x-1; c < x+2; c++) {
        int wc = c;                             /* wrapped column */
        if (wc >= wid) wc = 0;
        else if (wc < 0) wc = wid - 1;
        for (int r = y-1; r < y+2; ++r) {
            if ((c == x) && (r == y)) continue; /* do not count myself  */
            int wr = r;                         /* wrapped row */
            if (wr < 0) wr = height - 1;
            else if (wr >= height) wr = 0;
            if (ALIVE == img.pixelIndex(wc, wr))
                retval ++;
        }
    }
    return retval;
}
//start id=mapfunctor
/** Mapping functor for conway's game of life */
struct LifeFunctor : public std::unary_function<LifeSlice, LifeSlice> {
    LifeSlice operator() (LifeSlice slice);
};

LifeSlice LifeFunctor::operator()(LifeSlice slice) {    /* Mapping function */
    QRect rect = slice.rect;
    QImage image = slice.image;
    QImage next = QImage(rect.size(), QImage::Format_Mono);
    next.fill(DEAD);
    int h = rect.height();  int w = rect.width();

    for (int c=0; c<w; ++c) {
        for (int r=0; r<h; ++r) {
            int x = c+rect.x();
            int y = r+rect.y();
            bool isAlive = (image.pixelIndex(x, y) == ALIVE);
            int nc = neighborCount(image, x, y);
            if (!isAlive && nc == 3)
                 next.setPixel(c, r, ALIVE);
            if (!isAlive) continue;
            if (nc == 2 || nc == 3)
                next.setPixel(c,r, ALIVE);
        }
    }
    slice.image = next;
    return slice;
}
//end
//start id=reduce
/** Reduce function */
void stitchReduce(QImage& next, const LifeSlice &slice) {
    if (next.isNull()) 
        next = QImage(boardSize, QImage::Format_Mono);
    QPainter painter(&next);
    painter.drawImage(slice.rect.topLeft(), slice.image);   /* Draw one piece of 
                an image onto another. */
}
//end
//start id="blockingMappedReduced"
void LifeMainWindow::calculate() {
    int w = boardSize.width();
    // This might not be optimal but it seems to work well...    
    int segments = QThreadPool::globalInstance()->maxThreadCount() * 2; 
    int ws = w/segments;                    /* Width of a segment. */
    LifeFunctor functor;                    /* Map functor. */
    while (m_running) {
        qApp->processEvents();              /* Ensure GUI is still responsive. */
        m_numGenerations++;
        QList<LifeSlice> slices;            /* Break up into smaller pieces. */
        for (int c=0; c<segments; ++c) {
            int tlx = c*ws;
            QRect rect(tlx, 0, ws, boardSize.height());
            LifeSlice slice(rect, m_current);    
            slices << slice;                /* Add the pieces to a collection
                    to be processed in parallel. */
        }
        m_current = QtConcurrent::blockingMappedReduced(slices, functor,
                    stitchReduce, QtConcurrent::UnorderedReduce );  /* Do the 
            work in parallel. stitchReduce can be called on each piece as it 
            is ready. */
        m_lifeWidget->setImage(m_current);
    }
}
//end

void LifeMainWindow::on_actionClear_triggered() {
    m_current.fill(DEAD);
    m_lifeWidget->setImage(m_current);
}

void LifeMainWindow::closeEvent(QCloseEvent *) {
    m_running = false;
}

void LifeMainWindow::on_actionQuit_triggered() {
    m_running=false;
    qApp->quit();
}

void LifeMainWindow::on_threadSpinBox_valueChanged(int v) {
    if ((v > 0) && (v < 100))
        QThreadPool::globalInstance()->setMaxThreadCount(v);
}

void LifeMainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, qApp->applicationName(),
                             tr("Conway's game of life using QtConcurrent mapReduce"));
}

void LifeMainWindow::on_actionAbout_Qt_triggered()
{
    qApp->aboutQt();
}
