//****************************************************************
//
// Program to compute areas of circles
// Written by: Duncan Buell, 15 December 2004
//
//****************************************************************
//
// Program Action                       
//   We assign the value of 'pi' at compile time
//   We then assign values to the radius 'r', compute the area,
//     and print radius and area to standard output
//
//****************************************************************
//
// Variables used:
//   a  -- the area that is computed
//   pi -- pi, assigned a value at compile time
//   r  -- the radius
//
//****************************************************************

#include <stdio.h> // always include the I/O routines
#include <math.h>  // always include the math routines

int main(int argc, char *argv[])
{
  double a,pi = 3.14159,r;

  printf("program execution begins\n");

  r = 1.0;
  a = pi * r * r;
  printf("if the radius is %lf, then the area is %lf\n",r,a);

  r = 2.0;
  a = pi * r * r;
  printf("if the radius is %lf, then the area is %lf\n",r,a);

  r = 3.0;
  a = pi * r * r;
  printf("if the radius is %lf, then the area is %lf\n",r,a);

  printf("program execution terminates normally\n");
  return(0);
} // end main
