#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string>
#include<fstream>
using namespace std;
void display(int a[10][10],int n){
  cout<<endl;
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      cout<<a[i][j]<<" ";
    }
    cout<<endl;
  }
}
void dis_path(string a[10][10],int n,int b[10][10]){  //Function to display result.
  for(int i=0;i<n;i++){
    cout<<"V"<<i+1<<"-Vj:Shortest path and length"<<endl;
    for(int j=0;j<n;j++){
      cout<<a[i][j]<<":"<<b[i][j]<<endl;
    }
  }
}
int main(){
  srand(time(0));
  int n=(rand()%6+5);
  int result,array[10][10];        //a[10][10] is the randomly generated matrix
  string path[10][10],temp;        //path[10][10] is the matix to show paths
  fstream file;
  cout<<"Randomly selected n:"<<n<<endl;
  for(int i=0;i<n;i++){
    for(int j=i;j<n;j++){
      if(i==j)
	array[i][j]=0;
      else{
	array[i][j]=rand()%10+1;
	array[j][i]=array[i][j];
      }
    }
  }
  //Starting to create path[10][10]
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++){
       file.open("temp.txt",ios::out);
       file<<"V"<<i+1;
       file.close();
       file.open("temp.txt",ios::in);
       file>>path[i][j];
       file.close();
    }
  cout<<"Amatrix:";
  display(array,n);
  //Start all pair Shortest Path
  for(int k=0;k<n;k++){
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
	result=(array[i][j]<(array[i][k]+array[k][j]))?array[i][j]:(array[i][k]+array[k][j]);
	//Creating paths[10][10] matrix and array[10][10] Pmatrix.
	if(result==array[i][j]){
	  path[i][j]=path[i][j];
	}
	else{
	  path[i][j].append(" ");
	   file.open("temp.txt",ios::out);
	   file<<"V"<<k+1;
	   file.close();
	   file.open("temp.txt",ios::in);
	   file>>temp;
	   file.close();
	   path[i][j].append(temp);
	}
	//For finding lengths.
	array[i][j]=result;
      }
    }
  }
  //Ending path[10][10] matrix.
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++){
      file.open("temp.txt",ios::out);
      file<<"V"<<j+1;
      file.close();
      file.open("temp.txt",ios::in);
      file>>temp;
      file.close();
      path[i][j].append(" ");
      path[i][j].append(temp);
    }
  cout<<"Pmatrix:";
  display(array,n);//Displaying the shortest paths lengths.
  cout<<endl;
  cout<<endl<<"The shortest paths are :"<<endl;  
  dis_path(path,n,array);//Displaying the shortest paths as route map.
  return 0;
}
