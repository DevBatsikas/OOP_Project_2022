#include "RequestDonationList.h"

RequestDonation& RequestDonationList::Get(int& _entityID)
{
	for (auto& requestDonation : rdEntities)
		if (requestDonation == _entityID)
			return requestDonation;
}

bool RequestDonationList::Add(RequestDonation& _newRequestDonation, std::vector<Entity*> _entityList)
{
	try
	{
		// Check Organization's entityList
		for (auto& entity : _entityList)
		{
			// If Entity exists in Organization's entityList
			if (*entity == _newRequestDonation)
			{
				// Check if RequestDonation arleady exists in
				// rdEntities list
				for (auto& requestDonation : rdEntities)
					// If RequestDonation exists update quantity
					if (_newRequestDonation == requestDonation)
					{
						Modify(requestDonation, _newRequestDonation.quantity);
						return true;
					}

				// If RequestDonation doesn't exist in rdEntities
				// add it to the list
				rdEntities.push_back(_newRequestDonation);
				return true;
			}
		}
		throw Exception::Entity("Entity not found in Organization's Entity List.\n");
	}
	catch (Exception::Entity& e)
	{
		std::cout << e.what();
		return false;
	}
}

void RequestDonationList::Remove(RequestDonation& _rd)
{
	for (auto it = rdEntities.begin(); it != rdEntities.end(); ++it)
		// Overloaded == operator in "RequestDonation.h"
		// Directly checks equality between ID's
		if (*it == _rd)
		{
			rdEntities.erase(it);
			std::system("cls");
			std::cout << "RequestDonation successfully removed." << std::endl;
			std::system("pause");
			return;
		}
}

void RequestDonationList::Modify(RequestDonation& _rd, double& _newQuantity)
{
	for (auto& requestDonation : rdEntities)
		if (_rd == requestDonation)
			requestDonation.quantity = _newQuantity;
}

void RequestDonationList::Reset()
{
	rdEntities.clear();
	std::system("cls");
	std::cout << "RequestDonation List cleared." << std::endl;
	std::system("pause");
}

// Instead of Monitor()
std::vector<RequestDonation>& RequestDonationList::GetRequestDonations()
{
	return rdEntities;
}
