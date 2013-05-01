#include "puzzle.h"
#include <QGridLayout>
#include <QAbstractButton>
#include <QAction>
#include <QMenu>
#include <QMenuBar>

// time()
#include <time.h>
// random()
#include <cstdlib>
// abs()
#include <math.h>

PuzzleModel::PuzzleModel(int r, int c, QObject* parent) :
    QObject(parent), m_Rows(r), m_Cols(c) {
    int val=0;
    for (r=0; r<m_Rows; ++r)
        for (c=0; c<m_Cols; ++c)
            m_Positions << val++;
}

int PuzzleModel::size() const {
    return m_Rows * m_Cols;
}

/**
   @param position1, position2 are positions in a m*n matrix
   @return true if the positions are neighboring.
*/
bool PuzzleModel::neighboring(int position1, int position2) const {
    int abval = abs(position1 - position2);
    return (abval == 1) or (abval == m_Cols);
}

bool PuzzleModel::slide(int tilenum) {
    int mypos = m_Positions.indexOf(tilenum);
    int zp = m_Positions.indexOf(0);
    if (neighboring(zp, mypos)) {
        m_Positions.swap(zp, mypos);
        emit gridChanged();
        return true;
    }
    return false;
}


void PuzzleModel::shuffle() {
    // seed the random number generator with the current time
    srandom(time(0));
    int i=0;
    while (i < 100) {
        int tilenum = random() % size();
        if (slide(tilenum)) ++i;
    }
}

int PuzzleModel::value(int r, int c) const {
    return m_Positions.at(index(r,c));
}

int PuzzleModel::index(int r, int c) const {
    return r*m_Cols+c;
}

QString PuzzleModel::toString() const {
    QStringList rows;
    for (int r=0; r<m_Rows; ++r) {
        QStringList currentRow;
        for (int c=0; c<m_Cols; ++c) {
            int squareNumber = m_Positions.at(index(r,c));
            QString stringValue = QString("%1").arg(squareNumber);
            currentRow << stringValue;
        }
        rows << currentRow.join("\t");
    }
    return rows.join("\n");
}

Tile::Tile(int tileNumber): m_Number(tileNumber) {
    QString label = "";
    if (tileNumber > 0) {
        label = QString("%1").arg(tileNumber);
    }
    setText(label);
    QString longText = "click here to push Tile # " + label;
    setWhatsThis(longText);
    setToolTip(longText);
    setStatusTip(longText);
}

PuzzleView::PuzzleView(PuzzleModel* model) : m_Model(model) {
    // Create the buttons
    int numTiles = m_Model->size();
    m_Layout = new QGridLayout(this);
    for (int i=0; i< numTiles; ++i) {
        QString name = QString("%1").arg(i);
        Tile* t = new Tile(i);
        m_Tiles.addButton(t);
    }

    /* This helps avoid connecting a signal for each button */      
    connect (&m_Tiles, SIGNAL(buttonClicked(QAbstractButton*)),
	    this, SLOT(tryToSlide(QAbstractButton*)));
    
    connect (m_Model, SIGNAL(gridChanged()), 
             this, SLOT(refresh()));
    refresh();
}

void PuzzleView::tryToSlide(QAbstractButton* button) {
    Tile* tile = qobject_cast<Tile*>(button);
    int number = tile->getNumber();
    m_Model->slide(number); /* won't do anything if the 0 is
	    	not adjacent */
}

void PuzzleView::refresh() {
    QList<QAbstractButton*> buttonList = m_Tiles.buttons();
    for (int r=0; r<m_Model->rows(); ++r) {
        for (int c=0; c<m_Model->cols(); ++c) {
            int v = m_Model->value(r,c);
            QAbstractButton* b = buttonList.at(v);
            m_Layout->addWidget(b, r, c);
        }
    }
}


void PuzzleApp::createWidgets() {
    m_Model = new PuzzleModel(4,4,this);
    m_View = new PuzzleView(m_Model);
    m_MainWin.setCentralWidget(m_View);
}

void PuzzleApp::createActions() {
    m_Shuffle = new QAction(this);
    m_Shuffle->setText("Shuffle");
    QMenu* game = new QMenu(&m_MainWin);
    game->setTitle("Game");
    m_MainWin.menuBar()->addMenu(game);
    game->addAction(m_Shuffle);
    connect (m_Shuffle, SIGNAL(triggered()), 
             m_Model, SLOT(shuffle()));
}

PuzzleApp::PuzzleApp(int argc, char** argv) :
    QApplication(argc, argv) {
    createWidgets();
    createActions();
    m_MainWin.show();
}
