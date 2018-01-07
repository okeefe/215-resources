/*



Basic Program File Structure and Sample Function Calls



File: stddev.cpp

Version: 1.0 

Created: 02/08/06 

Last updated: 02/08/06

Adapted from code written by: Dr. C. S. Tritt

Modified by : Pat O'Keefe


*/



#include <iostream>  // Header for stream I/O.

#include <iomanip> // Header for I/O manipulators.

#include <math.h>  // sqrt ()

using namespace std;



// Function declarations (prototype) with default values.



float sum(float required_term, float optional_term = 0.0);

float avg(float required_term, float required_term);

float stdev(float required_term, int required_term);

// Main program



int main(void)

{

// Declare variables.  Some programmers like to declare their variables just

// before use.  I like to declare all of mine at the top a each function.

	int p=4; //  Output numeric precision.

	float a; // Units and description of a.

	float b=0; // Units and description of b.

	int n=0;  //number of values
	
	float dev=0; // deviation
	

	cout.setf(ios::showpoint); // Show decimal points.  Good until explicitly changed.

	cout << setprecision(p);  // Set the precision.  Good until explicitly changed.


        while (cin) 
	{

	cin >> a;

        if (a == -1000) //check for terminating input.
                {
                cout << "End of Input. \n";
                cout << "working with " << n << " values." << endl;
                cout << "Avg: " << avg(b, n) << endl;
                cout << "stddev: " << stdev(dev, n) << endl;
                return 0;
                }

	n = n + 1;

	b=sum(a,b);

	dev = dev + (pow(a - avg(b, n) , 2));

	}

}



// Define the sum, avg, and stdev functions.



float sum(float x, float y)

{

	// This function returns the sum of its arguments.

	

	return (x + y);

}


float avg(float sum, float n)

{
	return (sum / n);

}


float stdev(float dev, int n)

{
	
	return (sqrt( (dev) / (n-1)));

}
