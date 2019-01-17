//******************************************************************************
// Copyright (c) 2018 Shili Xu
// File: main.cpp
// Author: Shili_Xu <shili_xu@qq.com>
// GitHub: https://github.com/ShiliXu1997
// License: GPLv3
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

