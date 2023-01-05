#include <stdio.h>
#include <string.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[100],*s2,ans[24];
  int x,n;
  memset(ans,0,sizeof(ans));
  f=fopen("d25.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    s2=s+strlen(s);
    s2--;
    n=0;
    while (s2>=s) { 
      if (*s2=='=') x=-2;
      else if (*s2=='-') x=-1;
      else x=*s2-'0';
      ans[n]+=x;
      if (ans[n]<-2) {ans[n]+=5; ans[n+1]--;}
      else if (ans[n]>2) {ans[n]-=5; ans[n+1]++;}
      n++;
      s2--;
    }  
    fgets(s,sizeof(s),f);
  }  
  fclose(f);
  n=23;
  while (ans[n]==0) n--;
  while (n>=0){
    if (ans[n]==-2) printf("=");
    else if (ans[n]==-1) printf("-");
    else printf("%d",ans[n]);
    n--;
  }
  printf("\n");   
}
