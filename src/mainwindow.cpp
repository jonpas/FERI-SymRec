#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this); 
    ui->graphicsView->installEventFilter(this);
    scene = ui->graphicsView->scene();

    createNetwork();

    updateUi();
}

MainWindow::~MainWindow() {
    delete network;
    delete ui;
}

void MainWindow::updateUi() {
    // Buttons
    ui->pushButtonInput->setEnabled(network != nullptr);
    ui->pushButtonTrain->setEnabled(network != nullptr && !network->trained());
    ui->pushButtonRecognize->setEnabled(network != nullptr && network->trained());

    // Status
    QString savedSymbolsStr = QString::number(symbols.size());
    QString networkStr = (network != nullptr && network->trained())
            ? ("Trained (" + QString::number(network->symbolsTrained()) + " symbols)")
            : "Untrained";

    ui->statusNetwork->setPlainText(
        "Saved Symbols: " + savedSymbolsStr + "\n"
        "Network: " + networkStr + "\n"
    );
}

// UI input getters
uint MainWindow::getSymbolPoints() {
    return ui->spinBoxSymbolPoints->text().toUInt();
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

void MainWindow::createNetwork() {
    network = new NeuralNetwork(getSymbolPoints(),
                                getHiddenNeurons(),
                                getLearningRate(),
                                getMomentumConst(),
                                getEpochs(),
                                getMinError());
}

bool MainWindow::drawingToPoints(QList<QPointF> &points) {
    int symbolPoints = static_cast<int>(network->symbolPoints());

    scene->stopDrawing();
    points = scene->simplify(symbolPoints);

    if (points.size() == symbolPoints) {
        scene->drawPoints(points);
        scene->normalize(points);
        return true;
    }
    return false;
}

// Slots
void MainWindow::on_pushButtonInput_clicked() {
    QList<QPointF> points;
    bool ok = drawingToPoints(points);

    if (ok) {
        QString text = QInputDialog::getText(this, "Character Name", "Which character did you draw?", QLineEdit::Normal, nullptr, &ok);
        if (ok && !text.isEmpty()) {
            char character = text.at(0).toLatin1();
            symbols.append({points, character});

            ui->statusBar->showMessage("Added symbol '" + QString(character) + "'");
        }
    } else {
        ui->statusBar->showMessage("Error! Symbol conversion failed! Symbol possibly does not have enough points.");
    }

    updateUi();
}

void MainWindow::on_pushButtonTrain_clicked() {
    if (symbols.size() > 0) {
        network->train(symbols);
        ui->statusBar->showMessage("Neural network successfully trained with " + QString::number(network->symbolsTrained()) + " symbols");
    } else {
        ui->statusBar->showMessage("Error! Neural network training failed! No symbols inputted.");
    }

    updateUi();
}

void MainWindow::on_pushButtonRecognize_clicked() {
    QList<QPointF> points;
    bool ok = drawingToPoints(points);

    if (ok) {
        char character = network->recognize(points);
        ui->statusBar->showMessage("Recognized: " + QString(character));
    } else {
        ui->statusBar->showMessage("Error! Symbol conversion failed! Symbol possibly does not have enough points.");
    }
}

void MainWindow::on_pushButtonResetNetwork_clicked() {
    delete network;
    createNetwork();

    ui->statusBar->showMessage("Neural network reset!");

    updateUi();
}
