#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[5700],*s2,xy[205][205],dir,c;
  char left[4][3]={{2,0,'r'},{2,0,'d'},{0,1,'r'},{0,1,'d'}},right[4][3]={{2,1,'l'},{0,2,'u'},{0,2,'l'},{2,1,'u'}};
  char up[3][3]={{1,1,'r'},{3,0,'r'},{3,0,'u'}},down[3][3]={{0,2,'d'},{3,0,'l'},{1,1,'l'}};
  int last=1,i,j,ki,kj,n,steps,wid=0,sz,used[6][6],ni,nj;
  memset(xy,' ',sizeof(xy));
  memset(used,0,sizeof(used));
  f=fopen("d22.txt","r");
  fgets(s,sizeof(s),f);
  if((s2=strchr(s,'\n')))*s2=0;
  while (*s!=0) {
    if(strlen(s)>wid) wid=strlen(s);
    strncpy(xy[last]+1,s,strlen(s));
    last++;
    fgets(s,sizeof(s),f);
    if((s2=strchr(s,'\n')))*s2=0;
  }
  fgets(s,sizeof(s),f);  
  if((s2=strchr(s,'\n')))*s2=0;
  fclose(f); 
  if (last>wid) sz=(last-1)/4; else sz=wid/4;
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
      while (steps) {  
        if (dir=='r') {
          while (steps) {
            if (xy[j][i+1]=='.') {steps--; i++;}
            else if (xy[j][i+1]=='#') steps=0;
            else if (xy[j][i+1]==' ') {
              ni=(i-1)/sz;        
              nj=(j-1)/sz;
              if (right[nj][2]=='u') {kj=(right[nj][0]+1)*sz; ki=right[nj][1]*sz+(j-1)%sz+1;}
              else if (right[nj][2]=='l') {kj=(right[nj][0]+1)*sz-(j-1)%sz; ki=(right[nj][1]+1)*sz;}
              if (xy[kj][ki]=='#') steps=0; 
              else {j=kj; i=ki; dir=right[nj][2]; steps--;break;} 
            }
          }
        }        
        else if (dir=='l') {
          while (steps) {
            if (xy[j][i-1]=='.') {steps--; i--;}
            else if (xy[j][i-1]=='#') steps=0;
            else if (xy[j][i-1]==' '){
              ni=(i-1)/sz;        
              nj=(j-1)/sz;
              if (left[nj][2]=='d') {kj=(left[nj][0])*sz+1; ki=left[nj][1]*sz+(j-1)%sz+1;}
              else if (left[nj][2]=='r') {kj=(left[nj][0]+1)*sz-(j-1)%sz; ki=(left[nj][1])*sz+1;}
              if (xy[kj][ki]=='#') steps=0;
              else {j=kj; i=ki; dir=left[nj][2]; steps--;break;}
            }
          }
        }        
        else if (dir=='u') {
          while (steps) {
            if (xy[j-1][i]=='.') {steps--; j--;}
            else if (xy[j-1][i]=='#') steps=0;
            else if (xy[j-1][i]==' '){
              ni=(i-1)/sz;        
              nj=(j-1)/sz;
              if (up[ni][2]=='u') {kj=(up[ni][0]+1)*sz; ki=up[ni][1]*sz+(i-1)%sz+1;}
              else if (up[ni][2]=='r') {kj=up[ni][0]*sz+(i-1)%sz+1; ki=(up[ni][1])*sz+1;}
              if (xy[kj][ki]=='#') steps=0;
              else {j=kj; i=ki; dir=up[ni][2]; steps--;break;}
            }
          }
        }         
        else if (dir=='d') {
          while (steps) {
            if (xy[j+1][i]=='.') {steps--; j++;}
            else if (xy[j+1][i]=='#') steps=0;
            else if (xy[j+1][i]==' '){
              ni=(i-1)/sz;        
              nj=(j-1)/sz;
              if (down[ni][2]=='d') {kj=(down[ni][0])*sz+1; ki=down[ni][1]*sz+(i-1)%sz+1;}
              else if (down[ni][2]=='l') {kj=down[ni][0]*sz+(i-1)%sz+1; ki=(down[ni][1]+1)*sz;}
              if (xy[kj][ki]=='#') steps=0;
              else {j=kj; i=ki; dir=down[ni][2]; steps--;break;}
            }
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
  printf("passwd=%d\n",n);            
}
