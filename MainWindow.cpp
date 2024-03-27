//
// Created by tang on 24-3-22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->pushButton->setText(QStringLiteral("Start Jamming"));
    connect(ui->pushButton,&QPushButton::clicked, this,&MainWindow::onClickPushbutton);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onClickPushbutton() {
    if (!threadIsRunning_){
        ui->pushButton->setText(QStringLiteral("Stop Jamming"));
        if (ui->comboBox_source->currentIndex() == 0){
            auto frontEndStruct = FrontEnd{ui->lineEdit_sampleFreq->text().toDouble(),
                                           ui->lineEdit_centerFreq->text().toDouble(),
                                           ui->lineEdit_gain->text().toDouble(),
                                           ui->lineEdit_IfGain->text().toDouble(),
                                           ui->lineEdit_RfGain->text().toDouble(),
                                           ui->lineEdit_Bandwidth->text().toDouble(),
                                           (ui->comboBox_agc->currentText() == "True")};
            // thread_ must define as a private variable in instantiation
            thread_ = std::make_unique<ProcessThread>(nullptr,frontEndStruct,typeChoose());
            thread_->start();
            threadIsRunning_ = true;
        }
    }
    else
    {
        ui->pushButton->setText(QStringLiteral("Start Jamming"));
        thread_->stopTopBlock();
        threadIsRunning_ = false;
    }

}

JammingType MainWindow::typeChoose() {
    if (ui->comboBox_type->currentText() == "Chirp Interference")
        return Chirp;
    else if (ui->comboBox_type->currentText() == "Square Interference")
        return Square;
    else if (ui->comboBox_type->currentText() == "Triangle Interference")
        return Triangle;
    else if (ui->comboBox_type->currentText() == "Saw Tooth Interference")
        return SawTooth;
    else
        return SingleTone;
}
