#include "common.h"
#include "shared.h"
#include <cstdio>
#include <dlfcn.h>

void segf()
{
	int* v = new int(0x77);
	*(v+1)=0x88;
}

void* load_shared()
{
	printf("loading shared object\n");

	// Withoud RTLD_DEEPBIND, shared object .ctor looks up symbol from global
	// scope, which in the end causes double free on static var
	//return dlopen("./libshared.so", RTLD_LOCAL | RTLD_LAZY);
	
	// With RTLD_DEEPBIND, shared object uses its own copy of the static variable.
	// Works similar to making taht static var LOCAL
	return dlopen("./libshared.so", RTLD_LOCAL | RTLD_LAZY | RTLD_DEEPBIND);
}

int main()
{
	auto handle = load_shared();
	if (! handle)
	{
		printf("failed to load libshared.so: %s\n", dlerror());
		exit(1);
	}

	auto dso_func = (void (*)()) dlsym(handle, "dso_func");
	if (! dso_func)
	{
		printf("failed to find dso_func in shared object: %s\n", dlerror());
		exit(1);
	}

	Common common;
	printf("main: %s\n", common.m_data.name.c_str());
	dso_func();

	printf("closing shared obj\n");
	dlclose(handle);
	printf("leaving main\n");
}
