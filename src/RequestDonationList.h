#pragma once
#include <vector>
#include "RequestDonation.h"
#include "Exception.h"

class RequestDonationList
{
public:
	RequestDonation& Get(int& _entityID);
	bool Add(RequestDonation& _newRequestDonation, std::vector<Entity*> _entityList);
	void Remove(RequestDonation& _rd);
	void Modify(RequestDonation& _rd, double& _newQuantity);
	void Reset();

	// We use this function isntead of Monitor()
	// because we want to display an interactive menu
	// which requires an array of names instead of
	// simply printing out the values
	std::vector<RequestDonation>& GetRequestDonations();
protected:
	std::vector<RequestDonation> rdEntities;
};
