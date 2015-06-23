#include <iostream>
using namespace std;

char ch1 = 'a', ch2 = 'b';

char ch3[4] = { 'c', 'd', 'e', 'f' };

char *ptr[3];

int main()
{
  ptr[0] = &ch1;
  ptr[1] = &ch2;
  ptr[2] = ch3;
  /*
    Base address of array ch[3] is stored at ptr[2]. Equivalently,
    ptr[2] = &ch3[0];
  */

  cout <<"Initial characters stored in ptr[0] and ptr[1]: " << *ptr[0] << " " << *ptr[1] << "\n";

  cout <<"ptr[2] : " << " " << *ptr[2] << "\n";
  cout <<"ch3[] : "<< " " << ch3 <<"\n";

  *ptr[0] = 'z';
  *ptr[1] = 'y';
  
  cout << "Final characters stored in ptr[0] and ptr[1]: " << *ptr[0] <<" " << *ptr[1] << "\n";

  return(0);
}
