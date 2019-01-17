//******************************************************************************
// Copyright (c) 2018 Shili Xu
// File: coresolve.cpp
// Author: Shili_Xu <shili_xu@qq.com>
// GitHub: https://github.com/ShiliXu1997
// License: GPLv3
//******************************************************************************

#include "coresolve.h"
using namespace std;
using namespace cv;

unsigned value = 0;

bool cmp(const Rect &a, const Rect &b)
{
    unsigned sa = max(a.width, a.height), sb = max(b.width, b.height);
    return sa >= sb;
}

void bubble_sort(vector<Rect> v, bool (*cmp)(const Rect &, const Rect &))
{
    unsigned n = v.size();
    for (unsigned i = 0; i != n - 1; ++i) {
        unsigned ed = n - i - 1;
        for (unsigned j = 0; j != ed; ++j)
            if (cmp(v[j + 1], v[j])) swap(v[j], v[j + 1]);
    }
}

int sgn(double x)
{
    if (fabs(x) < EPS) return 0;
    return x > 0;
}

unsigned dist(Point2i a, Point2i b, unsigned sz)
{
    double dx = abs(a.x - b.x), dy = abs(a.y - b.y);
    double d = sqrt(dx * dx + dy * dy);
    return sgn(d) <= 0 ? 0 : static_cast<unsigned>(min(abs(d - sz), 5.0 * sz) / (5 * sz) * 200);
}

void get_mask(Mat &src, Mat &mask)
{
    cvtColor(src, src, COLOR_BGR2HSV);
    vector<Mat> from;
    split(src, from);
    for (unsigned r = 0; r != src.rows; ++r) {
        const uchar *h = from[0].ptr<const uchar>(r);
        const uchar *s = from[1].ptr<const uchar>(r);
        const uchar *v = from[2].ptr<const uchar>(r);
        uchar *cur = mask.ptr<uchar>(r);
        for (unsigned c = 0; c != src.cols; ++c) {
            if (5 <= h[c] && h[c] <= 115 && 40 <= s[c] && s[c] <= 115 && 170 <= v[c] && v[c] <= 245)
                cur[c] = 255;
            else
                cur[c] = 0;
        }
    }
    // 开运算消除干扰
    morphologyEx(mask, mask, MORPH_OPEN, getStructuringElement(MORPH_CROSS, Size(3, 3)));
}

void set_mask(Mat &dest, Mat &mask)
{
    vector<vector<Point2i> > contours;
    vector<Vec4i> hierarchy;

    // 寻找轮廓线
    findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    vector<Rect> boundRect(contours.size());
    vector<Point2i> centers(contours.size());

    if (1 <= contours.size() && contours.size() <= 40) {
        for (unsigned i = 0; i != contours.size() && i != 2; ++i) {
            Rect &now = boundRect[i];
            now = boundingRect((Mat)contours[i]);
        }
        bubble_sort(boundRect, cmp);
        unsigned sz = 0;
        for (unsigned i = 0; i != contours.size() && i != 2; ++i) {
            Rect &now = boundRect[i];
            int x = now.x, y = now.y, w = now.width, h = now.height;
            // 绘制轮廓线和外接矩形
            drawContours(dest, contours, i, Scalar(0, 0, 255), 2);
            rectangle(dest, Point2i(x, y), Point(x + w, y + h), Scalar(0, 255, 0), 2);
            centers[i] = Point2i(x + w / 2, y + h / 2);
            circle(dest, centers[i], 3, Scalar(255, 0, 0), 2);
            sz += w + h;
        }
        if (centers.size() == 1)
            value = 0;
        if (centers.size() == 2)
            value = dist(centers[0], centers[1], sz / 4);
        cout << "Value: " << value << endl;
    }
}
