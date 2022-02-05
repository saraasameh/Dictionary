#include<iostream>
#include "tree.cpp"
#include<string>

using namespace std;

int main()
{
	tree<string> B;

	
	B.readfromfile();
	B.menu();
	

	system("pause");
	return 0;
}