#pragma once

#include <QMainWindow>

#include "scene.h"
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

    QList<QList<QPointF>> symbols;
    QList<char> characters;

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
    DataRow pointsToData(QList<QPointF> points);
    Data symbolsToData(QList<QList<QPointF>> symbols);
    Data charactersToData(QList<char> characters);

private slots:
    void on_pushButtonInputPredict_clicked();
    void on_pushButtonTrainReset_clicked();
};
