#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[100],*s2;
  int xs[32],ys[32],xb[32],yb[32],d[32];
  int n=0,x,cnt,lasts;
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
  cnt=0;
  for (n=0;n<lasts;n++) if (yb[n]==2000000) { // don't count spots with a beacon
    for (x=0;x<n;x++) if (xb[x]==xb[n]) break;
    if (x==n) cnt--;
  }    
  for (x=-4000000; x<8000000;x++) {
    for (n=0;n<lasts;n++) if (abs(x-xs[n])+abs(2000000-ys[n])<=d[n]) break;
    if (n!=lasts) cnt++;
  }  
  printf("\n%d locations\n",cnt);
}
