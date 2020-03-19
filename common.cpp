#include "common.h"

#if !USE_WRAPPER
StaticData Common::m_data;
#else
SharedStaticObject<StaticData> Common::m_data;
#endif
