#include "Menu.h"

// Constructor
Menu::Menu(Organization& _organization)
    :organization(_organization),
    loggedInUser(nullptr)
{
    DisplayPage(LOGIN_PAGE);
}


#pragma region Pages

// Displays the given page
void Menu::DisplayPage(int _page, Entity* _entity, Beneficiary* _beneficiary, Donator* _donator, RequestDonation* _rd)
{
    if (_page == EXIT_PAGE)
        ExitMain();

    else if (_page == LOGIN_PAGE)
        LoginMain();

    else if (_page == REGISTER_PAGE)
        RegisterMain();

    else
    {
        // Add page to history
        history.push_back(_page);
        
        // Select header to display
        switch (loggedInUserType)
        {
        case ADMIN:
            AdminHeader();

            // Select page content to display
            switch (_page)
            {
            case ADMIN_MAIN_PAGE:
                AdminMain();
                break;
            case SELECT_ENTITY_CATEGORY_PAGE:
                SelectEntityCategory();
                break;
            case MATERIALS_LIST_PAGE:
                MaterialsList();
                break;
            case SERVICES_LIST_PAGE:
                ServicesList();
                break;
            case ENTITY_DETAILS_PAGE:
                EntityDetails(*_entity);
                break;
            case ADMIN_MONITOR_ORGANIZATION_PAGE:
                AdminMonitorOrganization();
                break;
            case ADMIN_LIST_BENEFICIARIES_PAGE:
                AdminListBeneficiaries();
                break;
            case ADMIN_LIST_DONATORS_PAGE:
                AdminListDonators();
                break;
            case ADMIN_BENEFICIARY_DETAILS_PAGE:
                AdminBeneficiaryDetails(*_beneficiary);
                break;
            case ADMIN_DONATOR_DETAILS_PAGE:
                AdminDonatorDetails(*_donator);
                break;
            case ADMIN_CURRENT_DONATIONS_PAGE:
                AdminCurrentDonations();
                break;
            default:
                break;
            }
            break;

        case DONATOR:
            DonatorHeader();

            // Select page content to display
            switch (_page)
            {
            case DONATOR_MAIN_PAGE:
                DonatorMain();
                break;
            case SELECT_ENTITY_CATEGORY_PAGE:
                SelectEntityCategory();
                break;
            case MATERIALS_LIST_PAGE:
                MaterialsList();
                break;
            case SERVICES_LIST_PAGE:
                ServicesList();
                break;
            case ENTITY_DETAILS_PAGE:
                EntityDetails(*_entity);
                break;
            case DONATOR_SHOW_OFFERS_PAGE:
                DonatorShowOffers();
                break;
            case DONATOR_OFFER_DETAILS_PAGE:
                DonatorOfferDetails(*_rd);
                break;
            default:
                break;
            }
            break;

        case BENEFICIARY:
            BeneficiaryHeader();

            // Select page content to display
            switch (_page)
            {
            case BENEFICIARY_MAIN_PAGE:
                BeneficiaryMain();
                break;
            case SELECT_ENTITY_CATEGORY_PAGE:
                SelectEntityCategory();
                break;
            case MATERIALS_LIST_PAGE:
                MaterialsList();
                break;
            case SERVICES_LIST_PAGE:
                ServicesList();
                break;
            case ENTITY_DETAILS_PAGE:
                EntityDetails(*_entity);
                break;
            case BENEFICIARY_SHOW_REQUESTS_PAGE:
                BeneficiaryShowRequests();
                break;
            case BENEFICIARY_REQUEST_DETAILS_PAGE:
                BeneficiaryRequestDetails(*_rd);
                break;
            default:
                break;
            }
            break;
            
        default:
            break;
        }  
    }
}

#pragma region Page headers

// Exit menu header
void Menu::ExitHeader()
{
    std::system("cls");
    std::cout << "===================================================================" << std::endl;
    std::cout << "=  Thank you for using the Volunteer - Donor Organization System  =" << std::endl;
    std::cout << "===================================================================" << std::endl;
}

