#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QValidator>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    populateUi();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::populateUi() {
    // Line Edit validations
    const QIntValidator *validatorNaturalUInt16 = new QIntValidator(1, std::numeric_limits<uint16_t>::max(), this);
    const QDoubleValidator *validatorNormalizedDouble3D = new QDoubleValidator(0.0, 1.0, 3, this);

    ui->lineEditHiddenNeurons->setValidator(validatorNaturalUInt16);
    ui->lineEditLearningRate->setValidator(validatorNormalizedDouble3D);
    ui->lineEditMomentumConst->setValidator(validatorNormalizedDouble3D);
    ui->lineEditEpochs->setValidator(validatorNaturalUInt16);
    ui->lineEditMinError->setValidator(validatorNormalizedDouble3D);
}

uint16_t MainWindow::getHiddenNeurons() {
    uint16_t size = static_cast<uint16_t>(ui->lineEditHiddenNeurons->text().toUInt());
    if (size < 1) size = 1; // Manual low-bound validation (validator doesn't handle it)
    ui->lineEditHiddenNeurons->setText(QString::number(size));
    return size;
}

double MainWindow::getLearningRate() {
    return ui->lineEditLearningRate->text().toDouble();
}

double MainWindow::getMomentumConst() {
    return ui->lineEditMomentumConst->text().toDouble();
}

double MainWindow::getMinError() {
    return ui->lineEditMinError->text().toDouble();
}

uint16_t MainWindow::getEpochs() {
    uint16_t size = static_cast<uint16_t>(ui->lineEditEpochs->text().toUInt());
    if (size < 1) size = 1; // Manual low-bound validation (validator doesn't handle it)
    ui->lineEditEpochs->setText(QString::number(size));
    return size;
}
