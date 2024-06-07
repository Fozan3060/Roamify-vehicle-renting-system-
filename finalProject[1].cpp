#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;
bool isValidContactNumber(const string& number) {
    // Check if the number is an integer
    for (char c : number) {
        if (!isdigit(c)) {
            return false;
        }
    }
    // Check if the number has 11 digits
    if (number.length() != 11) {
        return false;
    }
    return true;
}
class RentalAgency; // Forward declaration
class Customer;
class Vehicle {
public:
    int vehicleID;
    string make;
    string model;
    int year;
    float rentalRate;
    bool available;
    int rentdays;
public:
    Vehicle(int id, string mk, string md, int yr, float rate) : vehicleID(id), make(mk), model(md), year(yr), rentalRate(rate), available(true), rentdays(0) {}
    virtual void displayDetails() const = 0;
     float calculateRentalCost(int days) const {
        return rentalRate * days;
    }
    
    bool isAvailable() const {
        return available;
    }
    
    void setAvailability(bool status) {
        available = status;
    }
};

class Car : public Vehicle {
    int seatingCapacity;
    string fuelType;
    string transmissionType;
public:
    Car(int id, string mk, string md, int yr, float rate, int seats, string fuel, string trans) 
        : Vehicle(id, mk, md, yr, rate), seatingCapacity(seats), fuelType(fuel), transmissionType(trans) {}
    
    void displayDetails() const override {
    	cout<<"\t\t\t\t ============================================="<<endl;
    	cout<<"\t\t\t\t                 CAR INFORMATION         "<<endl;
    	cout<<"\t\t\t\t Vehicle ID: " << vehicleID << endl;
    	cout<<"\t\t\t\t Make: " << make << ", Model: " << model << ", Year: " << year << endl;
    	cout<<"\t\t\t\t Seating Capacity: " << seatingCapacity <<endl;
		cout<<"\t\t\t\t Fuel Type: " << fuelType << ", Transmission: " << transmissionType << endl;
    	cout<<"\t\t\t\t Rental Rate: " << rentalRate << " per day" << endl;
    	cout<<"\t\t\t\t Availability: " << (available ? "Available" : "Not Available") << endl;
    	cout<<"\t\t\t\t ============================================="<<endl;

    }
};

class Motorbike : public Vehicle {
    string type;
public:
    Motorbike(int id, string mk, string md, int yr, float rate, string tp)
        : Vehicle(id, mk, md, yr, rate), type(tp) {}

    void displayDetails() const override {
    	cout<<"\t\t\t\t ============================================="<<endl;
    	cout<<"\t\t\t\t                MOTORBIKE INFORMATION         "<<endl;
    	cout<<"\t\t\t\t Vehicle ID: " << vehicleID << endl;
    	cout<<"\t\t\t\t Make: " << make << ", Model: " << model << ", Year: " << year << endl;
    	cout<<"\t\t\t\t Type: " << type << endl;
    	cout<<"\t\t\t\t Rental Rate: " << rentalRate << " per day" << endl;
    	cout<<"\t\t\t\t Availability: " << (available ? "Available" : "Not Available") << endl;
    	cout<<"\t\t\t\t ============================================="<<endl;
    	
    }
};

class Bicycle : public Vehicle {
    string type;
public:
    Bicycle(int id, string mk, string md, int yr, float rate, string tp)
        : Vehicle(id, mk, md, yr, rate), type(tp) {}
    void displayDetails() const override {
    	cout<<"\t\t\t\t ============================================="<<endl;
    	cout<<"\t\t\t\t                BICYCLE INFORMATION         "<<endl;
		cout<<"\t\t\t\t Vehicle ID: " << vehicleID << endl;
		cout<<"\t\t\t\t Make: " << make << ", Model: " << model << ", Year: " << year << endl;
		cout<<"\t\t\t\t Type: " << type << endl;
		cout<<"\t\t\t\t Rental Rate: " << rentalRate << " per day" << endl;
		cout<<"\t\t\t\t Availability: " << (available ? "Available" : "Not Available") << endl;
		cout<<"\t\t\t\t ============================================="<<endl;
    }
};

class Bus : public Vehicle {
    int seatingCapacity;
public:
    Bus(int id, string mk, string md, int yr, float rate, int seats)
        : Vehicle(id, mk, md, yr, rate), seatingCapacity(seats) {}

