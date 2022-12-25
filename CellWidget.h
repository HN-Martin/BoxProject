// -*- explicit-buffer-name: "CellWidget.h<M1-MOBJ/8-10>" -*-

#ifndef NETLIST_CELL_WIDGET_H
#define NETLIST_CELL_WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QRect>
#include <QPoint>
class QPainter;
#include "Box.h"


namespace Netlist {

  class Cell;
  class NodeTerm;


  class CellWidget : public QWidget {
    Q_OBJECT;
  public:
                    CellWidget         ( QWidget* parent=NULL );
    virtual        ~CellWidget         ();
            void    setCell            ( Cell* );
    inline  Cell*   getCell            () const{ return cell_; }
    inline  int     xToScreenX         ( int x ) const{ return x - viewport_.getX1();}
    inline  int     yToScreenY         ( int y ) const{ return viewport_.getY2() - y;}
    inline  QRect   boxToScreenRect    ( const Box& b) const;
    inline  QPoint  pointToScreenPoint ( const Point& pt) const;
    inline  int     screenXToX         ( int x ) const{ return x + viewport_.getX1();}
    inline  int     screenYToY         ( int y ) const{ return viewport_.getY2() - y;}
    inline  Box     screenRectToBox    ( const QRect& b) const;
    inline  Point   screenPointToPoint ( const QPoint& pt) const;
    virtual QSize   minimumSizeHint    () const;
    virtual void    resizeEvent        ( QResizeEvent* );
  protected:
    virtual void    paintEvent         ( QPaintEvent* );
    virtual void    keyPressEvent      ( QKeyEvent* );
  public slots:
            void    goLeft             ();
            void    goRight            ();
            void    goUp               ();
            void    goDown             ();
  private:
    Cell* cell_;
    Box   viewport_;
};

  inline Cell* CellWidget::getCell () const { return cell_; }

  inline QPoint  CellWidget::pointToScreenPoint ( const Point& pt) const{
	  Qpoint p(xToScreenX(pt.getX()) , yToScreenY(pt.getY()));
	  return p;
  }

  inline  QRect   CellWidget::boxToScreenRect    ( const Box& b) const{
	  int w= b.getWidth(), h = b.getHeight();
	  Qrect r(xToScreenX(b.getX1()) , yToScreenY(b.getY1()), w ,h);
	  return r;
  }


  inline  Point   CellWidget::screenPointToPoint ( const QPoint& pt) const{
	  Point p(screenXToX(pt.x()), screenYToY(pt.y()));
	  return p;
  }

  inline  Box     CellWidget::screenRectToBox    ( const QRect& r) const{
	  Point p1=screenPointToPoint(r.bottomLeft()), p2=screenPointToPoint(r.topRight());
  	  Box b(p1.getX(), p1.getY(), p2.getX(), p2.getY());
  	  return b;
    }

}  // Netlist namespace.

#endif  // NETLIST_CELL_WIDGET_H
