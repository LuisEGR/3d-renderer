#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <math.h>
#include "raster.h"
#include "line.h"
#include "polygon.h"
int main(){
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
	Color linec = {122, 122, 122};
	Segment linea2to1 = {-138, 310, 129, 399};
	Segment linea1to3 = {129, 399, 213, 304};
	Segment linea3to2 = {213, 304, 138, 310};
	drawPolygon(myRaster, linea2to1, linea1to3, linea3to2, linec);

	// InputData input;
	// input = {myRaster, linea2to1, linec};	
	// createLine(input);
	// input = {myRaster, linea1to3, linec};	
	// createLine(input);
	// input = {myRaster, linea3to2, linec};	
	// createLine(input); 


	printRaster(myRaster, fondo);
}

