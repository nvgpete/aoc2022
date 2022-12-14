#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[300],*s2,xy[500][1000];
  int i,i1,i2,j,j1,j2,jmax=0,ns=0;
  memset(xy,'.',sizeof(xy));
  f=fopen("d14.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    s2=s;
    i1=strtol(s2,&s2,10);
    j1=strtol(s2+1,&s2,10);
    if (j1>jmax) jmax=j1;
    while (*s2) {
      i2=strtol(s2+4,&s2,10);
      j2=strtol(s2+1,&s2,10);
      if (j2>jmax) jmax=j2;
      if (i1==i2) {
        if (j1<j2) for (j=j1;j<=j2;j++) xy[j][i1]='#';
        else for (j=j2;j<=j1;j++) xy[j][i1]='#';
        j1=j2;
      } else {  
        if (i1<i2) for (i=i1;i<=i2;i++) xy[j1][i]='#';
        else for (i=i2;i<=i1;i++) xy[j1][i]='#';
        i1=i2;
      }
    }    
    fgets(s,sizeof(s),f);
  }  
  fclose(f);
  memset(xy[jmax+2],'#',sizeof(xy[jmax+2])); 
  while (xy[j=0][i=500]!='s') {
    while (1) {
      while (xy[j+1][i]=='.' && j<jmax) j++;
      if(j==jmax) {
        jmax+=2;
        printf("Part 1 =%d sand.\n",ns);
        continue;
      }  
      if (xy[j+1][i-1]=='.') {j++;i--;}
      else if (xy[j+1][i+1]=='.') {j++;i++;}
      else break;
    }
    xy[j][i]='s';
    ns++;
  }    
  printf("Part 2 =%d sand.\n",ns);
}
