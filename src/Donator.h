#pragma once
#include "User.h"
#include "Offers.h"

class Offers;
class Organization;

class Donator : public User
{
public:
	// Constructor
	Donator(std::string _phone, std::string _name);
	// Destructor
	~Donator();

	// offersList wrappers
	bool Add(RequestDonation& _newRequestDonation, Organization& _organization);
	void Remove(RequestDonation& _rd);
	void Modify(RequestDonation& _rd, double& _newQuantity);
	void Reset();

	bool Commit(Organization& _organization);
	std::vector<RequestDonation>* GetOffers(); // Instead of Monitor()
private:
	Offers* offersList;
};
