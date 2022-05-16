#include "Entity.h"

// Constructor
Entity::Entity(std::string& _name, std::string& _description, int& _id)
	:name(_name), description(_description), id(_id)
{

}

// Default destructor
Entity::~Entity()
{

}

std::string& Entity::GetName()
{
	return name;
}

int& Entity::GetID()
{
	return id;
}

std::string Entity::GetEntityInfo()
{
	return
		"Name: " + name +
		"\nDescription: " + description +
		"\nID: " + std::to_string(id) + "\n";
}


// Operator overloading

// Overloading << (Print operator)
std::ostream& operator<<(std::ostream& _stream, Entity& _entity)
{
	_stream << _entity.GetEntityInfo() + _entity.GetDetails();
	return _stream;
}

// Overloading == between 2 Entities
bool operator==(Entity& _entity1, Entity& _entity2)
{
	return (_entity1.id == _entity2.id);
}

// Overloading == between Entity and int
bool operator==(Entity& _entity, int& _id)
{
	return (_entity.id == _id);
}
