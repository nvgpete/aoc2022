#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char op[2200];
long val[2200];
int m1[2200],m2[2200];
long get(int n) {
  long x1,x2;
  if (op[n]==0) return val[n];
  x1=get(m1[n]);
  x2=get(m2[n]);
  if (op[n]=='+') return x1+x2;
  if (op[n]=='*') return x1*x2;
  if (op[n]=='-') return x1-x2;
  return x1/x2;
}
int main(int argc,char **argv) {
  FILE *f;
  char s[100],*s2,nm[2200][4];
  int last=0,n,k,k2,root;
  memset(op,0,sizeof(op));
  f=fopen("d21.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    for (n=0;n<last;n++) if (strncmp(s,nm[n],4)==0) break;
    if (n==last) strncpy(nm[last++],s,4);
    if (strncmp(s,"root",4)==0) root=n;
    k=atoi(s+6);
    if (k>0) val[n]=k;
    else {
      for (k=0;k<last;k++) if (strncmp(s+6,nm[k],4)==0) break;
      if (k==last) strncpy(nm[last++],s+6,4);
      m1[n]=k;
      for (k2=0;k2<last;k2++) if (strncmp(s+13,nm[k2],4)==0) break;
      if (k2==last) strncpy(nm[last++],s+13,4);
      m2[n]=k2;
      op[n]=*(s+11);
    }  
    fgets(s,sizeof(s),f);
  }  
  fclose(f); 
  printf("Monkey yells %ld\n",get(root));
}
