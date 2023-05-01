#include "Plane.h"

Plane::Plane()
{
    brand = "unknown";
    model = "unknown";
    amount_passenger = 0;
    capacity_passenger = 0;
    amount_crew = 0;
    capacity_crew = 0;
    flight_number = 0;
}
Plane::Plane(std::string brand, std::string model, int capacity_passenger, int capacity_crew, int flight_number)
{
    this->brand = brand;
    this->model = model;
    amount_passenger = 0;
    this->capacity_passenger = capacity_passenger;
    amount_crew = 0;
    this->capacity_crew = capacity_crew;
    this->flight_number = flight_number;
}
Plane::~Plane()
{
    std::vector<Passenger>().swap(passenger_list);
    std::vector<Crew>().swap(crew_list);
}
void Plane::output_plus()
{
    std::cout << brand << " " << model << " " << amount_passenger << "/" << capacity_passenger << " + " << amount_crew << "/" << capacity_crew << " " << flight_number << std::endl;
    std::cout << "Crew assigned to this plane:" << std::endl;
    if (!crew_list.empty())
    {
        for (auto it : crew_list)
        {
            std::cout << "\t";
            it.output();
        }
    }
    else
    {
        std::cout << "None" << std::endl;
    }
    std::cout << "Passengers assigned to this plane:" << std::endl;
    if (!passenger_list.empty())
    {
        for (auto it : passenger_list)
        {
            std::cout << "\t";
            it.output();
        }
    }
    else
    {
        std::cout << "None" << std::endl;
    }
}
void Plane::output()
{
    std::cout << brand << " " << model << " " << amount_passenger << "/" << capacity_passenger << " + " << amount_crew << "/" << capacity_crew << " " << flight_number << std::endl;
}
bool Plane::add_passenger(std::string name, std::string surname, int age, std::string nationality, int flight_number, bool luggage)
{
    if (amount_passenger < capacity_passenger)
    {
        Passenger new_passenger(name, surname, age, nationality, flight_number, luggage);
        passenger_list.push_back(new_passenger);
        amount_passenger++;
        return 0;
    }
    else
    {
        std::cout << "Plane is already full" << std::endl;
        return 1;
    }
    return 0;
}
bool Plane::add_crew(std::string name, std::string surname, int age, std::string nationality, int flight_number, std::string role)
{
    if (amount_crew < capacity_crew)
    {
        Crew new_crew(name, surname, age, nationality, flight_number, role);
        crew_list.push_back(new_crew);
        amount_crew++;
        return 0;
    }
    else
    {
        std::cout << "Plane has all crew members" << std::endl;
        return 1;
    }
    return 0;
}
bool Plane::modify()
{
    std::string brand, model;
    std::cout << "Input new plane data:" << std::endl;
    std::cout << "Brand: ";
    std::cin >> brand;
    std::cout << "Model: ";
    std::cin >> model;
    this->brand = brand;
    this->model = model;
    std::cout << "Data changed" << std::endl;
    return 0;
}
bool Plane::delete_passenger(std::string name, std::string surname)
{
    for (int i = 0; i < passenger_list.size(); i++)
    {
        if ((passenger_list[i].name == name) || (passenger_list[i].surname == surname))
        {
            std::cout << "Deleting choosen passenger data" << std::endl;
            passenger_list.erase(passenger_list.begin() + i);
            amount_passenger--;
            return 0;
        }
    }
    std::cout << "Passenger not found" << std::endl;
    return 1;
}
bool Plane::delete_crew(std::string name, std::string surname)
{
    for (int i = 0; i < crew_list.size(); i++)
    {
        if ((crew_list[i].name == name) || (crew_list[i].surname == surname))
        {
            std::cout << "Deleting choosen crew member data" << std::endl;
            crew_list.erase(crew_list.begin() + i);
            amount_crew--;
            return 0;
        }
    }
    std::cout << "Crew member not found" << std::endl;
    return 1;
}