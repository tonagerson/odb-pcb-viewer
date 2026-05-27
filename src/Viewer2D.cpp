#include "Viewer2D.hpp"
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>
#include <QMouseEvent>
#include <QDebug>
#include "core/Product_Model.hpp"
#include "core/form.hpp"

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
                QPointF pt_modele(edges[i].get_x(), edges[i].get_y());
                QPointF pt_ecran = _view_transform.transformToView(pt_modele);
                chemin_carte.lineTo(pt_ecran);
            }
            chemin_carte.closeSubpath();
        }

        //Dessin de la carte
        painter.setPen(QPen(Qt::black, 0));//contour
        painter.setBrush(QBrush(QColor(34, 139, 34)));//rempissage
        painter.drawPath(chemin_carte);



        // DESSIN DES COMPOSANTS


        // Configuration du pinceau pour les pistes de cuivre
        painter.setPen(QPen(Qt::yellow, 0)); // On utilise le jaune sur fond vert pour bien voir
        painter.setBrush(Qt::yellow);

        // On récupère la matrice
        Matrix m = pcb->get_matrix();

        bool premiere_couche_cuivre_dessinee = false; // Pour éviter le plat de spaghettis

        // On parcourt toutes les couches
        for (Layer& layer : m.get_layersArr()) {

            // 🛑 FILTRE ROBUSTE : On utilise le type de la couche, pas son nom texte !
            // SIGNAL = Couche de cuivre (pistes et pastilles)
            if (layer.get_layer_type() != SIGNAL) {
                continue;
            }

            // On ne dessine que la toute première couche de cuivre trouvée (le Top)
            if (premiere_couche_cuivre_dessinee) {
                continue;
            }
            premiere_couche_cuivre_dessinee = true;

            qDebug() << "Affichage de la couche de cuivre :" << QString::fromStdString(layer.get_name());
            // On parcourt toutes les formes de la couche
            for (Form* f : layer.get_forms()) {

                //  UNE LIGNE
                Line* line = dynamic_cast<Line*>(f);
                if (line != nullptr) {
                    QPointF p1 = _view_transform.transformToView(QPointF(line->xs, line->ys));
                    QPointF p2 = _view_transform.transformToView(QPointF(line->xe, line->ye));
                    painter.drawLine(p1, p2);
                    continue;
                }

                // UNE PASTILLE
                Pad* pad = dynamic_cast<Pad*>(f);
                if (pad != nullptr) {
                    QPointF p = _view_transform.transformToView(QPointF(pad->x, pad->y));
                    // Dessine un petit cercle de 2 pixels autour du point
                    painter.drawEllipse(p, 2, 2);
                    continue;
                }

                // UN ARC
                ArcForm* arc = dynamic_cast<ArcForm*>(f);
                if (arc != nullptr) {

                    QPointF p1 = _view_transform.transformToView(QPointF(arc->xs, arc->ys));
                    QPointF p2 = _view_transform.transformToView(QPointF(arc->xe, arc->ye));
                    painter.drawLine(p1, p2);
                    continue;
                }
            }
        }
    }

    painter.end();
}

void Viewer2D::mouseMoveEvent(QMouseEvent * event)
{
    // Translating view need repaint
    if(_drag_active)
    {
        QPoint delta = event->pos() - _mouse_position;
        _view_transform.translate(delta);
        this->update();
    }

    _mouse_position = event->pos();
}

void Viewer2D::mousePressEvent(QMouseEvent * event)
{
    if(event->button() == Qt::LeftButton)
    {
        _drag_active = true;
        _mouse_position = event->pos();
    }
}

void Viewer2D::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        _drag_active = false;
    }
}

void Viewer2D::wheelEvent(QWheelEvent *event)
{
    if(event->buttons() == Qt::NoButton)
    {
        _view_transform.zoom(event->angleDelta().y());
        this->update();
    }
}