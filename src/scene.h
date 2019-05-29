#pragma once

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPathItem>

class Scene : public QGraphicsScene {
    Q_OBJECT
public:
    static const QRectF Boundary;

    Scene(QObject *parent = nullptr);
    ~Scene();

    void stopDrawing();

    // Vectorize drawn symbol to specified amount of vectors (all available if 0)
    QList<QPointF> vectorize(int vectors = 0) const;
    void drawVectorized(QList<QPointF> points);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent */*event*/);

    void clipToBounds(QPointF &point);

private:
    bool drawing = false;
    QPointF point;
    QGraphicsPathItem *pathItem = nullptr;

    QList<QGraphicsPathItem *> pathItems;

    void reset();
    void clearPathItems();
};
