#include "common.h"
#include <cstdio>

void dso_func()
{
	printf("from dso: %s\n", Common::m_data.name.c_str());	
}