// Login menu header
void Menu::LoginHeader()
{
    std::system("cls");
    std::cout << "==========================================================" << std::endl;
    std::cout << "=  Welcome to the Volunteer - Donor Organization System  =" << std::endl;
    std::cout << "==========================================================" << std::endl;
}

// Register menu header
void Menu::RegisterHeader()
{
    std::system("cls");
    std::cout << "==========================================================" << std::endl;
    std::cout << "=  Welcome to the Volunteer - Donor Organization System  =" << std::endl;
    std::cout << "==========================================================" << std::endl;
}

// Admin menu header
void Menu::AdminHeader()
{
    std::system("cls");
    std::cout << "===++ADMIN++==============================================" << std::endl;
    std::cout << organization << *(loggedInUser);
    std::cout << "==========================================================" << std::endl;
}

// Donator menu header
void Menu::DonatorHeader()
{
    std::system("cls");
    std::cout << "===++DONATOR++============================================" << std::endl;
    std::cout << organization << *(loggedInUser);
    std::cout << "==========================================================" << std::endl;
}

// Beneficiary menu header
void Menu::BeneficiaryHeader()
{
    std::system("cls");
    std::cout << "===++BENEFICIARY++========================================" << std::endl;
    std::cout << organization << *(loggedInUser);
    std::cout << "==========================================================" << std::endl;
}

#pragma endregion

#pragma region Exit pages

// Main exit page
void Menu::ExitMain()
{
    ExitHeader();
    std::system("pause");
}

#pragma endregion

#pragma region Login pages

// Main login page
void Menu::LoginMain()
{
    // Clear history list
    history.clear();

    LoginHeader();
    std::cout << "Enter your phone number below." << std::endl;
    std::cout << "- ";

    std::string credentials;
    std::cin >> credentials;

    // Check credentials and show corresponding landing page
    // for each type of User
    loggedInUserType = CheckLoginCredentials(credentials);

    switch (loggedInUserType)
    {
    case ADMIN:
        DisplayPage(ADMIN_MAIN_PAGE);
        break;
    case DONATOR:
        DisplayPage(DONATOR_MAIN_PAGE);
        break;
    case BENEFICIARY:
        DisplayPage(BENEFICIARY_MAIN_PAGE);
        break;
    default:
        DisplayPage(REGISTER_PAGE);
        break;
    }
}

#pragma endregion

#pragma region Register pages

// Main register page
void Menu::RegisterMain()
{
    RegisterHeader();
    std::cout << "No user found with that phone number." << std::endl;
    
    // Create a menu with the following options and await user selection
    std::array<std::string, 4> options{ {"Register - Donator", "Register - Beneficiary", "Login", "Exit"} };

    switch (SelectionMenu(options))
    {
    case 0:
        RegisterDetails(true);
        break;
    case 1:
        RegisterDetails(false);
        break;
    case 2:
        DisplayPage(LOGIN_PAGE);
        break;
    case 3:
        DisplayPage(EXIT_PAGE);
        break;
    default:
        break;
    }
}

// Register user details page
void Menu::RegisterDetails(bool _donatorRegister)
{
    // Get type of registration
    std::string registrationType = (_donatorRegister) ? "++DONATOR++" : "++BENEFICIARY++";

    // Get user details
    RegisterHeader();
    std::cout << "Registering as " << registrationType << ". Please enter your details below." << std::endl;

    std::string phone, name;
    int noPersons = 1;
    std::cout << "- Phone number: ";
    std::cin >> phone;
    std::cout << "- Name: ";
    std::cin >> name;

    // If registration type is Beneficiary
    // get noPersons as well.
    if (!_donatorRegister)
    {
        std::cout << "- Number of people in your family: ";
        std::cin >> noPersons;
    }
    
    // Attempt to register with given User details
    // If User already exists throws exception
    bool registeredSuccessfully = false;
    if (_donatorRegister)
        registeredSuccessfully = organization.InsertDonator(*(new Donator(phone, name)));
    else
        registeredSuccessfully = organization.InsertBeneficiary(*(new Beneficiary(phone, name, noPersons)));

    if (registeredSuccessfully)
    {
        std::cout << "Successfully registered as " << registrationType << "." << std::endl;
        std::system("pause");
    }

    DisplayPage(LOGIN_PAGE);
}

