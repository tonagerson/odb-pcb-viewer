#include <string_view>
#include <string>
#include "ApplicationController.hpp"
#include <QFileDialog>
#include "core/Product_Model.hpp"
#include "mainwindow.h"

ApplicationController::ApplicationController(std::shared_ptr<ApplicationModel> model, Viewer2D * viewer2d)
{
    _model = model;
    _viewer2d = viewer2d;
}

void ApplicationController::onOpenFileRequest()
{
    QString dirPath = QFileDialog::getExistingDirectory(
        nullptr,
        tr("Ouvrir un dossier ODB++"),
        "",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
        );

    if (dirPath.isEmpty()) {
        return;
    }

    Product_Model* pcb = new Product_Model();
    pcb->Parse(dirPath.toStdString());
    _model->setProductModel(pcb);

    _viewer2d->update();

    MainWindow* mainWin = dynamic_cast<MainWindow*>(_viewer2d->parentWidget());
    if (mainWin) {
        mainWin->populateLayerList();
    }
}