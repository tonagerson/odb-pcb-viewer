#pragma once

#include<QPoint>
#include <QPointF>

class ViewTransform
{
  public:
  ViewTransform() = default;
  ~ViewTransform() = default;

  void translate(const QPoint& delta);
  void zoom(const int direction, const QPointF& pos);

  QPointF transformToView(const QPointF & point) const;

  private:
  QPointF _translation = {300.0,300.0};
  float _zoom = {150.0f};
};
