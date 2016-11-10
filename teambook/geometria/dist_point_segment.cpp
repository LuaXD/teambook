struct point{
	double x,y;
};
inline double dist(const point &a, const point &b){
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
inline double distsqr(const point &a, const point &b){
	return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}
double distance_point_to_segment(const point &a, const point &b, const point &pnt){
	double u = ((pnt.x - a.x)*(b.x - a.x) + (pnt.y - a.y)*(b.y - a.y)) / distsqr(a, b);
	point intersection;
	intersection.x = a.x + u*(b.x - a.x);
	intersection.y = a.y + u*(b.y - a.y);

	if (u < 0.0 || u > 1.0)
		return min(dist(a, pnt), dist(b, pnt));

	return dist(pnt, intersection);
}