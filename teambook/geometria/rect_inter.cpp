#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
#define MAXC 2501
struct Rect{
	int x1,y1, x2,y2;
	int color;
	int area;
	Rect(int _x1, int _y1, int _x2, int _y2){
		x1 = _x1;
		y1 = _y1;
		x2 = _x2;
		y2 = _y2;
		getArea();
	}
	int getArea(){
		if(x1>=x2 || y1>=y2)return area = 0;
		return area = (x2-x1)*(y2-y1);
	}
};
Rect interseccion(Rect t, Rect r){
	int x1,y1,x2,y2;
	x1 = max(t.x1,r.x1);
	y1 = max(t.y1,r.y1);
	x2 = min(t.x2,r.x2);
	y2 = min(t.y2,r.y2);
	Rect res(x1,y1,x2,y2);
	return res;
}