#include<unistd.h>
#include<string.h>
#include<fstream>
#include<iostream>
using namespace std;
int w[10],p[10],out2[100],num=0,out1[100][3];
int refinement(int n,int W){
  if(n==0 || W==0){
    return 0;
  }
  else if(w[n-1]>W){
    return refinement(n-1,W);
  }
  else{
    out2[num]=W;
    num++;
    if(refinement(n-1,W)>=(refinement(n-1,W-w[n-1])+p[n-1])){
       out1[n-1][0]=0;
      out1[n-1][1]=0;
      out1[n-1][2]=0;
      return refinement(n-1,W);
    }
    else{
      out1[n-1][0]=n;
      out1[n-1][1]=p[n-1];
      out1[n-1][2]=w[n-1];
      return refinement(n-1,W-w[n-1])+p[n-1];
    }
  }
}    
int main(int argc,char* argv[]){
  fstream file;
  int n;
  int W;
  char filename[20],temp[20];
  int opt;
  int comb[1024][2];
  int profit;
  while((opt=getopt(argc,argv,"k:"))!=-1){
    switch(opt){
    case 'k':
      strcpy(filename,optarg);
      break;
    }
  }
  file.open(filename,ios::in);
  file>>n;
  file>>W;
  for(int i=0;i<n;i++){
    file>>temp;
    file>>p[i];
    file>>w[i];
  }
  file.close();
  cout<<"Number:"<<n<<endl;
  cout<<"Weight:"<<W<<endl;
  profit=refinement(n,W);
  int count=0;
  file.open("entries2.txt",ios::out);
  file<<n<<","<<out2[count];
  count++;
  for(int i=0;i<n;i++){
    for(int j=0;j<i*2;j++){
      file<<n-i<<","<<out2[count]<<"\t";
      count++;
    }
    file<<endl;
  }
  file.close();
  file.open("output2.txt",ios::out);
  file<<n<<"\t"<<profit<<"\t"<<W<<endl;
  for(int i=0;i<n;i++){
    if(out1[i][0]!=0)
    file<<"Item"<<out1[i][0]<<"\t"<<out1[i][1]<<"\t"<<out1[i][2]<<endl;
  }
}
