#pragma once

#include <QMainWindow>

#include "scene.h"
#include "neuralnetwork.h"

namespace Ui {
class MainWindow;
}

using SymbolList = QList<QList<QPointF>>;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Scene *scene;

    SymbolList symbols;

    NeuralNetwork *network = nullptr;

    void updateButtons();
    void updateStatus();

    // UI input getters
    uint getSymbolVectors();
    uint getHiddenNeurons();
    double getLearningRate();
    double getMomentumConst();
    uint getEpochs();
    double getMinError();

private slots:
    void on_pushButtonLearn_clicked();
    void on_pushButtonInput_clicked();
    void on_pushButtonRecognize_clicked();
    void on_pushButtonCreateNetwork_clicked();
};
