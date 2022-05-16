#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <span>

#include "Organization.h"

class Menu
{
public:
	// Constructor
	Menu(Organization&);
	
private:
	// Windows console handle
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);


	// Pages
	// Each page is represented by an entry in the enum below.
	// Passing an int from the enum to the "DisplayPage()" function
	// you call the corresponding function for that page. Every page
	// or in other words every entry in the enum has its own function

	enum pageType
	{
		EXIT_PAGE,
		LOGIN_PAGE,
		REGISTER_PAGE,

		ADMIN_MAIN_PAGE,
		ADMIN_MONITOR_ORGANIZATION_PAGE,
		ADMIN_LIST_BENEFICIARIES_PAGE,
		ADMIN_LIST_DONATORS_PAGE,
		ADMIN_BENEFICIARY_DETAILS_PAGE,
		ADMIN_DONATOR_DETAILS_PAGE,
		ADMIN_CURRENT_DONATIONS_PAGE,

		DONATOR_MAIN_PAGE,
		DONATOR_SHOW_OFFERS_PAGE,
		DONATOR_OFFER_DETAILS_PAGE,

		BENEFICIARY_MAIN_PAGE,
		BENEFICIARY_SHOW_REQUESTS_PAGE,
		BENEFICIARY_REQUEST_DETAILS_PAGE,

		SELECT_ENTITY_CATEGORY_PAGE,
		MATERIALS_LIST_PAGE,
		SERVICES_LIST_PAGE,
		ENTITY_DETAILS_PAGE
	};

	// Displays the given page
	// Has optional parameters for passing to pages
	// that require more details for example the
	// Entity Details page which needs to know about
	// which Entity we are talking about
	void DisplayPage(int _page, Entity* = nullptr, Beneficiary* = nullptr, Donator* = nullptr, RequestDonation* = nullptr);

	// Holds the history of pages. Every time we visit a new page
	// it's corresponding number from the enum is added to this list
	std::vector<int> history;

	// Page headers
	// Called before each page display
	// according the loggedInUserType
	void ExitHeader();
	void LoginHeader();
	void RegisterHeader();
	void AdminHeader();
	void DonatorHeader();
	void BeneficiaryHeader();

	// Page functions
	// After this point are the functions that correspond
	// to each page. The names should give you a basic idea
	// of what their purpose is but there are more details about
	// each one of them in the "Menu.cpp" file in the corresponding function

	// Exit pages
	void ExitMain();
	
	// Login pages
	void LoginMain();

	// Register pages
	void RegisterMain();
	void RegisterDetails(bool);

	// Admin pages
	void AdminMain();
	void AdminMonitorOrganization();
	void AdminListBeneficiaries();
	void AdminListDonators();
	void AdminBeneficiaryDetails(Beneficiary& _beneficiary);
	void AdminDonatorDetails(Donator& _donator);
	void AdminCurrentDonations();

	// Donator pages
	void DonatorMain();
	void DonatorShowOffers();
	void DonatorOfferDetails(RequestDonation&);

	// Beneficiary pages
	void BeneficiaryMain();
	void BeneficiaryShowRequests();
	void BeneficiaryRequestDetails(RequestDonation&);

	// Global pages
	void SelectEntityCategory();
	void MaterialsList();
	void ServicesList();
	void EntityDetails(Entity&);


	// User
	enum userType
	{
		ADMIN,
		DONATOR,
		BENEFICIARY,
		UNREGISTERED
	};

	int loggedInUserType;

	User* loggedInUser;


	 // Organization
	Organization organization;


	// Helper functions

	// Shows an interactive selection menu that the user
	// can navigate with the arrow keys instead of the classic
	// "enter a number to select" menu. This makes the menu navigation
	// proccess more streamlined since it is a better user
	// experience and it does not allow the user to enter an invalid value
	// for example a char where an int is expected, thus removing the need
	// for any error handling.
	// The options are dynamic according to the array passed as a parameter.
	// It displays each string in the array as a different option and then
	// returns the index of said array as a selection.
	int SelectionMenu(std::span<std::string>);

	// Checks given phone against organization's users
	int CheckLoginCredentials(std::string&);

	// Goes back a page from history
	void GoBackPage();
};
