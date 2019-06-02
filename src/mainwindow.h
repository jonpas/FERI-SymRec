#pragma once

#include <QMainWindow>
#include <QMap>

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
    QMap<char, DataRow> charCodeMap;

    NeuralNetwork *network = nullptr;

    void updateUi();

    // UI input getters
    uint getSymbolPoints() const;
    uint getHiddenNeurons() const;
    double getLearningRate() const;
    double getMomentumConst() const;
    uint getEpochs() const;
    double getMinError() const;

    void createNetwork();
    bool drawingToPoints(QList<QPointF> &points) const;
    DataRow pointsToData(QList<QPointF> points) const;
    Data symbolsToData() const;
    Data charactersToData() const;
    void encodeCharacters();

private slots:
    void on_pushButtonInputPredict_clicked();
    void on_pushButtonTrain_clicked();
    void on_pushButtonReset_clicked();
};
