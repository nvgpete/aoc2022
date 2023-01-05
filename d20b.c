#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define KEY 811589153L
int main(int argc,char **argv) {
  FILE *f;
  char s[100],*s2;
  long x[6000],k,k3;
  int xx[6000],n,j,k2,last=0,z;
  f=fopen("d20.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    x[last++]=atoi(s);
    fgets(s,sizeof(s),f);
  }  
  fclose(f);
  for (n=0;n<last;n++) {
    xx[n]=n;
    x[n]*=KEY;
  }
  for (z=0;z<10;z++) {
    for (n=0;n<last;n++) {
      for (j=0;j<last;j++) if (xx[j]==n) break;
      k=x[j];
      k3=k;
      k%=(last-1);
      if (k<0) k+=last-1;
      if (k==0) continue;
      k2=j+k;
      if (k2<last) {
        memmove(x+j,x+j+1,sizeof(x[0])*k);
        memmove(xx+j,xx+j+1,sizeof(xx[0])*k);
        x[k2]=k3;
        xx[k2]=n;
      } else {
        k2-=last-1;
        memmove(x+k2+1,x+k2,sizeof(x[0])*(j-k2));  
        memmove(xx+k2+1,xx+k2,sizeof(xx[0])*(j-k2));  
        x[k2]=k3;
        xx[k2]=n;
      }
    }
  }
  for (j=0;j<last;j++) if (x[j]==0) break;
  printf("part b=%ld\n",x[(j+1000)%last]+x[(j+2000)%last]+x[(j+3000)%last]);
}
