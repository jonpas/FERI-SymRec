#include "scene.h"

Scene::Scene(QObject *parent) : QGraphicsScene(parent) {
}

Scene::~Scene() {
    // TODO delete pathItems
}

#include <QDebug>
void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    //qDebug() << "mouse press";
    point = event->scenePos();

    pathItem = new QGraphicsPathItem();
    pathItem->setPen(QPen(Qt::black, 3, Qt::SolidLine));

    QPainterPath path;
    path.moveTo(point);
    pathItem->setPath(path);

    this->addItem(pathItem);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (pathItem != nullptr) {
        point = event->scenePos();

        QPainterPath path = pathItem->path();
        path.lineTo(point);
        pathItem->setPath(path);
    }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    //qDebug() << "mouse RELEASE" << pathItem->;
    pathItem = nullptr;
}
