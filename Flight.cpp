#include "Flight.h"

Flight::Flight()
{
    flight_number = 0;
    from_where = "unknown";
    to_where = "unknown";
}
Flight::Flight(int flight_number, std::string from_where, std::string to_where)
{
    this->flight_number = flight_number;
    this->from_where = from_where;
    this->to_where = to_where;
}
Flight::~Flight()
{
}
void Flight::output_plus()
{
    std::cout << flight_number << " " << from_where << " ---> " << to_where << std::endl;
    std::cout << "Plane assigned to that flight:" << std::endl;
    plane.output_plus();
    std::cout << std::endl;
}
void Flight::output()
{
    std::cout << flight_number << " " << from_where << " ---> " << to_where << std::endl;
}
void Flight::add_plane(std::string brand, std::string model, int capacity_passenger, int capacity_crew, int flight_number)
{
    Plane new_plane(brand, model, capacity_passenger, capacity_crew, flight_number);
    this->plane = new_plane;
}
bool Flight::modify()
{
    std::string from_where, to_where;
    std::cout << "Input new flight data:" << std::endl;
    std::cout << "Starting point: ";
    std::cin >> from_where;
    std::cout << "Destination: ";
    std::cin >> to_where;
    this->from_where = from_where;
    this->to_where = to_where;
    std::cout << "Data changed" << std::endl;
    return 0;
}