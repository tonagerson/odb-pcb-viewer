#pragma once

#include<QPoint>

class ViewTransform
{
  public:
  ViewTransform() = default;
  ~ViewTransform() = default;

  void translate(const QPoint& delta);
  void zoom(const int direction);

  QPointF transformToView(const QPointF & point) const;

  private:
  QPoint _translation = {300,300};
  float _zoom = {150.0f};
};
