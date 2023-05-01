#include "Crew.h"

Crew::Crew() : Passenger()
{
    role = "unknown";
}
Crew::Crew(std::string name, std::string surname, int age, std::string nationality, int flight_number, std::string role) : Passenger(name, surname, age, nationality, flight_number)
{
    this->role = role;
}
Crew::~Crew()
{
}
void Crew::output()
{
    std::cout << role << " " << name << " " << surname << " " << age << " " << nationality << " " << flight_number << " " << std::endl;
}
bool Crew::modify()
{
    std::string name, surname, age, nationality, role;
    std::cout << "Input new passenger data:" << std::endl;
    std::cout << "Name: ";
    std::cin >> name;
    std::cout << "Surname: ";
    std::cin >> surname;
    std::cout << "Age: ";
    std::cin >> age;
    std::cout << "Nationality: ";
    std::cin >> nationality;
    std::cout << "Role: ";
    std::cin >> role;
    try
    {
        this->name = name;
        this->surname = surname;
        this->age = std::stoi(age);
        this->nationality = nationality;
        this->role = role;
        return 0;
    }
    catch (const std::invalid_argument & ia)
    {
        std::cout << ia.what() << std::endl;
        return 1;
    }
    catch (const std::out_of_range & oor)
    {
        std::cout << oor.what() << std::endl;
        return 1;
    }
    catch (const std::exception & e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
}