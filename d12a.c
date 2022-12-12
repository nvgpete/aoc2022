#include <stdio.h>
#include <string.h>
#define SZ 1000  
int main(int argc,char **argv) {
  FILE *f;
  char s[200],*s2,xy[43][175],h;
  int d[43][175],jj[SZ],ii[SZ];
  int last=1,next,dist,i,j,Si=0,Sj=0,Ei=0,Ej=0;
  memset(xy,'z',sizeof(xy));
  memset(d,-1,sizeof(d));
  f=fopen("d12.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    memcpy(xy[last]+1,s,strlen(s));
    last++;
    fgets(s,sizeof(s),f);
  }  
  fclose(f);
  for (j=0;j<43;j++) {
    xy[j][174]=0;
    if ((s2=strchr(xy[j],'S'))) {
      Si=s2-xy[j];
      Sj=j;
      xy[Sj][Si]='a';
    }  
    if ((s2=strchr(xy[j],'E'))) {
      Ei=s2-xy[j];
      Ej=j;
      xy[Ej][Ei]='z';
    }  
  }  
  jj[0]=Sj; ii[0]=Si; d[Sj][Si]=0; last=1; next=0; 
  while (1) {
    j=jj[next];
    i=ii[next++];
    if (next==SZ) next=0;
    h=xy[j][i];
    dist=d[j][i];
    if (j==Ej && i==Ei) break;
    if (xy[j+1][i]-h<2 && d[j+1][i]==-1) {
      d[j+1][i]=dist+1;
      ii[last]=i;
      jj[last++]=j+1;
      if (last==SZ) last=0;
    }  
    if (xy[j-1][i]-h<2 && d[j-1][i]==-1) {
      d[j-1][i]=dist+1;
      ii[last]=i;
      jj[last++]=j-1;
      if (last==SZ) last=0;
    }  
    if (xy[j][i+1]-h<2 && d[j][i+1]==-1) {
      d[j][i+1]=dist+1;
      ii[last]=i+1;
      jj[last++]=j;
      if (last==SZ) last=0;
    }  
    if (xy[j][i-1]-h<2 && d[j][i-1]==-1) {
      d[j][i-1]=dist+1;
      ii[last]=i-1;
      jj[last++]=j;
      if (last==SZ) last=0;
    }
  }    
  printf("Part 1 %d steps.\n",d[Ej][Ei]); 
  memset(d,-1,sizeof(d));
  jj[0]=Ej; ii[0]=Ei; d[Ej][Ei]=0; last=1; next=0; 
  while (1) {
    j=jj[next];
    i=ii[next++];
    if (next==SZ) next=0;
    h=xy[j][i];
    dist=d[j][i];
    if (xy[j][i]=='a') break;
    if (h-xy[j+1][i]<2 && d[j+1][i]==-1) {
      d[j+1][i]=dist+1;
      ii[last]=i;
      jj[last++]=j+1;
      if (last==SZ) last=0;
    }  
    if (h-xy[j-1][i]<2 && d[j-1][i]==-1) {
      d[j-1][i]=dist+1;
      ii[last]=i;
      jj[last++]=j-1;
      if (last==SZ) last=0;
    }  
    if (h-xy[j][i+1]<2 && d[j][i+1]==-1) {
      d[j][i+1]=dist+1;
      ii[last]=i+1;
      jj[last++]=j;
      if (last==SZ) last=0;
    }  
    if (h-xy[j][i-1]<2 && d[j][i-1]==-1) {
      d[j][i-1]=dist+1;
      ii[last]=i-1;
      jj[last++]=j;
      if (last==SZ) last=0;
    }
  }    
  printf("Part 2 %d steps.\n",dist); 
}
