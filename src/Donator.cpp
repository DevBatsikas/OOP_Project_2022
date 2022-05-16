#include "Donator.h"

// Constructor
Donator::Donator(std::string _phone, std::string _name)
	:User(_phone, _name), offersList(new Offers)
{

}

// Destructor
Donator::~Donator()
{
	User::~User();
}

bool Donator::Add(RequestDonation& _newRequestDonation, Organization& _organization)
{
	return offersList->Add(_newRequestDonation, _organization.GetEntityList());
}

void Donator::Remove(RequestDonation& _rd)
{
	offersList->Remove(_rd);
}

void Donator::Modify(RequestDonation& _rd, double& _newQuantity)
{
	offersList->Modify(_rd, _newQuantity);
}

void Donator::Reset()
{
	offersList->Reset();
}

bool Donator::Commit(Organization& _organization)
{
	return offersList->Commit(_organization);
}

std::vector<RequestDonation>* Donator::GetOffers()
{
	return &(offersList->GetRequestDonations());
}
