#pragma once

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPathItem>

class Scene : public QGraphicsScene {
    Q_OBJECT
public:
    Scene(QObject *parent = nullptr);
    ~Scene();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QPointF point;
    QGraphicsPathItem *pathItem = nullptr;
};
