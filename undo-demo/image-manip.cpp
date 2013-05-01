#include <QRect>
#include <QColor>
#include "image-manip.h"
#include <QDebug>


//start id=adjustcolors
void AdjustColors::adjust(double radj, double gadj, double badj) {
   int h(m_Image.height()), w(m_Image.width());
   int r, g, b;
   QRgb oldpix, newpix;
   m_Saved = m_Image.copy(QRect()); // save a copy of entire image   
   for(int y = 0; y < h; ++y) {
      for(int x = 0; x < w; ++x) {
         oldpix = m_Image.pixel(x,y);
         r = qRed(oldpix) * radj;
         g = qGreen(oldpix) * gadj;
         b = qBlue(oldpix) * badj;
         newpix = qRgb(r,g,b);
         m_Image.setPixel(x,y,newpix);
      }
   }
}

void AdjustColors::redo() {
   qDebug() << "AdjustColors::redo()";
   adjust(m_RedAdj, m_GreenAdj, m_BlueAdj);
}

void AdjustColors::undo() {
    qDebug() << "AdjustColors::undo()";
    m_Image = m_Saved.copy(QRect()); 
}
//end
//start id=mirrorpixels
void MirrorPixels::reflect() {
    qDebug() << "MirrorPixels::reflect()";
    m_Saved = m_Image.copy(QRect());
    int h(m_Image.height()), w(m_Image.width());
    QRgb pix;
    if(m_Horizontal) {
       int midpt = h / 2;
       for(int x = 0; x < w; ++x) {
          for(int y = 0; y < midpt; ++y) {
             pix = m_Image.pixel(x,y);
             m_Image.setPixel(x,h - 1 - y,pix);
          }
       }       
    }
    else {
       int midpt = w / 2;
       for(int y = 0; y < h; ++y) {
          for(int x = 0; x < midpt; ++x) {
             pix = m_Image.pixel(x,y);
             m_Image.setPixel(w-1-x,y,pix);
          }
       }
    } 
}

void MirrorPixels::redo() {
   qDebug() << "MirrorPixels::redo()";
   reflect();
}


void MirrorPixels::undo() {
    qDebug() << "MirrorPixels::undo()";
    m_Image = m_Saved.copy(QRect()); 
}
//end
