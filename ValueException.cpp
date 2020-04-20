#include "ValueException.h"

ValueException::ValueException(std::string a_typename) {

	m_typename = a_typename;
}

std::string ValueException::message() {
	return std::string("Argument of type ") + this->m_typename + std::string(" is invalid. Link died.");
}
