#pragma once
#include <iostream>
#include <string>

class Entity
{
public:
	// Constructor
	Entity(std::string& _name, std::string& _description, int& _id);

	// Declaring Destructor as Pure Virtual makes class
	// abstract meaning it can not have instances
	virtual ~Entity() = 0;

	std::string& GetName();
	int& GetID();


	// Virtual functions for derived classes

	// Material
	virtual double GetLevel1() { return 0; };
	virtual double GetLevel2() { return 0; };
	virtual double GetLevel3() { return 0; };


	// Operator overloading

	// Overloading << (Print operator)
	friend std::ostream& operator<<(std::ostream& _stream, Entity& _entity);
	// Overloading == between 2 Entities
	friend bool operator==(Entity& _entity1, Entity& _entity2);
	// Overloading == between Entity and int
	friend bool operator==(Entity& _entity, int& _id);
private:
	std::string name;
	std::string description;
	int id;

	std::string GetEntityInfo();
	// Declaring function as pure virtual forces
	// subclasses to implement it
	virtual std::string GetDetails() = 0;
};
