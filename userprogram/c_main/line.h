#ifndef LINE_H
#define LINE_H
#include <math.h>
//触摸向上的直线
#define UPLINE 1
//触摸向下的直线
#define DOWNLINE 2
//触摸向左的直线
#define LEFTLINE 3
//触摸向左的直线
#define RIGHTLINE 4
//触摸哦为其他
#define OTHER 0
int judge_Line(int* x, int* y,int length);
#endif
