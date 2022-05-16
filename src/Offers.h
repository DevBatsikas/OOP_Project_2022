#pragma once
#include "RequestDonationList.h"
#include "Organization.h"

class Organization;

class Offers : public RequestDonationList
{
public:
	bool Commit(Organization& _organization);
};
