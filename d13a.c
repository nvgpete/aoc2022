#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int cmp(char *s,char *s1) {
  int n,n1;
  char stmp[10];
  s++; s1++;
  while (*s!=']' && *s1!=']') { 
    if (*s=='[' && *s1=='[') { // set compare
      if ((n=cmp(s,s1))) return n;
      n=1;
      s++;
      while (n) {
        if (*s=='[') n++;
        else if (*s==']') n--;
        s++;
      }  
      n=1;
      s1++;
      while (n) {
        if (*s1=='[') n++;
        else if (*s1==']') n--;
        s1++;
      }
    } else if (*s!='[' && *s1!='[') { // number compare
      n=strtol(s,&s,10);
      n1=strtol(s1,&s1,10);
      if (n1>n) return 1;
      else if (n>n1) return -1;
    } else if (*s=='[' && *s1!='[') { // set vs number compare
      n1=strtol(s1,&s1,10);
      sprintf(stmp,"[%d]",n1);
      if ((n=cmp(s,stmp))) return n;
      n=1;
      s++;
      while (n) {
        if (*s=='[') n++;
        else if (*s==']') n--;
        s++;
      }  
    } else { // number vs set compare 
      n1=strtol(s,&s,10);
      sprintf(stmp,"[%d]",n1);
      if ((n=cmp(stmp,s1))) return n;
      n=1;
      s1++;
      while (n) {
        if (*s1=='[') n++;
        else if (*s1==']') n--;
        s1++;
      }
    }
    if (*s==',') s++;
    if (*s1==',') s1++;
  }
// if we get here, one or both sets are out of elements  
  if (*s==*s1) return 0;
  if (*s==']') return 1;
  else return -1;  
}
      
int main(int argc,char **argv) {
  FILE *f;
  char s[270],s1[270],*s2;
  int ok=0,n=0,k,n2=1,n6=2; //n6=2 since k6>k2
  f=fopen("d13.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    if(cmp(s,"[[2]]")==1) n2++;
    if(cmp(s,"[[6]]")==1) n6++;
    fgets(s1,sizeof(s),f);
    if((s2=strchr(s1,'\n')))*s2=0;
    if(cmp(s1,"[[2]]")==1) n2++;
    if(cmp(s1,"[[6]]")==1) n6++;
    n++;
    if ((k=cmp(s,s1))==1) ok+=n;
    fgets(s,sizeof(s),f);
    fgets(s,sizeof(s),f);
  }  
  fclose(f); 
  printf("%d in order\n",ok);
  printf("pos2*pos6=%d\n",n2*n6);
}
