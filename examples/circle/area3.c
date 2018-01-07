//*****************************************************************
//
// Program 'area3.c' to compute areas of circles
// Written by: Duncan Buell, 15 December 2004
//
//*****************************************************************
//
// Program Action                       
//
// This is a variant version of the previous program 'area2.c' 
// We assign the value of the parameter 'pi' at compile time
// We then erroneously try to assign a new value of 'pi'
//
// The purpose of this program is to show that using parameter
// variables can prevent us from making careless errors
//
//*****************************************************************
//
// Variables used:
//   a  -- the area that is computed
//   r  -- the radius
//
// Parameter variables used:
//   pi -- the real parameter pi, assigned a value at compile time
//
//*****************************************************************

#include <stdio.h> // always include the I/O routines
#include <math.h>  // always include the math routines

#define PI 3.14159 // by convention defined constants are all caps

int main(int argc, char *argv[])
{
  double a,r; // this line changed for area3

  printf("program execution begins\n");

  r = 1.0;
  a = PI * r * r;
  printf("if the radius is %lf, then the area is %lf\n",r,a);

//  PI = 4.0; // this line was added for the area2 program
  r = 2.0;
  a = PI * r * r;
  printf("if the radius is %lf, then the area is %lf\n",r,a);

  r = 3.0;
  a = PI * r * r;
  printf("if the radius is %lf, then the area is %lf\n",r,a);

  printf("program execution terminates normally\n");
  return(0);
} // end main
