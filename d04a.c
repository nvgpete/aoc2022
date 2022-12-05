#include <stdio.h>
#include <string.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[100],*s2;
  int a,b,c,d,count=0,count2=0;
  f=fopen("d04.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    sscanf(s,"%d-%d,%d-%d",&a,&b,&c,&d);
    if ((a<=c && b>=d) || (c<=a && d>=b)) count++;
    if (!((c>a && c>b) || (d<a && d<b))) count2++;
    fgets(s,sizeof(s),f);
  }  
  fclose(f); 
  printf("Contain=%d\n",count);
  printf("Overlap=%d\n",count2);
}
