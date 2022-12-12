#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[100],*s2,sc[240];
  int x=1,cycle=0,ss=0,i;
  memset(sc,' ',sizeof(sc));
  f=fopen("d10.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    if (s[0]=='n') {
      if (abs(x-cycle%40)<2) sc[cycle]='#';
      cycle++;
      if (cycle % 40==20) ss+=cycle*x;
      if (cycle==240) break;
    }   
    else { 
      if (abs(x-cycle%40)<2) sc[cycle]='#';
      cycle++;
      if (cycle % 40==20) ss+=cycle*x;
      if (cycle==240) break;
      if (abs(x-cycle%40)<2) sc[cycle]='#';
      cycle++;
      if (cycle % 40==20) ss+=cycle*x;
      x+=atoi(s+5);
      if (cycle==240) break;
    }  
    fgets(s,sizeof(s),f);
  }  
  fclose(f);
  printf("Signal=%d\n",ss);
  for(i=0;i<240;i+=40) printf("%.40s\n",sc+i); 
}
