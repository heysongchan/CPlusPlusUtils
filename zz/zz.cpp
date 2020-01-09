// zz.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <memory.h>
#include <stdio.h>
#include <string>
#include <locale>
#include <codecvt>
#include <fstream>
#include <sstream>
#include <iostream>
#include "util.h"


using namespace std;

class zz
{
public:
	zz(){
		id = 11;
		char* c = "heysong";
		memcpy(name, c, 8);
	}
	unsigned id;
	char name[200];

};

void write()
{
	zz* z = new zz();
	unsigned size = sizeof(*z);
	char* c = new char[size];
	memset(c, 0, size);
	memcpy(c, z, size);
	FILE* f = fopen("H:/zz/zz", "w");
	unsigned n = 0;
	while (n < size)
	{
		fputc(c[n], f); n++;
	}
	printf("%d\n", size);
}

void read(){
	FILE* f = fopen("H:/zz/zz", "r");
	char* c = new char[204];
	memset(c, 0, 204);
	fread(c, 1, 204, f);
	zz* z = (zz*)c;
	printf("%p\n   %d\n", z,sizeof(*z));
}

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace std;
	

	wstring wstr=s2ws("你");


	
	return 0;
}

