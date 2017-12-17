/*



Basic Program File Structure and Sample Function Call



File: sum.cpp

Version: 3.1

Created: 9/24/96

Last updated: 10/20/99

Written by: Dr. C. S. Tritt



*/



#include <iostream>  // Header for stream I/O.

#include <iomanip> // Header for I/O manipulators.



using namespace std;



// Function declaration (prototype) with default values.



float sum(float required_term, float optional_term = 0.0);



// Main program



int main(void)

{

// Declare variables.  Some programmers like to declare their variables just

// before use.  I like to declare all of mine at the top a each function.



	int p; //  Output numeric precision.

	float a; // Units and description of a.

	float b; // Units and description of b.

	

	cout.setf(ios::showpoint); // Show decimal points.  Good until explicitly changed.



	cout << "Enter the output precision (an integer): ";

	cin >> p;

	if (!cin)

	{

		cout << "Input error.  Aborting.\n";

		return 1;

	}

	cout << setprecision(p);  // Set the precision.  Good until explicitly changed.



	cout << "Enter two real numbers to be summed: ";

	cin >> a >> b;

	if (!cin)

	{

		cout << "Input error.  Aborting.\n";

		return 2;

	}



	cout << "Entered values: a = " << a << " and b = " << b << endl;

	cout << "So sum(a, b) = " << sum(a, b) << endl;

	cout << "And sum(a) = " << sum(a) << endl;



	return 0;

}



// Define the sum function.



float sum(float x, float y)

{

	// This function returns the sum of its arguments.

	

	return (x + y);

}
