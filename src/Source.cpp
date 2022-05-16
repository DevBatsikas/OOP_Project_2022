#include "Menu.h"

int main()
{
    Organization RedCross{"Red Cross"};


    // Create Entities
    Material Milk{ "Milk", "Drinkable milk", 0, 1.2, 3.4, 10.6 };
    Material Sugar{ "Sugar", "Crystalic sugar", 1, 0.5, 1.4, 6.6 };
    Material Rice{ "Rice", "White rice", 2, 2.3, 5, 20.2 };

    Service MedicalSupport{ "Medical Support" , "Health services", 3 };
    Service NurserySupport{ "Nursery Support" , "Child Services", 4 };
    Service BabySitting{ "Baby Sitting" , "Child services", 5 };

    // Add Entities to Organization
    RedCross.AddEntity(Milk);
    RedCross.AddEntity(Sugar);
    RedCross.AddEntity(Rice);

    RedCross.AddEntity(MedicalSupport);
    RedCross.AddEntity(NurserySupport);
    RedCross.AddEntity(BabySitting);


    // Set organization admin
    Admin RedCrossAdmin{ "6980119940", "Thodoris" };
    RedCross.SetAdmin(RedCrossAdmin);

    // Add Donators
    Donator Donator1{ "69111", "Donator 1" };
    RedCross.InsertDonator(Donator1);

    // Add Beneficiaries
    Beneficiary Beneficiary1{ "6911", "Beneficiary 1" };
    Beneficiary Beneficiary2{ "6922", "Beneficiary 2", 15 };
    RedCross.InsertBeneficiary(Beneficiary1);
    RedCross.InsertBeneficiary(Beneficiary2);

    
    Menu menu{RedCross};
}
