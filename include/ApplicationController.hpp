#pragma once
#include <QObject>
#include "ApplicationModel.hpp"
#include "Viewer2D.hpp"

class ApplicationController : public QObject {
  Q_OBJECT
  public:
  ApplicationController(std::shared_ptr<ApplicationModel> model, Viewer2D * viewer2d);

  public slots:
  void onOpenFileRequest();

  private:
  std::shared_ptr<ApplicationModel> _model;
  Viewer2D * _viewer2d;
};
