#pragma once
#include <memory>
#include <istream>
#include <ostream>

class Node
{
private:
	int m_info;
	std::unique_ptr<Node> p_left,  p_right;

public:
	Node();
	Node(int val);

	// rule of three
	~Node();
	Node(const Node& a_ntc);
	Node& operator =(const Node& rhs);

	int GetValue();
	void SetValue(int val);
	std::unique_ptr<Node>& GetLeft();
	std::unique_ptr<Node>& GetRight();
	void SetLeft(int val);
	void SetRight(int val);
	Node* CopyChildren();
	void DeleteChildren();

	friend bool operator ==(Node& lhs, Node& rhs);
	friend bool operator !=(Node& lhs, Node& rhs);
	friend std::istream& operator >>(std::istream& input, Node& n);
	friend std::ostream& operator <<(std::ostream& output, Node& n);
};

