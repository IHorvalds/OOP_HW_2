#pragma once
#include "Tree.h"
#include <istream>
#include <ostream>
#include <vector>


class ABC: public Tree
{
public:
	ABC();
	ABC(void* a_root_val, std::string a_typename);
	//ABC(int a_root_val);

	// rule of five
	virtual ~ABC();
	ABC(ABC& a_ot);
	ABC(ABC&& a_rv_ot) noexcept;
	ABC& operator =(ABC& a_ot);
	ABC& operator =(ABC&& a_rv_ot) noexcept;

	ABC& operator+(int a_nti) override;
	ABC& operator+(const ABC& rhs);
	bool DeleteNode(int a_ntr) override;

	unsigned int GetHeight() override;

	friend std::istream& operator >>(std::istream& input, ABC& rhs);
	friend std::ostream& operator <<(std::ostream& input, const ABC& rhs);
};

