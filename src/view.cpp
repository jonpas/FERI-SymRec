#include "view.h"

View::View(QWidget *parent) : QGraphicsView(parent) {
    scene = new Scene(this);
    scene->setSceneRect(0, 0, 300, 300); // Disable auto-scrolling
    setScene(scene);
}

View::~View() {
    delete scene;
}

void View::resizeEvent(QResizeEvent */*event*/) {
    fitInView(sceneRect()/*, Qt::KeepAspectRatio*/);
}
