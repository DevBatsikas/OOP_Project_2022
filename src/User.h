#pragma once
#include <iostream>
#include <vector>
#include <string>

class Organization;
class RequestDonation;
class RequestDonationList;
class Entity;

class User
{
public:
	// Constructor
	User(std::string& _phone, std::string& _name);

	// Declaring Destructor as Pure Virtual makes class
	// abstract meaning it can not have instances
	virtual ~User() = 0;

	std::string& GetName();


	// Virtual functions for derived classes

	// Donator
	virtual bool Add(RequestDonation& _newRequestDonation, Organization& _organization) { return true; };
	virtual void Modify(RequestDonation& _rd, double& _newQuantity) { };
	virtual std::vector<RequestDonation>* GetOffers() { return nullptr; };

	// Beneficiary
	// requestsList wrappers
	virtual bool Add(double& _quantity, Organization& _organization, Entity& _entity) { return true; };
	virtual bool Modify(RequestDonation& _rd, double& _newQuantity, Organization& _organization) { return true; };
	virtual std::vector<RequestDonation>* GetRequests() { return nullptr; };

	// receivedList wrappers
	virtual RequestDonationList* GetReceivedList() { return nullptr; };
	virtual void ClearReceivedList() { };
	virtual void AddReceived(RequestDonation& _rd, Organization& _organization) { };

	// Shared
	virtual void Remove(RequestDonation& _rd) { };
	virtual void Reset() { };
	virtual bool Commit(Organization& _organization) { return true; };


	// Operator overloading

	// Overloading << (Print operator) instead of ToString()
	friend std::ostream& operator<<(std::ostream& _stream, User& _user);
	// Overloading == between 2 Users
	friend bool operator==(User& _user1, User& _user2);
	// Overloading == between string and User
	friend bool operator==(std::string& _phone, User& _user);
private:
	std::string name;
	std::string phone;
};
