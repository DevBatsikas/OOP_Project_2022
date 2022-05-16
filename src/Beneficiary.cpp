#include "Beneficiary.h"

// Constructor
Beneficiary::Beneficiary(std::string _phone, std::string _name, int _noPersons)
	:User(_phone, _name), noPersons(_noPersons), requestsList(new Requests), receivedList(new RequestDonationList)
{

}

// Destructor
Beneficiary::~Beneficiary()
{
	User::~User();
}

RequestDonationList* Beneficiary::GetReceivedList()
{
	return receivedList;
}

void Beneficiary::AddReceived(RequestDonation& _rd, Organization& _organization)
{
	(*receivedList).Add(_rd, _organization.GetEntityList());
}

std::vector<RequestDonation>* Beneficiary::GetRequests()
{
	return &(requestsList->GetRequestDonations());
}

int& Beneficiary::GetPersons()
{
	return noPersons;
}

// requestsList wrappers
bool Beneficiary::Add(double& _quantity, Organization& _organization, Entity& _entity)
{
	return requestsList->Add(_quantity, *this, _organization, _entity);
}

void Beneficiary::Remove(RequestDonation& _rd)
{
	requestsList->Remove(_rd);
}

bool Beneficiary::Modify(RequestDonation& _rd, double& _newQuantity, Organization& _organization)
{
	return requestsList->Modify(_newQuantity, *this, _organization, _rd);
}

void Beneficiary::Reset()
{
	requestsList->Reset();
}

bool Beneficiary::Commit(Organization& _organization)
{
	return requestsList->Commit(_organization, *this);
}

void Beneficiary::ClearReceivedList()
{
	(*receivedList).Reset();
}
