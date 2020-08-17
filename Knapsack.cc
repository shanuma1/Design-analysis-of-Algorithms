#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fstream>
using namespace std;
int main(int argc,char*argv[]){
  int p[8],w[8];
  int W=0;
  float temp=0;
  char filename[20];
  srand(time(0));
  int n;
  fstream file;
  int opt;
  while((opt=getopt(argc,argv,"k:"))!=-1){
    switch((char)opt){
    case 'k':
      strcpy(filename,optarg);
      break;
    }
  }
  cout<<endl<<filename<<endl<<endl;
  file.open(filename,ios::out);
  n=rand()%5+4;
  for(int i=0;i<n;i++){
    p[i]=rand()%21+10;
    w[i]=rand()%16+5;   
  }
  for(int i=0;i<n;i++)
    temp+=.6*w[i];
  W=temp;
  cout<<n<<"\t"<<W<<endl;
  file<<n<<"\t"<<W<<endl;
  for(int i=0;i<n;i++){
    cout<<"\nItem"<<i+1<<"\t"<<p[i]<<"\t"<<w[i];
    file<<"\nItem"<<i+1<<"\t"<<p[i]<<"\t"<<w[i];
  }
  cout<<endl;
  file.close();
}
