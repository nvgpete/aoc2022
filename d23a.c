#include <stdio.h>
#include <string.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[100],*s2,xy[300][300];
  int last=110,i,j,k,dd,n,dir=0,x1,x2,y1,y2,count;
  memset(xy,0,sizeof(xy));
  f=fopen("d23.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    strncpy(xy[last]+110,s,strlen(s));
    last++;
    fgets(s,sizeof(s),f);
  }  
  fclose(f);
  for (j=0;j<300;j++) for (i=0;i<300;i++) if (xy[j][i]=='#') xy[j][i]=64;else xy[j][i]=0;
  k=0;
  do {
    for (j=0;j<300;j++) for (i=0;i<300;i++) {
      if (xy[j][i]>10 && (xy[j-1][i-1]>10 || xy[j-1][i]>10 || xy[j-1][i+1]>10 || xy[j][i-1]>10 || xy[j][i+1]>10 || xy[j+1][i-1]>10 || xy[j+1][i]>10 || xy[j+1][i+1]>10)){
        dd=dir;
        for (n=0;n<4;n++) {
          if (dd==0 && xy[j-1][i-1]<10 && xy[j-1][i]<10 && xy[j-1][i+1]<10) {
            xy[j][i]+=4;
            xy[j-1][i]++;
            break;
          } 
          if (dd==1 && xy[j+1][i-1]<10 && xy[j+1][i]<10 && xy[j+1][i+1]<10) {
            xy[j][i]+=5;
            xy[j+1][i]++;
            break;
          } 
          if (dd==2 && xy[j+1][i-1]<10 && xy[j][i-1]<10 && xy[j-1][i-1]<10) {
            xy[j][i]+=6;
            xy[j][i-1]++;
            break;
          } 
          if (dd==3 && xy[j+1][i+1]<10 && xy[j][i+1]<10 && xy[j-1][i+1]<10) {
            xy[j][i]+=7;
            xy[j][i+1]++;
            break;
          } 
          dd=(dd+1)&3;
        }  
      }
    }
   for (j=0;j<300;j++) for (i=0;i<300;i++) if (xy[j][i]>1 && xy[j][i]<10) {
      if (xy[j-1][i]>64 && (xy[j-1][i]&7)==5) xy[j-1][i]=64;
      if (xy[j+1][i]>64 && (xy[j+1][i]&7)==4) xy[j+1][i]=64;
      if (xy[j][i-1]>64 && (xy[j][i-1]&7)==7) xy[j][i-1]=64;
      if (xy[j][i+1]>64 && (xy[j][i+1]&7)==6) xy[j][i+1]=64;
      xy[j][i]=0;
    }
   count=0;
   for (j=0;j<300;j++) for (i=0;i<300;i++) if (xy[j][i]>=68) {
      if ((xy[j][i]&7)==4) {if (xy[j-1][i]>=64) printf("4\n"); xy[j-1][i]=64; xy[j][i]=0; }  
      else if ((xy[j][i]&7)==5) {if (xy[j+1][i]>=64) printf("5\n");xy[j+1][i]=64; xy[j][i]=0; }  
      else if ((xy[j][i]&7)==6) {if (xy[j][i-1]>=64) printf("6\n");xy[j][i-1]=64; xy[j][i]=0; }  
      else if ((xy[j][i]&7)==7) {if (xy[j][i+1]>=64) printf("7\n");xy[j][i+1]=64; xy[j][i]=0; }
      count++;
    }
    dir=(dir+1)&3;
    k++;
    if (k==10) {
      dd=0;
      for (j=0;j<300;j++) for(i=0;i<300;i++) dd+=(xy[j][i]>=64); 
      x1=300;x2=0;y1=300;y2=0;
      for (j=0;j<300;j++) for(i=0;i<300;i++) if(xy[j][i]){
       if (j<y1) y1=j;
       if (j>y2) y2=j;
       if (i<x1) x1=i;
       if (i>x2) x2=i;
     }
     dd=0;
     for (j=y1;j<=y2;j++) for (i=x1;i<=x2;i++) dd+=(xy[j][i]==0);
     printf("After 10 rounds, %d empty squares.\n",dd);
   }    
  } while (count);
  printf("%d rounds.\n",k);
}
