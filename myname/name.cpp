#include <iostream>
#include <string>
using namespace std;
#include "name.h"

void name::GetFirst(string str) {
	str=first;
}

void name::SetFirst(string str) {
	first=str;
}

void name::GetMiddle(string str) {
	str=middle;
}

void name::SetMiddle(string str) {
	middle=str;
}

void name::GetLast(string str) {
	str=last;
}

void name::SetLast(string str) {
	last=str;
}

void name::PrintLast() {
	cout << last << "\n";
}
void name::PrintMiddle() {
        cout << middle;
}
void name::PrintFirst() {
        cout << first;
}
