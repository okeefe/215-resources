#include <iostream>
#include <string>
using namespace std;
#include "name.h"

int main () {
        name myName;

        myName.SetLast(LAST);
        myName.SetMiddle(MI);
        myName.SetFirst(FIRST);

        cout <<"My name is: ";
        myName.PrintFirst();
        myName.PrintMiddle();
        myName.PrintLast();
	
        return 0;
}
