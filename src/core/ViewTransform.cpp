#include "core/ViewTransform.hpp"

void ViewTransform::translate(const QPoint &delta)
{
  _translation += delta;
}

void ViewTransform::zoom(const int direction, const QPointF& pos)
{
    float step = 1.1;
    float new_zoom = direction >= 0 ? _zoom * step : _zoom / step;
    _translation = pos - (pos - _translation) * new_zoom / _zoom;
    _zoom = new_zoom;
}

QPointF ViewTransform::transformToView(const QPointF &point) const
{
    QPointF inverted = QPointF(point.x(), -point.y());
    QPointF screen_point = inverted * _zoom + _translation;
    return screen_point;
}

