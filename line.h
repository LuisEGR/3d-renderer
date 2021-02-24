#ifndef LINE_H
#define LINE_H
using namespace std;

pthread_t thread1;
pthread_t thread2;
typedef struct Segment
{
  int x1;
  int y1;
  int x2;
  int y2;
} Segment;

typedef struct InputData{
	unsigned char *** raster;
	Segment linea;
	Color color;
} InputData;

//Implementing threads inside this function
void * calculate_table (void *generic_pointer){
  //Creo una estructura para guardar el input.
  InputData * input = 0;
  input = (InputData*) generic_pointer;
  //struct Segment *the_segment = 0;
  Segment the_segment = input->linea;
  Color col = input->color;
  unsigned char *** myRaster = input->raster;

  printf ("\nThis <<thread>> is calculating from (%d, %d) to (%d,%d)\n",
	  the_segment.x1, the_segment.y1, the_segment.x2, the_segment.y2);
  /* insert the line drawing algoritm here */
  /* paramets for Bresenham line drawing algorithm */
  const bool steep = (fabs(the_segment.y2 - the_segment.y1) > fabs(the_segment.x2 - the_segment.x1 ));
  
  if(steep){
    swap(the_segment.x1, the_segment.y1);
    swap(the_segment.x2, the_segment.y2);
  }

  if(the_segment.x1 > the_segment.x2){
    swap(the_segment.x1, the_segment.x2);
    swap(the_segment.y1, the_segment.y2);
  }


  int dx = the_segment.x2 - the_segment.x1;
  int dy = fabs(the_segment.y2 - the_segment.y1);
  float error = dx / 2.0f;
  const int ystep = (the_segment.y1 < the_segment.y2) ? 1 : -1;
  int y = (int)the_segment.y1;

  const int maxX = (int)the_segment.x2;
  
  for(int x=(int)the_segment.x1; x<maxX; x++)
  {
    //x += 960;
    //y += 540;
    if(steep)
    {
      //if(x >= 0 && y >= 0 && x <= 1920 && y <= 1080){
      if(x+960 > 0 && y+540 > 0 && x < 1920 && y < 1080){      
        printf ("\nPixel: %d, %d : %d,%d,%d", y, x, col.r, col.g, col.b);
        put_pixel(myRaster, y+540, x+960, col.r, col.g, col.b); 
      }
    }
    else
    {
      if(x+540 >= 0 && y+960 >= 0 && x <= 1920 && y <= 1080){
      //if(x+960 > 0 && y+540 > 0 && x+960 < 1920 && y+540 < 1080){
        printf ("\npixel: %d, %d : %d,%d,%d", x, y, col.r, col.g, col.b);
        put_pixel(myRaster, x+540, y+960, col.r, col.g, col.b); 
      }
    }
 
    error -= dy;
    if(error < 0)
    {
        y += ystep;
        error += dx;
    }
  }

  return NULL;

}
//Function to create a line using the Bresenham algorithm and 2 threads.
//int createLine(unsigned char *** raster,InputData input){
int createLine(InputData input){
/* set the limits */
	struct Segment part1;
	struct Segment part2;

	int x1 = input.linea.x1;
	int x2 = input.linea.x2;
	int y1 = input.linea.y1;
	int y2 = input.linea.y2;

	// unsigned int x = 0;
	// unsigned int y = 0;

	part1.x1 = x1;
	part1.y1 = y1;
	part1.x2 = x1 + (x2 - x1) / 2;//Hasta la mitad de la linea
	part1.y2 = y1 + (y2 - y1) / 2;//primera mitad de la linea

	part2.x1 = x1 + (x2 - x1) / 2 + 1;
	part2.y1 = y1 + (y2 - y1) / 2 + 1;
	part2.x2 = x2;
	part2.y2 = y2;

	InputData p1 = {input.raster, part2, input.color};
	InputData p2 = {input.raster, part1, input.color};
  /* create the thread */
  if (pthread_create (&thread1, NULL, calculate_table, &p1))
    {
      fprintf (stderr, "Error creating thread\n");
      return 1;
    }
  /* create the thread */
  if (pthread_create (&thread2, NULL, calculate_table, &p2))
    {
      fprintf (stderr, "Error creating thread\n");
      return 1;
    }

  /* wait for the threads to finish */
  if (pthread_join (thread1, NULL))
    {
      fprintf (stderr, "Error joining thread\n");
      return 2;
    }
  /* wait for the threads to finish */
  if (pthread_join (thread2, NULL))
    {
      fprintf (stderr, "Error joining thread\n");
      return 2;
    }
    //Print the table into the raster
 //    for (x = part1.x1, y = part1.y1; x <= part2.x2; y <= part2.y2; x++){
	// 	printf ("\n %d, %d", x, y);
	// 	raster[x][y][0] = color.r;
	// 	raster[x][y][1] = color.g;
	// 	raster[x][y][2] = color.b;		
	// }
    return 0;
        
}
//Function to get the actual quadrant of the segment
int getQuadrant(Segment &linea){
  int actualQuadrant = 0;
  //Obtaining the quadrant
  float m = (float)(linea.y2 - linea.y1) / (linea.x2 - linea.x1);
  if(m < 0 && m >= -1 && linea.x1 < linea.x2){
    //cout<<"1st Quadrant";
    actualQuadrant = 1;
  }else if(linea.y2 < linea.y1 && m < -1){
    //cout<<"2nd Quadrant";
    actualQuadrant = 2;

  }else if(linea.y2 < linea.y1 && m > 1){
    //cout<<"3rd Quadrant";
    actualQuadrant = 3;

  }else if( m > 0 && m <= 1 && linea.x2 < linea.x1){
    //cout<<"4th Quadrant";
    actualQuadrant = 4;

  }else if( m <= 0 && m >= -1 && linea.x2 < linea.x1){
    //cout<<"5th Quadrant";
    actualQuadrant = 5;

  }else if( m < -1 && linea.y1 < linea.y2){
    //cout<<"6th Quadrant";
    actualQuadrant = 6;

  }else if( m > 1 && linea.y1 < linea.y2){
    //cout<<"7th Quadrant";
    actualQuadrant = 7;

  }else if( m >= 0 && m <= 1 && linea.x1 < linea.x2){
    //cout<<"8th Quadrant";
    actualQuadrant = 8;

  }
  return actualQuadrant;
   /*Octantes*/
  // 8vo: 
  //  0<=m<=1
  //  x1<x2
  // 7mo
  //  1<m<infinito
  //  y1<y2
  // 6to
  //  -1>m>-infinito
  //  y1<y1
  // 5to
  //  x2<x1
  //  0>=m>=-1
  // 4to
  //  0<m<=1
  //  x2<x1
  // 3ro 
  //  y2<y1
  //  1<m<infinito
  // 2do
  //  y2<y1
  //  -1>m>-infinito
  // 1ro
  //  0>m>=-1
  //  x1<x2
}
#endif