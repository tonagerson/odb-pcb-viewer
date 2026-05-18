#pragma once
#include "core/GraphicObject.hpp"

class Axis : public GraphicObject
{
  public:
  Axis();
  ~Axis() = default;

  virtual void paint(QPainter * painter, const ViewTransform * view_transform) override;
};
