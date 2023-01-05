#include <stdio.h>
#include <string.h>
struct state {
  char bot[4],res[4],min,nbot,bcnt; //# of bots, # of resources, minute, next bot to build, # of bots built
};
int oc[4],pc[4],best; // ore to build, previous res to build for bots 2,3
char order[20]; 
void next(struct state st) {
  int rr[4],tt[4],nb=st.nbot,n,k,n2,bb=0;
  while (st.min<24 && bb==0) {
    st.min++;
    for (n=0;n<4;n++) rr[n]=st.bot[n]; // save new resources created
    if (st.res[0]>=oc[nb] && (nb<2 || st.res[nb-1]>=pc[nb])) { // build next bot if possible
      st.res[0]-=oc[nb];
      if (nb>=2) st.res[nb-1]-=pc[nb];
      st.bot[nb]++;
      bb=1;
    }
// heuristics to terminate path if we seem to be overbuilding some resources    
#ifdef FAST      
    if (st.res[0]>20 || st.res[1]>3*pc[2] || st.res[2]>2*pc[3]) return;
#endif    
#ifdef FASTEST      
    if (st.res[0]>6 || st.res[1]>2*pc[2]+1 || st.res[2]>pc[3]) return;
#endif    
    for (n=0;n<4;n++) st.res[n]+=rr[n]; // add resources saved above
  }
  if (st.min>=24) { // done, see how we did
    if (st.res[3]>best) best=st.res[3];
    return;
  }
// figure out reasonable order to try to build next bot  
  if (st.res[0]>=oc[0]) tt[0]=0; else tt[0]=(oc[0]-st.res[0])/st.bot[0]+1;
  if (st.res[0]>=oc[1]) tt[1]=0; else tt[1]=(oc[1]-st.res[0])/st.bot[0]+1;
  if (st.bot[1]==0) tt[2]=100;
  else {
    if (st.res[0]>=oc[2]) n=0; else n=(oc[2]-st.res[0])/st.bot[0]+1;
    if (st.res[1]>=pc[2]) tt[2]=0; else tt[2]=(pc[2]-st.res[1])/st.bot[1]+1;
    if (n>tt[2]) tt[2]=n;;
  }  
  if (st.bot[2]==0) tt[3]=100;
  else {
    if (st.res[0]>=oc[3]) n=0; else n=(oc[3]-st.res[0])/st.bot[0]+1;
    if (st.res[2]>=pc[3]) tt[3]=0; else tt[3]=(pc[3]-st.res[2])/st.bot[2]+1;
    if (n>tt[3]) tt[3]=n;;
  }
  st.bcnt++;
// call self to build next bot  
  while (1) { 
    n2=3; n=tt[3];
    for (k=2;k>=0;k--) if(tt[k]<n) {n2=k;n=tt[k];}
    if (n!=100) {
      tt[n2]=100;
      st.nbot=n2;
      next(st);
    } else break;
  }        
}  
int main(int argc,char **argv) {
  FILE *f;
  struct state st;
  char s[200],*s2;
  int ocost[32][4],pcost[32][4];
  int n,d[6],total=0;
  f=fopen("d19.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    sscanf(s,"Blueprint %d: Each ore robot costs %d ore. Each clay robot costs %d ore. Each obsidian robot costs %d ore and %d clay. Each geode robot costs %d ore and %d",&n,d,d+1,d+2,d+3,d+4,d+5);
    ocost[n][0]=oc[0]=d[0]; ocost[n][1]=oc[1]=d[1]; ocost[n][2]=oc[2]=d[2]; pcost[n][2]=pc[2]=d[3]; ocost[n][3]=oc[3]=d[4]; pcost[n][3]=pc[3]=d[5];
    memset(&st,0,sizeof(st));
    best=0;
    st.bot[0]=1;
    if (oc[0]>=oc[1]) st.nbot=1;
    order[0]=st.nbot+'0';
    next(st);
    st.nbot=1-st.nbot;
    order[0]=st.nbot+'0';
    next(st);
    total+=best*n;
    fgets(s,sizeof(s),f);
  }  
  fclose(f);
  printf("Total=%d\n",total); 
}
