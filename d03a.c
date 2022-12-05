#include <stdio.h>
#include <string.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[100],*s2;
  int i,count=0;
  f=fopen("d03.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    s2=s+strlen(s)/2;
    i=0;
    while (strchr(s2,s[i])==NULL) i++;
    if (s[i]<='Z') count+=s[i]-'A'+27;
    else count+=s[i]-'a'+1;
    fgets(s,sizeof(s),f);
  }  
  fclose(f); 
  printf("count=%d\n",count);
}
