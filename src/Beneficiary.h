#pragma once
#include "User.h"
#include "Requests.h"
#include "RequestDonationList.h"

class Requests;
class Organization;

class Beneficiary : public User
{
public:
	// Constructor
	Beneficiary(std::string _phone, std::string _name, int _noPersons = 1);
	// Destructor
	~Beneficiary();

	int& GetPersons();

	// receivedList wrappers
	RequestDonationList* GetReceivedList();
	void ClearReceivedList();
	void AddReceived(RequestDonation& _rd, Organization& _organization);

	// requestsList wrappers
	bool Add(double& _quantity, Organization& _organization, Entity& _entity);
	void Remove(RequestDonation& _rd);
	bool Modify(RequestDonation& _rd, double& _newQuantity, Organization& _organization);
	void Reset();
	bool Commit(Organization& _organization);
	std::vector<RequestDonation>* GetRequests();
private:
	int noPersons;

	Requests* requestsList;
	RequestDonationList* receivedList;
};
