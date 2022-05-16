#include "Material.h"

// Constructor
Material::Material
(
	std::string _name, std::string _description, int _id,
	double _level1, double _level2, double _level3
)
	:Entity(_name, _description, _id), level1(_level1), level2(_level2), level3(_level3)
{

}

double Material::GetLevel1()
{
	return level1;
}

double Material::GetLevel2()
{
	return level2;
}

double Material::GetLevel3()
{
	return level3;
}

std::string Material::GetDetails()
{
	return 
		"Type: Material\nLevel 1: " + std::to_string(this->level1) +
		"\nLevel 2: " + std::to_string(this->level2) +
		"\nLevel 3: " + std::to_string(this->level3) + "\n";
}
