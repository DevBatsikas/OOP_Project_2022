#pragma once
#include <vector>
#include <map>
#include <typeinfo>

#include "Admin.h"
#include "Donator.h"
#include "Beneficiary.h"
#include "Material.h"
#include "Service.h"
#include "RequestDonationList.h"

#include "Exception.h"

class Donator;
class Beneficiary;

class Organization
{
public:
	// Constructor
	Organization(std::string _name);


	void SetAdmin(Admin& _admin);
	Admin& GetAdmin();

	void AddEntity(Entity& _entity);
	void RemoveEntity(int& _id);

	bool InsertDonator(Donator& _donator);
	void RemoveDonator(Donator& _donator);

	bool InsertBeneficiary(Beneficiary& _beneficiary);
	void RemoveBeneficiary(Beneficiary& _beneficiary);

	// Instead of printing, these functions return the lists
	// because we create an interactive menu which is handled by
	// the Menu class
	std::vector<Donator*>& GetDonators(); // Instead of ListDonators()
	std::vector<Beneficiary*>& GetBeneficiaries(); // Instead of ListBeneficiaries()
	// Returns a vector of the entities of a specific category
	std::vector<Entity*> GetEntitiesByCategory(bool _isMaterialCategory); // Instead of ListEntities()


	// Helper functions

	// Checks if entity exists in the entityList
	// With the template you can pass either an entity
	// or an int to the function and check if the ID exists in the list
	template <typename T>
	inline bool EntityExistsInEntityList(T& _entity)
	{
		for (auto& entity : entityList)
			if (*entity == _entity)
				return true;

		return false;
	}

	std::vector<Entity*>& GetEntityList();

	// currentDonations wrappers
	RequestDonation& GetDonation(int& _id);
	bool AddDonation(RequestDonation& _newRequestDonation);
	void RemoveDonation(RequestDonation& _rd);
	void ModifyDonation(RequestDonation& _rd, double _newQuantity);
	std::vector<RequestDonation>& GetDonations();
	void ResetDonations();
	

	// Operator overloading

	// Overloading << (Print operator)
	friend std::ostream& operator<<(std::ostream& _stream, Organization& _organization);
private:
	std::string name;

	Admin* admin;
	std::vector<Donator*> donatorList;
	std::vector<Beneficiary*> beneficiaryList;

	std::vector<Entity*> entityList;

	RequestDonationList currentDonations;
};
