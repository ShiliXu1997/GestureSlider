#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QTimer>

#include <opencv2/opencv.hpp>
using namespace cv;

#include "coresolve.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    VideoCapture *capture;
    QTimer *timer;

private slots:
    void get_frame();
};

#endif // MAINWINDOW_H
