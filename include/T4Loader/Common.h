#pragma once
#include <stdio.h>

#include <string>
using namespace std;

namespace T4
{
	string Format(const char* Txt,...);
	bool Read(FILE* fp,void* Var,size_t Sz,string& Error);
};

