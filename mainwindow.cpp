#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    capture = new VideoCapture(0);
    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(get_frame()));
    timer->start(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::get_frame()
{
    Mat src, dest, mask;
    *capture >> src;
    if (!src.empty()) {
        dest = src.clone();
        mask = Mat::zeros(src.rows, src.cols, CV_8UC1);
        get_mask(src, mask);
        set_mask(dest, mask);
        cvtColor(dest, dest, COLOR_BGR2RGB);
        QImage image(dest.data, dest.cols, dest.rows, QImage::Format_RGB888);
        ui->label->setPixmap(QPixmap::fromImage(image));
        ui->lcdNumber->display(static_cast<int>(value));
        ui->verticalSlider->setValue(static_cast<int>(value));
    }
}
