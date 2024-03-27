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
    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->pushButton,&QPushButton::clicked, this,&MainWindow::onClickPushbutton);
    connect(ui->comboBox_type, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, [=](int index) {
                if (index == 1)
                    ui->stackedWidget->setCurrentIndex(1);
                else
                    ui->stackedWidget->setCurrentIndex(0);
            });

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
            if (ui->comboBox_type->currentText() == "Chirp Interference"){
                ChirpStruct in_struct = {ui->lineEdit_chirpSamplingFreq->text().toDouble(),
                                         ui->lineEdit_chirpMin->text().toDouble(),
                                         ui->lineEdit_chirpMax->text().toDouble(),
                                         ui->lineEdit_chirpPeriod->text().toDouble(),
                                         ui->comboBox_chirpType->currentText()
                };
                thread_ = std::make_unique<ProcessThread>(nullptr,frontEndStruct,in_struct);
            }
            else if (ui->comboBox_type->currentText() == "Square Interference"){
                SquareStruct in_struct =  {ui->lineEdit_sampleFreq->text().toDouble(),
                                            ui->lineEdit_WaveFreq->text().toDouble(),
                                            ui->lineEdit_Amplitude->text().toDouble()};
                thread_ = std::make_unique<ProcessThread>(nullptr,frontEndStruct,in_struct);
            }
            else if (ui->comboBox_type->currentText() == "Triangle Interference"){
                TriangeStruct in_struct =  {ui->lineEdit_sampleFreq->text().toDouble(),
                                            ui->lineEdit_WaveFreq->text().toDouble(),
                                            ui->lineEdit_Amplitude->text().toDouble()};
                thread_ = std::make_unique<ProcessThread>(nullptr,frontEndStruct,in_struct);
            }
            else if (ui->comboBox_type->currentText() == "Saw Tooth Interference"){
                SawToothStruct in_struct =  {ui->lineEdit_sampleFreq->text().toDouble(),
                                            ui->lineEdit_WaveFreq->text().toDouble(),
                                            ui->lineEdit_Amplitude->text().toDouble()};
                thread_ = std::make_unique<ProcessThread>(nullptr,frontEndStruct,in_struct);
            }
            else{
                SingleToneStruct in_struct =  {ui->lineEdit_sampleFreq->text().toDouble(),
                            ui->lineEdit_WaveFreq->text().toDouble(),
                            ui->lineEdit_Amplitude->text().toDouble()};
                thread_ = std::make_unique<ProcessThread>(nullptr,frontEndStruct,in_struct);
            }
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
