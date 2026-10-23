# C.A.L.S Employee System
    This program was devloped in C++ to support C.A.L.S in managing their employees more effectively and ensure that as the business grows the program remains scalable, by allowing managers to create new employee records and calculate salaries of any type of employee.

## Project Overview
C.A.L.S needs to allow managers to create new employees records and manage this records through a clear system in order to accuratley calculate salaries. The program i devloped allows managers and admins to access their designated portals from which they may perform their requiered operations. 

The manager portal gives mangers access to various features, such as creting new employees, finding them in the system, removing them from the system, calculating their montly pay, and calculating the total pay for every type of employee. 

The admin portal also allows admin users to create new employee records, but also features an option to quickly compare employees salaries.

## Features
**Manager portal:** 
- Create employee records
- Finding and removing employees
- Calcualating monthly pay
- Calculating total pay for all C.A.L.S employees

**Admin portal:**
- Calculate admin monthly pay
- Create employee records
- Compare employee salaries

## Class Structure
**Employee class** 
The employee class is a base class that is responsible for creating new employees and assigning them basic attributes such as a name, salary and ID. It makes use of encapsulation to ensure that these attributes are protected and only accessible to child classes through, the class itself also controls how they are used. This makes the program more secure and more relaible at storing the employee records safely. 

**Manager class**
The manager class is a child class of the employee, it essentially inherits the name, salary and ID from the parent class and uses them to create and manage employees. It has an vector that stores pointers to all created employees, and features options such searching for an employee or removing them from the vector. It also overrides the CalculatePay method from the parent employee class because a manger has a differnet structure to how their pay is calcualted. A extra mangement feature is calculating the total pay across al of C.A.L.S employees. 

**Admin class** 
The admin class also inherits from the employee class, and features the option to create new employees and add them to the private vector in the manager class using encapsulation. It also features a compare salaries option to find out which employee is paid more from two. 

## Programming Concepts Used
**In the devlopment of this system i used various programming concepts which includes:**

*Encapsulation* : I stored attributes as protected in the parent class.
*Getters and setters* : I used getters and setters to access those protected attributes from child classes.
*Inheritance* : Child classes such as the manager and admin class where inherited from the base employee calss.
*Polymorphism* : This was a crucial part in making the program dynamic, I made the calculatePay() method within the employee class a virtual method, and overrid it in the two child classes to ensure that the program calculates the pay depending on the employee type. So, the logic behind how pay is calculated between employees, managers and admins is different without sepreat pay calculation methods in each class.
*Constructors* : These were used so that when the users create instances of a class, they can pass in the name and salary of the new employee.
*Dynamic memory allocation* : I used dynamic memory allocation to create employee, manager and admin objects while the program is running. I then used pointers to access these objects and perform the different operations.

## Pay Calculations
For each employee type the monthly pay is calculated differently. For the a normal employee the monthly salary is calculated by divding their yearly salary by 12. 
However, for managers the process is more complex. Managers get a bonus for each employee that they manage. So they have the same monthly salary but multiplied by (1 + 0.1 for each employee that they manage), to achieve this the program had to check how many employees objects there are and calculate manager pay accordingly.

For admins their monthly salary benefits from a 15% increase. 

## Requierments and Installation
To compile and run the program, you will need the following:

WinLibs version GCC 16.2.0 to compile the C++ code.
Visual Studio Code


To compile the code open the terminal in Visual Studio Code and make sure that the current directory is the folder containing .\cals_employee_system.cpp. Then run the following command to compile the source code into an executable file:

`g++ -std=c++17 -Wall -Wextra -pedantic -g .\cals_employee_system.cpp -o .\cals_employee_system.exe`


To run the program use the following command in the terminal:

`.\cals_employee_system.exe`


## User Guide

To start using the program, run the `ap5.exe` file in the terminal. Once the program starts, the user will be presented with a main menu where they can choose between the Manager Portal, Admin Portal or exiting the system.

**Manager Portal**

To access the manager portal, select option 1 from the main menu. If a manager has not been created yet, the program will ask the user to enter the manager's name and yearly salary. Once this information has been entered, the manager will be created and the manager menu will be displayed.

The manager has access to several options. They can create new employee records by entering the employee's name and yearly salary. Each new employee is automatically assigned a unique staff ID, which can then be used to find the employee or calculate their monthly pay. The manager can also remove employees from the system by entering their staff ID, or find an employee to view their name and ID.

Another option allows the manager to calculate the total monthly pay for the team. This includes the manager's own calculated pay as well as the calculated pay of all employees assigned to them. Once the manager has finished using the portal, they can select option 6 to return to the main menu.

**Admin Portal**

To access the admin portal, select option 2 from the main menu. However, a manager must be created first, otherwise the program will display an error message and return to the main menu. If an admin has not been created yet, the program will ask for their name and yearly salary before displaying the admin menu.

The admin can calculate their own monthly pay, which includes a 15% increase. They can also create new employee records, which are added to the manager's list of employees. This allows the admin to compare two employees by entering their staff IDs. The program then compares their salaries and displays the name of the employee with the higher salary. If both employees have the same salary, the program returns the first employee.

Once the admin has finished using the portal, they can select option 4 to return to the main menu.

**Exiting the Program**

To exit the system, select option 3 from the main menu. This will end the program.

## Improvements
There are several improvements that i would do to this program including:
- A login portal after the user selects a portal to access - this would ensure that the manager and admin portals remain strictly accessible only to authorised users.
- Also the admin portal shouldn't depend on a manager employee to exist in order to be accessible. This is a major problem with my program because i used the currentManager pointer to access methods from the manager class from the admin portal. This causes the program to try access currentManager however, if the user went straight to the admin portal the currentManager was never asigned a name and salary and so it is yet set to nullptr. To fix this i choose to force the user into creating a manager object before being able to access the admin portal which is not the ideal solution to this problem.
- The program could be improved by allowing managers or administrators to edit existing employee information. For example, they could change an employee's name or salary without having to create a new employee record.
- More input validation could be added throughout the program. For example, the program could check that the user enters a valid salary.
- The employee system could include more ways of finding employees. For example, the user could search by employee ID, name or salary. This would become more useful as the number of employees in the system increases.







