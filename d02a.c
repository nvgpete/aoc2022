#include <stdio.h>
#include <string.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[100],*s2;
  int tot=0,tot2=0,pts[3][3]={{4,8,3},{1,5,9},{7,2,6}},pts2[3][3]={{3,4,8},{1,5,9},{2,6,7}};
  f=fopen("d02.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    tot+=pts[s[0]-'A'][s[2]-'X'];
    tot2+=pts2[s[0]-'A'][s[2]-'X'];
    fgets(s,sizeof(s),f);
  }  
  fclose(f);
  printf("part a=%d\n",tot); 
  printf("part b=%d\n",tot2); 
}