#pragma endregion

#pragma region Admin pages

// Main admin page
void Menu::AdminMain()
{
    // Options menu
    std::array<std::string, 4> options{ {"View", "Monitor Organization", "Logout", "Exit"} };

    switch (SelectionMenu(options))
    {
    case 0:
        DisplayPage(SELECT_ENTITY_CATEGORY_PAGE);
        break;
    case 1:
        DisplayPage(ADMIN_MONITOR_ORGANIZATION_PAGE);
        break;
    case 2:
        DisplayPage(LOGIN_PAGE);
        break;
    case 3:
        DisplayPage(EXIT_PAGE);
        break;
    default:
        break;
    }
}

// Admin monitor organization page
void Menu::AdminMonitorOrganization()
{
    // Options menu
    std::array<std::string, 5> options{ {"List Beneficiaries", "List Donators", "Reset Beneficiaries Lists", "Current Donations", "Back"}};

    switch (SelectionMenu(options))
    {
    case 0:
        DisplayPage(ADMIN_LIST_BENEFICIARIES_PAGE);
        break;
    case 1:
        DisplayPage(ADMIN_LIST_DONATORS_PAGE);
        break;
    case 2:
        for (auto& beneficiary : organization.GetBeneficiaries())
            beneficiary->ClearReceivedList();
        DisplayPage(ADMIN_MONITOR_ORGANIZATION_PAGE);
        break;
    case 3:
        DisplayPage(ADMIN_CURRENT_DONATIONS_PAGE);
        break;
    case 4:
        GoBackPage();
        break;
    default:
        break;
    }
}

// Admin list beneficiaries page
void Menu::AdminListBeneficiaries()
{
    // Get list of Beneficiaries
    std::vector<Beneficiary*> beneficiariesList = organization.GetBeneficiaries();

    std::vector<std::string> options;
    int counter = 1;

    // Create a list of options with the names displayed
    for (auto& beneficiaryPtr : beneficiariesList)
    {
        options.push_back(std::to_string(counter) + " | " + beneficiaryPtr->GetName());
        counter++;
    }
    options.push_back("Back");

    unsigned int selection = SelectionMenu(options);

    // Display entity details page
    if (selection < beneficiariesList.size())
        DisplayPage(ADMIN_BENEFICIARY_DETAILS_PAGE, nullptr, beneficiariesList[selection]);
    else if (selection == beneficiariesList.size())
        GoBackPage();
}

// Admin list donators page
void Menu::AdminListDonators()
{
    // Get list of Donators
    std::vector<Donator*> donatorsList = organization.GetDonators();

    std::vector<std::string> options;
    int counter = 1;

    // Create a list of options with the names displayed
    for (auto& donatorPtr : donatorsList)
    {
        options.push_back(std::to_string(counter) + " | " + donatorPtr->GetName());
        counter++;
    }
    options.push_back("Back");

    unsigned int selection = SelectionMenu(options);

    // Display donator details page
    if (selection < donatorsList.size())
        DisplayPage(ADMIN_DONATOR_DETAILS_PAGE, nullptr, nullptr, donatorsList[selection]);
    else if (selection == donatorsList.size())
        GoBackPage();
}

