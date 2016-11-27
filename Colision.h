#include <stdbool.h>
#include "Point.h"
bool Colide(Point* p1,int np1, Point* p2, int np2);

bool JudgeIntersected(int ax,int ay,int bx,int by,int cx,int cy, int dx,int dy);

bool Straddle(int ax,int ay,int bx, int by,Point a, Point b);

int Side(Point p, int ax, int ay, int bx, int by);
