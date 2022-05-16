#include "Organization.h"

// Constructor
Organization::Organization(std::string _name)
	:name(_name), admin(nullptr)
{
	
}


void Organization::SetAdmin(Admin& _admin)
{
	admin = &_admin;
}

Admin& Organization::GetAdmin()
{
	return *(admin);
}

void Organization::AddEntity(Entity& _entity)
{
	try
	{
		// Throws exception if Entity already in entityList
		for (auto& entityPtr : entityList)
			// Overloaded == operator in "Entity.h"
			// Directly checks between ID's
			if (*entityPtr == _entity)
				throw Exception::Entity("Entity already exists.\n");

		entityList.push_back(&_entity);
	}
	catch (Exception::Entity& e)
	{
		std::cout << e.what();
	}
}

void Organization::RemoveEntity(int& _id)
{
	// Loop through the Entity list and remove
	// Entity with the given ID
	for (auto it = entityList.begin(); it != entityList.end(); ++it)
		// Overloaded == operator in "Entity.h"
		// Directly checks equality between the
		// Entity's ID and the given ID
		if (**it == _id)
		{
			entityList.erase(it);
			std::system("cls");
			std::cout << "Entity successfully removed." << std::endl;
			std::system("pause");
			return;
		}
}

bool Organization::InsertDonator(Donator& _donator)
{
	try
	{
		// Throws exception if Donator already exists in donatorList
		for (auto& donatorPtr : donatorList)
			if (*donatorPtr == _donator)
				throw Exception::User("Donator already exists.\n");

		donatorList.push_back(&_donator);
		return true;
	}
	catch (Exception::User& e)
	{
		std::cout << e.what();
		return false;
	}
}

void Organization::RemoveDonator(Donator& _donator)
{
	for (auto it = donatorList.begin(); it != donatorList.end(); ++it)
		// Overloaded == operator in "User.h"
		// Directly checks between phone numbers
		if (**it == _donator)
		{
			donatorList.erase(it);
			std::system("cls");
			std::cout << "Donator successfully removed." << std::endl;
			std::system("pause");
			return;
		}
}

bool Organization::InsertBeneficiary(Beneficiary& _beneficiary)
{
	try
	{
		// Throws exception if Beneficiary already exists in beneficiaryList
		for (auto& beneficiaryPtr : beneficiaryList)
			if (*beneficiaryPtr == _beneficiary)
				throw Exception::User("Beneficiary already exists.\n");

		beneficiaryList.push_back(&_beneficiary);
		return true;
	}
	catch (Exception::User& e)
	{
		std::cout << e.what();
		return false;
	}
}

void Organization::RemoveBeneficiary(Beneficiary& _beneficiary)
{
	for (auto it = beneficiaryList.begin(); it != beneficiaryList.end(); ++it)
		// Overloaded == operator in "User.h"
		// Directly checks between phone numbers
		if (**it == _beneficiary)
		{
			beneficiaryList.erase(it);
			std::system("cls");
			std::cout << "Beneficiary successfully removed." << std::endl;
			std::system("pause");
			return;
		}
}

// Instead of ListDonators()
std::vector<Donator*>&  Organization::GetDonators()
{
	return donatorList;
}

// Instead of ListBeneficiaries()
std::vector<Beneficiary*>&  Organization::GetBeneficiaries()
{
	return beneficiaryList;
}

// Returns a vector of pointers to the Entities with the selected category
// Instead of ListEntities()
std::vector<Entity*> Organization::GetEntitiesByCategory(bool _isMaterialCategory)
{
	std::vector<Entity*> categorizedEntities;

	if (_isMaterialCategory)
	{
		for (auto& entityPtr : entityList)
			if (typeid(*entityPtr) == typeid(Material))
				categorizedEntities.push_back(entityPtr);
	}
	else
	{
		for (auto& entityPtr : entityList)
			if (typeid(*entityPtr) == typeid(Service))
				categorizedEntities.push_back(entityPtr);
	}

	return categorizedEntities;
}


// Helper functions

std::vector<Entity*>& Organization::GetEntityList()
{
	return entityList;
}

// currentDonations wrappers
RequestDonation& Organization::GetDonation(int& _id)
{
	return currentDonations.Get(_id);
}

bool Organization::AddDonation(RequestDonation& _newRequestDonation)
{
	return currentDonations.Add(_newRequestDonation, entityList);
}

void Organization::RemoveDonation(RequestDonation& _rd)
{
	currentDonations.Remove(_rd);
}

void Organization::ModifyDonation(RequestDonation& _rd, double _newQuantity)
{
	currentDonations.Modify(_rd, _newQuantity);
}

std::vector<RequestDonation>& Organization::GetDonations()
{
	return currentDonations.GetRequestDonations();
}

void Organization::ResetDonations()
{
	currentDonations.Reset();
}


// Operator overloading

// Overloading << (Print operator)
std::ostream& operator<<(std::ostream& stream, Organization& organization)
{
	stream << "Organization: " + organization.name + "\n";
	return stream;
}
