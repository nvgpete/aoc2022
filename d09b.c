#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[100],*s2,xy[500][500],d;
  int i[10],j[10],n,k,m,count=0;
  memset(xy,0,sizeof(xy));
  for (k=0;k<10;k++) {
    i[k]=250;
    j[k]=250;
  }  
  xy[i[9]][j[9]]=1;
  f=fopen("d09.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    sscanf(s,"%c %d",&d,&n);
    for(k=0;k<n;k++) {
      if (d=='D') i[0]++;
      else if (d=='U') i[0]--;
      else if (d=='L') j[0]--;
      else j[0]++;
      for (m=1;m<10;m++) {
        if (abs(i[m-1]-i[m])<2 && abs(j[m-1]-j[m])<2) break;
        if (i[m-1]-i[m]==2) {
          i[m]++;
          if (j[m-1]-j[m]>0) j[m]++;
          else if (j[m-1]-j[m]<0) j[m]--;
        }  
        if (i[m-1]-i[m]==-2) {
          i[m]--;
          if (j[m-1]-j[m]>0) j[m]++;
          else if (j[m-1]-j[m]<0) j[m]--;
        }  
        if (j[m-1]-j[m]==2) {
          j[m]++;
          if (i[m-1]-i[m]>0) i[m]++;
          else if (i[m-1]-i[m]<0) i[m]--;
        }  
        if (j[m-1]-j[m]==-2) {
          j[m]--;
          if (i[m-1]-i[m]>0) i[m]++;
          else if (i[m-1]-i[m]<0) i[m]--;
        }  
      }
      xy[i[9]][j[9]]=1;
    }            
    fgets(s,sizeof(s),f);
  }  
  fclose(f);
  for (m=0;m<500;m++) for(n=0;n<500;n++) count+=xy[m][n];
  printf("Locations=%d\n",count);
}
