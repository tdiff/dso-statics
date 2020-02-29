#include "common.h"
#include "shared.h"
#include <cstdio>

void segf()
{
	int* v = new int(0x77);
	*(v+1)=0x88;
}

int main()
{
//	segf();
	Common common;
	printf("main: %s\n", common.m_data.name.c_str());
	dso_func();
}
