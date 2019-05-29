#include "view.h"

View::View(QWidget *parent) : QGraphicsView(parent) {
    scene = new Scene(this);
    scene->setSceneRect(Scene::Boundary); // Disable auto-scrolling
    setScene(scene);
}

View::~View() {
    delete scene;
}

Scene *View::getScene() {
    return scene;
}

void View::resizeEvent(QResizeEvent */*event*/) {
    fitInView(sceneRect()/*, Qt::KeepAspectRatio*/);
}
