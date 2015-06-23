#include <iostream>
using namespace std;

char *pPointer[1];

void SomeFunction()
{
	*pPointer = new char[1];
        *pPointer = "123ABCD1234567890";
}

int main() {
        SomeFunction();
        printf("Value of *pPointer: %s\n", *pPointer);
}
