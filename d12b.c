#include <stdio.h>
#include <string.h>
#define SZ 1000  
int main(int argc,char **argv) {
  FILE *f;
  char s[200],*s2,xy[43][175],h;
  int d[43][175],jj[SZ],ii[SZ];
  int x,y,last=1,next,dist,i,j;
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
//  for (j=0;j<43;j++) printf("%.175s\n",xy[j]);
//  printf("%c\n",xy[21][1]);
  jj[0]=21; ii[0]=147; d[21][147]=0; last=1; next=0; xy[21][1]='a';
  xy[21][147]='z';
  while (1) {
    j=jj[next];
    i=ii[next++];
    if (next==SZ) next=0;
//      next=0;
//      for (y=0;y<43;y++) {for (x=0;x<25; x++) printf("%3d ",d[y][x]); printf("\n");}
//      printf("%d\n",last);
//      break;   
//    }
    h=xy[j][i];
    if (h=='a') break;
    dist=d[j][i];
//    if (j==21 && i==147) break;
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
  printf("%d steps.\n",d[j][i]); 
}
