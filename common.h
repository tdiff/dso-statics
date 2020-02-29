#include <string>
#include <cstdio>

struct StaticData
{
	StaticData()
		: name("this is the name of the static object")
	{
		printf("creating StaticData at 0x%p\n", this);
		fflush(stdout); 
	}

	~StaticData()
	{
		printf("destroying StaticData at 0x%p\n", this);
		fflush(stdout); 
	}

	std::string name;
};

class Common
{
public:
	static StaticData m_data;
};