    void displayDetails() const override {
    	cout<<"\t\t\t\t ============================================="<<endl;
		cout<<"\t\t\t\t                 BUS INFORMATION         "<<endl;
		cout<<"\t\t\t\t Vehicle ID: " << vehicleID << endl;
		cout<<"\t\t\t\t Make: " << make << ", Model: " << model << ", Year: " << year << endl;
        cout<<"\t\t\t\t Seating Capacity: " << seatingCapacity << endl;
        cout<<"\t\t\t\t Rental Rate: " << rentalRate << " per day" << endl;
        cout<<"\t\t\t\t Availability: " << (available ? "Available" : "Not Available") << endl;
        cout<<"\t\t\t\t ============================================="<<endl;
    }
};
class RentalAgency {
    static const int MAX_VEHICLES = 100; // Maximum number of vehicles in the fleet
    Vehicle* fleet[MAX_VEHICLES]; // Array to store pointers to vehicles
public:
    int numVehicles;
    RentalAgency() : numVehicles(0) {} // Constructor to initialize members

    void addVehicle(Vehicle* vehicle) {
        if (numVehicles < MAX_VEHICLES) {
            fleet[numVehicles++] = vehicle;
        } else {
            cout << "Cannot add more vehicles. Maximum limit reached." << endl;
        }
    }
    void removeVehicle(Vehicle* vehicle){
        if(numVehicles>=0){
            fleet[numVehicles--]=vehicle;
        }
        else{
            cout<<"Cannot remove vehicles. Current Vehicles stored are 0"<<endl;
        }
    }

    void displayAvailableVehicles() const {
	    cout<<"\t\t\t\t\t ================================="<<endl;
		cout<<"\t\t\t\t\t|        AVAILABLE VEHICLES       | "<<endl;
		cout<<"\t\t\t\t\t ================================="<<endl;
        for (int i = 0; i < numVehicles; ++i) {
            if (fleet[i]->isAvailable()) {
                fleet[i]->displayDetails();
                cout << endl;
            }
        }
    }
    friend void rentVehicle(Customer& customer, RentalAgency& agency, int vehicleID, int days);
    friend void addRentedVehicle(RentalAgency& agency,Customer& C,int vehicleID);
};

class Customer {
	int rent_days;
    bool loggedIn;
    string C_username, C_password, C_name, C_email, C_contact;
    int customerID ;
    int option;
    static const int MAX_RENTED_VEHICLES = 5; // Maximum number of rented vehicles
    Vehicle* rentedVehicles[MAX_RENTED_VEHICLES];
    int numRentedVehicles; // Track the number of rented vehicles
public:

    Customer() : loggedIn(false), option(0), numRentedVehicles(0) {} // Constructor to initialize members
	//Declared Inside class and defined outside...
	void start();
	void login();
	void signup();
	void getCustomerID() const{
		ifstream myFile("UserCredentials.txt");
	  string fileUsername, fileEmail, filePassword, filePhoneNum;
        int fileCustomerID;
         while (myFile >> fileUsername >> fileEmail >> filePassword >> filePhoneNum >>fileCustomerID) {
            if (fileUsername == C_username && filePassword == C_password) {
                cout<<"\t\t\t\t\t   Customer ID : "<<fileCustomerID<<endl;
                break; // No need to continue checking, exit loop
            }
        }
	}
	//Declared and defined inside....
    void displayDetails() const {  
	cout<<endl;
	cout<<"\t\t\t\t\t ========================================="<<endl;
	cout<<"\t\t\t\t\t                YOUR PROFILE            "<<endl; 
	cout<<"\t\t\t\t\t                                   "<<endl; 
	getCustomerID();
	cout<<"\t\t\t\t\t   Customer Username : "<<C_username<<endl; 
	cout<<"\t\t\t\t\t   Customer Email : "<<C_email<<endl;
	cout<<"\t\t\t\t\t   Customer Phone : "<<C_contact<<endl; 
	cout<<"\t\t\t\t\t                                  "<<endl; 
	cout<<"\t\t\t\t\t =========================================="<<endl;  
    }
    void displayRentedVehicles() const {
    	system("cls");
    	cout<<"\t\t\t\t\t ================================"<<endl;
    	cout<<"\t\t\t\t\t         RENTED VEHICLES :       "<<endl;
        for (int i = 0; i < numRentedVehicles; ++i) {
        	cout<<"\t\t\t\t\t Vehicle Number #"<<i+1<<" : "<<endl;
        	cout<<"\t\t\t\t\t Vehicle ID #"<<rentedVehicles[i]->vehicleID<<" : "<<endl;
        	cout<<"\t\t\t\t\t Vehicle  : "<<rentedVehicles[i]->make<<"  "<<rentedVehicles[i]->model<<" "<<rentedVehicles[i]->year<<endl;
        	cout<<"\t\t\t\t\t Vehicle per day rental cost : "<<rentedVehicles[i]->rentalRate<<endl;
        	cout<<"\t\t\t\t\t You rented for : "<<rentedVehicles[i]->rentdays<<" days !"<<endl;
        	cout<<"\t\t\t\t\t Cost : "<<rentedVehicles[i]->rentalRate*rentedVehicles[i]->rentdays<<endl;
            cout << endl;
        }
        cout<<"\t\t\t\t\t ================================"<<endl;
    }

