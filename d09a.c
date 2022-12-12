#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[100],*s2,xy[500][500],d;
  int i=250,i2=250,j=250,j2=250,n,k,count=0;
  memset(xy,0,sizeof(xy));
  xy[i2][j2]=1;
  f=fopen("d09.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    sscanf(s,"%c %d",&d,&n);
    for(k=0;k<n;k++) {
      switch (d) {
        case 'D': i++;
                  if (i-i2>1) {
                    i2=i-1;
                    if (j!=j2) j2=j;
                  }  
                  break;
        case 'U': i--;
                  if (i2-i>1) {
                    i2=i+1;
                    if (j!=j2) j2=j;
                  }  
                  break;
        case 'L': j--;
                  if (j2-j>1) {
                    j2=j+1;
                    if (i!=i2) i2=i;
                  }  
                  break;
        case 'R': j++;
                  if (j-j2>1) {
                    j2=j-1;
                    if (i!=i2) i2=i;
                  }  
                  break;
      }
      xy[i2][j2]=1;
      if(i2==0 || j2==0 || i2==499 || j2==499) printf("Overflow!\n");
    }            
    fgets(s,sizeof(s),f);
  }  
  fclose(f);
  for (i=0;i<500;i++) for(j=0;j<500;j++) count+=xy[i][j];
  printf("Locations=%d\n",count);
  for (i=245;i<256;i++) {for (j=245;j<256;j++) printf("%d",xy[i][j]); printf("\n");}  
}
