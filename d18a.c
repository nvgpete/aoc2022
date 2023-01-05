#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc,char **argv) {
  struct pos {
    int x,y,z;
    };
  struct pos stk[10000];
  struct pos p;  
  FILE *f;
  char s[100],*s2,xyz[22][22][22];
  int xx[2140],yy[2140],zz[2140];
  int last=0,n,d,total=0,next=0;
  memset(xyz,0,sizeof(xyz));
  f=fopen("d18.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    sscanf(s,"%d,%d,%d",xx+last,yy+last,zz+last);
    xyz[xx[last]+1][yy[last]+1][zz[last]+1]=1;
    total+=6;
    for (n=0;n<last;n++) if (abs(xx[last]-xx[n])+abs(yy[last]-yy[n])+abs(zz[last]-zz[n])==1) total-=2;
    last++;
    fgets(s,sizeof(s),f);
  }  
  fclose(f);
  printf("Surface total=%d\n",total);
  total=0;
  last=1;
  stk[0].x=0; stk[0].y=0;stk[0].z=0;
  xyz[0][0][0]=2;
  while (next!=last) {
    p=stk[next++];
    if (p.x<21) {
      d=xyz[p.x+1][p.y][p.z];
      if (d==0) {
        xyz[p.x+1][p.y][p.z]=2;
        stk[last]=p;
        stk[last].x++;
        last++;
      } else if (d==1) total++; 
    }  
    if (p.x!=0) {
      d=xyz[p.x-1][p.y][p.z];
      if (d==0) {
        xyz[p.x-1][p.y][p.z]=2;
        stk[last]=p;
        stk[last].x--;
        last++;
      } else if (d==1) total++;
    }  
    if (p.y<21) {
      d=xyz[p.x][p.y+1][p.z];
      if (d==0) {
        xyz[p.x][p.y+1][p.z]=2;
        stk[last]=p;
        stk[last].y++;
        last++;
      } else if (d==1) total++;
    }  
    if (p.y!=0) {
      d=xyz[p.x][p.y-1][p.z];
      if (d==0) {
        xyz[p.x][p.y-1][p.z]=2;
        stk[last]=p;
        stk[last].y--;
        last++;
      } else if (d==1) total++;
    }  
    if (p.z<21) {
      d=xyz[p.x][p.y][p.z+1];
      if (d==0) {
        xyz[p.x][p.y][p.z+1]=2;
        stk[last]=p;
        stk[last].z++;
        last++;
      } else if (d==1) total++;
    }  
    if (p.z!=0) {
      d=xyz[p.x][p.y][p.z-1];
      if (d==0) {
        xyz[p.x][p.y][p.z-1]=2;
        stk[last]=p;
        stk[last].z--;
        last++;
      } else if (d==1) total++;
    }
    if (last>9990) { printf("Buffer too small\n"); break;}
  }      
  printf("Surface total without holes=%d\n",total);
}