// Admin beneficiary details page
void Menu::AdminBeneficiaryDetails(Beneficiary& _beneficiary)
{
    std::cout << _beneficiary;
    std::cout << "--------------------" << std::endl;
    std::cout << "Received Items: " << std::endl;
    std::vector<RequestDonation> receivedList = _beneficiary.GetReceivedList()->GetRequestDonations();

    // Display requests if any
    if (receivedList.size() == 0)
        std::cout << "=====No Requests=====" << std::endl;
    else
        for (auto& requestDonation : receivedList)
            std::cout << requestDonation;

    // Options menu
    std::array<std::string, 4> options{ {"Clear Received List", "Delete User", "Back", "Exit"} };

    switch (SelectionMenu(options))
    {
    case 0:
        _beneficiary.ClearReceivedList();
        DisplayPage(ADMIN_BENEFICIARY_DETAILS_PAGE, nullptr, &_beneficiary);
        break;
    case 1:
        organization.RemoveBeneficiary(_beneficiary);
        GoBackPage();
        break;
    case 2:
        GoBackPage();
        break;
    case 3:
        DisplayPage(EXIT_PAGE);
        break;
    default:
        break;
    }
}

// Admin donator details page
void Menu::AdminDonatorDetails(Donator& _donator)
{
    // Donator details
    std::cout << _donator;
    std::cout << "-------------------" << std::endl;
    std::cout << "Offers: " << std::endl;
    std::vector<RequestDonation>* offers = _donator.GetOffers();

    // Display offers if any
    if (offers->size() == 0)
        std::cout << "=====No Offers=====" << std::endl;
    else
        for (auto& requestDonation : *offers)
            std::cout << requestDonation;

    // Options menu
    std::array<std::string, 3> options{ {"Delete User", "Back", "Exit"} };

    switch (SelectionMenu(options))
    {
    case 0:
        organization.RemoveDonator(_donator);
        GoBackPage();
        break;
    case 1:
        GoBackPage();
        break;
    case 2:
        DisplayPage(EXIT_PAGE);
        break;
    default:
        break;
    }
}

// Admin current donations page
void Menu::AdminCurrentDonations()
{
    std::cout << "Donations Received: " << std::endl;
    std::vector<RequestDonation> currentDonations = organization.GetDonations();

    // Display donations if any
    if (currentDonations.size() == 0)
        std::cout << "====No Donations====" << std::endl;
    else
        for (auto& requestDonation : currentDonations)
            std::cout << requestDonation;

    // Options menu
    std::array<std::string, 2> options{ {"Back", "Exit"} };

    switch (SelectionMenu(options))
    {
    case 0:
        GoBackPage();
        break;
    case 1:
        DisplayPage(EXIT_PAGE);
        break;
    default:
        break;
    }
}

#pragma endregion

#pragma region Donator pages

// Main donator page
void Menu::DonatorMain()
{
    std::array<std::string, 5> options{ {"Add Offer", "Show Offers", "Commit", "Logout", "Exit"} };

    switch (SelectionMenu(options))
    {
    case 0:
        DisplayPage(SELECT_ENTITY_CATEGORY_PAGE);
        break;
    case 1:
        DisplayPage(DONATOR_SHOW_OFFERS_PAGE);
        break;
    case 2:
        loggedInUser->Commit(organization);
        DisplayPage(DONATOR_MAIN_PAGE);
        break;
    case 3:
        DisplayPage(LOGIN_PAGE);
        break;
    case 4:
        DisplayPage(EXIT_PAGE);
        break;
    default:
        break;
    }
}

void Menu::DonatorShowOffers()
{
    // Get list of Offers
    std::vector<RequestDonation>* offers = loggedInUser->GetOffers();

    std::vector<std::string> options;
    int counter = 1;

    // Create a list of options
    for (auto& requestDonation : *offers)
    {
        options.push_back(std::to_string(counter) + " | " + requestDonation.GetName());
        counter++;
    }
    options.push_back("Clear Offers");
    options.push_back("Commit");
    options.push_back("Back");

    unsigned int selection = SelectionMenu(options);

    // Display offer details page
    if (selection < offers->size())
        DisplayPage(DONATOR_OFFER_DETAILS_PAGE, nullptr, nullptr, nullptr, &(*offers)[selection]);
    else if (selection == offers->size()) // Reset offers
    {
        loggedInUser->Reset();
        GoBackPage();
    }  
    else if (selection == offers->size() + 1) // Commit offers
    {
        loggedInUser->Commit(organization);
        GoBackPage();
    }
    else
        GoBackPage();
}

