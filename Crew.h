#pragma once
#include <iostream>
#include "Passenger.h"

class Crew : public Passenger
{
private:
	std::string role;
	friend bool save_to_files();
	friend bool search_engine(std::string wanted);
	friend bool search_engine(int wanted);
public:
	Crew();     ///Default constructor
	Crew(std::string name, std::string surname, int age, std::string nationality, int flight_number, std::string role);     ///Constructor used for creating Crew class object basing on Passenger class
	~Crew();     ///Default destructor
	void output();     ///Method will display only the data from Crew class
	bool modify();     ///Method used to modify the object data
};