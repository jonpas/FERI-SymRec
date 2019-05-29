#pragma once

#include <QMainWindow>

#include "scene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Scene *scene;

    // UI input getters
    uint getSymbolVectors();
    uint getHiddenNeurons();
    double getLearningRate();
    double getMomentumConst();
    double getMinError();
    uint getEpochs();

private slots:
    void on_pushButtonLearn_clicked();
};
