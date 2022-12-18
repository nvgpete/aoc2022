#include <stdio.h>
#include <string.h>
int main(int argc,char **argv) {
  struct rock {
    int sz,y[5],x[5];
  };   
  FILE *f;
  char s[10100],*s2;
  char cc[4000][7];
  struct rock rr[5]={{4,{0,0,0,0},{2,3,4,5}},{5,{1,0,1,1,2},{2,3,3,4,3}},{5,{0,0,0,1,2},{2,3,4,4,4}},{4,{0,1,2,3},{2,2,2,2}},{4,{0,0,1,1},{2,3,2,3}}};
  struct rock r;
  int i,k,n,rn,hgt=0;
  memset(cc,' ',sizeof(cc));
  memset(cc[0],'#',7);                                  
  f=fopen("d17.txt","r");
  fgets(s,sizeof(s),f);
  if((s2=strchr(s,'\n')))*s2=0;
  fclose(f);
  s2=s;
  rn=0;
  for (k=0;k<2022;k++) {
    r=rr[rn];
    for (n=0;n<r.sz;n++) r.y[n]+=hgt+1;
    for (i=0;i<4;i++) {
      if (*s2=='>' && r.x[3]!=6) for (n=0;n<r.sz;n++) r.x[n]++;
      else if (*s2=='<' && r.x[0]!=0) for (n=0;n<r.sz;n++) r.x[n]--;
      s2++; if (*s2==0) s2=s;
    }
    while (1) {
      for (n=0;n<r.sz;n++) if (cc[r.y[n]-1][r.x[n]]=='#') break;
      if (n!=r.sz) break; 
      for (n=0;n<r.sz;n++) r.y[n]--;
      if (*s2=='>' && r.x[3]!=6) {
        for (n=0;n<r.sz;n++) if (cc[r.y[n]][r.x[n]+1]=='#') break;
        if (n==r.sz) for (n=0;n<r.sz;n++) r.x[n]++;
      } else if (*s2=='<' && r.x[0]!=0) {
        for (n=0;n<r.sz;n++) if (cc[r.y[n]][r.x[n]-1]=='#') break;
        if (n==r.sz) for (n=0;n<r.sz;n++) r.x[n]--;
      }  
      s2++; if (*s2==0) s2=s;
    }
    for (n=0;n<r.sz;n++) {
      if (r.y[n]>hgt) hgt=r.y[n];
      cc[r.y[n]][r.x[n]]='#';
    }    
    rn++; if (rn==5) rn=0;
  }
  printf("%d\n",hgt); 
}
