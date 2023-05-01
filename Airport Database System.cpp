/*
*Project: Airport Database System
*Made by: Szymon Siąkała
*MK.2
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#if defined(WIN32) || defined(_WIN32)     ///Checking the system
#include <windows.h>
#include <stdlib.h>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#endif

#include "Flight.h"
#include "Plane.h"
#include "Passenger.h"

std::vector <Flight> all_flights;     ///All database is stored in this vector

void header()
{
    std::cout << "##########################################################" << std::endl;
    std::cout << "#          CHOPIN   AIRPORT   DATABASE   SYSTEM          #" << std::endl;
    std::cout << "##########################################################" << std::endl;
}

void clear()     ///For windows function will use system("cls") function and for other systems few std::endl
{
#if defined(WIN32) || defined(_WIN32)
    system("cls");
#else
    std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
#endif
}

bool read_from_files()     ///Function will read from files line by line and save data to all_flights vector, it is using overloaded std::getline to read strings untill sign #
{
    std::ifstream passengers_database("Passengers.txt");
    std::ifstream crew_database("Crew.txt");
    std::ifstream planes_database("Planes.txt");
    std::ifstream flights_database("Flights.txt");
    int i = 0;
    std::cout << "Loading data, please wait..." << std::endl;
    try
    {
        if (!flights_database.is_open())
        {
            throw 1;
        }
        std::string line;
        while (std::getline(flights_database, line))     ///Loop used to go through the whole file line by line
        {
            std::stringstream ss(line);
            std::string flight_number_string;
            std::string from_where;
            std::string to_where;
            std::getline(ss, flight_number_string, '#');     ///Function will get all characters from line untill the # sign
            int flight_number_int = std::stoi(flight_number_string);      ///Conversion from std::string to int
            std::getline(ss, from_where, '#');
            std::getline(ss, to_where, '#');
            all_flights.emplace_back(flight_number_int, from_where, to_where);     ///We add data to the vector, we will repeat the process for planes, passengers and crew members
            try
            {
                if (!planes_database.is_open())
                {
                    throw 1;
                }
                while (std::getline(planes_database, line))
                {
                    std::stringstream ss(line);
                    std::string brand;
                    std::string model;
                    std::string amount_passenger_string;
                    std::string capacity_passenger_string;
                    std::string amount_crew_string;
                    std::string capacity_crew_string;
                    std::getline(ss, brand, '#');
                    std::getline(ss, model, '#');
                    std::getline(ss, amount_passenger_string, '#');
                    int amount_passenger_int = std::stoi(amount_passenger_string);
                    std::getline(ss, capacity_passenger_string, '#');
                    int capacity_passenger_int = std::stoi(capacity_passenger_string);
                    std::getline(ss, amount_crew_string, '#');
                    int amount_crew_int = std::stoi(amount_crew_string);
                    std::getline(ss, capacity_crew_string, '#');
                    int capacity_crew_int = std::stoi(capacity_crew_string);
                    std::getline(ss, flight_number_string, '#');
                    flight_number_int = std::stoi(flight_number_string);
                    all_flights[i].add_plane(brand, model, capacity_passenger_int, capacity_crew_int, flight_number_int);
                    try
                    {
                        if (!passengers_database.is_open())
                        {
                            throw 1;
                        }
                        if (!crew_database.is_open())
                        {
                            throw 'a';
                        }
                        for (int j = 0; j < amount_passenger_int; j++)
                        {
                            while (std::getline(passengers_database, line))
                            {
                                std::stringstream ss(line);
                                std::string name;
                                std::string surname;
                                std::string age_string;
                                std::string nationality;
                                std::string luggage_string;
                                std::getline(ss, name, '#');
                                std::getline(ss, surname, '#');
                                std::getline(ss, age_string, '#');
                                int age_int = std::stoi(age_string);
                                std::getline(ss, nationality, '#');
                                std::getline(ss, flight_number_string, '#');
                                flight_number_int = std::stoi(flight_number_string);
                                std::getline(ss, luggage_string, '#');
                                int luggage_int = std::stoi(luggage_string);
                                all_flights[i].plane.add_passenger(name, surname, age_int, nationality, flight_number_int, luggage_int);
                                break;
                            }
                        }
                        for (int j = 0; j < amount_crew_int; j++)
                        {
                            while (std::getline(crew_database, line))
                            {
                                std::stringstream ss(line);
                                std::string role;
                                std::string name;
                                std::string surname;
                                std::string age_string;
                                std::string nationality;
                                std::getline(ss, role, '#');
                                std::getline(ss, name, '#');
                                std::getline(ss, surname, '#');
                                std::getline(ss, age_string, '#');
                                int age_int = std::stoi(age_string);
                                std::getline(ss, nationality, '#');
                                std::getline(ss, flight_number_string, '#');
                                flight_number_int = std::stoi(flight_number_string);
                                all_flights[i].plane.add_crew(name, surname, age_int, nationality, flight_number_int, role);
                                break;
                            }
                        }
                    }
                    catch(int)     ///Program will display errors if files don't exist
                    {
                        std::cout << std::endl << "Problem occurred while oppening the Passengers.txt file" << std::endl;
                        passengers_database.close();
                        crew_database.close();
                        planes_database.close();
                        flights_database.close();
                        return 1;
                    }
                    catch (char)
                    {
                        std::cout << std::endl << "Problem occurred while oppening the Crew.txt file" << std::endl;
                        passengers_database.close();
                        crew_database.close();
                        planes_database.close();
                        flights_database.close();
                        return 1;
                    }
                    break;     ///It is necessary to break the loop after each plane object loaded from database, because the data from flight would be overwritten
                }
            }
            catch(int)
            {
                std::cout << std::endl << "Problem occurred while oppening the Planes.txt file" << std::endl;
                passengers_database.close();
                crew_database.close();
                planes_database.close();
                flights_database.close();
                return 1;
            }
            i++;     ///Count the amount of elements in the all_flights vector
            Sleep(500);
            std::cout << "#";
        }
        std::cout << std::endl;
    }
    catch (int)
    {
        std::cout << "Problem occurred while oppening the Flights.txt file" << std::endl;
        passengers_database.close();
        crew_database.close();
        planes_database.close();
        flights_database.close();
        return 1;
    }
    passengers_database.close();
    crew_database.close();
    planes_database.close();
    flights_database.close();
    return 0;
}

bool save_to_files()     ///Function will save all data from the all_flights vector to files and separate each element of data by # sign
{
    std::cout << "Saving database, please wait..." << std::endl;
    try
    {
        if (all_flights.empty())     ///Function will check if the file exist
        {
            throw 1;
        }
        std::ofstream passengers_database("Passengers.txt");
        std::ofstream planes_database("Planes.txt");
        std::ofstream flights_database("Flights.txt");
        std::ofstream crew_database("Crew.txt");
        for (auto it : all_flights)
        {
            flights_database << it.flight_number << "#" << it.from_where << "#" << it.to_where << std::endl;
            planes_database << it.plane.brand << "#" << it.plane.model << "#" << it.plane.amount_passenger << "#" << it.plane.capacity_passenger << "#" << it.plane.amount_crew << "#" << it.plane.capacity_crew << "#" << it.plane.flight_number << std::endl;     //Let's save our planes in the file
            if (!it.plane.passenger_list.empty())
            {
                for (auto jt : it.plane.passenger_list)
                {
                    passengers_database << jt.name << "#" << jt.surname << "#" << jt.age << "#" << jt.nationality << "#" << jt.flight_number << "#" << jt.luggage << std::endl;
                }
            }
            if (!it.plane.crew_list.empty())
            {
                for (auto jt : it.plane.crew_list)
                {
                    crew_database << jt.role << "#" << jt.name << "#" << jt.surname << "#" << jt.age << "#" << jt.nationality << "#" << jt.flight_number << std::endl;
                }
            }
            Sleep(500);
            std::cout << "#";
        }
        passengers_database.close();
        planes_database.close();
        flights_database.close();
        crew_database.close();
        std::cout << std::endl;
    }
    catch (int)
    {
        std::cout << "Database is empty" << std::endl;
        return 1;
    }
    return 0;
}

bool search_engine(std::string wanted)     ///Function to search through the database for strings, it will compare all std::string variables from database to the string user want to find
{
    try
    {
        if (all_flights.empty())
        {
            throw 1;
        }
        std::cout << "Searching for word: " << wanted << " in database" << std::endl << std::endl;
        for (auto it : all_flights)
        {
            if ((it.to_where == wanted) || (it.from_where == wanted))
            {
                it.output_plus();
                continue;
            }
            else if ((it.plane.brand == wanted) || (it.plane.model == wanted))
            {
                it.output_plus();
                continue;
            }
            bool found = false;
            for (auto jt : it.plane.passenger_list)
            {
                if (!found)
                {
                    if ((jt.name == wanted) || (jt.surname == wanted) || (jt.nationality == wanted))
                    {
                        it.output();     ///Function uses 2 types of display methods
                        it.plane.output();
                        std::cout << "Passengers assigned to this plane:" << std::endl;
                        std::cout << "\t";
                        jt.output();
                        found = true;
                        continue;
                    }
                }
                else if (found)
                {
                    if ((jt.name == wanted) || (jt.surname == wanted) || (jt.nationality == wanted))
                    {
                        std::cout << "\t";
                        jt.output();
                        continue;
                    }
                }
            }
            for (auto jt : it.plane.crew_list)
            {
                if (!found)
                {
                    if ((jt.name == wanted) || (jt.surname == wanted) || (jt.nationality == wanted) || (jt.role == wanted))
                    {
                        it.output();
                        std::cout << "Plane assigned to that flight:" << std::endl;
                        it.plane.output();
                        std::cout << "Crew assigned to this plane:" << std::endl;
                        std::cout << "\t";
                        jt.output();
                        found = true;
                        continue;
                    }
                }
                else if (found)
                {
                    if ((jt.name == wanted) || (jt.surname == wanted) || (jt.nationality == wanted) || (jt.role == wanted))
                    {
                        std::cout << "\t";
                        jt.output();
                        continue;
                    }
                }
            }
            if (!found)
            {
                std::cout << "Data not found in flight number: " << it.flight_number << std::endl << std::endl;
            }
            else if (found)
            {
                std::cout << std::endl;
            }
        }
    }
    catch (int)
    {
        std::cout << "Database is empty" << std::endl;
        return 1;
    }
    return 0;
}

bool search_engine(int wanted)     ///Function to search through the database for integers, it will compare all integers variables from database to the integer user want to find, function based on search_engine(std::string)
{
    try
    {
        if (all_flights.empty())
        {
            throw 1;
        }
        std::cout << "Searching for number: " << wanted << " in database" << std::endl << std::endl;
        for (auto it : all_flights)
        {
            if (it.flight_number == wanted)
            {
                it.output_plus();
                continue;
            }
            else if ((it.plane.amount_passenger == wanted) || (it.plane.capacity_passenger == wanted) || (it.plane.amount_crew == wanted) || (it.plane.capacity_crew == wanted))
            {
                it.output_plus();
                continue;
            }
            bool found = false;
            for (auto jt : it.plane.passenger_list)
            {
                if (!found)
                {
                    if (jt.age == wanted)
                    {
                        it.output();
                        std::cout << "Plane assigned to that flight:" << std::endl;
                        it.plane.output();
                        std::cout << "Passengers assigned to this plane:" << std::endl;
                        std::cout << "\t";
                        jt.output();
                        found = true;
                        continue;
                    }
                }
                else if (found)
                {
                    if (jt.age == wanted)
                    {
                        std::cout << "\t";
                        jt.output();
                        continue;
                    }
                }
            }
            for (auto jt : it.plane.crew_list)
            {
                if (!found)
                {
                    if (jt.age == wanted)
                    {
                        it.output();
                        std::cout << "Plane assigned to that flight:" << std::endl;
                        it.plane.output();
                        std::cout << "Crew assigned to this plane:" << std::endl;
                        std::cout << "\t";
                        jt.output();
                        found = true;
                        continue;
                    }
                }
                else if (found)
                {
                    if (jt.age == wanted)
                    {
                        std::cout << "\t";
                        jt.output();
                        continue;
                    }
                }
            }
            if (!found)
            {
                std::cout << "Data not found in flight number:  " << it.flight_number << std::endl << std::endl;
            }
            else if (found)
            {
                std::cout << std::endl;
            }
        }
    }
    catch (int)
    {
        std::cout << "Database is empty" << std::endl;
        return 1;
    }
    return 0;
}

bool search_engine(bool wanted)     ///Function to search through the database for bools, it will compare all bool variables from database to the bool user want to find, function based on search_engine(std::string)
{
    try
    {
        if (all_flights.empty())
        {
            throw 1;
        }
        if (!wanted)
        {
            std::cout << "Searching for all passengers without luggage" << std::endl << std::endl;
        }
        else if (wanted)
        {
            std::cout << "Searching for all passengers with luggage" << std::endl << std::endl;
        }
        for (auto it : all_flights)
        {
            bool found = false;
            for (auto jt : it.plane.passenger_list)
            {
                if (!found)
                {
                    if (jt.luggage == wanted)
                    {
                        it.output();
                        std::cout << "Plane assigned to that flight:" << std::endl;
                        it.plane.output();
                        std::cout << "Passengers assigned to this plane:" << std::endl;
                        std::cout << "\t";
                        jt.output();
                        found = true;
                        continue;
                    }
                }
                else if (found)
                {
                    if (jt.luggage == wanted)
                    {
                        std::cout << "\t";
                        jt.output();
                        continue;
                    }
                }
            }
            if (!found)
            {
                std::cout << "Data not found in flight number: " << it.flight_number << std::endl << std::endl;
            }
            else if (found)
            {
                std::cout << std::endl;
            }
        }
    }
    catch (int)
    {
        std::cout << "Database is empty" << std::endl;
        return 1;
    }
    return 0;
}

bool try_again(bool statement)     ///User will get here if something will go wrong, function will ask the user if he would like to go to the main menu or exit the program
{
    if (statement == false)
    {
        system("pause");
        return true;
    }
    std::string choice;
    std::cout << "Would you like to go back to main menu?" << std::endl;
    std::cin >> choice;
    if ((choice[0] == 'y') || (choice[0] == 'Y'))
    {
        statement = true;
        clear();
        return true;
    }
    else
    {
        clear();
        return false;
    }
}

bool modify_menu()     ///Second menu for adding, modifying and deleting the data
{
    std::string choice, data1, data2, data3, data4, data5, data6;
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "1.Add new passegner" << std::endl;
    std::cout << "2.Add new plane" << std::endl;
    std::cout << "3.Add new flight" << std::endl;
    std::cout << "4.Add new crew member" << std::endl;
    std::cout << "5.Modify passenger" << std::endl;
    std::cout << "6.Modify plane" << std::endl;
    std::cout << "7.Modify flight" << std::endl;
    std::cout << "8.Modify crew member" << std::endl;
    std::cout << "9.Delete passenger" << std::endl;
    std::cout << "10.Delete plane" << std::endl;
    std::cout << "11.Delete flight" << std::endl;
    std::cout << "12.Delete crew member" << std::endl;
    std::cout << "0.Go back to main menu" << std::endl;
    std::cin >> choice;
    try
    {
        switch (std::stoi(choice))     //
        {
        case 1:
            clear();
            header();
            std::cout << "Input new passenger data:" << std::endl;
            std::cout << "Name: ";
            std::cin >> data1;
            std::cout << "Surname: ";
            std::cin >> data2;
            std::cout << "Age: ";
            std::cin >> data3;
            std::cout << "Nationality: ";
            std::cin >> data4;
            std::cout << "Flight number: ";
            std::cin >> data5;
            std::cout << "Luggage: ";
            std::cin >> data6;
            try
            {
                for (int i = 0; i < all_flights.size(); i++)
                {
                    if (all_flights[i].flight_number == std::stoi(data5))
                    {
                        if ((data6 == "true") || (data6 == "True") || (data6 == "TRUE"))
                        {
                            if(!all_flights[i].plane.add_passenger(data1, data2, std::stoi(data3), data4, std::stoi(data5), true))
                            {
                                std::cout << "Passenger added to flight number: " << std::stoi(data5) << std::endl;
                            }
                            else
                            {
                                return 1;     ///Every function will return 1 if it will encounter an error
                            }
                        }
                        else if ((data6 == "false") || (data6 == "False") || (data6 == "FALSE"))
                        {
                            if (!all_flights[i].plane.add_passenger(data1, data2, std::stoi(data3), data4, std::stoi(data5), false))
                            {
                                std::cout << "Passenger added to flight number: " << std::stoi(data5) << std::endl;
                            }
                            else
                            {
                                return 1;
                            }
                        }
                        else
                        {
                            std::cout << "Data is incorrect" << std::endl;
                            return 1;
                        }
                        return 0;
                    }
                }
                std::cout << "Flight number not found" << std::endl;
                return 1;
            }
            catch (const std::invalid_argument & ia)     ///Exceptions to catch errors from std::stoi()
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
        break;
        case 2:
            clear();
            header();
            std::cout << "Input new plane data:" << std::endl;
            std::cout << "Brand: ";
            std::cin >> data1;
            std::cout << "Model: ";
            std::cin >> data2;
            std::cout << "Capacity of passengers: ";
            std::cin >> data3;
            std::cout << "Capacity of crew: ";
            std::cin >> data4;
            std::cout << "Flight number: ";
            std::cin >> data5;
            try
            {
                for (int i = 0; i < all_flights.size(); i++)
                {
                    if (all_flights[i].plane.flight_number != std::stoi(data5))
                    {
                        if (all_flights[i].flight_number == std::stoi(data5))
                        {
                            all_flights[i].add_plane(data1, data2, std::stoi(data3), std::stoi(data4), std::stoi(data5));
                            std::cout << "Plane added to flight number: " << std::stoi(data5) << std::endl;
                            return 0;
                        }
                    }
                    else
                    {
                        std::cout << "You cant override planes" << std::endl;
                        return 1;
                    }
                }
                std::cout << "Flight number not found" << std::endl;
                return 1;
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
        break;
        case 3:
            clear();
            header();
            std::cout << "Input new flight data:" << std::endl;
            std::cout << "Flight number: ";
            std::cin >> data1;
            std::cout << "Starting point: ";
            std::cin >> data2;
            std::cout << "Destination: ";
            std::cin >> data3;
            try
            {
                for (int i = 0; i < all_flights.size(); i++)
                {
                    if (all_flights[i].flight_number == std::stoi(data1))
                    {
                        std::cout << "Flight number already existing in database" << std::endl;
                        return 1;
                    }
                }
                all_flights.emplace_back(std::stoi(data1), data2, data3);
                std::cout << "Flight number: " << std::stoi(data1) << " added to database" << std::endl;
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
        break;
        case 4:
            clear();
            header();
            std::cout << "Input new crew member data:" << std::endl;
            std::cout << "Name: ";
            std::cin >> data1;
            std::cout << "Surname: ";
            std::cin >> data2;
            std::cout << "Age: ";
            std::cin >> data3;
            std::cout << "Nationality: ";
            std::cin >> data4;
            std::cout << "Flight number: ";
            std::cin >> data5;
            std::cout << "Role: ";
            std::cin >> data6;
            try
            {
                for (int i = 0; i < all_flights.size(); i++)
                {
                    if (all_flights[i].flight_number == std::stoi(data5))
                    {
                        if (!all_flights[i].plane.add_crew(data1, data2, std::stoi(data3), data4, std::stoi(data5), data6))
                        {
                            std::cout << "Crew member added to flight number: " << std::stoi(data5) << std::endl;
                        }
                        else
                        {
                            return 1;
                        }
                        return 0;
                    }
                }
                std::cout << "Flight number not found" << std::endl;
                return 1;
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
            break;
        case 5:
            clear();
            header();
            std::cout << "Input passenger data you would like to change:" << std::endl;
            std::cout << "Name: ";
            std::cin >> data1;
            std::cout << "Surname: ";
            std::cin >> data2;
            std::cout << "Flight number: ";
            std::cin >> data3;
            try
            {
                if (all_flights.empty())
                {
                    throw 1;
                }
                std::cout << "Searching for this passenger in database" << std::endl;
                for (int i = 0; i < all_flights.size(); i++)
                {
                    for (int j = 0; j < all_flights[i].plane.passenger_list.size(); j++)
                    {
                        if ((all_flights[i].plane.passenger_list[j].name == data1) && (all_flights[i].plane.passenger_list[j].surname == data2) && (all_flights[i].flight_number == std::stoi(data3)))
                        {
                            clear();
                            header();
                            return all_flights[i].plane.passenger_list[j].modify();
                        }
                    }
                }
                std::cout << "Passenger not found" << std::endl;
                return 0;
            }
            catch (int)
            {
                std::cout << "Database is empty" << std::endl;
                return 1;
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
        break;
        case 6:
            clear();
            header();
            std::cout << "Input plane data you would like to change: " << std::endl;
            std::cout << "Flight number: ";
            std::cin >> data1;
            try
            {
                if (all_flights.empty())
                {
                    throw 1;
                }
                std::cout << "Searching for this plane in database" << std::endl;
                for (int i = 0; i < all_flights.size(); i++)
                {
                    if (all_flights[i].plane.flight_number == std::stoi(data1))
                    {
                        clear();
                        header();
                        return all_flights[i].plane.modify();
                    }
                }
                std::cout << "Plane not found" << std::endl;
            }
            catch (int)
            {
                std::cout << "Database is empty" << std::endl;
                return 1;
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
            return 0;
        break;
        case 7:
            clear();
            header();
            std::cout << "Input flight data you would like to change: " << std::endl;
            std::cout << "Flight number: ";
            std::cin >> data1;
            try
            {
                if (all_flights.empty())
                {
                    throw 1;
                }
                std::cout << "Searching for flight with number: " << std::stoi(data1) << " in database" << std::endl;
                for (int i = 0; i < all_flights.size(); i++)
                {
                    if (all_flights[i].flight_number == std::stoi(data1))
                    {
                        clear();
                        header();
                        return all_flights[i].modify();
                    }
                }
                std::cout << "Flight not found" << std::endl;
            }
            catch (int)
            {
                std::cout << "Database is empty" << std::endl;
                return 1;
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
        break;
        case 8:
            clear();
            header();
            std::cout << "Input crew member data you would like to change:" << std::endl;
            std::cout << "Name: ";
            std::cin >> data1;
            std::cout << "Surname: ";
            std::cin >> data2;
            std::cout << "Flight number: ";
            std::cin >> data3;
            try
            {
                if (all_flights.empty())
                {
                    throw 1;
                }
                std::cout << "Searching for this crew member in database" << std::endl;
                for (int i = 0; i < all_flights.size(); i++)
                {
                    for (int j = 0; j < all_flights[i].plane.crew_list.size(); j++)
                    {
                        if ((all_flights[i].plane.crew_list[j].name == data1) && (all_flights[i].plane.crew_list[j].surname == data2) && (all_flights[i].plane.crew_list[j].flight_number == std::stoi(data3)))
                        {
                            clear();
                            header();
                            return all_flights[i].plane.crew_list[j].modify();
                        }
                    }
                }
                std::cout << "Passenger not found" << std::endl;
                return 0;
            }
            catch (int)
            {
                std::cout << "Database is empty" << std::endl;
                return 1;
            }
        break;
        case 9:
            clear();
            header();
            std::cout << "Input passenger data you would like to delete:" << std::endl;
            std::cout << "Name: ";
            std::cin >> data1;
            std::cout << "Surname: ";
            std::cin >> data2;
            std::cout << "Flight number: ";
            std::cin >> data3;
            try
            {
                if (all_flights.empty())
                {
                    throw 1;
                }
                std::cout << "Searching for this passenger in database" << std::endl;
                for (int i = 0; i < all_flights.size(); i++)
                {
                    if (all_flights[i].flight_number == std::stoi(data3))
                    {
                        return all_flights[i].plane.delete_passenger(data1, data2);
                    }
                }
                std::cout << "Passenger not found" << std::endl;
                return 1;
            }
            catch (int)
            {
                std::cout << "Database is empty" << std::endl;
                return 1;
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
            return 0;      
        break;
        case 10:
            clear();
            header();
            std::cout << "Input plane data you would like to delete: " << std::endl;
            std::cout << "Flight number: ";
            std::cin >> data1;
            try
            {
                if (all_flights.empty())
                {
                    throw 1;
                }
                std::cout << "Searching for this plane in database" << std::endl;
                for (int i = 0; i < all_flights.size(); i++)
                {
                    if (all_flights[i].flight_number == std::stoi(data1))
                    {
                        std::cout << "Deleting choosen plane data" << std::endl;
                        all_flights[i].plane.brand = "unknown";
                        all_flights[i].plane.model = "unknown";
                        all_flights[i].plane.amount_passenger = 0;
                        all_flights[i].plane.capacity_passenger = 0;
                        all_flights[i].plane.amount_crew = 0;
                        all_flights[i].plane.capacity_crew = 0;
                        all_flights[i].plane.passenger_list.clear();
                        all_flights[i].plane.crew_list.clear();
                        return 0;
                    }
                }
                std::cout << "Plane not found" << std::endl;
                return 1;
            }
            catch (int)
            {
                std::cout << "Database is empty" << std::endl;
                return 1;
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
            return 0;
        break;
        case 11:
            clear();
            header();
            std::cout << "Input flight data you would like to delete: " << std::endl;
            std::cout << "Flight number: ";
            std::cin >> data1;
            try
            {
                clear();
                header();
                try
                {
                    if (all_flights.empty())
                    {
                        throw 1;
                    }
                    std::cout << "Searching for flight with number: " << std::stoi(data1) << " in database" << std::endl;
                    for (int i = 0; i < all_flights.size(); i++)
                    {
                        if (all_flights[i].flight_number == std::stoi(data1))
                        {
                            std::cout << "Deleting choosen flight data" << std::endl;
                            all_flights.erase(all_flights.begin() + i);
                            return 0;
                        }
                    }
                    std::cout << "Flight not found" << std::endl;
                    return 1;
                }
                catch (int)
                {
                    std::cout << "Database is empty" << std::endl;
                    return 1;
                }
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
        break;
        case 12:
            clear();
            header();
            std::cout << "Input crew member data you would like to delete:" << std::endl;
            std::cout << "Name: ";
            std::cin >> data1;
            std::cout << "Surname: ";
            std::cin >> data2;
            std::cout << "Flight number: ";
            std::cin >> data3;
            try
            {
                if (all_flights.empty())
                {
                    throw 1;
                }
                std::cout << "Searching for this crew member in database" << std::endl;
                for (int i = 0; i < all_flights.size(); i++)
                {
                    if (all_flights[i].flight_number == std::stoi(data3))
                    {
                        return all_flights[i].plane.delete_crew(data1, data2);
                    }
                }
                std::cout << "Passenger not found" << std::endl;
                return 1;
            }
            catch (int)
            {
                std::cout << "Database is empty" << std::endl;
                return 1;
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
            return 0;
            break;
        case 0:
            return 0;
        break;
        default:
            return 1;
        break;
        }
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

int main()     ///Main menu where all the most important processes will take place
{
    bool statement;
    do
    {
        std::string choice;
        statement = false;
        header();
        if (read_from_files())     ///First it will try to read data from files
        {
            statement = try_again(statement);
        }
        else
        {
            do
            {
                statement = false;
                clear();
                header();
                std::cout << "What would you like to do?" << std::endl;
                std::cout << "1.Inspect database" << std::endl;
                std::cout << "2.Search in database" << std::endl;
                std::cout << "3.Modify database" << std::endl;
                std::cout << "4.Save database" << std::endl;
                std::cout << "0.Exit" << std::endl;
                std::cin >> choice;
                try
                {
                    switch (std::stoi(choice))
                    {
                    case 1:
                        clear();
                        header();
                        for (auto it : all_flights)
                        {
                            it.output_plus();
                        }
                        statement = try_again(false);
                        break;
                    case 2:
                        clear();
                        header();
                        std::cout << "Input information you would like to find:" << std::endl;
                        std::cin >> choice;
                        if ((choice == "true") || (choice == "True") || (choice == "TRUE"))
                        {
                            statement = try_again(search_engine(true));
                        }
                        else if ((choice == "false") || (choice == "False") || (choice == "FALSE"))
                        {
                            statement = try_again(search_engine(false));
                        }
                        else
                        {
                            try
                            {
                                statement = try_again(search_engine(std::stoi(choice)));
                            }
                            catch (const std::invalid_argument & ia)
                            {
                                statement = try_again(search_engine(choice));
                            }
                            catch (const std::out_of_range & oor)
                            {
                                statement = try_again(search_engine(choice));
                            }
                            catch (const std::exception & e)
                            {
                                std::cout << "Something went wrong" << std::endl;
                                statement = try_again(true);
                            }
                        }
                        break;
                    case 3:
                        clear();
                        header();
                        statement = try_again(modify_menu());
                        break;
                    case 4:
                        clear();
                        header();
                        statement = try_again(save_to_files());
                        break;
                    case 0:
                        break;
                    default:
                        statement = try_again(true);
                        break;
                    }
                }
                catch (const std::invalid_argument & ia)     ///Exceptions to catch errors from std::stoi() functions
                {
                    std::cout << ia.what() << std::endl;
                    statement = try_again(true);
                }
                catch (const std::out_of_range & oor)
                {
                    std::cout << oor.what() << std::endl;
                    statement = try_again(true);
                }
                catch (const std::exception & e)
                {
                    std::cout << e.what() << std::endl;
                    statement = try_again(true);
                }
            } while (statement);
            statement = false;
        }
    } while (statement);
    clear();
    header();
    std::cout << "Exiting the database system" << std::endl;
    std::vector<Flight>().swap(all_flights);     ///At the end of the program it will create and empty vector and swap the existing one with it
    #if defined(WIN32) || defined(_WIN32)
        _CrtDumpMemoryLeaks();     ///Program will check for data leaks
    #endif
    return 0;
}