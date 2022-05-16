#pragma once
#include "Entity.h"

class Material : public Entity
{
public:
	// Constructor
	Material
	(
		std::string _name, std::string _description, int _id,
		double _level1, double _level2, double _level3
	);

	double GetLevel1();
	double GetLevel2();
	double GetLevel3();
private:
	std::string GetDetails();

	double level1, level2, level3;
};
