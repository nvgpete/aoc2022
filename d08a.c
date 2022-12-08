#include <stdio.h>
#include <string.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[100][101],s2[100][100],*s3,h;
  int i=0,j,k,n,min,count=0,best=1;
  memset(s2,0,sizeof(s2));
  f=fopen("d08.txt","r");
  fgets(s[0],sizeof(s[0]),f);
  if((s3=strchr(s[0],'\n')))*s3=0;
  while (!feof(f)) {
    i++;
    fgets(s[i],sizeof(s[i]),f);
    if((s3=strchr(s[i],'\n')))*s3=0;
  }  
  fclose(f);
  for (i=0;i<99;i++) {
    min=-1;
    j=0;
    while (min!='9' && j<98) {
      if (s[i][j]>min) {
        s2[i][j]=1;
        min=s[i][j];
      }  
      j++;
    }  
    min=-1;
    j=98;
    while (min!='9' && j>0) {
      if (s[i][j]>min) {
        s2[i][j]=1;
        min=s[i][j];
      }  
      j--;
    }  
    min=-1;
    j=0;
    while (min!='9' && j<98) {
      if (s[j][i]>min) {
        s2[j][i]=1;
        min=s[j][i];
      }  
      j++;
    }  
    min=-1;
    j=98;
    while (min!='9' && j>0) {
      if (s[j][i]>min) {
        s2[j][i]=1;
        min=s[j][i];
      }  
      j--;
    }  
  }
  for (i=0;i<99;i++) for(j=0;j<99;j++) count+=s2[i][j];
  printf("Visible=%d\n",count);
  for (i=1;i<98;i++) for(j=1;j<98;j++) {
    h=s[i][j];
    k=j-1;
    while (s[i][k]<h && k>0) k--;
    n=j-k;
    if(i==3 && j==3) printf("%d ",n);
    k=j+1; 
    while (s[i][k]<h && k<98) k++;
    n*=(k-j);
    if(i==3 && j==3) printf("%d ",n);
    k=i-1;
    while (s[k][j]<h && k>0) k--;
    n*=(i-k);
    if(i==3 && j==3) printf("%d ",n);
    k=i+1; 
    while (s[k][j]<h && k<98) k++;
    n*=(k-i);
    if(i==3 && j==3) printf("%d ",n);
    if (n>best) best=n;
    if (i==3 && j==3) printf("%d\n",n);
  }  
  printf("Best=%d\n",best);
}
