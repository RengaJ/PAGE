#include "page_debug.h"

using namespace PAGE;

void Debug::Log(std::string message)
{
    std::cout << message << std::endl;
}
void Debug::LogLine(std::string message)
{
    std::cout << message;
}
void Debug::LogError(std::string message)
{
    std::cout << "ERROR: " << message << std::endl;
}
void Debug::LogWarning(std::string message)
{
    std::cout << "WARNING: " << message << std::endl;
}
