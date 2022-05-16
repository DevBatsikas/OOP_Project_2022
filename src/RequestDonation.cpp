#include "RequestDonation.h"

// Constructor
RequestDonation::RequestDonation(Entity& _entity, double _quantity)
	:entity(&_entity), quantity(_quantity)
{

}

// Get name of Entity
std::string& RequestDonation::GetName()
{
	return entity->GetName();
}

int& RequestDonation::GetID()
{
	return entity->GetID();
}


// Operator overloading

// Overloading << (Print operator)
std::ostream& operator<<(std::ostream& _stream, RequestDonation& _rd)
{
	_stream << (*_rd.entity).GetName() << " (" << _rd.quantity << ")\n";
	return _stream;
}

// Overloading == between 2 RequestDonations
bool operator==(RequestDonation& _rd1, RequestDonation& _rd2)
{
	return (*_rd1.entity == *_rd2.entity);
}

// Overloading == between a RequestDonation and an int
bool operator==(RequestDonation& _rd, int& _id)
{
	return (*_rd.entity == _id);
}

// Overloading == between a RequestDonation and an Entity
bool operator==(RequestDonation& _rd, Entity& _entity)
{
	return (*_rd.entity == _entity);
}
