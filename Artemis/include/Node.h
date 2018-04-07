#pragma once
#include<iostream>
#include "tags/Tag.h"

class Node
{
public:
	Tag* m_Tag;
	Node* m_Parent;
	Node* m_PrevSibling;
	Node* m_NextSibling;
	Node* m_FirstChild;
	Node* m_LastChild;

	Node() :
		m_Tag(nullptr),
		m_Parent(nullptr),
		m_PrevSibling(nullptr),
		m_NextSibling(nullptr),
		m_FirstChild(nullptr),
		m_LastChild(nullptr)
	{

	}

	Node(Tag* tag) :
		m_Tag(tag),
		m_Parent(nullptr),
		m_PrevSibling(nullptr),
		m_NextSibling(nullptr),
		m_FirstChild(nullptr),
		m_LastChild(nullptr)
	{

	}

};
