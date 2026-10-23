#include <iostream>
#include <vector>

// created the employee class
class Employee {
    protected:
    std::string name;
    float salary = 0.0f; // used 0.0f so the program knows how the datatype should look like
    int staffID;
    static int IDCounter; // static means there is one shared ID counter for all employee objects

    public:
    Employee(const std::string& newName, float newSalary) : name(newName), salary(newSalary) { // my employee class constructor that takes in a name and a salary
        staffID = IDCounter; // Sets the ID for each user to the current IDCounter
        IDCounter++; // increments the static IDCounter variable each time a instance of the employee class is created
    }

    // using the virtual keyword, i can override this method in any of my other child classes to have a different logic without creating an entierly new method
    virtual float CalculatePay () {
        float calculatedPay = 0.0f;
        calculatedPay = salary / 12;
        return calculatedPay;
    } 


    std::string getName () { return name; } // Getter for name
    void setName (std::string newName) {name = newName;} // Setter for name

    float getSalary () { return salary; } // Getter for salary

    void setSalary (float newSalary) { // Setter for salary
        if (newSalary >= 0) { // Checks that the new salary is not negative before updating it
            salary = newSalary;
        } else { std::cout << std::endl << "ERROR: Please enter a value!" << std::endl << "Current salary is: " << getSalary() << std::endl; }
    }

    int getStaffID () { return staffID; } // Getter for the staff ID

    // Virtual destructor prevents undefined behaviour when deleting derived objects via base pointers
    virtual ~Employee() = default; 
};

// This stores the static IDCounter variable outside the class so that the value is not rewritten everytime a new instance of the class is created
int Employee::IDCounter = 0; 


// manager class inherited from the employee class
class Manager: public Employee {
    private:
    // vector that will store pointers to all employees objects created
    std::vector<Employee*> managedEmployees = {}; 

    public: 
    Manager(std::string name, float salary) : Employee(name, salary) {} // manager class constructor

    // override makes it that the method must match the virtual method in my parent class perfelcty, this will flag bugs if the methods don't match
    virtual float CalculatePay () override { 
        float calculatedPay = 0.0f;
        float multiplier = 1.0f;
    
        calculatedPay = salary / 12;
        
        // This loops through the vetor that stores all the employee instances and counts how many employees there are
        for (size_t i = 0; i < managedEmployees.size(); i++) {
            // Based on how many employees there are, it adds 0.1 to the multiplier variable for each employee instance
            if (managedEmployees[i]) {
                multiplier = multiplier + 0.1;
            }
        }
        calculatedPay = calculatedPay * multiplier;
        return calculatedPay; 
    }


    // this is the assign employee method that adds employee instances to the managed employee vector 
    bool assignEmployee (Employee& employee) { // Employee pointer reference as an argument
        for (size_t i = 0; i < managedEmployees.size(); i++) {
            // The if statment checks wether the newly created employee ID already exists in the managed employees vector
            if (managedEmployees[i]->getStaffID() == employee.getStaffID()) { // Need to use the arrow operator to access the pointers to employees stored in the vector
                return false; // if true it returns false and doesn't add the employee to the vector
            }
        }
        // push_back adds the new employee to the back of the managedEmployee vector
        managedEmployees.push_back(&employee); // used & as it stores the memory address of the existing Employee object rather than copying it to the memory
        return true;
    }

    // remove employee method removes employees from the managed employee vector
    bool removeEmployee (Employee& employee) {
        for (size_t i = 0; i < managedEmployees.size(); i++) {
            if (managedEmployees[i]->getStaffID() == employee.getStaffID()) { // checks if the employee that needs to be removed exists in the vector
                managedEmployees.erase(managedEmployees.begin() + i);
                return true;
            }
        }
        return false; // false is returned if the employee didn't exist so there wasn't what to be removed
    }

