#include <QPainterPath>
#include "Viewer2D.hpp"
#include <QPainter>
#include <QPaintEvent>
#include "core/Product_Model.hpp"
#include "core/Feature.hpp"
#include "core/Form.hpp"
#include "core/Layer.hpp"

Viewer2D::Viewer2D(std::shared_ptr<ApplicationModel> model, QWidget *parent) : QWidget(parent),
    _drag_active(false),
    _mouse_position({0,0})
{
    _model = model;
    this->setMouseTracking(true);
}

Viewer2D::~Viewer2D() {}

void Viewer2D::setLayerVisible(const std::string& layerName, bool visible) {
    if (visible) {
        _hidden_layers.erase(layerName); // On enlève des couches cachées
    } else {
        _hidden_layers.insert(layerName); // On la cache
    }
    this->update();
}

void Viewer2D::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);

    //FOND DE LA FENETRE EN BLANCHE
    painter.fillRect(event->rect(), Qt::white);

    if (_model->hasProductModel()) {
        Product_Model* pcb = _model->getProductModel();


        // DESSIN DU CONTOUR DE LA CARTE EN VERT

        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(30, 120, 30));

        Surface pcb_surface = pcb->get_surface();
        QPainterPath boardPath;

        for (Outline& outline : pcb_surface.get_outlineArr()) {
            std::vector<Edge*> edges = outline.get_edgeArr();
            if (edges.empty()) continue;

            QPainterPath subPath;
            QPointF startPt = _view_transform.transformToView(QPointF(edges[0]->get_x(), edges[0]->get_y()));
            subPath.moveTo(startPt);

            for (size_t i = 1; i < edges.size(); ++i) {
                QPointF endPt = _view_transform.transformToView(QPointF(edges[i]->get_x(), edges[i]->get_y()));
                subPath.lineTo(endPt);
            }
            subPath.closeSubpath();
            boardPath.addPath(subPath);
        }
        painter.drawPath(boardPath);



        // DESSIN DES PISTES ET COMPOSANTS EN JAUNE

        painter.setPen(QPen(Qt::yellow, 0));
        painter.setBrush(Qt::yellow);

        for (Layer& layer : pcb->get_layers()) {

            //on dessine pas si c'est pas dans la liste cahée
            if (_hidden_layers.find(layer.get_layerName()) != _hidden_layers.end()) {
                continue;
            }
            // Filtrage des couches pleines

            layer_type type = pcb->get_matrix().get_layer_type(layer.get_layerName());

            // On ignore le vernis, les plans de masse et la documentation
            if (type == SOLDER_MASK || type == POWER_GROUND || type == DOCUMENT) {
                continue;
            }

            std::string colorStr = pcb->get_matrix().get_layer_color(layer.get_layerName());
            QColor layerColor(Qt::yellow); // Secours

            if (colorStr.length() >= 6) {
                try {
                    // conversion pour Qt (0 à 255)
                    int r = std::stoi(colorStr.substr(0, 2)) * 255 / 99;
                    int g = std::stoi(colorStr.substr(2, 2)) * 255 / 99;
                    int b = std::stoi(colorStr.substr(4, 2)) * 255 / 99;
                    layerColor = QColor(r, g, b);
                } catch(...) {}
            }
            layerColor.setAlpha(180);

            painter.setPen(QPen(layerColor, 0));
            painter.setBrush(layerColor);

            Feature feature = layer.get_feature();

            //  Dessin des Lignes (Pistes) et des Pads (Composants)
            for (Form* f : feature.get_forms()) {

                Line* line = dynamic_cast<Line*>(f);
                if (line != nullptr) {
                    QPointF p1 = _view_transform.transformToView(QPointF(line->get_start().get_x(), line->get_start().get_y()));
                    QPointF p2 = _view_transform.transformToView(QPointF(line->get_end().get_x(), line->get_end().get_y()));
                    painter.drawLine(p1, p2);
                    continue;
                }

                Pad* pad = dynamic_cast<Pad*>(f);
                if (pad != nullptr) {
                    QPointF p = _view_transform.transformToView(QPointF(pad->get_position().get_x(), pad->get_position().get_y()));
                    // Dessine un petit cercle jaune pour marquer composant
                    painter.drawEllipse(p, 2, 2);
                    continue;
                }
            }

            // Dessin des Surfaces
            for (Surface* surface : feature.get_surfaces()) {
                QPainterPath featPath;
                for (Outline& outline : surface->get_outlineArr()) {
                    std::vector<Edge*> edges = outline.get_edgeArr();
                    if (edges.empty()) continue;

                    QPainterPath subPath;
                    QPointF startPt = _view_transform.transformToView(QPointF(edges[0]->get_x(), edges[0]->get_y()));
                    subPath.moveTo(startPt);

                    for (size_t i = 1; i < edges.size(); ++i) {
                        QPointF endPt = _view_transform.transformToView(QPointF(edges[i]->get_x(), edges[i]->get_y()));
                        subPath.lineTo(endPt);
                    }
                    subPath.closeSubpath();
                    featPath.addPath(subPath);
                }
                painter.drawPath(featPath);
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
        _mouse_position = event->pos();
        this->update();
    }


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
        _view_transform.zoom(event->angleDelta().y(), event->position());
        this->update();
    }
}