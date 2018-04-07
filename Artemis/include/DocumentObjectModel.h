#pragma once
#include<iostream>
#include<stack>
#include"tags/Tag.h"
#include"Node.h"

class DOM
{
public:
	Node* m_Root;
	Node* m_Start;
	Node* m_Last;
public:
	DOM()
	{

	}
	DOM(Node* root):
		m_Root(root)
	{

	}
};
