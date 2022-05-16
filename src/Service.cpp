#include "Service.h"

// Constructor
Service::Service(std::string _name, std::string _description, int _id)
	:Entity(_name, _description, _id)
{

}

std::string Service::GetDetails()
{
	return "Type: Service\n";
}
