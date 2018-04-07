#pragma once

#include <string>
#include <unordered_map>

#include "../defs.h"

enum class Tags;

struct Tag
{
	std::string name;
	std::string id;

	// Type of this tag
	Tags tagType;
	std::unordered_map<std::string, std::string> attributes;

	Tag(std::string name, Tags type) :
		name(name),
		tagType(type)
	{
	}

	bool HasAttribute(std::string name)
	{
		foundPos = attributes.find(name);
		return (foundPos != attributes.end());
	}

	bool Is(Tags type)
	{
		return this->tagType == type;
	}

	std::string GetAttribute(std::string name)
	{
		if (foundPos != attributes.end() && foundPos->first == name)
		{
			return foundPos->second;
		}

		return "ERROR:INVALID_ATTRIBUTE";
	}

	template <typename T>
	T* Get()
	{
		return dynamic_cast<T*>(this);
	}

	virtual ~Tag()
	{

	}

private:
	std::unordered_map<std::string, std::string>::iterator foundPos;
};
