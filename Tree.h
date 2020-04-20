#pragma once

#include "Node.h"
#include <istream>
#include <ostream>
#include <memory>
#include <vector>

class Tree // Must be subclassed. All public methods need to be implemented in the subclass.
{
private:
	std::unique_ptr<Node> p_root;

public:
	virtual ~Tree() = default;

	std::unique_ptr<Node>& GetRoot();
	virtual Tree& operator +(int a_nti) = 0;
	bool operator ==(Tree& rhs);
	virtual bool DeleteNode(int a_ntd) = 0;


	virtual unsigned int GetHeight() = 0;
	static void GetNodes(std::vector<Node>& accumulator, std::unique_ptr<Node>& a_start);
};

