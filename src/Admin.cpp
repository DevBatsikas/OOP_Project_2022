#include "Admin.h"

// Constructor
Admin::Admin(std::string _phone, std::string _name)
	:User(_phone, _name)
{

}

// Destructor
Admin::~Admin()
{
	User::~User();
}
