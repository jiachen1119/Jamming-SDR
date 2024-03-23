//
// Created by tang on 24-3-22.
//

#ifndef JAMMING_SDR_MAINWINDOW_H
#define JAMMING_SDR_MAINWINDOW_H

#include <QMainWindow>
#include "ProcessThread.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

public slots:
    void onClickPushbutton();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<ProcessThread> thread_;
};


#endif //JAMMING_SDR_MAINWINDOW_H
