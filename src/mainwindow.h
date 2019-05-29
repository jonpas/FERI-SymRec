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

    void populateUi();

    uint16_t getHiddenNeurons();
    double getLearningRate();
    double getMomentumConst();
    double getMinError();
    uint16_t getEpochs();
};
