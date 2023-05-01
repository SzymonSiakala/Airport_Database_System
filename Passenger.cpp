#include "Passenger.h"


Passenger::Passenger()
{
    name = "unknown";
    surname = "unknown";
    age = 0;
    nationality = "unknown";
    flight_number = 0;
    luggage = false;
}
Passenger::Passenger(std::string name, std::string surname, int age, std::string nationality, int flight_number, bool luggage)
{
    this->name = name;
    this->surname = surname;
    this->age = age;
    this->nationality = nationality;
    this->flight_number = flight_number;
    this->luggage = luggage;
}
Passenger::Passenger(std::string name, std::string surname, int age, std::string nationality, int flight_number)
{
    this->name = name;
    this->surname = surname;
    this->age = age;
    this->nationality = nationality;
    this->flight_number = flight_number;
    luggage = false;
}
Passenger::~Passenger()
{
}
void Passenger::output()
{
    std::cout << name << " " << surname << " " << age << " " << nationality << " " << flight_number << " ";
    if (!luggage)
    {
        std::cout << "NO" << std::endl;
    }
    else if (luggage)
    {
        std::cout << "YES" << std::endl;
    }
}
bool Passenger::modify()
{
    std::string name, surname, age, nationality, luggage;
    std::cout << "Input new passenger data:" << std::endl;
    std::cout << "Name: ";
    std::cin >> name;
    std::cout << "Surname: ";
    std::cin >> surname;
    std::cout << "Age: ";
    std::cin >> age;
    std::cout << "Nationality: ";
    std::cin >> nationality;
    std::cout << "Luggage: ";
    std::cin >> luggage;
    try
    {
        if ((luggage == "true") || (luggage == "True") || (luggage == "TRUE"))
        {
            this->name = name;
            this->surname = surname;
            this->age = std::stoi(age);
            this->nationality = nationality;
            this->luggage = true;
        }
        else if ((luggage == "false") || (luggage == "False") || (luggage == "FALSE"))
        {
            this->name = name;
            this->surname = surname;
            this->age = std::stoi(age);
            this->nationality = nationality;
            this->luggage = false;
        }
        else
        {
            std::cout << "Data is incorrect" << std::endl;
            return 1;
        }
        std::cout << "Data changed" << std::endl;
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