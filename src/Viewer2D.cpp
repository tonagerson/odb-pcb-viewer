#include "Viewer2D.hpp"
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>
#include <QMouseEvent>
#include <QDebug>
#include "core/Product_Model.hpp"

Viewer2D::Viewer2D(std::shared_ptr<ApplicationModel> model, QWidget *parent) : QWidget(parent),
_drag_active(false),
_mouse_position({0,0})
{
  _model = model;
  this->setMouseTracking(true);
}

Viewer2D::~Viewer2D()
{
}

void Viewer2D::paintEvent(QPaintEvent *event)
{


    // qDebug() << "Viewer2D::paintEvent " << this->size().width() << "," << this->size().height();
    QPainter painter;
    painter.begin(this);

    //  pour lisser les lignes diagonales et les cercles
    painter.setRenderHint(QPainter::Antialiasing);

    //  Nettoyer l'écran
    painter.setBrush(Qt::white);
    painter.fillRect(event->rect(), Qt::white);

    //Appiquer la matrice de transformation(zoom et déplacement)


    //  Dessiner l'axe X/Y de référence
    if (_model->getAxis()) {
        _model->getAxis()->paint(&painter, &_view_transform);
    }

    //  Dessiner le circuit imprimé
    // if  le parser a bien chargé un modèle
    if (_model->hasProductModel()) {
        //la carte
        Product_Model* pcb = _model->getProductModel();
        //après la surface
        Surface surf = pcb->get_surface();

        std::vector<Outline> contours = surf.get_outlineArr();
        QPainterPath chemin_carte;
        //parcours de contour de la surface
        for(Outline outline : surf.get_outlineArr()){
            std::vector<Edge> edges = outline.get_edgeArr();//segment



            if(edges.empty()) continue;
            QPointF pt_depart_modele(edges[0].get_x(), edges[0].get_y());

            QPointF pt_depart_ecran = _view_transform.transformToView(pt_depart_modele);

            //premier point du segment
            chemin_carte.moveTo(pt_depart_ecran);
            //on trace les lignes pour les points
            for(size_t i = 1; i < edges.size(); i++){
               // chemin_carte.lineTo(edges[i].get_x(), edges[i].get_y());
                QPointF pt_modele(edges[i].get_x(), edges[i].get_y());
                QPointF pt_ecran = _view_transform.transformToView(pt_modele);

                chemin_carte.lineTo(pt_ecran);
            }
            chemin_carte.closeSubpath();


    }
        //Dessin
        painter.setPen(QPen(Qt::black, 0));//contour
        painter.setBrush(QBrush(QColor(34, 139, 34)));//rempissage

        painter.drawPath(chemin_carte);


    }

    painter.end();
}

void Viewer2D::mouseMoveEvent(QMouseEvent * event)
{
  //qDebug() << "Viewer2D::mouseMoveEvent " << event->pos().x() << "," << event->pos().y();

  // Translating view need repaint
  if(_drag_active)
  {
    QPoint delta = event->pos() - _mouse_position;
   // qDebug() << "Viewer2D::mouseMoveEvent translate delta : " << delta;
    _view_transform.translate(delta);
    this->update();
  }

  _mouse_position = event->pos();
}

void Viewer2D::mousePressEvent(QMouseEvent * event)
{
  qDebug() << "Viewer2D::mousePressEvent " << event->button();
  if(event->button() == Qt::LeftButton)
  {
    _drag_active = true;
    _mouse_position = event->pos();
    qDebug() << "Viewer2D::mousePressEvent drag active = true, position = " << _mouse_position;
  }
}

void Viewer2D::mouseReleaseEvent(QMouseEvent *event)
{
  qDebug() << "Viewer2D::mouseReleaseEvent " << event->button();
  if(event->button() == Qt::LeftButton)
  {
    qDebug() << "Viewer2D::mousePressEvent drag active = false";
    _drag_active = false;
  }
}

void Viewer2D::wheelEvent(QWheelEvent *event)
{
  qDebug() << "Viewer2D::wheelEvent " << event->angleDelta();
  if(event->buttons() == Qt::NoButton)
  {
    _view_transform.zoom(event->angleDelta().y());
    this->update();
  }
}
