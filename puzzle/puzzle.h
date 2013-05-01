#ifndef PUZZLE_H
#define PUZZLE_H

#include <QApplication>
#include <QMainWindow>
#include <QList>
#include <QPushButton>
#include <QActionGroup>
#include <QButtonGroup>

class QGridLayout;

/** Stores the internal representation of a puzzle, 
    containing no knowledge of the view */
class PuzzleModel : public QObject {
    Q_OBJECT
  public:
    /** Creates a new rows*columns puzzle */
    PuzzleModel(int rows, int columns, QObject* parent=0);

    /** Returns the index into m_Positions for a given r,c 
    @return 0 if the empty square, or the tile# at that position. */
    int value(int r, int c) const;

    QString toString() const;

	/** @return dimension of puzzle */
    int size() const;

    /** Attempts to slide the numbered tile. 
    @return true if it succeeds, which is only
    possible if square 0 is a neighbor. 
    */    
    bool slide(int tilenum); 

    /** @return true if two positions are neighboring.
        pos1 and pos2 are index positions (offsets from 0)
	*/
    bool neighboring(int pos1, int pos2) const;

    int rows() const {return m_Rows;}
    int cols() const {return m_Cols;}

    /** @return the index into an array that stores the 
        tile at position (r,c).
    */
    int index(int r, int c) const;
  public slots:
    void shuffle(); 
  signals:
    void gridChanged();
	
  private:
    QList<int> m_Positions;
    int m_Rows, m_Cols;
};

/** A single tile in the GUI of the 15 puzzle */
class Tile : public QPushButton {
    Q_OBJECT
  public:
    Tile(int tileNumber);
    int getNumber() {return m_Number;}
  private:
    int m_Number;
    
};

/** A view for the puzzle */
class PuzzleView : public QWidget {
    Q_OBJECT
  public:
    PuzzleView(PuzzleModel*);
  public slots:
    void refresh();
    void tryToSlide(QAbstractButton* button);
  private:
    PuzzleModel *m_Model;
    QGridLayout *m_Layout;
    QButtonGroup m_Tiles;
};

/** Controller class for puzzle game - manages all other objects. */
class PuzzleApp : public QApplication {
    Q_OBJECT
  public:
    PuzzleApp(int argc, char* argv[]);
    void createWidgets();
    void createActions();
  private:
    QMainWindow m_MainWin;
    PuzzleModel *m_Model;
    PuzzleView *m_View;
    QAction* m_Shuffle;
};
#endif        //  #ifndef PUZZLE_H

