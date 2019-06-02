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
uint MainWindow::getSymbolPoints() const {
    return ui->spinBoxSymbolPoints->text().toUInt();
}

uint MainWindow::getHiddenNeurons() const {
    return ui->spinBoxHiddenNeurons->text().toUInt();
}

double MainWindow::getLearningRate() const {
    return ui->doubleSpinBoxLearningRate->text().toDouble();
}

double MainWindow::getMomentumConst() const {
    return ui->doubleSpinBoxMomentumConst->text().toDouble();
}

uint MainWindow::getEpochs() const {
    return ui->spinBoxEpochs->text().toUInt();
}

double MainWindow::getMinError() const {
    return ui->doubleSpinBoxMinError->text().toDouble();
}

void MainWindow::createNetwork() {
    network = new NeuralNetwork(getLearningRate(), getMomentumConst(), getEpochs(), getMinError());

    // Input: x, y flattened (2x amount of coordinates)
    network->addLayer(Layer(getSymbolPoints() * 2, getHiddenNeurons(), "sigmoid", {-0.5, 0.5}, {0.0, 0.0}));
    // Hidden: set by user
    network->addLayer(Layer(getHiddenNeurons(), static_cast<uint>(characters.size()), "sigmoid", {-0.5, 0.5}, {0.0, 0.0}));
    // Output: amount of different characters
}

bool MainWindow::drawingToPoints(QList<QPointF> &points) const {
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

DataRow MainWindow::pointsToData(QList<QPointF> points) const {
    DataRow pointsData;
    for (auto &point : points) {
        pointsData.append({point.x(), point.y()});
    }
    return pointsData;
}

Data MainWindow::symbolsToData() const {
    Data symbolsData;
    for (auto &symbol : symbols) {
        symbolsData.append(pointsToData(symbol));
    }
    return symbolsData;
}

Data MainWindow::charactersToData() const {
    Data charData;
    for (auto &character : characters) {
        charData.append(charCodeMap[character]);
    }
    return charData;
}

void MainWindow::encodeCharacters() {
    int charAmount = characters.toSet().size();

    for (int i = 0; i < characters.size(); ++i) {
        DataRow charRow;

        if (!charCodeMap.contains(characters[i])) {
            for (int j = 0; j < charAmount; ++j) {
                charRow.append((i == j) ? 1 : 0);
            }

            charCodeMap[characters[i]] = charRow;
        }
    }
}

// Slots
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
        double prediction = predictions.at(0);
        char character = characters.at(static_cast<int>(prediction));
        ui->statusBar->showMessage("Recognized: " + QString(character) + " (-> " + QString::number(prediction) + ")");
    }

    updateUi();
}

void MainWindow::on_pushButtonTrain_clicked() {
    if (symbols.size() > 0) {
        createNetwork();
        encodeCharacters();
        network->train(symbolsToData(), charactersToData());
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
