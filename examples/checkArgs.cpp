#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
        char* input1;
        if(argc != 2){
                cout << "usage: "<< argv[0] << " cmd line arg.\n";
                exit(0);
        }
        input1=argv[1];
        cout << "pls stand by. " << endl << input1 <<" is your input"  << endl;
 }

