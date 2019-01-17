//******************************************************************************
// Project Name: GestureSlider
// File Name: main.cpp
// Author: Shili_Xu
// E-Mail: shili_xu@qq.com
// Created Time: Sat 08 Dec 2018 05:28:37 PM CST
//******************************************************************************

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

