#include <stdio.h>
#include <string.h>
#include <stdlib.h>
  struct node {
    char name[24];
    char type;
    int parent,size,nc,child[20];
  };
  struct node nd[1000];  
int sum(int n) {
  int tot=0,i;
  if (nd[n].type=='f') return nd[n].size;
  for (i=0;i<nd[n].nc;i++) tot+=sum(nd[n].child[i]);
  nd[n].size=tot;
  return tot;
}   
int main(int argc,char **argv) {
  FILE *f;
  char s[100],*s2;
  int last=1,cwd=0,i,total,best;
  strcpy(nd[0].name,"/");
  nd[0].type='d';
  nd[0].parent=0;
  nd[0].size=-1;
  f=fopen("d07.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    if (s[0]=='$') {
      if (s[2]=='c') {
        if (s[5]=='/') cwd=0;
        else if (s[5]=='.') cwd=nd[cwd].parent;
        else for (i=0;i<nd[cwd].nc;i++) if (strcmp(s+5,nd[nd[cwd].child[i]].name)==0) cwd=nd[cwd].child[i];
      }
    } else { //result of ls
      if (s[0]=='d') {
        strcpy(nd[last].name,s+4);
        nd[last].type='d';
        nd[last].parent=cwd;
        nd[last].size=-1;
        nd[last].nc=0;
        nd[cwd].child[nd[cwd].nc++]=last;
        last++;
      } else {
        nd[last].size=strtol(s,&s2,10);
        strcpy(nd[last].name,s2+1);
        nd[last].type='f';
        nd[last].parent=cwd;
        nd[cwd].child[nd[cwd].nc++]=last;
        last++;
      }
    }             
    fgets(s,sizeof(s),f);
  }  
  fclose(f);
  sum(0); 
  total=0;
  for (i=0;i<last;i++) if (nd[i].type=='d' && nd[i].size<=100000) total+=nd[i].size;
  printf("Total size=%d\n",total);
  total=nd[0].size-40000000;
  best=70000000;
  for (i=0; i<last;i++) if (nd[i].type=='d' && nd[i].size>total) {
    if (nd[i].size<best) best=nd[i].size;
  }
  printf("Smallest=%d\n",best);  
}
