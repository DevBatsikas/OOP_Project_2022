#pragma once
#include <stdexcept>

namespace Exception
{
	class Entity : public std::runtime_error
	{
	public:
		Entity(const char* what) : runtime_error(what){ };
		~Entity(){ std::system("pause"); };
	};

	class User : public std::runtime_error
	{
	public:
		User(const char* what) : runtime_error(what) { };
		~User() { std::system("pause"); };
	};

	class Organization : public std::runtime_error
	{
	public:
		Organization(const char* what) : runtime_error(what) { };
		~Organization() { std::system("pause"); };
	};
}

