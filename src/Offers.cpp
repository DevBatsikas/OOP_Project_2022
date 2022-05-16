#include "Offers.h"

bool Offers::Commit(Organization& _organization)
{
	bool wasSuccessful = true;

	// Commit RequestDonations to Organization's currentDonations
	for (auto& requestDonation : rdEntities)
		wasSuccessful = _organization.AddDonation(requestDonation);
		

	// If commit was successful reset rdEntities list
	if (wasSuccessful)
	{
		std::system("cls");
		std::cout << "Commit was successful." << std::endl;
		std::system("pause");
		Reset();
		return true;
	}

	std::system("cls");
	std::cout << "Certain items were not commited." << std::endl;
	std::system("pause");
	return false;
}
