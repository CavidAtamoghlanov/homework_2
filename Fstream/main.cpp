#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;
typedef unsigned short ushort;
#include"models.h"
#include"start.h"


int main()
{
	try
	{
		start();
	}
	catch (exception& ex)
	{
		cout << ex.what() << endl;
	}


	return 0;
}