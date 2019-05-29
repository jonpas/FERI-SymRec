#include "view.h"

View::View(QWidget *parent) : QGraphicsView(parent) {
    _scene = new Scene(this);
    _scene->setSceneRect(Scene::Boundary); // Disable auto-scrolling
    setScene(_scene);
}

View::~View() {
    delete _scene;
}

Scene *View::scene() const {
    return _scene;
}

void View::resizeEvent(QResizeEvent */*event*/) {
    fitInView(sceneRect()/*, Qt::KeepAspectRatio*/);
}
