#include "User.h"

// Constructor
User::User(std::string& _phone, std::string& _name)
	:phone(_phone), name(_name)
{

}

// Default destructor
User::~User()
{

}

std::string& User::GetName()
{
	return name;
}


// Operator overloading

// Overloading << (Print operator)
std::ostream& operator<<(std::ostream& _stream, User& _user)
{
	_stream << "Name: " + _user.name + "\nPhone: " + _user.phone + "\n";
	return _stream;
}

// Overloading == between 2 Users
bool operator==(User& _user1, User& _user2)
{
	return (_user1.phone == _user2.phone);
}

// Overloading == between string and User
bool operator==(std::string& _phone, User& _user)
{
	return (_phone == _user.phone);
}
