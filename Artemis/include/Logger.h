#pragma once

#include<iostream>
#include<string>

namespace Artemis {
	class Logger
	{
	private:
		std::string message;
	public:
		void Success(std::string message);
		void Warning(std::string message);
		void Error(std::string message);
	};
}