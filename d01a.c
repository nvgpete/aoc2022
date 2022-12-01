#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[100],*s2;
  int x,sum,max1=0,max2=0,max3=0;
  f=fopen("d01.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    x=atoi(s);
    if (x) sum+=x;
    else {
      if (sum>max1) { 
        max3=max2;
        max2=max1;
        max1=sum;
      } else if (sum>max2) {
        max3=max2;
        max2=sum;
      } else if (sum>max3) max3=sum;     
      sum=0;
    }  
    fgets(s,sizeof(s),f);
  }  
  fclose(f);
  if (sum>max1) { 
    max3=max2;
    max2=max1;
    max1=sum;
  } else if (sum>max2) {
    max3=max2;
    max2=sum;
  } else if (sum>max3) max3=sum;     
  printf("Most Calories=%d\n",max1);
  printf("3 most calories=%d\n",max1+max2+max3); 
}
