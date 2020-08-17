#include<unistd.h>
#include<string.h>
#include<fstream>
#include<iostream>
#include<math.h>
using namespace std;
int count=0,bound,final_profit=0;
int p[10],w[10],item[10],num=0;
int comb;
int n;
int W;
fstream entry;
void bin(unsigned n) 
{ 
    if (n > 1) 
    bin(n>>1); 
      
    cout<<(n & 1); 
}
int KWF2(int i,int weight,int profit){
  int b=profit;
  while(weight<W && i<=n){
    if(weight+w[i]<=W){
      weight=weight+w[i];
      b=b+p[i];
    }
    else{
      b=b+p[i]*(W-weight)/w[i];
      weight=W;
    }
    i++;
  }
  return b;
}
    
int check(){
  int weight=0;
  int profit=0;
  int temp2[10];
  int temp1=0;
  for(int i=0;i<n;i++){
    if(comb&(int)pow(2,n-1-i)){
      if((weight+w[i])<=W){
	temp2[temp1++]=i;
	weight=weight+w[i];
	profit=profit+p[i];
	bound=KWF2(i+1,weight,profit);
	entry<<++count<<" "<<profit<<" "<<weight<<" "<<bound<<endl;
	if(bound<profit)
	  return 0;
      }
      else{
	if(profit>=final_profit){
	  final_profit=profit;
	  for(int j=0;j<temp1;j++)
	    item[j]=temp2[j];
	  num=temp1;
	}
	return 0;
      }
    }
  }
  if(profit>=final_profit){
	  final_profit=profit;
	  for(int j=0;j<temp1;j++)
	    item[j]=temp2[j];
	  num=temp1;
	}
  return 0;
}    
int main(int argc,char* argv[]){
  fstream file;
  char filename[20],temp[20];
  int opt;
  entry.open("entries3.txt",ios::out);
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
  comb=pow(2,n)-1;
  int r;
  while(comb){
    check();
    comb--;
  }
  cout<<"Profit is:"<<final_profit;
  entry.close();
  file.open("output3.txt",ios::out);
  file<<num<<"\t"<<final_profit<<"\t"<<W<<endl;
  for(int i=0;i<num;i++){
    file<<"Item"<<i+1<<"\t"<<p[item[i]]<<"\t"<<w[item[i]]<<endl;
  }
  file.close();
}
