#ifndef RASTER_H
#define RASTER_H
#define W 1920
#define H 1080
typedef struct Color{
	unsigned char r;
	unsigned char g;
	unsigned char b;
} Color;

//Function to put a pixel of specified color into a specific position into the given raster.
void put_pixel(unsigned char *** raster, int x, int y, unsigned char r, unsigned char g, unsigned char b){
	raster[x][y][0] = r;
	raster[x][y][1] = g;
	raster[x][y][2] = b;
}
//Function for printing the raster into a file,
//receiving also a default background color for those pixels not 
//defined previously using put_pixel() function
void printRaster(unsigned char *** raster, Color background){
	FILE *f;
	unsigned char r, g, b;
	srand(time(NULL));
	f = fopen( "imageRaster.ppm", "w");
	fprintf(f, "P3\n");	
	fprintf(f, "1920 1080 255\n");
	for(int i=0;i<H; i++){
		for(int j=0;j<W;j++){
			r = (raster[i][j][0] != 0)?raster[i][j][0]:background.r;
			g = (raster[i][j][1] != 0)?raster[i][j][1]:background.g;
			b = (raster[i][j][2] != 0)?raster[i][j][2]:background.b;
			//fprintf(f, "%d %d %d ", background.r, background.g, 256 );
			fprintf(f, "%d %d %d ", r, g, b);
		}
		fprintf(f, "\n");
	}
	fclose(f);
}

#endif