void Menu::DonatorOfferDetails(RequestDonation& _rd)
{
    std::cout << _rd;

    std::array<std::string, 4> options{ {"Delete Offer", "Edit quantity", "Back", "Exit"} };

    switch (SelectionMenu(options))
    {
    case 0:
        loggedInUser->Remove(_rd);
        GoBackPage();
        break;
    case 1:
        // Take quantity and add to the Donator's offersList
        DonatorHeader();
        std::cout << "Old quantity: " << _rd.quantity << std::endl;
        double quantity;
        std::cout << "Enter new quantity: ";
        std::cin >> quantity;

        loggedInUser->Modify(_rd, quantity);
        DonatorHeader();
        std::cout << "Offer successfully updated." << std::endl;
        std::system("pause");
        GoBackPage();
        break;
    case 2:
        GoBackPage();
        break;
    case 3:
        DisplayPage(EXIT_PAGE);
        break;
    default:
        break;
    }
}

#pragma endregion

#pragma region Beneficiary pages

// Main beneficiary page
void Menu::BeneficiaryMain()
{
    std::array<std::string, 5> options{ {"Add Request", "Show Requests", "Commit", "Logout", "Exit"} };

    switch (SelectionMenu(options))
    {
    case 0:
        DisplayPage(SELECT_ENTITY_CATEGORY_PAGE);
        break;
    case 1:
        DisplayPage(BENEFICIARY_SHOW_REQUESTS_PAGE);
        break;
    case 2:
        loggedInUser->Commit(organization);
        DisplayPage(BENEFICIARY_MAIN_PAGE);
        break;
    case 3:
        DisplayPage(LOGIN_PAGE);
        break;
    case 4:
        DisplayPage(EXIT_PAGE);
        break;
    default:
        break;
    }
}

void Menu::BeneficiaryShowRequests()
{
    // Get list of Requests
    std::vector<RequestDonation>* requests = loggedInUser->GetRequests();

    std::vector<std::string> options;
    int counter = 1;

    // Create a list of options
    for (auto& requestDonation : *requests)
    {
        options.push_back(std::to_string(counter) + " | " + requestDonation.GetName());
        counter++;
    }
    options.push_back("Clear Requests");
    options.push_back("Commit");
    options.push_back("Back");

    unsigned int selection = SelectionMenu(options);

    // Display request details page
    if (selection < requests->size())
        DisplayPage(BENEFICIARY_REQUEST_DETAILS_PAGE, nullptr, nullptr, nullptr, &(*requests)[selection]);
    else if (selection == requests->size()) // Reset offers
    {
        loggedInUser->Reset();
        GoBackPage();
    }
    else if (selection == requests->size() + 1) // Commit offers
    {
        loggedInUser->Commit(organization);
        DisplayPage(BENEFICIARY_MAIN_PAGE);
    }
    else
        GoBackPage();
}

void Menu::BeneficiaryRequestDetails(RequestDonation& _rd)
{
    std::cout << _rd;

    std::array<std::string, 4> options{ {"Delete Request", "Edit quantity", "Back", "Exit"} };

    switch (SelectionMenu(options))
    {
    case 0:
        loggedInUser->Remove(_rd);
        GoBackPage();
        break;
    case 1:
        // Take quantity and add to the Donator's offersList
        BeneficiaryHeader();
        std::cout << "Old quantity: " << _rd.quantity << std::endl;
        double quantity;
        std::cout << "Enter new quantity: ";
        std::cin >> quantity;

        // If modification was successful
        if (loggedInUser->Modify(_rd, quantity, organization))
        {
            BeneficiaryHeader();
            std::cout << "Offer successfully updated." << std::endl;
            std::system("pause");
        }
        GoBackPage();
        break;
    case 2:
        GoBackPage();
        break;
    case 3:
        DisplayPage(EXIT_PAGE);
        break;
    default:
        break;
    }
}

#pragma endregion

#pragma region Global pages

