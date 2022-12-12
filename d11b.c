#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[100],*s2,op[8];
  int ni[8],val[8],div[8],tr[8],fal[8],sum[8];
  int n,i,k;
  long w,itm[8][40];
  memset(ni,0,sizeof(ni));
  memset(sum,0,sizeof(sum));
  f=fopen("d11.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    sscanf(s,"Monkey %d",&n);
    fgets(s,sizeof(s),f);
    s2=s+18;
    itm[n][0]=strtol(s2,&s2,10);
    ni[n]=1;
    while (*s2==',') {
      itm[n][ni[n]]=strtol(s2+1,&s2,10);
      ni[n]++;
    }  
    fgets(s,sizeof(s),f);
    if ((s2=strchr(s,'+'))!=NULL) {
      op[n]='+';
      val[n]=atoi(s2+2);
    } else {
      s2=strchr(s,'*')+2;
      if ((val[n]=atoi(s2))) op[n]='*';
      else op[n]='s';
    }         
    fgets(s,sizeof(s),f);
    div[n]=atoi(s+21);
    fgets(s,sizeof(s),f);
    tr[n]=atoi(s+29);
    fgets(s,sizeof(s),f);
    fal[n]=atoi(s+30);
    fgets(s,sizeof(s),f);
    fgets(s,sizeof(s),f);
  }  
  fclose(f);
  for (i=0;i<10000;i++) {
    for (n=0;n<8;n++) {
      sum[n]+=ni[n];
      for (k=0;k<ni[n];k++) {
        if (op[n]=='+') w=itm[n][k]+val[n];
        else if (op[n]=='*') w=itm[n][k]*val[n];
        else w=itm[n][k]*itm[n][k];
        w=w%9699690;
        if (w % div[n]) itm[fal[n]][ni[fal[n]]++]=w;      
        else itm[tr[n]][ni[tr[n]]++]=w;
      }
      ni[n]=0;
    }
  }
  printf("Multiply two largest\n"); 
  for (n=0;n<8;n++) printf("%d\n",sum[n]);      
}
