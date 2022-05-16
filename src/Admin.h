#pragma once
#include "User.h"

class Admin : public User
{
public:
	// Constructor
	Admin(std::string _phone, std::string _name);
	// Destructor
	~Admin();

private:
	bool isAdmin = true;
};
