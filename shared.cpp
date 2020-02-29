#include "common.h"
#include <cstdio>

extern "C" {

void dso_func()
{
	printf("from dso: %s\n", Common::m_data.name.c_str());	
}

}
