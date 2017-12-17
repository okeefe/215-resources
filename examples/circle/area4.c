//*****************************************************************
//
// Program 'area4.c' to compute areas of circles
// Written by: Duncan Buell, 15 December 2004
//
//*****************************************************************
//
// Program Action                       
//
// This is a variant version of the previous program 'area3.c' 
// We declare 'pi' to be a double variable, not a parameter, so
//   that we will be permitted to assign it to get the best
//   possible numerical value for the constant pi.
//
// The best possible way to get pi is done below.  Why is this?
// 1. The arc tangent of 1.0 is pi/4, and the function will
//    compute this to the maximum accuracy possible on the
//    current computer being used
// 2. Multiplication by a power of 2 (in this case, by 4.0)
//    will only change the exponent but otherwise not affect the
//    numerical accuracy of the representation for pi           
//
//*****************************************************************
//
// Note that one other thing this demonstrates is that there is
// no magic in programming, no perfect answers.  Using a parameter
// is the safest thing from a program correctness and "don't shoot
// yourself in the foot" point of view, but sometimes one has to
// use less-safe methods in order to get maximally-accurate
// programs.
//
//*****************************************************************
//
// Variables used:
//   a  -- the area that is computed
//   pi -- the value pi, computed using the arc tangent
//   r  -- the radius
//
//*****************************************************************

#include <stdio.h> // always include the I/O routines
#include <math.h>  // always include the math routines

int main(int argc, char *argv[])
{
  double a,pi,r; // this line changed for area3

  printf("program execution begins\n");

  pi = 4.0 * atan(1.0);
  printf("the computed value of pi is %lf\n",pi);

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
