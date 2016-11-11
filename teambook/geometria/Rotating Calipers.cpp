#include<bits/stdc++.h>
using namespace std;
/*
author:     Eddy Cael Mamani Canaviri
Language:   C++
Date:       11/11/2016
Sample problem:  https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3729
           j
         ///-------
      ///  |       \\
   ///     |         \\
  u|       |           \\ v
   |       |            |
   |       |            | 
   |       |            |  
           |            |  
           X  90 grades
         ___________
         i        i+1
 
*/
#define EPS 0.00000001
#define pi acos(-1)
struct Punto
    { double x,y;
    Punto(){x=y=0;}
    Punto(double xx,double yy):x(xx),y(yy) {}
    double mod2()
        { return x*x+y*y; }
    double mod() // get modulus vector's
        { return sqrt(x*x+y*y); }
    Punto ort()
        { return Punto (-y,x); }
    Punto rotate(double ang){
    // if ang is positive the rotation is /\
    //                            *------>*
    // if ang is negative the rotation is \/
       return Punto(x*cos(ang)-y*sin(ang)
                           ,x*sin(ang)+y*cos(ang));
       }
    Punto unit(){ // gets unitary vector
      double nor=mod();
      return Punto(x/nor,y/nor);
      }
    };
ostream& operator<<(ostream &o,const Punto&a)
   { o<<"("<<a.x<<","<<a.y<<")"; return o; }
bool operator<(const Punto &a,const Punto &b)
   { if(a.x!=b.x) return a.x<b.x; return a.y<b.y; }
Punto operator+(const Punto &a,const Punto &b)
   { return Punto  (a.x+b.x,a.y+b.y); }
Punto operator-(const Punto &a,const Punto &b)
   { return Punto  (a.x-b.x,a.y-b.y); }
Punto operator*(const Punto &a,const double &k)
   { return Punto  (a.x*k,a.y*k); }
Punto operator/(const Punto &a,const double &k)
   { return Punto  (a.x/k,a.y/k); }
double cruz(const Punto&a,const Punto &b)
   { return (a.x*b.y-a.y*b.x); }
double dot(const Punto&a,const Punto &b)
   { return (a.x*b.x+a.y*b.y); }
double area(const Punto&a,const Punto &b,const Punto &c)
   { return cruz(b-a,c-a); }
Punto interRectas(const Punto &a,const Punto &b,const Punto &c,const Punto &d)
   { return a+((b-a)*cruz(c-a,d-c))/cruz(b-a,d-c); }
Punto proyecta(const Punto &p,const Punto &a,const Punto &b)
    { return interRectas(a,b,p,p+(a-b).ort()); }
vector<Punto> ConvexHull(vector<Punto> &pol){
    sort(pol.begin(),pol.end());
    int i=0,k=0,t,n=pol.size();
    vector<Punto> h(2*n);
    while(i<n){
        while(k>=2 && area(h[k-2],h[k-1],pol[i])<= 0) k--;
        h[k++]=pol[i++];
        }
    i=n-2;
    t=k;
    while(i>=0){
        while(k>t&&area(h[k-2],h[k-1],pol[i])<=0 ) k--;
        h[k++]=pol[i--];
        }
    return vector<Punto >(h.begin(),h.begin()+k-1);
    }
vector<Punto> p;
void rotating_calipers(int n)
   {
   int i,j;
   p.resize(n);
   for(i = 0; i < n; i++)
      scanf("%lf %lf",&p[i].x,&p[i].y);
      //cin>>p[i].x>>p[i].y;
   p = ConvexHull(p);
   n = p.size();
   i = 0;
   j = 2;
   double mnArea = 1000000000000.0;
   double mnPerimeter = 1000000000000.0;
   int u,v;
   Punto A,B,X;
   while(area(p[i],p[(i + 1) % n],p[j]) <
         area(p[i],p[(i + 1) % n],p[( j + 1) % n]))
      j = ( j + 1 ) % n;
   u = j;//j+1
   X = proyecta(p[j],p[i],p[(i+1)%n]);
   while(area(X,p[j],p[u])
         <area(X,p[j],p[( u + 1 ) % n]))
      u = ( u + 1 ) % n;
   v = j;//(j-1+n)%n;
   while(area(X,p[v],p[j])
         <area(X,p[( v - 1 + n) % n],p[j]))
      v = ( v - 1 + n) % n;
   while(i < n){
      while(area(p[i],p[( i + 1) % n],p[j])
           <area(p[i],p[( i + 1) % n],p[ ( j + 1 ) % n]))
         j = ( j + 1) % n;
      X=proyecta(p[j],p[i],p[( i + 1 ) % n]);
      while(area(X,p[j],p[u])
           <area(X,p[j],p[( u + 1 ) % n]))
         u = ( u + 1 ) % n;
      while(area(X,p[v],p[j])
           <area(X,p[( v + 1 ) %n],p[j]))
         v = ( v + 1) % n;
      // the graphic is valid HERE!
      A=proyecta(p[u],p[i],p[(i+1)%n]);
      B=proyecta(p[v],p[i],p[(i+1)%n]);
      mnPerimeter = min(mnPerimeter,((A-B).mod()+(p[j]-X).mod())*2);
      mnArea = min(mnArea,(p[j]-X).mod()*(A-B).mod());
      i++;
      }
   printf("%.2f %.2f\n",mnArea,mnPerimeter);
   }
int main(int argc, char const *argv[]) {
      int n;
      while(scanf("%d",&n)==1){
         if(!n) break;
         rotating_calipers(n);
      }
      return 0;
   }