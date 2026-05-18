#include "core/ViewTransform.hpp"

void ViewTransform::translate(const QPoint &delta)
{
  _translation += delta;
}

void ViewTransform::zoom(const int direction)
{
  float step = 1.1;
  _zoom = direction>=0?_zoom*step:_zoom/step;
}

QPointF ViewTransform::transformToView(const QPointF &point) const
{
  return point * _zoom + _translation;
}

