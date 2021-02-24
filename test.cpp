#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <vector>
#include <sstream>
#include "raster.h"
#include "line.h"

#define SCALE_FACTOR 10
using namespace std;

int main()
{
   //ifstream archivo("who.is.that.pokemon.obj");
   ifstream file("who.is.that.pokemon.obj");
   string str;
   string file_contents;
   string vertices[1000];
   string faces[1000];
   
   int fcs_1[1000];
   int fcs_2[1000];
   int fcs_3[1000];

   int vcs_x[1000];
   int vcs_y[1000];
   int vcs_z[1000];

   int vc, fc;
   vc = 1;
   fc = 1;
   string::size_type sz;

   while (getline(file, str))
   {
   vector<string>tokens;
   string buf="";            
      if(str.substr(0,1) == "v"){
         vertices[vc] = str.substr(2);         
         stringstream ss(vertices[vc]);
         while(ss>>buf){
         	tokens.push_back(buf);
         }
         vcs_x[vc] = (int) (stof(tokens[0],&sz) * SCALE_FACTOR); 
         vcs_y[vc] = (int) (stof(tokens[1],&sz) * SCALE_FACTOR); 
         vcs_z[vc] = (int) (stof(tokens[2],&sz) * SCALE_FACTOR);
         cout<<"VCX: "<<vcs_x[vc]<<"\t";
         cout<<"VCY: "<<vcs_y[vc]<<"\t";
         cout<<"VCZ: "<<vcs_z[vc]<<"\t\n";
         vc++;
      }
      if(str.substr(0,1) == "f"){
        faces[fc] = str.substr(2);
        stringstream ff(faces[fc]);
      	while(ff>>buf){
        	tokens.push_back(buf);
        }
        //Saving the faces points on int format, so I can use as index in the vertex array
         fcs_1[fc] = stoi(tokens[0],&sz);
         fcs_2[fc] = stoi(tokens[1],&sz);
         fcs_3[fc] = stoi(tokens[2],&sz);
         cout<<"FC1: "<<fcs_1[fc]<<"\t";
         cout<<"FC2: "<<fcs_2[fc]<<"\t";
         cout<<"FC3: "<<fcs_3[fc]<<"\t\n";
         fc++;
      }
     //file_contents += str;
     //file_contents.push_back('|');
   }  
   //Printing the faces on the vector;
   for (int i = 0; i < 1000; ++i)
   {
      cout<<faces[i]<<"|";
   }
   cout<<"vertices: "<<vc;
   cout<<"Caras: "<<fc;
   return 0;
}
