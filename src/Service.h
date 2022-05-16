#pragma once
#include "Entity.h"

class Service : public Entity
{
public:
	// Constructor
	Service(std::string _name, std::string _description, int _id);
private:
	std::string GetDetails();
};
