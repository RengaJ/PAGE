#ifndef __PAGE_DEBUG_H
#define __PAGE_DEBUG_H

#include <iostream>
#include <string>

namespace PAGE
{
	class Debug
	{
		public:
			static void Log(char* message) { std::cout << message << std::endl; }
			static void Log(std::string message) { std::cout << message << std::endl; }
			static void LogLine(std::string message) { std::cout << message; }
			static void LogLine(char* message) { std::cout << message; }

			static void LogError(char* message) { std::cout << "ERROR: " << message << std::endl; }
			static void LogError(std::string message) { std::cout << "ERROR: " << message << std::endl; }

			static void LogWarning(char* message) { std::cout << "WARNING: " << message << std::endl; }
			static void LogWarning(std::string message) { std::cout << "WARNING: " << message << std::endl; }
		private:
			Debug() {};
	};
}
#endif
