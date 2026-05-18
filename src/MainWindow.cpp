#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setMinimumSize(QSize(900, 600));

  // Create objects
  _model = std::make_shared<ApplicationModel>();
  _viewer2d = new Viewer2D(_model);
  _controller = std::make_shared<ApplicationController>(_model, _viewer2d);

  // Set central view
  this->setCentralWidget(_viewer2d);

  // Set menu
  _file_menu = new QMenu("File");
  this->menuBar()->addMenu(_file_menu);
  QAction * open_file_action = new QAction("Open File");
  _file_menu->addAction(open_file_action);

  // Connect user's click event on open file menu to Controler's method
  connect(open_file_action, &QAction::triggered, _controller.get(), &ApplicationController::onOpenFileRequest);
}

MainWindow::~MainWindow() {
  delete ui;
}
