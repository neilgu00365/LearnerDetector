//
// Created by 贵阳 on 2016/12/4.
//

#include "utils.h"

void s_drawLines(Mat &img, const vector<Point2f> &firstPts,
                               const vector<Point2f> &secondPts,
                               const Scalar &color, int thickness) {
    for(int i = 0; i < firstPts.size(); i++) {
        if(secondPts[i] == PT_ERROR)
            continue;
        line(img, firstPts[i], secondPts[i], color, thickness);
    }
}

void s_drawCircles(Mat &img, const vector<Point2f> &pts, const Scalar &color, int radius) {
    for(int i = 0; i < pts.size(); i++) {
        circle(img, pts[i], radius, color);
    }
}
void s_drawRect(Mat &img, const Rect_<float> &rect, const Scalar &color, int thickness) {
    rectangle(img, rect, color, thickness);
}

void onMouse(int event, int x, int y, int flags, void* param) {
    pair<pair<void*, void*>, bool*> pp = *(pair<pair<void*, void*>, bool*>*)(param);
    pair<void*, void*> p = pp.first;

    bool &selectValid = *((bool*)pp.second);
    Rect &rect = *((Rect*)p.first);

    static Point2i pre_pos = {0, 0}, cur_pos = {0, 0};

    if(event == CV_EVENT_LBUTTONDOWN && flags != CV_EVENT_FLAG_LBUTTON) {
        selectValid = false;
        pre_pos = Point2i(x, y);
    } else if(flags == CV_EVENT_FLAG_LBUTTON && event == CV_EVENT_LBUTTONDOWN) {
        cur_pos = Point2i(x, y);
        int x0 = min(pre_pos.x, cur_pos.x);
        int y0 = min(pre_pos.y, cur_pos.y);
        int x1 = max(pre_pos.x, cur_pos.x) - x0;
        int y1 = max(pre_pos.y, cur_pos.y) - y0;
        rect = Rect(x0, y0, x1, y1);
        selectValid = false;
        cout << "Mouse Move Here !" << endl;
    } else if(event == CV_EVENT_LBUTTONUP) {
        cur_pos = Point2i(x, y);
        int x0 = min(pre_pos.x, cur_pos.x);
        int y0 = min(pre_pos.y, cur_pos.y);
        int x1 = max(pre_pos.x, cur_pos.x) - x0;
        int y1 = max(pre_pos.y, cur_pos.y) - y0;
        rect = Rect(x0, y0, x1, y1);
        selectValid = true;
        cout << "Mouse Left Up !" << endl;
    }
}
