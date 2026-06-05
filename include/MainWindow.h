#pragma once
#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <memory>
#include "ApplicationController.hpp"
#include "ApplicationModel.hpp"
#include "Viewer2D.hpp"
#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void populateLayerList();
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    std::shared_ptr<ApplicationController> _controller;
    std::shared_ptr<ApplicationModel> _model;
    Viewer2D * _viewer2d;
    QMenu * _file_menu;
    QListWidget* _list_layers;
};