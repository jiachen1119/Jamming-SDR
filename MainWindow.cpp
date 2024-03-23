//
// Created by tang on 24-3-22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // thread_ must define as a private variable in instantiation
    thread_ = std::make_unique<ProcessThread>(nullptr);

    ui->pushButton->setText(QStringLiteral("Start Jamming"));
    connect(ui->pushButton,&QPushButton::clicked, this,&MainWindow::onClickPushbutton);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onClickPushbutton() {
    if (!thread_->isRunning()){
        ui->pushButton->setText(QStringLiteral("Stop Jamming"));
        thread_->startTopBlock();
    } else
    {
        ui->pushButton->setText(QStringLiteral("Start Jamming"));
        thread_->stopTopBlock();
    }

}
