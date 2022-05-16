#pragma once
#include "RequestDonationList.h"
#include "Material.h"
#include "Beneficiary.h"
#include "Organization.h"

#include "Exception.h"

class Beneficiary;
class Organization;

class Requests : public RequestDonationList
{
public:
	bool ValidRequestDonation(double& _quantity, Beneficiary& _beneficiary, Entity& _entity);
	bool AvailableInOrganization(Organization& _organization, Entity& _entity, double& _amount);

	bool Add(double& _quantity, Beneficiary& _beneficiary, Organization& _organization, Entity& _entity);
	bool Modify(double& _newQuantity, Beneficiary& _beneficiary, Organization& _organization, RequestDonation& _rd);
	bool Commit(Organization& _organization, Beneficiary& _beneficiary);
};