// Select entity category page
void Menu::SelectEntityCategory()
{
    std::vector<Entity*> materialsList = organization.GetEntitiesByCategory(true);
    std::vector<Entity*> servicesList = organization.GetEntitiesByCategory(false);

    std::array<std::string, 3> options
    {
        {
            "Materials (" + std::to_string(materialsList.size()) + ")",
            "Services (" + std::to_string(servicesList.size()) + ")",
            "Back"
        }
    };

    switch (SelectionMenu(options))
    {
    case 0:
        DisplayPage(MATERIALS_LIST_PAGE);
        break;
    case 1:
        DisplayPage(SERVICES_LIST_PAGE);
        break;
    case 2:
        GoBackPage();
        break;
    default:
        break;
    }
}

// Materials list page
void Menu::MaterialsList()
{
    // Get list of Material pointers
    std::vector<Entity*> materialsList = organization.GetEntitiesByCategory(true);

    std::vector<std::string> options;
    int counter = 1;

    // Create a list of options
    for (auto& materialPtr : materialsList)
    {
        options.push_back(std::to_string(counter) + " | " + materialPtr->GetName());
        counter++;
    }
    options.push_back("Back");

    unsigned int selection = SelectionMenu(options);

    // Display entity details page
    if (selection < materialsList.size())
        DisplayPage(ENTITY_DETAILS_PAGE, materialsList[selection]);
    else if (selection == materialsList.size())
        GoBackPage();
}

// Services list page
void Menu::ServicesList()
{
    // Get list of Service pointers
    std::vector<Entity*> servicesList = organization.GetEntitiesByCategory(false);

    std::vector<std::string> options;
    int counter = 1;

    // Create a list of options
    for (auto& servicePtr : servicesList)
    {
        options.push_back(std::to_string(counter) + " | " + servicePtr->GetName());
        counter++;
    }
    options.push_back("Back");

    unsigned int selection = SelectionMenu(options);

    // Display entity details page
    if (selection < servicesList.size())
        DisplayPage(ENTITY_DETAILS_PAGE, servicesList[selection]);
    else if (selection == servicesList.size())
        GoBackPage();
}

// Entity details page
void Menu::EntityDetails(Entity& _entity)
{
    std::cout << _entity;

    switch (loggedInUserType)
    {
        // Menu for Admin entities
    case ADMIN:
    {
        std::array<std::string, 2> options{ {"Back", "Exit"} };

        switch (SelectionMenu(options))
        {
        case 0:
            GoBackPage();
            break;
        case 1:
            DisplayPage(EXIT_PAGE);
            break;
        default:
            break;
        }
        break;
    }
    // Menu for Donator Entities view
    case DONATOR:
    {
        std::array<std::string, 3> options{ {"Make Offer", "Back", "Exit"}};

        switch (SelectionMenu(options))
        {
        case 0:
            // Take quantity and add to the Donator's offersList
            DonatorHeader();
            double quantity;
            std::cout << "Enter quantity: ";
            std::cin >> quantity;

            loggedInUser->Add((*new RequestDonation(_entity, quantity)), organization);
            DonatorHeader();
            std::cout << "Offer successfully added." << std::endl;
            std::system("pause");
            GoBackPage();
            break;
        case 1:
            GoBackPage();
            break;
        case 2:
            DisplayPage(EXIT_PAGE);
            break;
        default:
            break;
        }
        break;
    }
    case BENEFICIARY:
    {
        std::array<std::string, 3> options{ {"Make Request", "Back", "Exit"} };

        switch (SelectionMenu(options))
        {
        case 0:
            BeneficiaryHeader();
            double quantity;
            std::cout << "Enter quantity: ";
            std::cin >> quantity;

            if (loggedInUser->Add(quantity, organization, _entity))
            {
                BeneficiaryHeader();
                std::cout << "Request successfully added." << std::endl;
                std::system("pause");
            }
            GoBackPage();
            break;
        case 1:
            GoBackPage();
            break;
        case 2:
            DisplayPage(EXIT_PAGE);
            break;
        default:
            break;
        }
        break;
    }
    default:
        break;
    }

    
}

