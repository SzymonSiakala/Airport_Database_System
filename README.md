# Airport Database System
### Author: Szymon Siąkała

#### Task:
Program will be an operational database for some airports. It will contain all information about passengers, flights and planes. Users will be able to add/delete/modify information stored in the database (txt files). Program will contain a search engine to help the user find the requested information like certain passengers, all flights to NY, all the people with luggage etc. Implement passenger, flight and plane as classes and use operators like for example assign and stream operators. Program will correctly manage the memory and use object-oriented programming techniques like streams and exceptions.

#### Problem analysis:
To solve this task we will use classes to store information about passengers, planes, flights and crew members. Search engine will be prepared as a separate function. We will implement modifying and deleting data as methods in classes. We will implement a user interface and use exceptions to detect errors.

#### External specification:
After turning on the program, users have to wait until data is loaded from files. Each **#** sign represents one flight loaded. If  no problems are detected in the process, the main menu should appear. To choose the proper option, users have to input numbers next to it. Every time something goes wrong, the program will ask the user if he wants to try again. To do that user has to input y or the program will shut down itself. User has few options to choose from:
##### **Inspect database**
All database will display to user.
##### **Search in database**
After inputing number or word program will search for it in database (for searching passengers with luggage input **true**, for passengers without luggage **false**).
##### **Modify database**
Bigger menu will appear, where user can choose exactly what he would like to do. User can add new elements to the database or modify and delete them. Program will demand appropriate data inputed.
##### **Save database**
Program will save our current database to text files. Each **#** sign represents one flight saved.
##### **Exit**
Program will shut down itself.

#### Internal specification:
Program is using 4 classes and few functions. Classes:
##### **Passenger**
Stores informations like: name, surname, age, nationality, flight number as strings or integers and information about luggage as bool. Class has 2 constructors, destructor, display method and method that will modify the data.
##### **Crew**
Stores informations like: name, surname, age, nationality, flight number and role as strings or integers. Class has a constructor, destructor, display method and method that will modify the data.
##### **Plane**
Stores informations like: brand, model, amount of passengers/crew members, capacity of the plane and flight number as strings or integers. Class has vectors with objects of **Passenger** and **Crew** classes, 2 constructors, destructor, 2 display methods, a function for assigning passengers and crew members to the plane, a function to delete passenger or crew member from vectors and a function to modify the data.
##### **Flight**
Stores informations like: place of departure, place of arrival and flight number as strings or integers. Class has object of **Plane** class, 2 constructors, destructor, 2 display methods, a function for assigning planes to the flight and a function to modify the data.

Our database is stored in a global vector called **all_flights** made out of **Flight** class objects. Each major part of the program is divided into separate functions such as:

##### **void header()**
Display header in our program, it has only cosmetic significance.
##### **bool read_from_files()**
Function is used to read data from files and store it to the **all_flights** vector. It uses the **std::stringstream** objects and **std::getline()** functions to read the data separated by **#** signs and save it to the strings. Intiger values will get converted by **std::stoi()** and passed to the classes constructors to create appropriate objects. File opening and data conversion are protected by exceptions.
##### **bool save_to_files()**
Function is used to save data to 3 files and separate it with **#** sign. It uses range-based for loops to go through the whole **all_flights** vector.
##### **bool search_engine()**
In fact, there are 3 overloaded functions with that name, but they all work on the same principle. We pass on the integer, string or bool variable and the function will go through database and compare our variable to all stored variables of the same type in the objects in the database. If we do not find information in a specific flight number, the program will display an appropriate message and start shuffling in the next one.
##### **bool try_again()**
Function is used to ask user if he wants to go to the main menu or quit the program.
##### **bool modify_menu()**
Menu used to modify the data in database. It is based on **switch()** function and will call proper option after inputing right number. To use most of the options user will need to input requested informations, the program will convert them and create new objects if needed. There are exceptions while we need to use **std::stoi()** function. Program will collect the bool values returned by called functions and pass them forward to the **main()** function.
##### **int main()**
Here is the **main menu** where the user will be redirected after starting the program. It is based on the **switch()** function like the **modify_menu()** and will direct user to the right funciton after choosing desired option. Function will collect bool values from called functions and pass them to the **try_again()** function to check if the user would like to continue using the program. The returned value is saved to the bool variable **statement** and is used to check whether the user wants to continue or not. If the **statement** is true we will go back to the beginning of the **main()** function, if not program will clear our database, check for the memory leaks and shut down itself.

#### Conclusions:
When asked if he wants to continue or quit the program, the user has to enter anything with the first character “ y ” ot “ Y ” to continue. Inputting data correctly is crucial for the program to work, if the user will make a mistake the program will not correct it or show where the user made an error, unless the error occurred while converting data from string to integer. It is not recommended to delete database files. Program will handle it but won't
recreate them or start properly. The user interface is simple and clear, user just need to follow the instructions displayed by the program. Function **_CrtDumpMemoryLeaks()** will detect a data leak, but I discovered that it is caused by the global vector **all_flights** being deallocated after the **_CrtDumpMemoryLeaks()** is executed.
