#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this); 
    ui->graphicsView->installEventFilter(this);
    scene = ui->graphicsView->getScene();

    updateButtons();
}

MainWindow::~MainWindow() {
    delete network;
    delete ui;
}

void MainWindow::updateButtons() {
    ui->pushButtonLearn->setEnabled(network != nullptr);
    ui->pushButtonRecognize->setEnabled(network != nullptr && network->isTrained());

    if (network != nullptr) {
        ui->pushButtonCreateNetwork->setText("Re-Create Neural Network");
    }
}

void MainWindow::updateStatus() {
    QString savedSymbolsStr = QString::number(symbols.size());
    QString networkStr = (network != nullptr && network->isTrained())
            ? ("Trained (" + QString::number(network->getSymbolsTrained()) + " symbols)")
            : "Untrained";

    ui->statusNetwork->setPlainText(
        "Saved Symbols: " + savedSymbolsStr + "\n"
        "Network: " + networkStr + "\n"
    );
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

uint MainWindow::getEpochs() {
    return ui->spinBoxEpochs->text().toUInt();
}

double MainWindow::getMinError() {
    return ui->doubleSpinBoxMinError->text().toDouble();
}

// Slots
void MainWindow::on_pushButtonInput_clicked() {
    ui->statusBar->showMessage("");

    int symbolVectors = static_cast<int>(getSymbolVectors());
    int symbolPoints = symbolVectors + 1;

    scene->stopDrawing();
    QList<QPointF> points = scene->simplify(symbolPoints);

    if (points.size() == symbolPoints) {
        scene->drawPoints(points);
        scene->normalize(points);
    } else {
        ui->statusBar->showMessage("Error! Symbol normalization failed! Symbol possibly does not have enough points.");
    }

    updateStatus();
}

void MainWindow::on_pushButtonLearn_clicked() {
    ui->statusBar->showMessage("");

    network->train();
    updateButtons();
    updateStatus();
}

void MainWindow::on_pushButtonRecognize_clicked() {
    ui->statusBar->showMessage("");
}

void MainWindow::on_pushButtonCreateNetwork_clicked() {
    delete network;
    network = new NeuralNetwork(getHiddenNeurons(),
                                getLearningRate(),
                                getMomentumConst(),
                                getEpochs(),
                                getMinError());
    updateButtons();
    updateStatus();
}
