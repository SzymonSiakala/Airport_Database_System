#pragma once
#include <iostream>
#include <sstream>

class Passenger
{
protected:
    std::string name;
    std::string surname;
    int age;
    std::string nationality;
    int flight_number;
    bool luggage;
    friend bool save_to_files();
    friend bool search_engine(std::string wanted);
    friend bool search_engine(int wanted);
    friend bool search_engine(bool wanted);
    friend bool modify_menu();
    friend int main();
    friend class Plane;
public:
    Passenger();     ///Default constructor
    Passenger(std::string name, std::string surname, int age, std::string nationality, int flight_number, bool luggage);     ///Constructor used for creating Passenger class object
    Passenger(std::string name, std::string surname, int age, std::string nationality, int flight_number);     ///Constructor used for creating Crew class object
    ~Passenger();     ///Default destructor
    void output();     ///Method will display the data
    bool modify();     ///Method used to modify the object data
};