    // this is the find employee method, which uses the staff ID to find wether the employee exists
    Employee* findEmployee (int ID) { // pointer method to the employee class and takes in a int attribute from the user ID
        for (size_t i = 0; i < managedEmployees.size(); i++) { // loops through the managed employees vector
            // checks wether the employees staffId in the vector matches with the attribute that the method is given.
            if (managedEmployees[i] -> getStaffID() == ID) {
                return managedEmployees[i]; // returns the found employee if the condition is true
            }
        }
        std::cout << std::endl << "Error, the member ID does not exist." << std::endl; // if the condition fails to find a match a, error message is displayed
        return nullptr; // if the condition fails then return and empty pointer, because we declared the method as a pointer to the employee class
    }
 
    // this is the calculate team pay method, which adds the salary total of all employees together including the manager
    float CalculateTeamPay () {
        float totalTeamPay = 0.0f; // stores the total slary of everyone added up
        float currentSalary = 0.0f; // temporarly stores the value of each employee so that it can safely be added to the total variable
        for (size_t i = 0; i < managedEmployees.size(); i++) {
                currentSalary = managedEmployees[i] -> CalculatePay(); // using a pointer to get the calculated pay of each member
                totalTeamPay = totalTeamPay + currentSalary; 
        }
        totalTeamPay = totalTeamPay + CalculatePay(); // adding the manager calculated pay on top
        return totalTeamPay;
    }
};

// admin class inherited from the employee class
class Admin : public Employee {
    public: 
    Admin(std::string name, float salary) : Employee(name, salary) {} // constructor

    // using the CalculatePay function again and overriding it
    virtual float CalculatePay () override {
        float calculatedPay = 0.0f;
        calculatedPay = (salary / 12) * 1.15f;  // used 1.15f to increase the calculated pay by 15%
        return calculatedPay;
    }

    // a method that returns a pointer of the employee with a higher salary
    Employee* moreSkilled (Employee& employeeA, Employee& employeeB) { // two pointers to employee objects as attributes
        if (employeeA.getSalary() >= employeeB.getSalary()) {
            return &employeeA; // the & returns the address pointer of that employee object
        } else {
            return &employeeB;
        }
    }
};

