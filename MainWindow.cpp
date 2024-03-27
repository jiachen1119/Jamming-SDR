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
        // thread_ must define as a private variable in instantiation
        thread_ = std::make_unique<ProcessThread>(nullptr);
        thread_->start();
        threadIsRunning_ = true;
    } else
    {
        ui->pushButton->setText(QStringLiteral("Start Jamming"));
        thread_->stopTopBlock();
        threadIsRunning_ = false;
    }

}
