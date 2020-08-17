#include<unistd.h>
#include<string.h>
#include<fstream>
#include<iostream>
#include<math.h>
using namespace std;
int main(int argc,char* argv[]){
  fstream file;
  int p[10],w[10];
  int n;
  int W;
  char filename[20],temp[20];
  int opt;
  int profit=0,weight=0;
  int comb;
  int temp_p=0;
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
  for(int i=0;i<pow(2,n);i++){
    for(int j=0;j<n;j++){
      if( i&(int)(pow(2,j)) ){
	profit+=p[j];
	weight+=w[j];
      }
    }
    if( (weight<=W) && (profit>temp_p)){
      comb=i;
      temp_p=profit;
    }
    profit=0;
    weight=0;
  }
  cout<<"Profit is: "<<temp_p<<endl;
  file.open("output1.txt",ios::out);
  file<<n<<"\t"<<temp_p<<"\t"<<W;
  for(int j=0;j<n;j++){
    if( comb&(int)(pow(2,j)) )
      file<<"\nItem"<<j+1<<"\t"<<p[j]<<"\t"<<w[j];
  }
}
