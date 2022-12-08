#include <stdio.h>
#include <string.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[100],*s2,st[9][100];
  int top[9],i,j,fr,t;
  memset(st,0,sizeof(st));
  memset(top,0,sizeof(top));
  f=fopen("d05.txt","r");
  for (i=7;i>=0;i--) {
    fgets(s,sizeof(s),f);
    for (j=0;j<9;j++) if(s[j*4+1]!=' ') {
      st[j][i]=s[j*4+1];
      if (top[j]==0) top[j]=i+1;
    }
  }    
  fgets(s,sizeof(s),f);
  fgets(s,sizeof(s),f);
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    sscanf(s,"move %d from %d to %d",&j,&fr,&t);
    top[fr-1]-=j;
    for (i=0;i<j;i++) {
      st[t-1][top[t-1]++]=st[fr-1][top[fr-1]+i];
    }  
    fgets(s,sizeof(s),f);
  }  
  fclose(f);
  printf("Top crates=");
  for (j=0;j<9;j++) printf("%c",st[j][top[j]-1]);
  printf("\n");
}  