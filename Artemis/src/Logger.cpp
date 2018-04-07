#include "Logger.h"

namespace Artemis {
	void Logger::Success(std::string message)
	{
		this->message = "[SUCCESS]: " + message;
		std::cout << this->message << std::endl;
	}
	void Logger::Warning(std::string message)
	{
		this->message = "[WARNING]: " + message;
		std::cout << this->message << std::endl;
	}
	void Logger::Error(std::string message)
	{
		this->message = "[ERROR]: " + message;
		std::cout << this->message << std::endl;
	}
}