#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[100],*s2;
  int xs[32],ys[32],xb[32],yb[32],d[32],r1[32],r2[32];
  int n=0,x,y,k,x1,x2,last,lasts;
  f=fopen("d15.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    sscanf(s,"Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d",xs+n,ys+n,xb+n,yb+n);
    d[n]=abs(xs[n]-xb[n])+abs(ys[n]-yb[n]);
    n++;
    fgets(s,sizeof(s),f);
  }  
  fclose(f);
  lasts=n; 
  for (y=0; y<=4000000;y++) {
    last=0;
    for (n=0;n<lasts;n++) {
      if (abs(y-ys[n])>d[n]) continue;
      x=d[n]-abs(y-ys[n]);
      x1=xs[n]-x;
      x2=xs[n]+x;
      k=last++;
      while (k>0 && x1<r1[k-1]) {
        r1[k]=r1[k-1];
        r2[k]=r2[k-1];
        k--;
      }
      r1[k]=x1;
      r2[k]=x2;  
    }
    x1=r1[0]; x2=r2[0];
    for (k=1;k<last;k++) {
      if (r1[k]>x2) { printf("Tuning freq=%ld (x=%d, y=%d)\n",(x2+1)*4000000L+y,x2+1,y); return 0;}
      if (r2[k]>x2) x2=r2[k];
      if (x2>=4000000) break;
    }  
  }  
}
