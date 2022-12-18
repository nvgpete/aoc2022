#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct pos {
  char step,loc;
  short pts,on;
  };
struct pos hist[31];
char nm[100][2];  
int flow[70],fmask[70],dst[70][6],xp[70][32];
int best=0;
void move(struct pos pp){
  struct pos p;
  int n,d,w=pp.loc;
  hist[(int)pp.step]=pp;
  if (flow[w] && (fmask[w]&p.on)==0) d=(29-pp.step)*flow[w]; else d=0;  
  for (n=0; n<pp.step;n++) if (xp[w][n]>=pp.pts+d) return;
  xp[w][(int)pp.step]=pp.pts;
  if(pp.step++==30) {
    if(pp.pts>best) { 
      best=pp.pts; 
    }
    return;
  }
  p=pp;
  if (flow[w] && (fmask[w]&p.on)==0) {
    p.on|=fmask[w];
    p.pts+=(30-p.step)*flow[w];
    move(p);
    p=pp;
  }
  n=0;
  while ((d=dst[w][n])>=0) {
    if (flow[d] && (fmask[d]&p.on)==0) {
      p.loc=d;
      move(p);
      p=pp;
    }  
    n++;
  }
  n=0;    
  while ((d=dst[w][n])>=0) {
    if (flow[d]==0 || (fmask[d]&p.on)) { 
      p.loc=d;
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
  struct pos p={0,0,0,0}; 
  memset(dst,-1,sizeof(dst));
  memset(fmask,0,sizeof(fmask));
  memset(xp,-1,sizeof(xp));
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
  for (n=0;n<last;n++) if (*nm[n]=='A' && *(nm[n]+1)=='A') break;
  p.loc=n;
  move(p);
  printf("best=%d\n",best);
}
