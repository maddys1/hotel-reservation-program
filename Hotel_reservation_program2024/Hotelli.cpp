#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <limits> 
#include <map> 
#include <set>

using namespace std;

struct Reservation {
    int roomNumber;
    string name;
};

// Function to get a random number within a range
int getRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Function to get valid input from the user
int getValidInput() {
    int input;
    while (true) {
        cin >> input;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
        }
        else {
            return input;
        }
    }
}

// Function to get a random available room number
int getRandomRoom(const vector<bool>& rooms, int start, int end) {
    vector<int> availableRooms;
    for (int i = start; i < end; i++) {
        if (!rooms[i]) {
            availableRooms.push_back(i + 1);
        }
    }
    if (availableRooms.empty()) {
        return -1;
    }
    int randomIndex = getRandomNumber(0, availableRooms.size() - 1);
    return availableRooms[randomIndex];
}

// Function to calculate the total price with a random discount
int calculateTotalPrice(int nights, int pricePerNight) {
    int discount = getRandomNumber(0, 2) * 10;
    int total = nights * pricePerNight;
    total -= total * discount / 100;
    return total;
}

// Function to search for a reservation by number
void searchReservationNumber(const map<int, Reservation>& reservations) {
    int reservationNumber;
    cout << "Enter reservation number: ";
    reservationNumber = getValidInput();
    auto it = reservations.find(reservationNumber);
    if (it != reservations.end()) {
        cout << "Reservation found: Room " << it->second.roomNumber << ", Name: " << it->second.name << endl;
    }
    else {
        cout << "Reservation not found." << endl;
    }
}

// Function to search for reservations by name
void searchByName(const map<int, Reservation>& reservations) {
    string name;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, name);
    bool found = false;
    for (const auto& reservation : reservations) {
        if (reservation.second.name == name) {
            cout << "Reservation found: Number " << reservation.first << ", Room " << reservation.second.roomNumber << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Reservation not found." << endl;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int n = getRandomNumber(40, 300) * 2;
    int singleRoomPrice = 100;
    int doubleRoomPrice = 150;

    vector<bool> rooms(n, false);
    map<int, Reservation> reservations;
    set<int> usedReservationNumbers;

    cout << "Welcome to the hotel!" << endl;

    while (true) {
        cout << "\n=========================\n";
        cout << "Main menu: " << endl;
        cout << "1. Reserve a room." << endl;
        cout << "2. Search for a reservation." << endl;
        cout << "3. Exit." << endl;
        cout << "=========================\n";
        cout << "Select an option: ";

        int option = getValidInput();

        if (option == 1) {
            int roomType;
            cout << "Select room type: 1 for single room, 2 for double room." << endl;
            while (true) {
                roomType = getValidInput();
                if (roomType == 1 || roomType == 2) {
                    break;
                }
                else {
                    cout << "Invalid room type selected. Please enter 1 for single room or 2 for double room." << endl;
                }
            }

            int roomNumber = (roomType == 1) ? getRandomRoom(rooms, 0, n / 2) : getRandomRoom(rooms, n / 2, n);

            if (roomNumber == -1) {
                cout << "All rooms are reserved." << endl;
                continue;
            }

            int reservationNumber;
            do {
                reservationNumber = getRandomNumber(10000, 99999);
            } while (usedReservationNumbers.count(reservationNumber));

            usedReservationNumbers.insert(reservationNumber);

            cout << "Enter your name: ";
            cin.ignore();
            string name;
            getline(cin, name);

            rooms[roomNumber - 1] = true;
            reservations[reservationNumber] = { roomNumber, name };

            cout << "Room " << roomNumber << " is reserved for you." << endl;
            cout << "Your reservation number is " << reservationNumber << "." << endl;
            cout << "How many nights would you like to stay?" << endl;

            int nights = getValidInput();
            int pricePerNight = (roomType == 1) ? singleRoomPrice : doubleRoomPrice;
            int total = calculateTotalPrice(nights, pricePerNight);
            cout << "You are staying " << nights << " nights and the total price is " << total << " euros." << endl;

        }
        else if (option == 2) {
            cout << "Search by: 1 for reservation number, 2 for name." << endl;
            int searchType = getValidInput();
            if (searchType == 1) {
                searchReservationNumber(reservations);
            }
            else if (searchType == 2) {
                searchByName(reservations);
            }
            else {
                cout << "Invalid search type." << endl;
            }
        }
        else if (option == 3) {
            cout << "Thanks for using the hotel reservation system!" << endl;
            break;
        }
        else {
            cout << "Invalid option. Please select 1, 2, or 3." << endl;
        }
    }

    return 0;
}