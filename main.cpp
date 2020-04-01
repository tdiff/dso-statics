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

#if 1
	// Withoud RTLD_DEEPBIND, shared object .ctor looks up symbol from global
	// scope, which in the end causes double free on static var
	return dlopen("./libshared.so", RTLD_LOCAL | RTLD_LAZY);
#else
	// With RTLD_DEEPBIND, shared object uses its own copy of the static variable.
	// Works similar to making that static var LOCAL
	return dlopen("./libshared.so", RTLD_LOCAL | RTLD_LAZY | RTLD_DEEPBIND);
#endif
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
	printf("main: %s\n", common.data().name.c_str());
	printf("main: %p\n", &common.data());
	dso_func();

	printf("closing shared obj\n");
	dlclose(handle);
	printf("leaving main\n");
}

