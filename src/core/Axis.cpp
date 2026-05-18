#include "core/Axis.hpp"
#include <QLine>

Axis::Axis(): GraphicObject()
{
  _bounding_box = BoundingBox(-100,-100,200,200);
}

void Axis::paint(QPainter *painter, const ViewTransform *view_transform)
{
  // X axis
  QLineF x_line(view_transform->transformToView(_bounding_box.leftMiddle()), view_transform->transformToView(_bounding_box.rightMiddle()));
  painter->setPen(Qt::red);
  painter->drawLine(x_line);

  // Y axis
  QLineF y_line(view_transform->transformToView(_bounding_box.topMiddle()), view_transform->transformToView(_bounding_box.bottomMiddle()));
  painter->setPen(Qt::green);
  painter->drawLine(y_line);
}
