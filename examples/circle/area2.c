//*****************************************************************
//
// Program 'area2.f90' to compute areas of circles
// Written by: Duncan Buell, 15 December 2004
//
//*****************************************************************
//
// Program Action                       
//
// This is a variant version of the previous program 'area1.c' 
// We assign the value of 'pi' at compile time
// We then assign a value to 'r' and print out the area
// We then erroneously assign a new value of 'pi', recompute
//     the area, and print out the erroneous value of the area
//
// The purpose of this program is to show that assigning values
// at compile time is dangerous and deprecated (except if done
// as in the next program)
//
//*****************************************************************
//
// Variables used:
//   a  -- the area that is computed
//   pi -- pi, assigned a value at compile time
//   r  -- the radius
//
//*****************************************************************

#include <stdio.h> // always include the I/O routines
#include <math.h>  // always include the math routines

int main(int argc, char *argv[])
{
  double a,pi = 3.14159,r;

  printf("program execution begins\n");

  r = 1.0;
  a = pi * r * r;
  printf("if the radius is %lf, then the area is %lf\n",r,a);

  pi = 4.0; // this line was added for the area2 program
  r = 2.0;
  a = pi * r * r;
  printf("if the radius is %lf, then the area is %lf\n",r,a);

  r = 3.0;
  a = pi * r * r;
  printf("if the radius is %lf, then the area is %lf\n",r,a);

  printf("program execution terminates normally\n");
  return(0);
} // end main
