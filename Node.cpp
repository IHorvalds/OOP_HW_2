#include "Node.h"
#include <memory>

Node::Node() : 
	m_info(INT_MIN), p_left(nullptr), p_right(nullptr) {}

Node::Node(int val) : m_info(val), p_left(nullptr), p_right(nullptr) {}

Node::Node(const Node& a_ntc) : p_left(nullptr), p_right(nullptr) {
	this->m_info = a_ntc.m_info;
}

Node& Node::operator=(const Node& rhs) {

	m_info = rhs.m_info;
	p_right = nullptr; 
	p_left = nullptr;
	return *this;
}

int Node::GetValue() {
	return m_info;
}

void Node::SetValue(int val) {
	m_info = val;
}

std::unique_ptr<Node>& Node::GetLeft() {
	return p_left;
}

std::unique_ptr<Node>& Node::GetRight() {
	return p_right;
}

void Node::SetLeft(int val) {
	p_left.reset(new Node(val));
}

void Node::SetRight(int val) {
	p_right.reset(new Node(val));
}

Node* Node::CopyChildren() { // Immediately cast this into a unique_ptr. Or don't, but you'll have to manage it yourself.

	Node* new_node = new Node(m_info);

	if (p_left.get()) {
		new_node->p_left.reset(p_left->CopyChildren());
	}

	if (p_right.get()) {
		new_node->p_right.reset(p_right->CopyChildren());
	}


	return new_node;
}

void Node::DeleteChildren() {

	if (p_left.get()) {
		p_left->DeleteChildren();
	}

	if (p_right.get()) {
		p_right->DeleteChildren();
	}

	p_left.reset();
	p_right.reset();

}

bool operator==(Node& lhs, Node& rhs) {
	return lhs.GetValue() == rhs.GetValue();
}

bool operator!=(Node& lhs, Node& rhs) {
	return lhs.GetValue() != rhs.GetValue();
}

Node::~Node() {

	p_left.release();
	p_right.release();
	// Not calling delete because it would delete the children.
}


std::istream& operator >>(std::istream& input, Node& n) {

	input >> n.m_info;
	return input;
}

std::ostream& operator <<(std::ostream& output, Node& n) {

	output << n.m_info;
	return output;
}