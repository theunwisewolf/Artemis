#pragma once

#define _USE_MATH_DEFINES

#include <cmath>
#include <stack>
#include <vector>
#include <string>
#include <cctype>
#include <sstream>
#include <iterator>

#include "../src/util/Earcut.hpp"

#include "tags\Tag.h"
#include "tags\Line.h"
#include "tags\Point.h"
#include "tags\Ellipse.h"
#include "tags\Square.h"
#include "tags\Polygon.h"
#include "tags\Triangle.h"
#include "tags\Rectangle.h"

#include "Node.h"
#include "Logger.h"

#include "defs.h"

namespace Artemis {

class Parser
{
private:
	size_t i;
	int m_ErrorCode;

	//Logger Logger;
	
	std::string m_Syntax;
	std::stack<Tag*> m_Tags;
	std::vector<Tag*> m_Primitives;
	
	bool parseOpeningTag();
	bool parseClosingTag();

public:
	Parser();
	Parser(std::string Syntax);
	
	bool Parse();

	// Setters & Getters
	inline void setSyntax(std::string syntax) { this->m_Syntax = syntax; };

	inline int getErrorCode() const { return m_ErrorCode; }

	// Returns the primitives parsed by the parser
	std::vector<Tag*> getPrimitives() const { return m_Primitives; }

	// Allocates memory for a tag
	template <typename T>
	Tag* InitTag(std::string name);

	std::string getErrorMessage() const;
};

}