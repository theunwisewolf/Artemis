#include "Parser.h"

namespace Artemis {
Parser::Parser() :
	m_ErrorCode(0)
{

}

Parser::Parser(std::string Syntax) : 
	m_Syntax(Syntax), 
	m_ErrorCode(0)
{

}

std::string Parser::getErrorMessage() const
{
	std::string errorMessage = "";
	
	if (this->m_ErrorCode & SYNTAX_ERROR)
	{
		errorMessage += "ERROR: Syntax Error Occurred.\n";
	}

	if (this->m_ErrorCode & MISSING_CLOSING_TAG)
	{
		errorMessage += "ERROR: Missing Closing Tag '>'.\n";
	}

	if (this->m_ErrorCode & MISSING_OPENING_TAG)
	{
		errorMessage += "ERROR: Missing Opening Tag '>'.\n";
	}

	if (this->m_ErrorCode & INVALID_TAG_NAME)
	{
		errorMessage += "ERROR: Invalid tag name.\n";
	}

	if (this->m_ErrorCode & INVALID_ATTRIBUTE_NAME)
	{
		errorMessage += "ERROR: Invalid attribute name.\n";
	}

	return errorMessage;
}

bool Parser::Parse()
{
	for (i = 0; i < m_Syntax.length(); i++)
	{
		// Whitespace before an opening tag
		if (std::isspace(m_Syntax[i]))
		{
			continue;
		}

		// Closing tag must be parsed first
		if (parseClosingTag() == false)
		{
			return false;
		}

		// Whitespace before an ending tag
		if (std::isspace(m_Syntax[i]))
		{
			continue;
		}

		// Parse the opening tag
		if (parseOpeningTag() == false)
		{
			return false;
		}
	}

	return true;
}

bool Parser::parseOpeningTag()
{
	// For storing the detected tags
	Tag* tag = nullptr;
	Tags tagType;

	// Begin Parsing a tag
	if (m_Syntax[i] == '<')
	{
		// Increment the counter since we have counted the angle bracket
		i++;

		// Parse Comments
		if (
			m_Syntax[i] == '!' && 
			m_Syntax[i + 1] == '-' && 
			m_Syntax[i + 2] == '-'
		)
		{
			i += 3;
			bool commentEnd = false;
			
			while (commentEnd == false)
			{
				if ((i + 2) >= m_Syntax.length())
				{
					m_ErrorCode |= MISSING_ATTRIBUTE;
					return false;
				}

				commentEnd = (m_Syntax[i] == '-' && m_Syntax[i + 1] == '-' && m_Syntax[i + 2] == '>');
				i++;
			}

			return true;
		}

		// Skip all the white spaces just after the '<' & the tag name
		while (std::isspace(m_Syntax[i]))
		{
			i++;
		}

		// No tag name? Wut?
		if (m_Syntax[i] == '>')
		{
			m_ErrorCode |= MISSING_TAG_NAME;
			return false;
		}

		bool isTagname = true;
		std::string tagName;

		while (m_Syntax[i] != '>')
		{
			// A space means this tag might have attributes
			if (std::isspace(m_Syntax[i]))
			{
				// We have counted the first space
				++i;

				// Skip any further whitespaces
				while (std::isspace(m_Syntax[i]))
				{
					i++;
				}

				// Object creation for the one asked by the user	
				// For tags with attributes
				if (isTagname && tagName.length())
				{
#ifdef _DEBUG
					std::cout << "Pushing " << tagName << " into stack." << std::endl;
#endif
					// Begin Matching tag names
					// <point> 
					if (tagName == "point")
					{
						tagType = Tags::POINT;

						m_Tags.push(this->InitTag<Point>(tagName));
						//m_Tags.push(Point(tagName));
						isTagname = false;
					}
					// <line>
					else if (tagName == "line")
					{
						tagType = Tags::LINE;

						m_Tags.push(this->InitTag<Line>(tagName));
						//m_Tags.push(Line(tagName));
						isTagname = false;
					}
					// <square>
					else if (tagName == "square")
					{
						tagType = Tags::SQUARE;

						m_Tags.push(this->InitTag<Square>(tagName));
						//m_Tags.push(Square(tagName));
						isTagname = false;
					}
					// <triangle>
					else if (tagName == "triangle")
					{
						tagType = Tags::TRIANGLE;

						m_Tags.push(this->InitTag<Triangle>(tagName));
						//m_Tags.push(Triangle(tagName));
						isTagname = false;
					}
					// <rectangle> & <rect>
					else if (tagName == "rectangle" || tagName == "rect")
					{
						tagType = Tags::RECT;

						m_Tags.push(this->InitTag<Rectangle>(tagName));
						//m_Tags.push(Rectangle(tagName));
						isTagname = false;
					}
					// <ellipse>
					else if (tagName == "ellipse")
					{
						tagType = Tags::ELLIPSE;

						m_Tags.push(this->InitTag<Ellipse>(tagName));
						//m_Tags.push(Ellipse(tagName));
						isTagname = false;
					}
					// <polygon>
					else if (tagName == "polygon")
					{
						tagType = Tags::POLYGON;

						m_Tags.push(this->InitTag<Polygon>(tagName));
						//m_Tags.push(Polygon(tagName));
						isTagname = false;
					}
				}
				else if(tagName.length() == 0)
				{
					m_ErrorCode |= INVALID_TAG_NAME;
					return false;
				}

				// Attribute names & values
				std::string attributeName;
				std::string attributeValue;

				// Checking for the attribute name
				uint32_t attributeNameLength = 0;
				bool scan = true;
				while (m_Syntax[i] != '=')
				{
					attributeNameLength++;
					if (attributeNameLength > MAX_ATTRIBUTE_NAME_LENGTH)
					{
						m_ErrorCode |= INVALID_ATTRIBUTE_NAME;
						return false;
					}

					// Attribute names do not have space, so now, continue until the equal-to sign is reached
					if (scan && std::isspace(m_Syntax[i]))
					{
						scan = false;
					}

					// TODO: check for valid attribute names

					if (scan)
					{
						attributeName += m_Syntax[i];
					}

					i++;
				}

				// Skip any further whitespaces
				while (std::isspace(m_Syntax[i]))
				{
					i++;
				}

				// Storing the value of the attribute passed
				i = i + 2;
				while (m_Syntax[i] != '"')
				{
					attributeValue += m_Syntax[i];
					i++;
				}

				// Global Attributes
				if (attributeName == "fillcolor")
				{
					int color;
					// rgb(r, g, b) format
					if (attributeValue[0] == 'r')
					{
						// Erase rgb(

					}
					// Hex #000000 format
					else if (attributeValue[0] == '#')
					{
						attributeValue = attributeValue.substr(1);

						// #fff
						if (attributeValue.length() == 3)
						{
							unsigned int value;
							std::string color = { attributeValue[0], attributeValue[0], attributeValue[1], attributeValue[1], attributeValue[2], attributeValue[2] };
							std::istringstream ss(color);
							ss >> std::hex >> value;

							((Point*)m_Tags.top())->color = value;
						}
						// #ffffff
						else if (attributeValue.length() == 6)
						{
							unsigned int value;
							std::string color = { attributeValue[0], attributeValue[1], attributeValue[2], attributeValue[3], attributeValue[4], attributeValue[5] };
							std::istringstream ss(color);
							ss >> std::hex >> value;

							((Point*)m_Tags.top())->color = value;
						}
						// Error: Invalid color value
						else
						{
							this->m_ErrorCode |= INVALID_ATTRIBUTE_VALUE;
							return false;
						}
					}
				}
				else if (attributeName == "scale")
				{
					((Point*)m_Tags.top())->scale = atof(attributeValue.c_str());
				}
				else if (attributeName == "id")
				{
					(m_Tags.top())->id = attributeValue.c_str();
				}

				// Checking for the attributes of respective tagName
				else if ( tagType == Tags::SQUARE )
				{
					if (attributeName == "sidelength")
					{
						((Square*)m_Tags.top())->sidelength = atoi(attributeValue.c_str());
					}
					else if (attributeName == "x")
					{
						((Square*)m_Tags.top())->x = atoi(attributeValue.c_str());
					}
					else if (attributeName == "y")
					{
						((Square*)m_Tags.top())->y = atoi(attributeValue.c_str());
					}
				}
				else if (tagType == Tags::ELLIPSE)
				{
					if (attributeName == "rx")
					{
						((Ellipse*)m_Tags.top())->rx = atof(attributeValue.c_str());
					}
					else if (attributeName == "ry")
					{
						((Ellipse*)m_Tags.top())->ry = atof(attributeValue.c_str());
					}
					else if (attributeName == "x")
					{
						((Ellipse*)m_Tags.top())->x = atof(attributeValue.c_str());
					}
					else if (attributeName == "y")
					{
						((Ellipse*)m_Tags.top())->y = atof(attributeValue.c_str());
					}
					else if (attributeName == "lod")
					{
						((Ellipse*)m_Tags.top())->lod = atoi(attributeValue.c_str());
					}
				}
				else if (tagType == Tags::RECT)
				{
					if (attributeName == "width")
					{
						((Rectangle*)m_Tags.top())->width = atoi(attributeValue.c_str());
					}
					else if (attributeName == "height")
					{
						((Rectangle*)m_Tags.top())->height = atoi(attributeValue.c_str());
					}
					else if (attributeName == "x")
					{
						((Rectangle*)m_Tags.top())->x = atoi(attributeValue.c_str());
					}
					else if (attributeName == "y")
					{
						((Rectangle*)m_Tags.top())->y = atoi(attributeValue.c_str());
					}
				}
				else if (tagType == Tags::POINT)
				{
					if (attributeName == "x")
					{
						((Point*)m_Tags.top())->x = atoi(attributeValue.c_str());
					}
					else if (attributeName == "y")
					{
						((Point*)m_Tags.top())->y = atoi(attributeValue.c_str());
					}
				}
				else if (tagType == Tags::LINE)
				{
					if (attributeName == "x1")
					{
						((Line*)m_Tags.top())->p1.x = atoi(attributeValue.c_str());
					}
					else if (attributeName == "y1")
					{
						((Line*)m_Tags.top())->p1.y = atoi(attributeValue.c_str());
					}
					else if (attributeName == "x2")
					{
						((Line*)m_Tags.top())->p2.x = atoi(attributeValue.c_str());
					}
					else if (attributeName == "y2")
					{
						((Line*)m_Tags.top())->p2.y = atoi(attributeValue.c_str());
					}
				}
				else if (tagType == Tags::TRIANGLE)
				{
					if (attributeName == "x1")
					{
						((Triangle*)m_Tags.top())->p1.x = atof(attributeValue.c_str());
					}
					else if (attributeName == "y1")
					{
						((Triangle*)m_Tags.top())->p1.y = atof(attributeValue.c_str());
					}
					else if (attributeName == "x2")
					{
						((Triangle*)m_Tags.top())->p2.x = atof(attributeValue.c_str());
					}
					else if (attributeName == "y2")
					{
						((Triangle*)m_Tags.top())->p2.y = atof(attributeValue.c_str());
					}
					else if (attributeName == "x3")
					{
						((Triangle*)m_Tags.top())->p3.x = atof(attributeValue.c_str());
					}
					else if (attributeName == "y3")
					{
						((Triangle*)m_Tags.top())->p3.y = atof(attributeValue.c_str());
					}
				}
				else if (tagType == Tags::POLYGON)
				{
					if (attributeName == "path")
					{
						std::string point1;
						std::string point2;

						for (int j = 0; j < attributeValue.length(); j++)
						{
							point1 = point2 = "";
							while (j < attributeValue.length() && attributeValue[j] != ',')
							{
								point1 += attributeValue[j];
								j++;
							}

							// Comma
							j++;

							while (j < attributeValue.length() && attributeValue[j] != ' ')
							{
								point2 += attributeValue[j];
								j++;
							}

							Point point;
							point.x = atof(point1.c_str());
							point.y = atof(point2.c_str());

							point.x *= ((Polygon*)m_Tags.top())->scale;
							point.y *= ((Polygon*)m_Tags.top())->scale;

							float x = ((Polygon*)m_Tags.top())->x;
							float y = ((Polygon*)m_Tags.top())->y;

							point.x += x;
							point.y += y;

							((Polygon*)m_Tags.top())->vertices.push_back(point);
						}

						std::vector<std::vector<Point>> polygon;

						polygon.push_back(((Polygon*)m_Tags.top())->vertices);

						// Run tessellation
						// Returns array of indices that refer to the vertices of the input polygon.
						// Three subsequent indices form a triangle.
						std::vector<uint32_t> indices = mapbox::earcut<uint32_t>(polygon);

						// Perform earcutting
						std::move(indices.begin(), indices.end(), std::back_inserter(((Polygon*)m_Tags.top())->indices));
					}
					else if (attributeName == "x")
					{
						((Polygon*)m_Tags.top())->x = atof(attributeValue.c_str());
					}
					else if (attributeName == "y")
					{
						((Polygon*)m_Tags.top())->y = atof(attributeValue.c_str());
					}
				}
				
				m_Tags.top()->attributes.emplace(attributeName, attributeValue);

				i++;
			}
			else
			{
				tagName += m_Syntax[i];
				i++;
			}
		}
		// For tags without attributes
		if (isTagname)
		{
#ifdef _DEBUG
			std::cout << "Pushing " << tagName << " into stack." << std::endl;
#endif

			if (tagName == "root")
			{
				tagType = Tags::ROOT;
			}
			else if (tagName == "figure")
			{
				tagType = Tags::FIGURE;
			}

			m_Tags.push(new Tag(tagName, tagType));
		}
		else
		{
			m_Primitives.push_back(m_Tags.top());
		}
	}

	return true;
}

bool Parser::parseClosingTag()
{
	if (m_Syntax[i] == '<' && m_Syntax[i + 1] == '/')
	{
		i = i + 2;
		std::string tagName;
		while (m_Syntax[i] != '>')
		{
			tagName += m_Syntax[i];
			i++;
		}

		// Checking 
#ifdef _DEBUG
		std::cout << "Popping " << tagName << " from stack." << std::endl;
#endif
		if (m_Tags.top()->name == tagName)
		{
			if (m_Tags.top()->tagType == Tags::TRIANGLE)
			{
				//Triangle triangle = *((Triangle*)(m_Tags.top()));
			}
			else if (m_Tags.top()->tagType == Tags::RECT)
			{
				//Rectangle rectangle = *((Rectangle*)(m_Tags.top()));
			}
			else if (m_Tags.top()->tagType == Tags::ELLIPSE)
			{
				Ellipse* e = (Ellipse*)m_Tags.top();
				
				// Compute the vertices
				// Push Center
				e->vertices.push_back(Point(/*e->x, e->y*/0.0f, 0.0f));
				e->uvs.push_back(Point(0.0f, 0.0f));

				for (float i = 0; i <= e->lod; i++)
				{
					float u = i / e->lod;
					float theta = 2 * M_PI * u;

					float _x = cosf(theta);
					float _y = sinf(theta);

					e->uvs.push_back(Point(_x, _y));

					/*
					// Now we update the actual position and radius of the ellipse in the renderer
					_x = e->x + e->rx * _x;
					_y = e->y + e->ry * _y;
					*/

					e->vertices.push_back(Point(_x, _y));
					e->indices.push_back(0);
					e->indices.push_back(((int)i + 1) % e->lod + 1);
					e->indices.push_back(i + 1);
				}
			}
			else if (m_Tags.top()->tagType == Tags::SQUARE)
			{
				//Square square = *((Square*)(m_Tags.top()));
			}
			else if (m_Tags.top()->tagType == Tags::LINE)
			{
				//Line line = *((Line*)(m_Tags.top()));
			}
			else if (m_Tags.top()->tagType == Tags::POINT)
			{
				//Point point = *((Point*)(m_Tags.top()));
			}

			m_Tags.pop();
		}

		else
		{
			m_ErrorCode |= MISSING_CLOSING_TAG;
		}
	}

	return true;
}

template <typename T>
Tag* Parser::InitTag(std::string name)
{
	T* primitive = new T(name);

	return (Tag*)primitive;
}

}