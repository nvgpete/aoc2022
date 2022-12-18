#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct pos {
  char step,loc1,loc2,part;
  short pts,on,left;
  };
struct pos hist[31];
char nm[100][2];  
int flow[70],fmask[70],dst[70][6],xp1[70][28],xp2[70][28];
int best=0;
void move(struct pos pp){
  struct pos p;
  int n,d,w;
  if (pp.pts+pp.left*(25-pp.step)<best) return;
  if (pp.part==0) {
    hist[(int)pp.step]=pp;
    w=pp.loc2;
    if (flow[w] && (fmask[w]&p.on)==0) d=(25-pp.step)*flow[w]; else d=0;  
    for (n=0; n<pp.step;n++) if (xp2[w][n]>=pp.pts+d) return;
    xp2[w][(int)pp.step]=pp.pts;
    w=pp.loc1;
    pp.part=1;
  } else {
    w=pp.loc1;
    if (flow[w] && (fmask[w]&p.on)==0) d=(25-pp.step)*flow[w]; else d=0;  
    for (n=0; n<pp.step;n++) if (xp1[w][n]>=pp.pts+d) return;
    xp1[w][(int)pp.step]=pp.pts;
    w=pp.loc2;
    pp.part=0;  
    pp.step++;
    if(pp.step==26 || pp.on==0x7fff) {
      if(pp.pts>best) { 
        best=pp.pts; 
//        printf("%d\n",best);
//        for (n=0;n<pp.step;n++) printf("%2d %.2s %.2s %4x %4d %3d\n",hist[n].step,nm[(int)hist[n].loc1],nm[(int)hist[n].loc2],hist[n].on,hist[n].pts,hist[n].left);
      }
      return;
    }
  }  
  p=pp;
  if (flow[w] && (fmask[w]&p.on)==0) {
    p.on|=fmask[w];
    p.pts+=(26-p.part-p.step)*flow[w];
    p.left-=flow[w];
    move(p);
    p=pp;
  }
  n=0;
  while ((d=dst[w][n])>=0) {
    if (d!=p.loc1 && d!=p.loc2 && flow[d] && (fmask[d]&p.on)==0) {
      if (p.part) p.loc1=d; else p.loc2=d;
      move(p);
      p=pp;
    }  
    n++;
  }
  n=0;    
  while ((d=dst[w][n])>=0) {
    if (flow[d]==0 || (fmask[d]&p.on)) { 
      if(d==p.loc1 || d==p.loc2) break;
      if(p.part) p.loc1=d; else p.loc2=d;
      move(p);
      p=pp;
    }  
    n++;
  }    
}  
int main(int argc,char **argv) {
  FILE *f;
  char s[100],*s2;
  int n,i,j,last=0,lastf=0;
  struct pos p={0,0,0,0,0}; 
  memset(dst,-1,sizeof(dst));
  memset(fmask,0,sizeof(fmask));
  memset(xp1,-1,sizeof(xp1));
  memset(xp2,-1,sizeof(xp2));
  f=fopen("d16.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    n=0;
    while (n<last && (nm[n][0]!=s[6] || nm[n][1]!=s[7])) n++;
    if (n==last) {
      nm[n][0]=s[6];
      nm[n][1]=s[7];
      last++;
    }
    if ((flow[n]=atoi(s+23))) fmask[n]=(1<<lastf++);
    s2=strstr(s,"valve")+5;
    if (*s2!='s') s2--;
    i=0;
    while (*s2) {
      s2+=2;
      j=0;
      while (j<last && (nm[j][0]!=*s2 || nm[j][1]!=*(s2+1))) j++;
      if (j==last) {
        nm[j][0]=*s2;
        nm[j][1]=*(s2+1);
        last++;
      }
      dst[n][i++]=j;
      s2+=2;
    }   
    fgets(s,sizeof(s),f);
  }  
  fclose(f);
  for (n=0;n<last;n++) { 
    if (*nm[n]=='A' && *(nm[n]+1)=='A') {
      p.loc1=n;
      p.loc2=n;
    }
    p.left+=flow[n];
  }    
  move(p);
  printf("Best=%d\n",best);
}
