#pragma once
#include "ApplicationModel.hpp"
#include "core/GraphicObject.hpp"
#include "core/ViewTransform.hpp"

#include <QWidget>

class Viewer2D : public QWidget {
  Q_OBJECT
  public:
  Viewer2D(std::shared_ptr<ApplicationModel> model, QWidget *parent = nullptr);
  ~Viewer2D();

  protected:
  // Paint the objects stored in model
  void paintEvent(QPaintEvent *event) override;

  // Use for trackball
  void mouseMoveEvent(QMouseEvent* event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent * event) override;

  private:
  std::shared_ptr<ApplicationModel> _model;

  // TrackBall
  bool _drag_active = false;
  QPoint _mouse_position;
  ViewTransform _view_transform;
};