#pragma endregion

#pragma endregion


#pragma region Helper functions

// Shows an interactive selection menu from the
// given array and returns the index of the selection
int Menu::SelectionMenu(std::span<std::string> _options)
{
    // Set default console attributes
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsoleOutput, &csbi);
    WORD consoleAttributes = csbi.wAttributes;
    COORD cursor = csbi.dwCursorPosition;

    // Hide the console blinking cursor
    CONSOLE_CURSOR_INFO lpConsoleCursorInfo;
    GetConsoleCursorInfo(hConsoleOutput, &lpConsoleCursorInfo);
    lpConsoleCursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsoleOutput, &lpConsoleCursorInfo);

    // Print options
    for (auto& option : _options)
        std::cout << "-  " << option << std::endl;

    bool selected = false;

    // Set first option as default
    UINT selection = 0;
    SetConsoleTextAttribute(hConsoleOutput, 12);
    SetConsoleCursorPosition(hConsoleOutput, cursor);
    std::cout << "-> " << _options[0];

    while (!selected)
    {
        system("pause>nul");

        // If ENTER pressed
        if (GetAsyncKeyState(VK_RETURN) & 0x8000)
            selected = true;

        // If DOWN ARROW pressed
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
        {
            // Making sure selection is within range of options
            if (selection < _options.size() - 1)
            {
                // Redraw old option
                SetConsoleTextAttribute(hConsoleOutput, consoleAttributes);
                SetConsoleCursorPosition(hConsoleOutput, cursor);
                std::cout << "-  " << _options[selection];

                // Draw current option
                cursor.Y += 1;
                SetConsoleTextAttribute(hConsoleOutput, 12);
                SetConsoleCursorPosition(hConsoleOutput, cursor);
                selection++;
                std::cout << "-> " << _options[selection];
            }
        }

        // If UP ARROW pressed
        else if (GetAsyncKeyState(VK_UP) & 0x8000)
        {
            // Making sure selection is within range of options
            if (selection > 0)
            {
                // Redraw old option
                SetConsoleTextAttribute(hConsoleOutput, consoleAttributes);
                SetConsoleCursorPosition(hConsoleOutput, cursor);
                std::cout << "-  " << _options[selection];

                // Draw current option
                cursor.Y -= 1;
                SetConsoleTextAttribute(hConsoleOutput, 12);
                SetConsoleCursorPosition(hConsoleOutput, cursor);
                selection--;
                std::cout << "-> " << _options[selection];
            }
        }
    }

    SetConsoleTextAttribute(hConsoleOutput, consoleAttributes);
    
    // Show the console blinking cursor again
    GetConsoleCursorInfo(hConsoleOutput, &lpConsoleCursorInfo);
    lpConsoleCursorInfo.bVisible = true;
    SetConsoleCursorInfo(hConsoleOutput, &lpConsoleCursorInfo);

    return selection;
}

// Checks given phone against organization's users
int Menu::CheckLoginCredentials(std::string& _credentials)
{
    // Overloaded == operator in "User.h"
    // Directly checks the phones
    if (_credentials == organization.GetAdmin())
    {
        loggedInUser = &(organization.GetAdmin());
        return ADMIN;
    }
    else
    {
        // Check Donators list
        for (auto& donator : organization.GetDonators())
            if (_credentials == *donator)
            {
                loggedInUser = donator;
                return DONATOR;
            }

        // Check Beneficiaries list
        for (auto& beneficiary : organization.GetBeneficiaries())
            if (_credentials == *beneficiary)
            {
                loggedInUser = beneficiary;
                return BENEFICIARY;
            }

        return UNREGISTERED;
    }
}

// Goes back a page from history
void Menu::GoBackPage()
{
    // Remove last element from history vector
    history.pop_back();
    int lastElem = history.back();
    history.pop_back();

    // Display last page
    DisplayPage(lastElem);
}

#pragma endregion
