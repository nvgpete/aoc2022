#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[5700],*s2,xy[205][205],dir,c;
  int last=1,i,j,k,n,steps;
  memset(xy,' ',sizeof(xy));
  f=fopen("d22.txt","r");
  fgets(s,sizeof(s),f);
  if((s2=strchr(s,'\n')))*s2=0;
  while (*s!=0) {
    strncpy(xy[last]+1,s,strlen(s));
    last++;
    fgets(s,sizeof(s),f);
    if((s2=strchr(s,'\n')))*s2=0;
  }
  fgets(s,sizeof(s),f);  
  if((s2=strchr(s,'\n')))*s2=0;
  fclose(f); 
  j=1;i=1;
  while (xy[j][i]!='.') i++;
  dir='r';
  s2=s;
  while ((c=*s2)) {
    if (c=='R') {
      if (dir=='r') dir='d';
      else if (dir=='d') dir='l';
      else if (dir=='l') dir='u';
      else if (dir=='u') dir='r';
      s2++;
    } else if (c=='L') {  
      if (dir=='r') dir='u';
      else if (dir=='d') dir='r';
      else if (dir=='l') dir='d';
      else if (dir=='u') dir='l';
      s2++;
    } else {
      steps=strtol(s2,&s2,10);  
      if (dir=='r') {
        while (steps) {
          if (xy[j][i+1]=='.') {steps--; i++;}
          else if (xy[j][i+1]=='#') steps=0;
          else if (xy[j][i+1]==' ') {
            k=i;
            while (xy[j][k-1]!=' ') k--; 
            if (xy[j][k]=='#') steps=0;
            else {i=k; steps--;}
          }
        }
      }        
      else if (dir=='l') {
        while (steps) {
          if (xy[j][i-1]=='.') {steps--; i--;}
          else if (xy[j][i-1]=='#') steps=0;
          else if (xy[j][i-1]==' '){
            k=i;
            while (xy[j][k+1]!=' ') k++; 
            if (xy[j][k]=='#') steps=0;
            else {i=k; steps--;}
          }
        }
      }        
      else if (dir=='u') {
        while (steps) {
          if (xy[j-1][i]=='.') {steps--; j--;}
          else if (xy[j-1][i]=='#') steps=0;
          else if (xy[j-1][i]==' '){
            k=j;
            while (xy[k+1][i]!=' ') k++; 
            if (xy[k][i]=='#') steps=0;
            else {j=k; steps--;}
          }
        }
      }        
      else if (dir=='d') {
        while (steps) {
          if (xy[j+1][i]=='.') {steps--; j++;}
          else if (xy[j+1][i]=='#') steps=0;
          else if (xy[j+1][i]==' '){
            k=j;
            while (xy[k-1][i]!=' ') k--; 
            if (xy[k][i]=='#') steps=0;
            else {j=k; steps--;}
          }
        }
      }
    }
  }
  if (dir=='r') n=0;
  else if (dir=='d') n=1;
  else if (dir=='l') n=2;
  else n=3;
  n+=1000*j+4*i;
  printf("passwd=%d final pos=%c %d %d\n",n,dir,i,j);            
}
