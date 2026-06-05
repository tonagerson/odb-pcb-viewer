#include <string_view>
#include <string>
#include <QDockWidget>
#include <QListWidget>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "core/Product_Model.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setMinimumSize(QSize(900, 600));

    // Création des objets
    _model = std::make_shared<ApplicationModel>();
    _viewer2d = new Viewer2D(_model);
    _controller = std::make_shared<ApplicationController>(_model, _viewer2d);

    // Le Viewer prend toute la place
    this->setCentralWidget(_viewer2d);

    // Création du panneau latéral
    QDockWidget *dock = new QDockWidget("Contrôle des couches", this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    _list_layers = new QListWidget(dock);
    dock->setWidget(_list_layers);
    this->addDockWidget(Qt::RightDockWidgetArea, dock); // Ajouté sur la droite

    // Action : Quand on coche/décoche une couche, on prévient Viewer2D
    connect(_list_layers, &QListWidget::itemChanged, this, [=](QListWidgetItem* item){
        bool isVisible = (item->checkState() == Qt::Checked);
        _viewer2d->setLayerVisible(item->text().toStdString(), isVisible);
    });

    // Configuration du menu
    _file_menu = new QMenu("File");
    this->menuBar()->addMenu(_file_menu);
    QAction * open_file_action = new QAction("Open File");
    _file_menu->addAction(open_file_action);

    connect(open_file_action, &QAction::triggered, _controller.get(), &ApplicationController::onOpenFileRequest);
}

MainWindow::~MainWindow() {
    delete ui;
}

// Remplir le menu avec les couches
void MainWindow::populateLayerList() {
    _list_layers->clear(); // On vide la liste
    if (_model->hasProductModel()) {
        Product_Model* pcb = _model->getProductModel();

        for (Layer& layer : pcb->get_layers()) {
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(layer.get_layerName()), _list_layers);
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // Ajoute la case à cocher
            item->setCheckState(Qt::Checked); // Couche visible par défaut
        }
    }
}