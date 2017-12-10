#include <iostream>

using namespace std;

int i = 0;

int *ptr1;

int main()
{
  ptr1 = new int;

  /*
    'new' allocates memory for an unnamed integer. The base memory address
    of the variable is then assigned to ptr1.  We can freely access the 
    unnamed variable through the pointer.
  */

  *ptr1 = 10;

  *ptr1 = 2 + *ptr1;

  cout << "Dynamic memory allocation : Value of ptr1 is " << *ptr1 << "\n";

  /*
    Free up allocated memory by dereferencing.  Use the pointer once more
    by assigning it another memory address.
  */

  delete ptr1;

  /*
    Same pointer is now allocated the base address of an array
  */

  ptr1 = new int[3];

  /*
    The unnamed array can be easily accessed using the pointer ptr1.
    There is more than one way to do this.
  */

  *(ptr1+0) = 2;
  *(1 + ptr1) = 4;
  2[ptr1]   = 6;

  cout << "Printing array of Pointers: \n";
  for (i=0; i<3; i=i+1)
    {
      cout << "ptr1[" << i << "] = " << ptr1[i] << "\n";
    }

  /*
    Free up memory by dereferencing the pointer.  Array size need not be 
    specified.  Deleted memory is returned to free store.
  */

  delete[ ] ptr1;

  return (0);
}

