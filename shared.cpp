#include "common.h"
#include <cstdio>

extern "C" {

void dso_func()
{
	printf("from dso: %s\n", Common::data().name.c_str());	
	printf("from dso: %p\n", &Common::data());
}

}
