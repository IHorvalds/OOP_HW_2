#include "ABC.h"
#include <memory>
#include <vector>
#include <iostream>
#include <functional>
#include <type_traits>
#include <algorithm> // for std::max
#include "ValueException.h"

ABC::ABC() {
	GetRoot() = nullptr;
}

//ABC::ABC(int a_root_val) {
//	p_root = std::unique_ptr<Node>(new Node(a_root_val));
//}

ABC::ABC(void* a_root_val, std::string a_typename) { // this initializer will throw a Value Exception Error unless the argument can be cast to an integer
	
	if (a_typename == "int") {
		int* _val = static_cast<int*>(a_root_val);
		GetRoot() = std::unique_ptr<Node>(new Node(*_val));
	} else {
		throw ValueException(a_typename);
	}
}

ABC::~ABC() {
	GetRoot()->DeleteChildren();
	// p_root will go out of scope here and the Node will be deleted automatically
}

ABC::ABC(ABC& a_ot) {

	if (a_ot.GetRoot()) {
		GetRoot().reset(a_ot.GetRoot()->CopyChildren());
	} else {
		GetRoot() = nullptr;
	}
}

ABC::ABC(ABC&& a_rv_ot) noexcept {

	if (a_rv_ot.GetRoot()) {
		Node* children = a_rv_ot.GetRoot()->CopyChildren();
		GetRoot()->DeleteChildren();
		GetRoot().reset(children);
	} else {
		GetRoot() = nullptr;
	}
}

ABC& ABC::operator=(ABC& a_ot) {

	if (a_ot.GetRoot()) {
		Node* children = a_ot.GetRoot()->CopyChildren();
		GetRoot()->DeleteChildren();
		GetRoot().reset(children);
	} else {
		GetRoot() = nullptr;
	}

	return *this;
}

ABC& ABC::operator=(ABC&& a_rv_ot) noexcept {
	
	if (a_rv_ot.GetRoot()) {
		GetRoot().reset(a_rv_ot.GetRoot()->CopyChildren());
	} else {
		GetRoot() = nullptr;
	}

	return *this;
}

ABC& ABC::operator+(int a_nti) {


	std::function<void(std::unique_ptr<Node>&)> traverse = [&traverse, a_nti](std::unique_ptr<Node>& a_starting_node) {

		if (a_nti > a_starting_node->GetValue()) {
			if (a_starting_node->GetRight().get()) {
				traverse(a_starting_node->GetRight());
			} else {
				a_starting_node->SetRight(a_nti);
			}
		}

		if (a_nti < a_starting_node->GetValue()) {
			if (a_starting_node->GetLeft().get()) {
				traverse(a_starting_node->GetLeft());
			} else {
				a_starting_node->SetLeft(a_nti);
			}
		}
	};

	traverse(this->GetRoot());
	return *this;
}

ABC& ABC::operator+(const ABC& rhs) {

	std::vector<Node> nodes;

	this->GetNodes(nodes, GetRoot());

	for (Node n : nodes) {
		*this + n.GetValue();
	}

	return *this;
}

bool ABC::DeleteNode(int a_ntr) {

	std::function<bool(std::unique_ptr<Node>&)> traverse = [&traverse, a_ntr](std::unique_ptr<Node>& a_starting_node) -> bool {

		if (a_ntr == a_starting_node->GetValue()) {
			// no children
			if (!a_starting_node->GetLeft().get() && !a_starting_node->GetRight().get()) {
				a_starting_node.reset();

				return true;
			}

			// only left sub-tree
			if (a_starting_node->GetLeft().get() && !a_starting_node->GetRight().get()) {
				a_starting_node.reset(a_starting_node->GetLeft().get());

				return true;
			}

			//only right sub-tree
			if (!a_starting_node->GetLeft().get() && a_starting_node->GetRight().get()) {
				a_starting_node.reset(a_starting_node->GetRight().get());

				return true;
			}

			// both sub-trees exist
			if (a_starting_node->GetLeft().get() && a_starting_node->GetRight().get()) {
				std::unique_ptr<Node> * p = &(a_starting_node->GetLeft());
				while ((*p)->GetRight().get()) {
					p = &((*p)->GetRight());
				}

				int n_gr_val = (*p)->GetValue();
				a_starting_node->SetValue(n_gr_val);

				*p = std::move((*p)->GetLeft());

				return true;
			}

		}

		if (a_ntr > a_starting_node->GetValue()) {
			if (a_starting_node->GetRight().get()) {
				return traverse(a_starting_node->GetRight());
			} else {
				return false;
			}
		}

		if (a_ntr < a_starting_node->GetValue()) {
			if (a_starting_node->GetLeft().get()) {
				return traverse(a_starting_node->GetLeft());
			} else {
				return false;
			}
		}

		return false;
	};
	
	return traverse(GetRoot());
}

unsigned int ABC::GetHeight() {


	std::function<unsigned int(std::unique_ptr<Node>&)> height = [&height](std::unique_ptr<Node>& a_starting_node) -> unsigned int {
		if (!a_starting_node.get()) {
			return 0;
		}

		return 1 + std::max(height(a_starting_node->GetLeft()), height(a_starting_node->GetRight()));
	};

	return height(GetRoot());
}

std::istream& operator>>(std::istream& input, ABC& rhs) {

	if (rhs.GetRoot()) {
		rhs.GetRoot()->DeleteChildren();
	}

	rhs.GetRoot().reset(new Node);
	input >> *(rhs.GetRoot());
	int new_info;
	while (!input.eof()) {
		input >> new_info;
		rhs = rhs + new_info;
	}

	return input;
}

std::ostream& operator<<(std::ostream& output, const ABC& rhs) {
	std::cout << "\nInorder\n------------------------------------------------------------------------------------\n";

	std::function<void(const std::unique_ptr<Node>&)> inorder = [&inorder](const std::unique_ptr<Node>& a_starting_node) {

		if (a_starting_node->GetLeft().get()) {
			inorder(a_starting_node->GetLeft());
		}

		std::cout << a_starting_node->GetValue() << " ";

		if (a_starting_node->GetRight().get()) {
			inorder(a_starting_node->GetRight());
		}

	};

	inorder(((ABC&)rhs).GetRoot());

	std::cout << "\nPreorder\n------------------------------------------------------------------------------------\n";

	std::function<void(const std::unique_ptr<Node>&)> preorder = [&preorder](const std::unique_ptr<Node>& a_starting_node) {

		std::cout << a_starting_node->GetValue() << " ";

		if (a_starting_node->GetLeft().get()) {
			preorder(a_starting_node->GetLeft());
		}

		if (a_starting_node->GetRight().get()) {
			preorder(a_starting_node->GetRight());
		}
	};

	preorder(((ABC&) rhs).GetRoot());

	std::cout << "\nPostorder\n------------------------------------------------------------------------------------\n";

	std::function<void(const std::unique_ptr<Node>&)> postorder = [&postorder](const std::unique_ptr<Node>& a_starting_node) {

		if (a_starting_node->GetLeft().get()) {
			postorder(a_starting_node->GetLeft());
		}

		if (a_starting_node->GetRight().get()) {
			postorder(a_starting_node->GetRight());
		}

		std::cout << a_starting_node->GetValue() << " ";
	};

	postorder(((ABC&) rhs).GetRoot());

	return output;
}