    // Method to calculate total rental cost
    float calculateTotalRentalCost() const {
        float totalCost = 0.0;
        for (int i = 0; i < numRentedVehicles; ++i) {
            totalCost += rentedVehicles[i]->rentalRate*rentedVehicles[i]->rentdays;
        }
        return totalCost;
    }
    
	void setday(){
		cout<<"\t\t\t\t Enter number of days to rent vehicle : ";
        cin>>rent_days;
	}
	int getday(){
		return rent_days;
	}
	void signout(){
		loggedIn = false;
	}
    // Declare rentVehicle as friend function
    friend void rentVehicle(Customer& customer, RentalAgency& agency, int vehicleID, int days);
    friend void removeRentVehicle(Customer& customer,int vehicleID);
    friend void addRentedVehicle(RentalAgency& agency,Customer& C,int vehicleID);
    friend void removeVehicleProcess(Customer& customer);
};
// Static member initialization

void Customer::start(){
        cout<<endl<<"\t\t\t\t\t  Enter your choice : ";
        cin>>option;
        if(option == 1){
            login();
        }
        else if(option == 2){
            signup();
        }
        else
        {
            if (!isdigit(option)) {
                throw "Character must not be entered ";
        }
        system("cls");
        cout<<"Invalid Choice !!! "<<endl;
        cout<<"\t\t\t\t\t ============================"<<endl;
		cout<<"\t\t\t\t\t|         LOGIN PAGE         | "<<endl;
		cout<<"\t\t\t\t\t|                            |"<<endl; 
		cout<<"\t\t\t\t\t| 1. Sign In                 | "<<endl;
		cout<<"\t\t\t\t\t| 2. Register                |"<<endl;
		cout<<"\t\t\t\t\t|                            |"<<endl; 
		cout<<"\t\t\t\t\t ============================"<<endl;
        start();
    	}
    }

