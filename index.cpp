#include <iostream>
#include <string>
#include <vector>

using namespace std;
 
class Room {  
    int id;
    bool isVacant;
    string customerName;
    double roomPrice;

    public: 
       Room(int roomId, double price) {
        id = roomId;
        isVacant = true;
        customerName = "";
        roomPrice = price;
    }

    int getId() {
        return id;
    }

    bool getIsVacant() {
        return isVacant;
    }

    string getCustomerName() {
        return customerName;
    }

    double getRoomPrice() {
        return roomPrice;
    }

    void displayInfo() {
        cout << "Room " << id << ": ";
        if (isVacant) {
            cout << "Vacant" << endl;
        } else {
            cout << "Occupied by " << customerName << endl;
        }
    }

    void book(string name) {
        isVacant = false;
        customerName = name;
    }

    void cancel() {
        isVacant = true;
        customerName = "";
    }

    void checkIn() {
        isVacant = false;
    }

    void checkOut() {
        isVacant = true;
        customerName = "";
    }
};

class Hotel {
    vector<Room*> vacantRooms;
    vector<Room*> checkedInRooms;

    public:
    Hotel() {
        //initialize a hotel with 10 rooms
        for (int i = 1; i <= 10; i++) {
            vacantRooms.push_back(new Room(i, 100.0)); // Set the room price to $100 
        }
    }

    void displayMenu() {
        cout << "*__*___*___*___*___*___*___*____*____*___*___* " << endl;
        cout << "             Welcome to Best-in hotel!         " << endl;
        cout << " --> Please select an option: " << endl;
        cout << "1. Vacancy" << endl;
        cout << "2. Reservation" << endl;
        cout << "3. Confirm Reservation - Booking" << endl;
        cout << "4. Check in" << endl;
        cout << "5. Check out" << endl;
        cout << "6. Payment" << endl;
        cout << "7. Quit" << endl;
        cout << "enter an Option: " << endl;
        cout << "---------------- " << endl;
    }

    void listVacantRooms() {
        cout << "Vacant rooms: " << endl;
        for (Room* room : vacantRooms) {
            if (room->getIsVacant()) {
                room->displayInfo();
            }
        }
    }

    void listConfirmedRooms() {
        cout << "Confirmed reservations: " << endl;
        for (Room* room : vacantRooms) {
            if (!room->getIsVacant()) {
                room->displayInfo();
            }
        }
    }

    void bookRoom() {
        listVacantRooms();

        cout << "Enter the room Id of the room you want to book: ";
        int roomId;
        cin >> roomId;

        //check if room exist and is vacant
        Room* selectedRoom = nullptr;
        for (Room* room : vacantRooms) {
            if (room->getId() == roomId && room->getIsVacant()) {
                selectedRoom = room;
                break;
            }
        }

        // handle not existing room number 
        if (!selectedRoom) {
            cout << "Invalid room Id" << endl;
            return;
        }

        cout << "Enter your name: ";
        string name;
        cin >> name;

        selectedRoom->book(name);
        cout << "Room " << roomId << " has been booked by " << name << endl;
    }

    void cancelReservation() {
        listConfirmedRooms();
        cout << "Enter the room Id of the reservation you want to cancel: ";
        int roomId;
        cin >> roomId; 
    }

     void roomCheckIn() {
        listConfirmedRooms();
        cout << "Enter the room ID to check in: ";
        int roomId;
        cin >> roomId;

        // Check if the room exists and is reserved
        Room* selectedRoom = nullptr;
        for (Room* room : vacantRooms) {
            if (room->getId() == roomId) {
                selectedRoom = room;
                break;
            }
        }

        // Handle non-existing room number or vacant room
        if (!selectedRoom || selectedRoom->getIsVacant()) {
            cout << "Invalid room ID or the room is not reserved" << endl;
            return;
        }

        // Move the room from the vacant room list to the checked-in room list
        vacantRooms.erase(
            remove(vacantRooms.begin(), vacantRooms.end(), selectedRoom),
            vacantRooms.end()
        );
        checkedInRooms.push_back(selectedRoom);

        selectedRoom->checkIn();
        cout << "Checked in successfully for Room " << roomId << endl;
    }

    void roomCheckOut() {
        // List all checked-in rooms
        cout << "Checked-in rooms: " << endl;
        for (Room* room : checkedInRooms) {
            room->displayInfo();
        }

        // Enter the checked-in room ID
        cout << "Enter the room ID to check out: ";
        int roomId;
        cin >> roomId;

        // Check if the room exists and is checked in
        Room* selectedRoom = nullptr;
        for (Room* room : checkedInRooms) {
            if (room->getId() == roomId) {
                selectedRoom = room;
                break;
            }
        }

        // Handle non-existing room number or vacant room
        if (!selectedRoom) {
            cout << "Invalid room ID or the room is not checked in" << endl;
            return;
        }

        // Move the room from the checked-in room list to the vacant room list
        checkedInRooms.erase(
            remove(checkedInRooms.begin(), checkedInRooms.end(), selectedRoom),
            checkedInRooms.end()
        );
        vacantRooms.push_back(selectedRoom);

        selectedRoom->checkOut();
        cout << "Checked out successfully for Room " << roomId << endl;
    }


    void processPayment() {
        // List all checked-out rooms
        cout << "Checked-out rooms: " << endl;
        for (Room* room : vacantRooms) {
            room->displayInfo();
        }

        // Enter the checked-out room ID
        cout << "Enter the room ID to process payment: ";
        int roomId;
        cin >> roomId;

        // Check if the room exists and is checked out
        Room* selectedRoom = nullptr;
        for (Room* room : vacantRooms) {
            if (room->getId() == roomId) {
                selectedRoom = room;
                break;
            }
        };
        // Handle non-existing room number or not checked out room
        if (!selectedRoom) {
            cout << "Invalid room ID or the room is not checked out" << endl;
            return;
        }

        // get the room price per night 
        double roomPrice = selectedRoom->getRoomPrice();

       //get the number of night stayed from the customer
       int numNights;
       cout << "Enter the total number of nights stayed: ";
       cin >> numNights;

       //Calculate the total amount due 
       double totalAmount = roomPrice * numNights;

       cout << "Room " << roomId << " has been checked out." << endl;
       cout << "Number of nights stayed: " << numNights << endl;
       cout << "Room price per night: $" << roomPrice << endl; 
       cout << "---------------------------" << endl;
       cout << "|  The total amount: $ " << totalAmount << " |" << endl;
       cout << "---------------------------" << endl;
    }
};

int main() {
    Hotel hotel;
    int choice;

    while (true) {
        hotel.displayMenu();

        cin >> choice;

        switch (choice) {
            case 1:
                hotel.listVacantRooms();
                break;

            case 2:
                hotel.bookRoom();
                break;

            case 3:
                hotel.listConfirmedRooms();
                break;

            case 4:
                hotel.roomCheckIn();
                break;

            case 5:
                hotel.roomCheckOut();
                break;

            case 6: 
                hotel.processPayment();
                break;
          
            case 7: 
                cout << "Thank you for using BEST-IN hotel. Goodbye!" << endl;
                cout << "*******************************************" << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}