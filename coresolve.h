//******************************************************************************
// Copyright (c) 2018 Shili Xu
// File: coresolve.h
// Author: Shili_Xu <shili_xu@qq.com>
// GitHub: https://github.com/ShiliXu1997
// License: GPLv3
//******************************************************************************

#ifndef CORESOLVE_H
#define CORESOLVE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include <opencv2/opencv.hpp>

#define EPS 1e-8

extern unsigned value;

bool cmp(const cv::Rect &a, const cv::Rect &b);
void bubble_sort(std::vector<cv::Rect> v, bool (*cmp)(const cv::Rect &, const cv::Rect &));

int sgn(double x);
unsigned dist(cv::Point2i a, cv::Point2i b, unsigned sz);

void get_mask(cv::Mat &src, cv::Mat &mask);
void set_mask(cv::Mat &dest, cv::Mat &mask);

#endif // CORESOLVE_H
