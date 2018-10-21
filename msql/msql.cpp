// msql.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "interpriter.h"
using namespace std;

BufferManager m;
Interpreter inp;
string wordline;
int main()
{

	cout << "welcome come to sk, zxd, jck's minisql" << endl;
	cout << ">> ";
	while (getline(cin, wordline, ';'))
	{

		if (inp.interpreter(wordline) == -1)
		{
			return 0;
		}
		cout << endl << ">> ";
	}
	return 0;
}