void Customer::login() {
        ifstream myFile("UserCredentials.txt");
        if (!myFile.is_open()) {
            throw "\t\t\t   Currently No user in database. First register to login in ! ";
        }
        string fileUsername, fileEmail, filePassword, filePhoneNum;
        int fileCustomerID;
        bool loginSuccessful = false; // Flag to track login success
		cout<<endl;
        cout << "\t\t\t\t\t Enter username : ";
        cin >> C_username;
        cout << "\t\t\t\t\t Enter password : ";
        cin >> C_password;

        while (myFile >> fileUsername >> fileEmail >> filePassword >> filePhoneNum >>fileCustomerID) {
            if (fileUsername == C_username && filePassword == C_password) {
            
                loginSuccessful = true; // Set flag to true if login successful
                C_email = fileEmail;
                C_contact = filePhoneNum;
                customerID = fileCustomerID;

                system("cls");
                cout<<endl;
                cout<<"\t\t\t\t\t ================================="<<endl;
				cout<<"\t\t\t\t\t|        LOGIN SUCCESSFULL        | "<<endl;
				cout<<"\t\t\t\t\t ================================="<<endl;

                loggedIn = true;
                break; // No need to continue checking, exit loop
            }
        }

        if (!loginSuccessful) {
        	cout<<endl;
            throw "\t\t\t\t\t Invalid Username or Password !!!";
        }
    }
    void Customer::signup(){
    	system("cls");
    	cout<<endl;
    	cout<<"\t\t\t\t\t ================================="<<endl;
		cout<<"\t\t\t\t\t|        REGISTRATION PAGE        | "<<endl;
		cout<<"\t\t\t\t\t ================================="<<endl;
        string fileUsername, fileEmail, filePassword, filePhoneNum;
        int fileCustomerID;
        cout<<endl<<endl;
        cout<<"\t\t\t\t\t ================================="<<endl;
		cout<<"\t\t\t\t\t Enter username:";
		cin>>C_username;
		while(C_username.length() <1)
        {
            cout<<"Username cannot be empty !!! "<<endl;
            cin>>C_username;
        }
        cout<<"\t\t\t\t\t Enter Email Address : ";
        cin>>C_email;
        while(C_email.find('@')==string::npos || C_email.find(".com")==string::npos){
            cout<<"\t\t\t\t\t Enter valid email address which must contain '@' and .com "<<endl;
            cout<<"\t\t\t\t\t Enter Email Address : ";
            cin>>C_email;
        }
        cout<<"\t\t\t\t\t Enter password : ";
        cin>>C_password;
        while(C_password.length() < 6)
        {
            cout<<"\t\t\t\t\t Password should atleast be 6 characters long !!! "<<endl;
            cout<<"\t\t\t\t\t Enter password : ";
            cin>>C_password;
        }
        cout<<"\t\t\t\t\t Enter phone number : ";
        cin>>C_contact;
        
        while(!isValidContactNumber(C_contact)){
        	cout<<"\t\t\t\t\t Invalid Phone Number !!! "<<endl;
        	cout<<"\t\t\t\t\t Enter phone number : ";
        	cin>>C_contact;
		}
		cout<<"\t\t\t\t\t ================================="<<endl;
		  
        // checking if user with this credentials already exist in database 
     ifstream myFile("UserCredentials.txt");
        if(myFile.is_open()){
            while (myFile >> fileUsername >> fileEmail >> filePassword >> filePhoneNum >>fileCustomerID) {
            if (fileUsername == C_username ) {
             throw "Error Username already taken. Kindly register with different username";  
            }
           else if(fileEmail==C_email){
             throw "Error Email already taken. Kindly register with different email";  
           }
           else if(filePassword==C_password){
             throw "Error Password already taken. Kindly register with different password";  
           }
           else if(filePhoneNum ==C_contact){
             throw "Error Phone number already taken. Kindly register with different phone number";  
           }
           else{
        	fileCustomerID = fileCustomerID + 1;
        	loggedIn=true;
		   }
        }
        }
		
        customerID++;
        cout<<"\t\t\t\t    ============================================"<<endl;
		cout<<"\t\t\t\t   |        ACCOUNT CREATED SUCCESSFULLY        | "<<endl;
		cout<<"\t\t\t\t    ============================================"<<endl;
		loggedIn = true;
        ofstream userFile;
        userFile.open("UserCredentials.txt",ios::app);
        if(userFile.is_open()){
            userFile<<C_username<<endl;
            userFile<<C_email<<endl;
            userFile<<C_password<<endl;
            userFile<<C_contact<<endl;
            userFile<<fileCustomerID<<endl;
        }
        else{
             throw "Error opening file ";
        }
           
    }

void addRentedVehicle(RentalAgency& agency, Customer& C, int vehicleID) {
    for (int i = 0; i < agency.numVehicles; ++i) {
        if (agency.fleet[i]->vehicleID == vehicleID) {
            if (C.numRentedVehicles < C.MAX_RENTED_VEHICLES) {
                C.rentedVehicles[C.numRentedVehicles++] = agency.fleet[i];
                cout << "\t\t\t\tVehicle with ID " << vehicleID << " added to rented vehicles." << endl;
                return;
            } else {
                cout<<"\t\t\t\tCannot add more vehicles. Maximum limit reached." << endl;
                return;
            }
        }
           
    }
	}

