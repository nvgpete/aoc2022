#include <stdio.h>
#include <string.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[4100];
  int i,j,k;
  f=fopen("d06.txt","r");
  fgets(s,sizeof(s),f);
  fclose(f);
  i=0;
  while (s[i]==s[i+1] || s[i]==s[i+2] || s[i]==s[i+3] || s[i+1]==s[i+2] || s[i+1]==s[i+3] || s[i+2]==s[i+3]) i++;
  printf("Marker end at %d\n",i+4); 
  i=0;
  j=14;
  while (j>0) {
    for (k=i+1;k<i+j;k++) if (s[i]==s[k]) break;
    if (k==i+j) j--;
    else j=14;
    i++;
  }  
  printf("Message at %d\n",i);            
}
