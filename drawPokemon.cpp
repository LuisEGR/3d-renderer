#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <vector>
#include <sstream>
#include "raster.h"
#include "line.h"
#include "polygon.h"
#define SCALE_FACTOR 10
using namespace std;

int main()
{
	
	unsigned char ***myRaster;	
	//Asigno memoria dinamicamente para mi matriz de 3 dimensiones..para el raster
	myRaster=(unsigned char***)malloc(1080*sizeof(unsigned char**));
	for(int i=0; i < H; i++)
	{
		myRaster[i]=(unsigned char**)malloc(1920*sizeof(unsigned char*));		
		for(int j=0; j < W; j++)
		{
			myRaster[i][j]=(unsigned char*)malloc(3*sizeof(unsigned char));
		}
	}
	Color fondo = {10, 10, 10}; //{R, G B}
	Color linec = {255, 255, 51};	
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
   fc = 0;
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
         // cout<<"VCX("<<vc<<"): "<<vcs_x[vc]<<"\t";
         // cout<<"VCY("<<vc<<"): "<<vcs_y[vc]<<"\t";
         // cout<<"VCZ("<<vc<<"): "<<vcs_z[vc]<<"\t\n";
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
         // cout<<"FC1("<<fc<<"): "<<fcs_1[fc]<<"\t";
         // cout<<"FC2("<<fc<<"): "<<fcs_2[fc]<<"\t";
         // cout<<"FC3("<<fc<<"): "<<fcs_3[fc]<<"\t\n";
         fc++;
      }
     //file_contents += str;
     //file_contents.push_back('|');
   }  
   cout<<"vertices: "<<vc<<endl;
   cout<<"Caras: "<<fc<<endl;

   for(int i = 0; i<1000; i++){
    //Vista Frontal xy
   	Segment l1 = {vcs_x[fcs_1[i]],vcs_y[fcs_1[i]],vcs_x[fcs_2[i]],vcs_y[fcs_2[i]]};
   	Segment l2 = {vcs_x[fcs_2[i]],vcs_y[fcs_2[i]],vcs_x[fcs_3[i]],vcs_y[fcs_3[i]]};
   	Segment l3 = {vcs_x[fcs_3[i]],vcs_y[fcs_3[i]],vcs_x[fcs_1[i]],vcs_y[fcs_1[i]]};

    //Vista superior xz
    // Segment l1 = {vcs_z[fcs_1[i]],vcs_x[fcs_1[i]],vcs_z[fcs_2[i]],vcs_x[fcs_2[i]]};
    // Segment l2 = {vcs_z[fcs_2[i]],vcs_x[fcs_2[i]],vcs_z[fcs_3[i]],vcs_x[fcs_3[i]]};
    // Segment l3 = {vcs_z[fcs_3[i]],vcs_x[fcs_3[i]],vcs_z[fcs_1[i]],vcs_x[fcs_1[i]]};

    //Vista lateral yz
    // Segment l1 = {vcs_z[fcs_1[i]],vcs_y[fcs_1[i]],vcs_z[fcs_2[i]],vcs_y[fcs_2[i]]};
    // Segment l2 = {vcs_z[fcs_2[i]],vcs_y[fcs_2[i]],vcs_z[fcs_3[i]],vcs_y[fcs_3[i]]};
    // Segment l3 = {vcs_z[fcs_3[i]],vcs_y[fcs_3[i]],vcs_z[fcs_1[i]],vcs_y[fcs_1[i]]};


   	//Segment linea2to1 = {138, 310, 129, 399};
	//Segment linea1to3 = {129, 399, 213, 304};
	//Segment linea3to2 = {213, 304, 138, 310};
	drawPolygon(myRaster, l1, l2, l3, linec);
   }
	printRaster(myRaster, fondo);

   return 0;
}