// show menu function for displaying the menu
void showMenu () {
    int userChoice; // stores the user option choice
    bool menuState = true; // state of the while loop taht displays the menu 

    Manager* currentManager = nullptr; // pointer to the manger class object
    Admin* currentAdmin = nullptr;

    // the menu appears as long as the menu state is true
    while (menuState) { 
        // welcome message
        std::cout << std::endl << "<<<--------------------------------->>>" << std::endl;
        std::cout << "Welcome to C.A.L.S Employee System" << std::endl;
        std::cout << "<<<--------------------------------->>>" << std::endl << std::endl;

        // displaying main option choices to the user
        std::cout << "Please select one of the following: " << std::endl << std::endl;
        std::cout << "1: Manager Portal" << std::endl;
        std::cout << "2: Admin Portal" << std::endl;
        std::cout << "3: Exit System" << std::endl;

        std::cin >> userChoice; // stores the user option

        if (userChoice == 1) { // handles manager portal option
            // it will have the user create a manager instance
            if (currentManager == nullptr) {
                    std::string managerName;
                    float managerSalary = 0.0f;

                    // welcome message for manager portal
                    std::cout << "<<<--------------------------------->>>" << std::endl;
                    std::cout << "Manager Portal" << std::endl;
                    std::cout << "<<<--------------------------------->>>" << std::endl << std::endl;

                    // asks the manager for their name and salary
                    std::cout << "Enter manager name: " << std::endl;
                    std::cin >> managerName;

                    std::cout << "Enter your salary: " << std::endl;
                    std::cin >> managerSalary;

                    // using the eneterd name and salary we can create a new instance of the manager class and store it in the currentManager variable
                    currentManager = new Manager(managerName, managerSalary); 
                }


                // same method for the manager sub-menu. As long as the managerPortalActive variable stays true the menu will appear
                bool managerPortalActive = true;
                while (managerPortalActive) {

                    // welcome message
                    std::cout << std::endl << "<<<--------------------------------->>>" << std::endl;
                    std::cout << "Manager Portal - Welcome, " << currentManager->getName() << std::endl;
                    std::cout << "<<<--------------------------------->>>" << std::endl << std::endl;

                    // main option for the manager
                    std::cout << "Please enter the option you require: " << std::endl << std::endl;
                    std::cout << "1: Add/Create New Employee" << std::endl;
                    std::cout << "2: Calculate an Employee's Pay" << std::endl;
                    std::cout << "3: Remove Employee" << std::endl;
                    std::cout << "4: Find Employee" << std::endl;
                    std::cout << "5: Calculate Team Pay" << std::endl;
                    std::cout << "6: Return to Main Menu" << std::endl;

                    int managerChoice;
                    std::cin >> managerChoice; // records manager choosen option

                    // handles option for creating new employee
                    if (managerChoice == 1) {  
                        std::string employeeName;
                        float employeeSalary = 0.0f;

                        std::cout << "Enter new name: " << std::endl;
                        std::cin >> employeeName;

                        std::cout << "Enter the salary: " << std::endl;
                        std::cin >> employeeSalary;

                        Employee* newEmployee = new Employee(employeeName, employeeSalary); // This line is responsible for creating a pointer refernce to the employee class
                        currentManager->assignEmployee(*newEmployee); // Here is were i assign the new employee to the managedEmployee vector using the pointer created earlier

                        // display clear information for the output of option 1. This will be the same for the other options!
                        std::cout << std::endl << "Employee " << newEmployee->getName() << " (ID: " << newEmployee->getStaffID() << ") created successfully!" << std::endl;
                        
                    } else if (managerChoice == 2) {  // Option for calculating pay 
                        // Ask which employee ID to calculate pay for
                        int targetID;
                        std::cout << "Enter the ID of the employee to calculate pay: ";
                        std::cin >> targetID;


                        Employee* emp = currentManager->findEmployee(targetID); // Using this to find and create a refernece of the employee using a pointer
                        if (emp != nullptr) { // decides wether the employee exists
                            std::cout << std::endl << "Calculated pay for the employee is " << emp->CalculatePay() << std::endl; 
                        }

                    } else if (managerChoice == 3) { // option for removing employee
                        // Ask which employee to remove
                        int targetID;
                        std::cout << "Enter the ID of the employee to remove: ";
                        std::cin >> targetID;

                        Employee* emp = currentManager->findEmployee(targetID); // Using this to find and create a refernece of the employee using a pointer
                        if (emp != nullptr) {
                            std::cout << std::endl << emp->getName() << " was removed successfully!" << std::endl;
                            currentManager->removeEmployee(*emp);
                            delete emp; // free the heap memory
                        }

                    } else if (managerChoice == 4) { // option for finding employee
                        int employeeID;
                        std::cout << std::endl << "Enter the ID for the employee you wish to find: " << std::endl;
                        std::cin >> employeeID;
                        
                        // Handle the returned pointer cleanly so it prints readable information instead of a memory location
                        Employee* foundEmp = currentManager->findEmployee(employeeID); // Using this pointer to find and create a refernece of the employee 
                        if (foundEmp != nullptr) { // decide wether this employee exists
                            std::cout << std::endl << "Found Employee: " << foundEmp->getName() << " (ID: " << foundEmp->getStaffID() << ")" << std::endl;
                        }

                    } else if (managerChoice == 5) { // calculate team pay

                        float calculatedTeamPay = currentManager->CalculateTeamPay();
                        std::cout << std::endl << "Calculated pay for the team is " << calculatedTeamPay << std::endl;

                    } else if (managerChoice == 6) { // option for returning to main menu

                        std::cout << std::endl << "Returning to main menu..." << std::endl;
                        managerPortalActive = false; // Breaks out of the manager sub-menu loop

                    } else { 
                        std::cout << std::endl << "Error, please choose a valid option!"; 
                    }
                } // Closed the while (managerPortalActive) loop here
    } else if (userChoice == 2) {

        // checks that a currentManager exists so it outputs a error message if it is set to nullptr
        // because the currentManager is used in the admin portal to call methods from the manager class
        if (currentManager == nullptr) {
                std::cout << "Please create a Manager first before using the Admin Portal." << std::endl;
                continue;
        }

        if (currentAdmin == nullptr) { // By default when the program is first launched it will force the user to create a admin instance because it doesn't exist yet
            std::string adminName;
            float adminSalary = 0.0f;

            std::cout << std::endl << "<<<--------------------------------->>>" << std::endl << std::endl;
            std::cout << "Admin Portal" << std::endl;
            std::cout << "<<<--------------------------------->>>" << std::endl << std::endl;
            
            std::cout << "Enter your name: " << std::endl;
            std::cin >> adminName;

            std::cout << "Enter your salary: " << std::endl;
            std::cin >> adminSalary;

            currentAdmin = new Admin(adminName, adminSalary);

        }
        
        bool adminPortalActive = true;
        while (adminPortalActive) { 
            // welcome message for the admin portal
            std::cout << std::endl << "<<<--------------------------------->>>" << std::endl;
            std::cout << "Admin Portal - Welcome, " << currentAdmin->getName() << std::endl;
            std::cout << "<<<--------------------------------->>>" << std::endl << std::endl;

            // displays the admin portal options
            std::cout << "Please enter the option you require: " << std::endl << std::endl;
            std::cout << "1: Calculate My Admin Pay" << std::endl;
            std::cout << "2: Add/Create New Employee" << std::endl; // Allows admin to add employee so he has what employees to compare when using option 3
            std::cout << "3: Which Employee Is More Skilled" << std::endl;
            std::cout << "4: Return To Main Menu" << std::endl;

            int adminChoice;
            std::cin >> adminChoice;

            if (adminChoice == 1) {
                std::cout << std::endl << "Your calculated pay equates to " << currentAdmin->CalculatePay() << std::endl;
            } else if (adminChoice == 2) {

                // allows admin to create employees and assign them to the managedEmployees vector
                std::string employeeName;
                float employeeSalary = 0.0f;

                std::cout << "Enter new name: " << std::endl;
                std::cin >> employeeName;

                std::cout << "Enter the salary: " << std::endl;
                std::cin >> employeeSalary;

                Employee* newEmployee = new Employee(employeeName, employeeSalary);
                currentManager->assignEmployee(*newEmployee); 

                std::cout << std::endl << "Employee " << newEmployee->getName() << " (ID: " << newEmployee->getStaffID() << ") created successfully!" << std::endl; 
                
            } else if (adminChoice == 3) { // handles the admin option for finding the higher paid employee from the two
                
                std::cout << std::endl << "Please enter the ID for employee A" << std::endl;
                int empA_ID;
                std::cin >> empA_ID; // stores the first employee's ID

                Employee* employeeA = currentManager->findEmployee(empA_ID); // storing the found employee in the employeeA pointer so that it can then be used in the moreSkilled method.

                std::cout << std::endl << "Please enter the ID for employee B" << std::endl;
                int empB_ID;
                std::cin >> empB_ID; // stores the second employee's ID

                Employee* employeeB = currentManager->findEmployee(empB_ID); 
                
                // This will store another pointer to the employee that the moreSkilled() method returns
                Employee* moreSkilledEmployee = currentAdmin->moreSkilled(*employeeA, *employeeB);

                // output a message of the more skilled worker
                // in the output message i used the getName() method on the employee pointer moreSkilledEmployee
                std::cout << std::endl << "The more skilled worker is " << moreSkilledEmployee->getName() << std::endl; 

            } else if (adminChoice == 4) { // option 4 will change the state of the admin portal to false and utlimetly return the user to the main menu
                adminPortalActive = false;
            } else { 
                std::cout << std::endl << "Error, please choose a valid option!" << std::endl; // if the user enters a invalid option this cout will display a errror message
            }
        }

    } else if (userChoice == 3) { // this option is responsible for changing the state of the main menu to false and ultimetly end the program
        menuState = false; 
    } else {
        std::cout << std::endl << "Error, please choose a valid option!" << std::endl; // using cout to display a message if the user enters a invalid option
    }
    }
}


int main () {
    showMenu();
}