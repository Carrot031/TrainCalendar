#include "Colision.h"
#include "Point.h"
#include <stdio.h>
#include <math.h>
bool Colide(Point* p1,int np1, Point* p2, int np2)
{
	int i,j;
	for(i = 1; i <= np1;i++){
		int ax, ay, bx, by;
		ax = p1[i-1].X;
		ay = p1[i-1].Y;
		if(i == np1){
			bx = p1[0].X;
			by = p1[0].Y;
		}else{
			bx = p1[i].X;
			by = p1[i].Y;
		}

		for(j = 1; j <= np2; j++){
			int cx, cy, dx, dy;
			cx = p2[j-1].X;
			cy = p2[j-1].Y;
			if(j == np2){
				dx = p2[0].X;
				dy = p2[0].Y;
			}else{
				dx = p2[j].X;
				dy = p2[j].Y;
			}

			if(JudgeIntersected(ax,ay,bx,by,cx,cy,dx,dy)){
				//printf("線分(%d,%d)(%d,%d)と線分(%d,%d)(%d,%d)は交錯しています。",ax,ay,bx,by,cx,cy,dx,dy);
				return true;
			}
		}
	}
	return false;
}

bool JudgeIntersected(int ax,int ay,int bx,int by,int cx,int cy, int dx,int dy)
{
	/*
	int ta = (cx - dx) * (ay - cy) + (cy - dy) * (cx - ax);
	int tb = (cx - dx) * (by - cy) + (cy - dy) * (cx - bx);
	int tc = (ax - bx) * (cy - ay) + (ay - by) * (ax - cx);
	int td = (ax - bx) * (dy - ay) + (ay - by) * (ax - dx);

	bool ret = (bool)((tc * td < 0) && (ta * tb < 0));
	if(ret){
		printf("%d\n",ret);
	}
	return ret;
	*/
	/*
	if(fmin(ax,bx) > fmax(cx,dx)) return false;
	if(fmin(ay,by) > fmax(cy,dy)) return false;
	if(fmin(cx,dx) > fmax(ax,bx)) return false;
	if(fmin(cy,dy) > fmax(ay,by)) return false;
	
	Point l1start = (Point){ax,ay};
	Point l1end = (Point){bx,by};
	Point l2start = (Point){cx,cy};
	Point l2end = (Point){dx,dy};
	return 
	Straddle(ax,ay,bx,by,l2start,l2end) &&
	Straddle(cx,cy,dx,dy,l1start,l1end);
	*/

	double s1x,s1y,s2x,s2y;
	s1x = bx - ax;
	s1y = by - ay;
	s2x = dx - cx;
	s2y = dy - cy;

	double s, t;
	s = (-s1y * (ax - cx) + s1x * (ay - cy)) / (-s2x * s1y + s1x * s2y);
	t = (s2x * (ay - cy) - s2y * (ax - cx)) / (-s2x * s1y + s1x * s2y);

	if(s >= 0 && s<=1 && t>=0 && t<=1){
		return true;
	}
	return false;
}

bool Straddle(int ax, int ay, int bx, int by, Point p1, Point p2)
{
	return 0 >= (Side(p1,ax,ay,bx,by),Side(p2,ax,ay,bx,by));
}

int Side(Point p,int ax, int ay, int bx, int by)
{
	Point p1 = (Point){ax,ay};
	Point p2 = (Point){bx,by};

	const int n = p.X * (p1.Y - p2.Y) + p1.X * (p2.Y - p.Y) * p2.X * (p.Y - p1.Y);
	if(n > 0) return 1;
	else if(n < 0) return -1;
	else return 0;
}
