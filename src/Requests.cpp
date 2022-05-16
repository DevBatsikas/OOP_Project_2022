#include "Requests.h"

bool Requests::ValidRequestDonation(double& _quantity, Beneficiary& _beneficiary, Entity& _entity)
{
	// If type is Service return true
	if (typeid(_entity) == typeid(Service))
		return true;

	RequestDonationList* receivedList = _beneficiary.GetReceivedList();

	// Get quantity taken already
	double takenQuantity = 0;
	for (auto& rd : (*receivedList).GetRequestDonations())
		if (rd == _entity)
			takenQuantity = rd.quantity;

	// Get limit according to Beneficiary's noPersons
	int persons = _beneficiary.GetPersons();
	double limit = 0;
	if (persons == 1)
		limit = _entity.GetLevel1();
	else if (persons >= 2 && persons <= 4)
		limit = _entity.GetLevel2();
	else
		limit = _entity.GetLevel3();

	// Check if beneficiary can get that amount
	if (_quantity + takenQuantity > limit)
		return false;
	else
		return true;
}

bool Requests::AvailableInOrganization(Organization& _organization, Entity& _entity, double& _amount)
{
	std::vector<RequestDonation> currentDonations = _organization.GetDonations();

	// If the amount requested exists in the organizations currentDonations
	// and amount requested is enough return true
	for (auto& rd : currentDonations)
		if (_entity == rd && rd.quantity >= _amount)
			return true;

	return false;
}

bool Requests::Add(double& _quantity, Beneficiary& _beneficiary, Organization& _organization, Entity& _entity)
{
	// Throws exception if either amount requested is not available in the Organization
	// or if the Beneficiary can't receive that amount
	try
	{
		// If amount requested is avaibale in Organization
		if (AvailableInOrganization(_organization, _entity, _quantity))
		{
			// If type is Service add it to Beneficiary's rdEntities
			if (typeid(_entity) == typeid(Service))
			{
				RequestDonationList::Add((*new RequestDonation(_entity, _quantity)), _organization.GetEntityList());
				return true;
			}
			else
				// If Beneficiary can receive amount requested add it to Beneficiary's rdEntities
				if (ValidRequestDonation(_quantity, _beneficiary, _entity))
				{
					RequestDonationList::Add((*new RequestDonation(_entity, _quantity)), _organization.GetEntityList());
					return true;
				}
				else
					throw Exception::User("You already have too much quantity of that Entity.\n");
		}
		throw Exception::Organization("Not enough quantity in organization for given Entity.\n");
	}
	catch (Exception::Organization& e)
	{
		std::cout << e.what();
		return false;
	}
	catch (Exception::User& e)
	{
		std::cout << e.what();
		return false;
	}
}

bool Requests::Modify(double& _newQuantity, Beneficiary& _beneficiary, Organization& _organization, RequestDonation& _rd)
{
	try
	{
		// Rechecks if Beneficiary can receive the requested amount before modifying the quantity
		Entity* _entity = _rd.entity;
		if (AvailableInOrganization(_organization, *_entity, _newQuantity))
		{
			if (typeid(*_entity) == typeid(Service))
			{
				RequestDonationList::Modify(_rd, _newQuantity);
				return true;
			}
			else
				if (ValidRequestDonation(_newQuantity, _beneficiary, *_entity))
				{
					RequestDonationList::Modify(_rd, _newQuantity);
					return true;
				}
				else
					throw Exception::User("Too high amount of Entity.\n");
		}
		throw Exception::Organization("Not enough quantity in organization for given Entity.\n");
	}
	catch (Exception::Organization& e)
	{
		std::cout << e.what();
		return false;
	}
	catch (Exception::User& e)
	{
		std::cout << e.what();
		return false;
	}
}

bool Requests::Commit(Organization& _organization, Beneficiary& _beneficiary)
{
	bool completed = true;
	for (auto& _rd : rdEntities)
	{
		Entity* _entity = _rd.entity;
		// Check if quantity is available in Organization
		if (AvailableInOrganization(_organization, *_entity, _rd.quantity))
		{
			// If Entity type is Service
			if (typeid(*_entity) == typeid(Service))
			{
				// Remove quantity from currentDonations of Organization
				_organization.ModifyDonation(_rd, _organization.GetDonation(_rd.entity->GetID()).quantity - _rd.quantity);
				// Add to Beneficiary's Received List
				_beneficiary.AddReceived(_rd, _organization);
				// Remove from Beneficiary's Requests List
				Remove(_rd);
				continue;
			}
			else // If Entity type is Material
				if (ValidRequestDonation(_rd.quantity, _beneficiary, *_entity))
				{
					// Remove quantity from currentDonations of Organization
					_organization.ModifyDonation(_rd, _organization.GetDonation(_rd.entity->GetID()).quantity - _rd.quantity);
					// Add to Beneficiary's Received List
					_beneficiary.AddReceived(_rd, _organization);
					// Remove from Beneficiary's Requests List
					Remove(_rd);
					continue;
				}
				else
					completed = false;
		}
		completed = false;
	}
	return completed;
}
