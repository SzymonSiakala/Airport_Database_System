#pragma once
#include <iostream>
#include "Passenger.h"
#include "Plane.h"

class Flight
{
private:
    int flight_number;
    std::string from_where;
    std::string to_where;
    Plane plane;
    friend bool save_to_files();
    friend bool read_from_files();
    friend bool search_engine(std::string wanted);
    friend bool search_engine(int wanted);
    friend bool search_engine(bool wanted);
    friend bool modify_menu();
    friend int main();
public:
    Flight();     ///Default constructor
    Flight(int flight_number, std::string from_where, std::string to_where);     ///Custom constructor for creating Flight class object
    ~Flight();     ///Default destructor
    void output_plus();     ///Method will display the data from Flight class and will call output_plus() function from class Plane
    void output();     ///Method will display only the data from Flight class
    void add_plane(std::string brand, std::string model, int capacity_passenger, int capacity_crew, int flight_number);     ///Method for assigning Plane class object
    bool modify();     ///Method used to modify the object data
};

