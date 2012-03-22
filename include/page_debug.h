#ifndef __PAGE_DEBUG_H
#define __PAGE_DEBUG_H

#include <iostream>
#include <string>

namespace PAGE
{
    namespace Debug
    {
			void Log(std::string message);
			void LogLine(std::string message);
			void LogError(std::string message);
			void LogWarning(std::string message);
	}
}
#endif
