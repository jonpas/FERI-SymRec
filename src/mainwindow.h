#pragma once

#include <QMainWindow>

#include "scene.h"
#include "symbol.h"
#include "neuralnetwork.h"

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

    QList<Symbol> symbols;

    NeuralNetwork *network = nullptr;

    void updateUi();

    // UI input getters
    uint getSymbolPoints();
    uint getHiddenNeurons();
    double getLearningRate();
    double getMomentumConst();
    uint getEpochs();
    double getMinError();

    void createNetwork();
    bool drawingToPoints(QList<QPointF> &points);

private slots:
    void on_pushButtonInput_clicked();
    void on_pushButtonTrain_clicked();
    void on_pushButtonRecognize_clicked();
    void on_pushButtonResetNetwork_clicked();
};
