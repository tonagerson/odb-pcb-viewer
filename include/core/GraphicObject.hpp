#pragma once
#include "core/ViewTransform.hpp"
#include <QRect>
#include <QPainter>

class BoundingBox : QRect
{
  public:
  BoundingBox() = default;
  BoundingBox(int x, int y, int width, int height) : QRect(x,y,width,height){}

  inline QPoint leftMiddle() const {return QPoint(this->left(),this->top()+ this->height()/2);}
  inline QPoint rightMiddle() const {return QPoint(this->right(),this->top()+ this->height()/2);}
  inline QPoint topMiddle() const {return QPoint(this->left()+ this->width()/2, this->top());}
  inline QPoint bottomMiddle() const {return QPoint(this->left()+ this->width()/2, this->bottom());}
};

/**
 * @brief The GraphicObject class is the abstract class for all object that can be painted
 *        in Viewer2D.
 */
class GraphicObject
{
  public:
  GraphicObject() = default;
  ~GraphicObject() = default;

  virtual void paint(QPainter * painter, const ViewTransform * view_transform) = 0;

  protected:
  BoundingBox _bounding_box;
};
