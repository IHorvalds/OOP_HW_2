#include "Tree.h"

std::unique_ptr<Node>& Tree::GetRoot() {
	return p_root;
}

bool Tree::operator==(Tree& rhs) {
	std::vector<Node> lhs_nodes, rhs_nodes;

	Tree::GetNodes(lhs_nodes, this->p_root);
	Tree::GetNodes(rhs_nodes, rhs.GetRoot());
	if (lhs_nodes.size() != rhs_nodes.size()) {
		return false;
	}

	for (size_t iterator = 0; iterator < lhs_nodes.size(); iterator++) {
		if (lhs_nodes[iterator] != rhs_nodes[iterator]) {
			return false;
		}
	}
	return true;
}

void Tree::GetNodes(std::vector<Node>& accumulator, std::unique_ptr<Node>& a_start) {
	accumulator.push_back(Node(*a_start)); //making a copy because I don't want memory addresses to be visible here. They could've been cleared. 

	if (a_start->GetLeft().get()) {
		Tree::GetNodes(accumulator, a_start->GetLeft());
	}
	if (a_start->GetRight().get()) {
		Tree::GetNodes(accumulator, a_start->GetRight());
	}
}
