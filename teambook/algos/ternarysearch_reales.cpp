//yeputons ~ 300 iteraciones es mas que suficiente
double l = a, r = b;
for(int i=0; i<200; i++) {
  double l1 = (l*2+r)/3;
  double l2 = (l+2*r)/3;
  if(f(l1) > f(l2)) 
  	r = l2; 
  else 
  	l = l1;
}
x = l;