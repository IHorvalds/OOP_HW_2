#include <iostream>
#include <fstream>
#include "ValueException.h"
#include "ABC.h"
#include <typeinfo>

int main()
{
    std::cout << "Hello World!\n\n\n\n";

    ////////////////////////////////////////////

    std::cout << "1. Instantiating the ABC\n";
    ABC l_binary_search_tree;
    std::string l_tree_name = Stringify(l_binary_search_tree);

    /////////////////////////////////////////////

    std::cout << "\n\n2. Reading from file...";

    std::ifstream f_istream("tree_input.txt");
    f_istream >> l_binary_search_tree;

    //////////////////////////////////////////////

    std::cout << "\n\n3. Writing the tree we just read\n\n" << l_binary_search_tree << "\n";

    ////////////////////////////////////////////

    std::cout << "\n\n4. Adding a new node\n\nType the number to insert: ";

    int l_node;
    for (int i = 0; i < 12; i++) {
        std::cin >> l_node;


        std::cout << "\nNew tree:\n" << (l_binary_search_tree = l_binary_search_tree + l_node) << "\n";
    }

    ////////////////////////////////////////////

    std::cout << "\n5. Deleting a node. Please, which number would you like to remove?\n";

    std::cin >> l_node;

    if (l_binary_search_tree.DeleteNode(l_node)) {
        std::cout << "\nNew tree:\n" << l_binary_search_tree << "\n";
    } else {
        std::cout << "\nError: " << l_node << " not found in tree" << "\n";
    }

    ///////////////////////////////////////////////

    std::cout << "\n6. Tree height\n\n";

    std::cout << l_tree_name + " height = " << l_binary_search_tree.GetHeight() << "\n";

    ////////////////////////////////////////////////

    std::cout << "\n7. Node list\n\n";

    std::vector<Node> l_node_list;
    Tree::GetNodes(l_node_list, l_binary_search_tree.GetRoot());

    for (auto& _n : l_node_list) {
        std::cout << _n << ' ';
    }
    std::cout << "\n";

    ///////////////////////////////////////////////////

    std::cout << "\n8. Copy constructor & ==\n\n";

    ABC l_binary_search_tree_copy(l_binary_search_tree);

    std::cout << "Please delete something from the copy\n\n";

    std::cin >> l_node;

    l_binary_search_tree_copy.DeleteNode(l_node);

    std::cout << "Here's the copy: \n\n";

    std::cout << l_binary_search_tree_copy << "\n\n";

    std::cout << (l_binary_search_tree == l_binary_search_tree_copy) << "\n\n";


    /////////////////////////////////////////////////

    std::cout << "\n9. Erroneous instantiation\n\n";

    try {
        std::string _arg = "Hello world";
        std::string _arg_typename = std::string(typeid(_arg).name());
        ABC err_abc = ABC((void*)_arg.c_str(), _arg_typename);
    } catch (ValueException& ve){
        std::cout << ve.message() << "\n";
    } catch(std::exception ee) {
        std::cout << ee.what() << "\n";
    }

    std::cout << "\nCorrect instantiation";

    try {
        std::unique_ptr<int> _arg(new int('a'));
        std::string _arg_typename = std::string(typeid(*_arg).name());
        ABC corr_abc = ABC(static_cast<void*>(_arg.get()), _arg_typename);

        std::cout << corr_abc << "\n";
    } catch (ValueException& ve) {
        std::cout << ve.message() << "\n";
    } catch (std::exception ee) {
        std::cout << ee.what() << "\n";
    }

    std::cout << "THE END.\nPress Enter..." << "\n";

    std::cin.get();
}
