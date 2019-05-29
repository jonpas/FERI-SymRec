#pragma once

#include <QObject>
#include <QGraphicsView>

#include "scene.h"

class View : public QGraphicsView {
    Q_OBJECT
public:
    View(QWidget *parent = nullptr);
    ~View() override;

private:
    Scene *scene;

    void resizeEvent(QResizeEvent */*event*/) override;
};
