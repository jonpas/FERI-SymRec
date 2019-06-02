#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this); 
    ui->graphicsView->installEventFilter(this);
    scene = ui->graphicsView->scene();

    updateUi();
}

MainWindow::~MainWindow() {
    delete network;
    delete ui;
}

void MainWindow::updateUi() {
    // Buttons
    ui->pushButtonInputPredict->setText(network == nullptr ? "Input" : "Predict");
    ui->pushButtonTrain->setEnabled(network == nullptr);

    // Status
    QString savedSymbolsStr = QString::number(symbols.size());
    QString networkStr = "Untrained";
    if (network != nullptr) {
        networkStr = network->trained() ? "Trained" : "Failed Training";
    }

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
    network = new NeuralNetwork(getLearningRate(), getMomentumConst(), getEpochs(), getMinError());

    // Input: x, y flattened (2x amount of coordinates)
    network->addLayer(Layer(getSymbolPoints() * 2, getHiddenNeurons(), "sigmoid"));
    // Hidden: set by user
    network->addLayer(Layer(getHiddenNeurons(), static_cast<uint>(characters.size()), "sigmoid"));
    // Output: amount of different characters
}

bool MainWindow::drawingToPoints(QList<QPointF> &points) {
    int symbolPoints = static_cast<int>(getSymbolPoints());

    scene->stopDrawing();
    points = scene->simplify(symbolPoints);

    if (points.size() == symbolPoints) {
        scene->drawPoints(points);
        scene->normalize(points);
        return true;
    }
    return false;
}

DataRow MainWindow::pointsToData(QList<QPointF> points) {
    DataRow pointsData;
    for (auto &point : points) {
        pointsData.append({point.x(), point.y()});
    }
    return pointsData;
}

Data MainWindow::symbolsToData(QList<QList<QPointF>> symbols) {
    Data symbolsData;
    for (auto &symbol : symbols) {
        symbolsData.append(pointsToData(symbol));
    }
    return symbolsData;
}

Data MainWindow::charactersToData(QList<char> characters) {
    Data charactersData;
    for (auto &character : characters) {
        int characterAscii = static_cast<int>(character);
        charactersData.append({static_cast<double>(characterAscii)});
    }
    return charactersData;
}

// Slots
#include <QDebug>
void MainWindow::on_pushButtonInputPredict_clicked() {
    QList<QPointF> points;
    bool ok = drawingToPoints(points);

    if (!ok) {
        ui->statusBar->showMessage("Error! Symbol conversion failed! Symbol possibly does not have enough points.");
        return;
    }

    if (network == nullptr) {
        // Input
        QString text = QInputDialog::getText(this, "Character Name", "Which character did you draw?", QLineEdit::Normal, nullptr, &ok);
        if (ok && !text.isEmpty()) {
            char character = text.at(0).toLatin1();
            symbols.append(points);
            characters.append(character);

            ui->statusBar->showMessage("Added symbol '" + QString(character) + "'");
        }
    } else {
        // Predict
        DataRow predictions = network->predict({pointsToData(points)});
        qDebug() << "predictions" << predictions;
        double prediction = predictions.at(0);
        char character = characters.at(static_cast<int>(prediction));
        ui->statusBar->showMessage("Recognized: " + QString(character) + " (-> " + QString::number(prediction) + ")");
    }

    updateUi();
}

void MainWindow::on_pushButtonTrain_clicked() {
    if (symbols.size() > 0) {
        createNetwork();
        //network->train(symbolsToData(symbols), charactersToData(characters));
        network->train(symbolsToData(symbols), {{1}, {2}});
        ui->statusBar->showMessage("Neural network successfully trained with " + QString::number(symbols.size()) + " symbols");
    } else {
        ui->statusBar->showMessage("Error! Neural network training failed! No symbols given.");
    }

    updateUi();
}

void MainWindow::on_pushButtonReset_clicked() {
    symbols.clear();
    characters.clear();

    delete network;
    network = nullptr;

    scene->reset();

    ui->statusBar->showMessage("Neural network reset!");

    updateUi();
}
