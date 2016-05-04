#include "Common.h"
#include <stdarg.h>

namespace T4
{
	string Format(const char* Txt,...)
	{
		va_list Args;
		va_start(Args,Txt);
		char Str[512];
		memset(Str,0,512);
        #ifdef __APPLE__
        vsnprintf(Str,512,Txt,Args);
        #else
		vsnprintf_s(Str,512,Txt,Args);
        #endif
		va_end(Args);
		string R(Str);
		return R;
	}

	bool Read(FILE* fp,void* Var,size_t Sz,string& Error)
	{
		if(fread(Var,Sz,1,fp) != 1)
		{
			Error = Format("Failed to read %lu bytes from file",Sz);
			fclose(fp);
			return false;
		}
		return true;
	}
};
