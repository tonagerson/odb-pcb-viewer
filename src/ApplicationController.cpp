#include "ApplicationController.hpp"
#include <QFileDialog>
#include <QDebug>
#include "core/Product_Model.hpp"

ApplicationController::ApplicationController(std::shared_ptr<ApplicationModel> model, Viewer2D * viewer2d)
{
  _model = model;
  _viewer2d = viewer2d;
}

void ApplicationController::onOpenFileRequest()
{


    // 1. Ouvre l'explorateur pour choisir le dossier du projet ODB++
    QString dirPath = QFileDialog::getExistingDirectory(
        nullptr,
        tr("Ouvrir un dossier ODB++"),
        "",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
        );

    if (dirPath.isEmpty()) {
        return;
    }


    // TODO futur : Passer "dirPath.toStdString()" au parser de ton camarade
    // pour qu'il remplisse le _model

    // TODO futur : Mettre à jour la vue une fois le parsing terminé
    // _viewer2d->update();
  /*qDebug() << "ApplicationController::onOpenFileRequest";
  qDebug() << "TODO : Open QOpenFileDialog and get file path";
  qDebug() << "TODO : Parser File and fill data structure in model";
  qDebug() << "TODO : Update view (_viewer2d->update())";



*/
    Product_Model* pcb = new Product_Model();
    pcb->Parse(dirPath.toStdString());
    _model->setProductModel(pcb);
     _viewer2d->update();
}
