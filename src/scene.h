#pragma once

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPathItem>

class Scene : public QGraphicsScene {
    Q_OBJECT
public:
    static const QRectF Boundary;
    static const double PenWidthDraw;
    static const double PenWidthPoints;
    static const double PenWidthPointsHalf;

    Scene(QObject *parent = nullptr);
    ~Scene();

    void stopDrawing();

    // Simplify drawn symbol to specified amount of points (all available if 0)
    QList<QPointF> simplify(int points = 0) const;
    // Normalize points to symbol bounding box (0, 1)
    void normalize(QList<QPointF> &points) const;

    void drawPoints(QList<QPointF> points);

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