// Define rentVehicle function
void rentVehicle(Customer& customer, RentalAgency& agency, int vehicleID, int days) {
    if (!customer.loggedIn) {
        throw  "You must be logged in to rent a vehicle." ;
        return;
    }
    bool found = false;
    for (int i = 0; i < agency.numVehicles; ++i) {
        if (agency.fleet[i]->vehicleID == vehicleID && agency.fleet[i]->isAvailable()) {
            agency.fleet[i]->rentdays = days;
            float rentalCost = agency.fleet[i]->calculateRentalCost(days);
            cout<<endl;
            
            cout<<"\t\t\t\tVehicle rented successfully for " << days << " days." << endl;
            cout<<"\t\t\t\tRental cost: $" << rentalCost << endl;
            addRentedVehicle(agency,customer,vehicleID);
            agency.fleet[i]->setAvailability(false);
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "\t\t\t\t\tVehicle not available or does not exist." << endl;
    }
}

	void removeRentVehicle(Customer& customer, int vehicleID) {
    int foundIndex = -1; // flag to track removing vehicle process
    for (int i = 0; i < customer.numRentedVehicles; i++) {
        if (customer.rentedVehicles[i]->vehicleID == vehicleID) {
        cout<<"\t\t\t\t\t ================================="<<endl;
		cout<<"\t\t\t\t\t        REMOVING VEHICLE         "<<endl; 
		cout<<"\t\t\t\t\t  ID: " << vehicleID <<endl;
		cout<<"\t\t\t\t\t  Make: " << customer.rentedVehicles[i]->make <<endl;
		cout<<"\t\t\t\t\t  Model: " << customer.rentedVehicles[i]->model << endl;
        cout<<"\t\t\t\t\t ================================="<<endl; 
            foundIndex = i; // Store the index of the found vehicle
            break; 
        }
    }
    if (foundIndex != -1) { // Check if the vehicle was found
        // Shift the remaining vehicles in the array to fill the gap
        for (int j = foundIndex; j < customer.numRentedVehicles - 1; j++) {
            customer.rentedVehicles[j] = customer.rentedVehicles[j + 1];
        }
        customer.numRentedVehicles--;
        cout<<endl;
        cout << "\t\t\t\t\t   Vehicle removed successfully." << endl;
    } else {
    	cout<<endl;
        cout << "\t\t\t\t  Invalid vehicle ID. No such vehicle exists in your inventory!" << endl;
    }
}
void removeVehicleProcess(Customer &c){
    char option;
    int veh_id;
    do
    {   cout<<endl;
        cout<<"\t\t\t\t  Do you want to remove any vehicles from rent inventory?"<<endl;
    cout<<"\t\t\t\t\tPress Y for yes and N for no : ";
    cin>>option;
        option=toupper(option);
         if(option!='N' && option!='Y'){
            cout<<"Invalid option selected. Please select valid option!"<<endl;
        }
        if(option=='N'){
            if(c.numRentedVehicles==0){
                cout<<"\t\t\t\t\tCurrently no vehicle rented !"<<endl;
            }
            else{
            c.displayRentedVehicles();
            
            }
    	    cout<<endl<<"\t\t\t\t\tYour Total for Rented Vehicles is : "<<c.calculateTotalRentalCost();
            break;

        }
        else{
           if(c.numRentedVehicles==0){
            cout<<"\t\t\t\t  Sorry ! You havent rented any vehicles to be removed !"<<endl;
             break;
           }

            c.displayRentedVehicles();
            cout<<"\t\t\t\t\tEnter vehicle Id to be removed: ";
           cin>>veh_id;
           removeRentVehicle(c,veh_id);
        }
    } while (option!='N');  
}
void vehicleRentProcess( RentalAgency &agency ,  Customer &c){
	system("cls");
    int veh_id,car_opt; // rented vehicle information
    char proceed;
    agency.displayAvailableVehicles();
    system("Color 0B");
    cout<<"\t\t\t\t ========================================"<<endl;
	cout<<"\t\t\t\t        VEHICLE RENTAL SYSTEM       "<<endl<<endl; 
	cout<<"\t\t\t\t Enter Vehicle ID to rent : ";
    cin>>veh_id;
    c.setday();
    cout<<"\t\t\t\t ========================================"<<endl;
	int days = c.getday();
     rentVehicle(c,agency,veh_id,days);
}
class UI{
	public:
	void printLOGO(){
	system("Color 0E");
	cout<<endl<<"\t\t\t\tWelcome to ROAMIFY (one stop for Vehicle Rentals) "<<endl<<endl;
    cout<<endl;
	cout<<"\t* * * * *        * * * *          *         *       *     * * * * *     * * * * *   *        *"<<endl;
	cout<<"\t*        *      *       *        * *        * *   * *         *         *            *      *"<<endl;
	cout<<"\t* * * * *       *       *       *   *       *  * *  *         *         * * * * *     *   *"<<endl;
	cout<<"\t*     *         *       *      * * * *      *   *   *         *         *               *"<<endl;
	cout<<"\t*       *       *       *     *       *     *       *         *         *               *"<<endl;
	cout<<"\t*         *      * * * *     *         *    *       *     * * * * *     *               *"<<endl<<endl<<endl;
	}
	void printMENU(){
	cout<<endl;
	system("Color 0E");
	cout<<"\t\t\t\t\t ================================="<<endl;
	cout<<"\t\t\t\t\t|        ROAMIFY DASHBOARD        |"<<endl; 
	cout<<"\t\t\t\t\t|                                 |"<<endl; 
	cout<<"\t\t\t\t\t|  0. Your Profile                |"<<endl; 
	cout<<"\t\t\t\t\t|  1. Rent Cars                   |"<<endl; 
	cout<<"\t\t\t\t\t|  2. View Your Cart              | "<<endl;
	cout<<"\t\t\t\t\t|  3. Remove Rented Vehicle       |"<<endl; 
	cout<<"\t\t\t\t\t|  4. Checkout                    |"<<endl; 
	cout<<"\t\t\t\t\t|  5. Sign out                    |"<<endl; 
	cout<<"\t\t\t\t\t|                                 |"<<endl; 
	cout<<"\t\t\t\t\t =================================="<<endl;
	}
	void checkoutMENU(Customer& c1){
	cout<<endl;
	cout<<"\t\t\t\t\t ================================"<<endl; 
	cout<<"\t\t\t\t\t          SUB TOTAL : "<<c1.calculateTotalRentalCost()<<endl; 
	cout<<"\t\t\t\t\t ================================"<<endl;
}
void loginPage(){
	cout<<"\t\t\t\t         ============================"<<endl;
	cout<<"\t\t\t\t\t|\t LOGIN PAGE          | "<<endl;
	cout<<"\t\t\t\t\t|                            |"<<endl; 
	cout<<"\t\t\t\t\t|\t 1. Sign In          | "<<endl;
	cout<<"\t\t\t\t\t|\t 2. Register         |"<<endl;
	cout<<"\t\t\t\t\t|                            |"<<endl; 
	cout<<"\t\t\t\t         ============================"<<endl;
}
	
}UserInterface;



int main() {
    // int veh_id,car_opt,rent_days; // rented vehicle information
    int choice;
    char proceed;
	Customer c1;
	UserInterface.printLOGO();
	UserInterface.loginPage();
    try
    {   
    
    c1.start();
    Car car1(1, "Toyota", "Camry", 2020, 50.0, 5, "Petrol", "Automatic");
    Car car2(2, "Honda", "Accord", 2019, 55.0, 5, "Petrol", "Automatic");
    Motorbike bike1(3, "Honda", "CBR 1000RR", 2021, 100.0, "Sport");
    Bicycle bicycle1(4, "Giant", "Talon", 2020, 20.0, "Mountain");
    Bus bus1(5, "Mercedes-Benz", "Sprinter", 2018, 150.0, 20);
    Car car0(6,"Toyota","Supra MK4",2004,80.0,2,"Petrol","Automatic");
    Car car4(7,"Mercedes-Benz","C63",2024,90,5,"Petrol","Automatic");
    Car car5(8,"Mercedes-Benz","G-Wagon",2021,120,5,"Diesel","Automatic"); 
    
    RentalAgency agency;
    agency.addVehicle(&car1);
    agency.addVehicle(&car2);
    agency.addVehicle(&bike1);
    agency.addVehicle(&bicycle1);
    agency.addVehicle(&bus1);
    agency.addVehicle(&car0);
    agency.addVehicle(&car4);
    agency.addVehicle(&car5);
	
	    
    while(1){
    UserInterface.printMENU();
    cout<<endl<<"\t\t\t\t\t Enter your choice : ";
    cin>>choice;
    	
    switch(choice){
    case 0:
    {
     system("cls");
	 c1.displayDetails();
     break;
	}
	case 1:
	{
	vehicleRentProcess(agency,c1);
	break;
	}
	case 2:
	{
	 c1.displayRentedVehicles();
	break;
	}
	case 3:
	{
		removeVehicleProcess(c1);
		break;
	}
	case 4:
	{
		UserInterface.checkoutMENU(c1);
		break;
	}
	case 5:
	{
		c1.signout();
		cout<<"\t\t\t\t\t ================================"<<endl; 
		cout<<"\t\t\t\t\t| ID successfully signed out !!! |"<<endl;
		cout<<"\t\t\t\t\t ================================"<<endl;
		exit(0);
	}
	default:{
		cout<<"Invalid Choice "<<endl;
		break;
	}
   	}
   	cout<<endl;
   	cout<<"\t\t\t\t\tPress any digit to continue and 0 to exit : ";
   	cin>>choice;
   	if(choice == 0)
   	break;
   	system("cls");
	   }
    }
    catch (const char* e){
        cout<<e<<endl;
    }
    return 0;
}
