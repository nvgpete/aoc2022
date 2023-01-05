#include <stdio.h>
#include <string.h>
#define SZ 600
char xy[SZ+1][30][125],fnd[SZ][30][125];
int max=999,best,done=0,last=0,xm,dstj;
void add(void) { // updates blizzards to next minute, noting repeat
  int i,j,z,step;
  done++;
  step=done; 
  for (j=0;j<last;j++) xy[step][j][0]=xy[step][j][xm-1]='#';
  for (i=0;i<xm;i++) xy[step][0][i]=xy[step][last-1][i]='#';
  xy[step][last-1][xm-2]=0;
  xy[step][0][1]=0;
  for (j=1;j<last-1;j++) for (i=1;i<xm-1;i++) {
    if ((z=xy[step-1][j][i])&1){ if (j==1) xy[step][last-2][i]|=1; else xy[step][j-1][i]|=1;}
    if (z&2){ if (i==xm-2) xy[step][j][1]|=2; else xy[step][j][i+1]|=2;}
    if (z&4){ if (j==last-2) xy[step][1][i]|=4; else xy[step][j+1][i]|=4;}
    if (z&8){ if (i==1) xy[step][j][xm-2]|=8; else xy[step][j][i-1]|=8;}
  }
  if (step%(last-2)==0 && step%(xm-2)==0) max=step;
}  
void mv(int j,int i,int steps) {
  int st;
  if(fnd[steps%SZ][j][i]) return;
  fnd[steps%SZ][j][i]=1;
  if (j==dstj) {
    if (steps<best) best=steps;
    return;  
  }
  if (steps>=best) return; 
  steps++;
  if(steps>done && steps<max) add();
  st=steps;
  if (st>max) st%=max;
  if (xy[st][j][i+1]==0) mv(j,i+1,steps);
  if (j<last-1 && xy[st][j+1][i]==0) mv(j+1,i,steps);
  if (j>0 && xy[st][j-1][i]==0) mv(j-1,i,steps);
  if (xy[st][j][i-1]==0) mv(j,i-1,steps);
  if (xy[st][j][i]==0) mv(j,i,steps);
  return;
}
int main(int argc,char **argv) {
  FILE *f;
  char s[125],*s2;
  int i,j,z;
  memset(xy,0,sizeof(xy));
  memset(fnd,0,sizeof(fnd));
  f=fopen("d24.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    strcpy(xy[0][last],s);
    last++;
    fgets(s,sizeof(s),f);
  }  
  fclose(f);
  xm=strlen(s);
  for  (j=0;j<last;j++) for (i=0;i<xm;i++)
    if ((z=xy[0][j][i])=='^') xy[0][j][i]=1; 
    else if (z=='>') xy[0][j][i]=2; 
    else if (z=='v') xy[0][j][i]=4; 
    else if (z=='<') xy[0][j][i]=8; 
    else if (z=='.') xy[0][j][i]=0;
  dstj=last-1;
  best=SZ;
  mv(0,1,0);
  printf("part a best=%d steps.\n",best);
  memset(fnd,0,sizeof(fnd));
  dstj=0;
  j=best;
  best=j+SZ;
  mv(last-1,xm-2,j);
  printf("back to start best=%d\n",best);
  memset(fnd,0,sizeof(fnd));
  j=best;
  dstj=last-1;
  best=j+SZ;
  mv(0,1,j);
  printf("Part b best=%d\n",best);
}  
