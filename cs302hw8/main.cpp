/* Name: Kristy Nguyen, NSHE ID: 5006243601, Assignment 8
 * Description: Implement NASA SpaceX to control lander simulator using 
                predefined throttle data to be used on each lander
 * Input:
	- attributes for a single lander (lander file)
    - potential value for lander object's change_flow_rate(double) 
        function (lander simulation file)
 * Output: 
    - output highest priority lander object
    - landed / crashed
    - output landers still in simulation if eof reached before priorityQ is empty
 */
#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include "lander.h"
#include "priorityQ.h"
using namespace std;

int main ()
{
    string landerFile;
    string simulationFile;
    bool invalid = true;
    ifstream inFile;

    do
    {   // Loop to prompt for lander file
        cout << "Enter lander file: ";
        cin >> landerFile;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        inFile.open(landerFile.c_str());

        if (inFile.is_open())
            invalid = false;
        else
            invalid = true;
    } while (invalid);

    // Do stuff to lander file
    // INSERT CODE HERE
    double mass = 0.0;
    double max_thrust = 0.0;
    double max_fuel = 0.0;
    double alt = 0.0;
    double fuel = 0.0;
    int id = 0;

    priorityQ<lander> priorityObj;

    while (!inFile.eof()) {
        inFile >> mass >> max_thrust >> max_fuel >> alt >> fuel >> id;

        lander landerObj(mass, max_thrust, max_fuel, alt, fuel, id);

        // priorityObj.insert(landerObj);

        // cout << "Mass: " << landerObj.get_mass() << endl;
        // cout << "Altitude: " << landerObj.get_altitude() << endl;
        // cout << "Fuel amount: " << landerObj.get_fuel_amount() << endl;
        // cout << "Id: " << landerObj.get_id() << endl << endl;
    }
    inFile.close(); // Close lander file
    invalid = true; // Reset bool value to true

    do
    {   // Prompt for simulation file
        cout << "Enter simulation file: ";
        cin >> simulationFile;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        inFile.open(simulationFile.c_str());
        
        if (inFile.is_open())
            invalid = false;
        else
            invalid = true;
    } while (invalid);

    // Do stuff to simulation file
    // INSERT CODE HERE
    // lander temp = priorityObj.getHighestPriority();
    // priorityObj.deleteHighestPriority();

    // invalid = true;
    // double number;
    // while (invalid) 
    // {
    //     inFile >> number;
    //     if (number >= 0 && number <= 1)
    //         invalid = false;
    //     else
    //         invalid = true;
    // }

    // cout << "Rocket " << temp.get_id() << endl;
    // cout << "Fuel: " << temp.get_fuel_amount() << endl;
    // cout << "Altitude: " << temp.get_altitude() << endl;
    // cout << "Velocity: " << temp.get_velocity() << endl << endl;

    // temp.change_flow_rate(number);
    // temp.simulate();
    // if (temp.get_status() == 'c')
    // {
    //     cout << "Rocket ID: " << temp.get_id() << " has crashed";
    //     cout << " :( At least nobody was on board" << endl << endl;
    // }

    // if (temp.get_status() == 'l')
    // {
    //     cout << "Rocket ID: " << temp.get_id() << " has successfully landed";
    //     cout << " and all astronauts are accounted for :)" << endl << endl;
    // }

    // if (temp.get_status() == 'a')
    // {
    //     priorityObj.insert(temp);
    // }

    inFile.close(); // Close simulation file

    return 0;
}