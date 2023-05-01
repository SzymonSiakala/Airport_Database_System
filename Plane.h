#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "Passenger.h"
#include "Crew.h"

class Plane
{
private:
    std::string brand;
    std::string model;
    int amount_passenger;
    int capacity_passenger;
    int amount_crew;
    int capacity_crew;
    int flight_number;
    std::vector <Passenger> passenger_list;
    std::vector <Crew> crew_list;
    friend bool save_to_files();
    friend bool search_engine(std::string wanted);
    friend bool search_engine(int wanted);
    friend bool search_engine(bool wanted);
    friend bool modify_menu();
    friend int main();
public:
    Plane();     ///Default constructor
    Plane(std::string brand, std::string model, int capacity_passenger, int capacity_crew, int flight_number);     ///Custom constructor for creating Plane class object
    ~Plane();     ///Custom destructor that will clear the data stored in vectors
    void output_plus();     ///Method will display the data from Plane class and will call output() function from class Passenger and Crew
    void output();     ///Method will display only the data from Plane class
    bool add_passenger(std::string name, std::string surname, int age, std::string nationality, int flight_number, bool luggage);     ///Method for assigning Passenger class objects to vector passenger_list
    bool add_crew(std::string name, std::string surname, int age, std::string nationality, int flight_number, std::string role);     ///Method for assigning Crew class objects to vector crew_list
    bool modify();     ///Method used to modify the object data
    bool delete_passenger(std::string name, std::string surname);     ///Method for deleting Passenger class objects from vector passenger_list
    bool delete_crew(std::string name, std::string surname);     ///Method for deleting Crew class objects from vector crew_list
};

