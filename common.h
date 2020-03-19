#include <string>
#include <cstdio>
#include <type_traits>

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

template <typename T>
struct SharedStaticObject
{
	std::size_t m_count; // will be zero-initialized as long as the owner is static
	std::aligned_storage_t<sizeof(T), alignof(T)> m_store;

	SharedStaticObject()
	{
		printf("m_count: %zu\n", m_count);
		if (m_count++ == 0)
		{
			new (&m_store) T();
		}
	}

	~SharedStaticObject()
	{
		if (--m_count == 0)
		{
			reinterpret_cast<T*>(&m_store)->~T();
		}
	}

	T& get()
	{
		return *reinterpret_cast<T*>(&m_store);
	}
};

#define USE_WRAPPER 1

class Common
{
#if !USE_WRAPPER
	static StaticData m_data;
#else
	static SharedStaticObject<StaticData> m_data;
#endif

public:
	static StaticData& data()
	{
#if !USE_WRAPPER
		return m_data;
#else
		return m_data.get();
#endif
	}
};
