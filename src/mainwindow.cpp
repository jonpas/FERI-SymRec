#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this); 
    ui->graphicsView->installEventFilter(this);
    scene = ui->graphicsView->getScene();
}

MainWindow::~MainWindow() {
    delete ui;
}

// UI input getters
uint MainWindow::getSymbolVectors() {
    return ui->spinBoxSymbolVectors->text().toUInt();
}

uint MainWindow::getHiddenNeurons() {
    return ui->spinBoxHiddenNeurons->text().toUInt();
}

double MainWindow::getLearningRate() {
    return ui->doubleSpinBoxLearningRate->text().toDouble();
}

double MainWindow::getMomentumConst() {
    return ui->doubleSpinBoxMomentumConst->text().toDouble();
}

double MainWindow::getMinError() {
    return ui->doubleSpinBoxMinError->text().toDouble();
}

uint MainWindow::getEpochs() {
    return ui->spinBoxEpochs->text().toUInt();
}

void MainWindow::on_pushButtonLearn_clicked() {
    ui->statusBar->showMessage("");
    int symbolVectors = static_cast<int>(getSymbolVectors());
    int symbolPoints = symbolVectors + 1;

    scene->stopDrawing();
    QList<QPointF> points = scene->simplify(symbolPoints);

    if (points.size() == symbolPoints) {
        scene->drawPoints(points);
        scene->normalize(points);
    } else {
        ui->statusBar->showMessage("Error! Symbol vectorization failed (symbol possibly too small)!");
    }

}
