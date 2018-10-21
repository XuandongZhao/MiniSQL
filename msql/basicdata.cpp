#include "stdafx.h"
#include "basicdata.h"
using namespace std;
keytype changetype(int type)
{
	if (type == 0)	return isint;
	if (type == 1)	return isfloat;
	if (type == 2)	return ischar;
	else {
		std::cerr << "UNKNOW TYPE IN CHANGETYPE" << '\n';
	}
}
const std::string path = "C://Users//Alan//Desktop//file";