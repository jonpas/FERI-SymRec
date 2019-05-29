#include "scene.h"

#include <cmath>

const QRectF Scene::Boundary = {0, 0, 300, 300};
const double Scene::PenWidthDraw = 2;
const double Scene::PenWidthPoints = 4;
const double Scene::PenWidthPointsHalf = PenWidthPoints / 2;

Scene::Scene(QObject *parent) : QGraphicsScene(parent) {
}

Scene::~Scene() {
    clearPathItems();
}

void Scene::stopDrawing() {
    drawing = false;
}

QList<QPointF> Scene::simplify(int vectors) const {
    QList<QPointF> points;

    for (auto &pathItem : pathItems) {
        QPainterPath path = pathItem->path();
        for (int i = 0; i < path.elementCount(); i++) {
            QPointF point = path.elementAt(i); // Get the value of the point at index i
            points.append(point);
        }
    }

    if (vectors > 0) {
        // Average until we have wanted amount
        while (points.size() > vectors) {
            // All but first and last
            for (int i = 1; i < points.size() - 1; ++i) {
                // Double-check if not last in case of odd size
                if (points.at(i + 1) == points.last()) break;

                points[i].setX((points[i].x() + points[i + 1].x()) / 2.0);
                points[i].setY((points[i].y() + points[i + 1].y()) / 2.0);
                points.removeAt(i + 1);

                // Exit if we have wanted amount
                if (points.size() <= vectors) break;
            }
        }
    }

    return points;
}

void Scene::normalize(QList<QPointF> &points) const {
    // Find minimal and maximum values in X and Y
    double minX = points.first().x();
    double minY = points.first().y();
    double maxX = minX;
    double maxY = minY;
    for (int i = 1; i < points.size(); ++i) {
        double curX = points.at(i).x();
        double curY = points.at(i).y();

        if (curX < minX) minX = curX;
        else if (curX > maxX) maxX = curX;

        if (curY < minY) minY = curY;
        else if (curY > maxY) maxY = curY;
    }

    // Calculate diagonal length
    double diagonalLength = sqrt((maxX - minX) * (maxX - minX) + (maxY - minY) * (maxY - minY));

    // Normalize (shift and scale)
    for (auto &point : points) {
        point.setX((point.x() - minX) / diagonalLength);
        point.setY((point.y() - minY) / diagonalLength);
    }
}

void Scene::drawPoints(QList<QPointF> points) {
    QPointF previous;
    for (auto &point : points) {
        if (point != points.first()) {
            addLine(previous.x(), previous.y(), point.x(), point.y(), QPen(Qt::red, PenWidthPointsHalf));
        }
        previous = point;

        addRect(point.x() - PenWidthPointsHalf, point.y() - PenWidthPointsHalf, PenWidthPoints, PenWidthPoints, QPen(Qt::blue));
    }
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (!drawing) {
        drawing = true;
        reset();
    }

    point = event->scenePos();

    pathItem = new QGraphicsPathItem();
    pathItems.append(pathItem);
    pathItem->setPen(QPen(Qt::black, PenWidthDraw, Qt::SolidLine));

    QPainterPath path;
    path.moveTo(point);
    pathItem->setPath(path);

    addItem(pathItem);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (pathItem != nullptr) {
        point = event->scenePos();
        if (!Boundary.contains(point)) {
            clipToBounds(point);
        }

        QPainterPath path = pathItem->path();
        path.lineTo(point);
        pathItem->setPath(path);
    }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent */*event*/) {
    pathItem = nullptr;
}

void Scene::clipToBounds(QPointF &point) {
    if (point.x() < Boundary.x()) {
        point.setX(Boundary.x());
    } else if (point.x() > Boundary.width()) {
        point.setX(Boundary.width());
    }

    if (point.y() < Boundary.y()) {
        point.setY(Boundary.y());
    } else if (point.y() > Boundary.height()) {
        point.setY(Boundary.height());
    }
}

void Scene::reset() {
    clearPathItems();
    pathItems.clear();
    clear();
}

void Scene::clearPathItems() {
    for (auto &pathItem : pathItems) {
        delete pathItem;
    }
}
