#pragma once

#include <QMainWindow>

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

    // UI input getters
    uint getSymbolVectors();
    uint getHiddenNeurons();
    double getLearningRate();
    double getMomentumConst();
    double getMinError();
    uint getEpochs();
};
