#pragma once
#include "Entity.h"

class RequestDonation
{
public:
	// Constructor
	RequestDonation(Entity& _entity, double _quantity);

	double quantity;
	Entity* entity;

	// Wrappers for entity functions
	std::string& GetName();
	int& GetID();


	// Operator overloading

	// Overloading << (Print operator)
	friend std::ostream& operator<<(std::ostream& _stream, RequestDonation& _rd);
	// Overloading == between 2 RequestDonations
	friend bool operator==(RequestDonation& _rd1, RequestDonation& _rd2);
	// Overloading == between a RequestDonation and an int
	friend bool operator==(RequestDonation& _rd, int& _id);
	// Overloading == between a RequestDonation and an Entity
	friend bool operator==(RequestDonation& _rd, Entity& _entity);
};
