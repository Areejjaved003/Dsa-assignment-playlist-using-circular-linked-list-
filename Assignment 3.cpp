#include <iostream>
#include <string>
using namespace std;

struct EventNode {
    string eventName;
    EventNode* next;

    EventNode(const string& name) : eventName(name), next(nullptr) {}
};

class CircularCalendar {
private:
    EventNode* head;
    EventNode* tail;
    EventNode* currentEvent;

public:
    CircularCalendar() : head(nullptr), tail(nullptr), currentEvent(nullptr) {}

    ~CircularCalendar() {
        if (head == nullptr) return;
        EventNode* current = head;
        EventNode* nextNode;
        do {
            nextNode = current->next;
            delete current;
            current = nextNode;
        } while (current != head);
    }

    void addEvent(const string& eventName) {
        EventNode* newNode = new EventNode(eventName);
        if (head == nullptr) {
            head = tail = newNode;
            tail->next = head;
        } else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head;
        }
        cout << "Event \"" << eventName << "\" added.\n";
    }

    void removeEvent(const string& eventName) {
        if (head == nullptr) {
            cout << "No events to remove.\n";
            return;
        }

        EventNode* current = head;
        EventNode* previous = nullptr;

        do {
            if (current->eventName == eventName) {
                if (current == head && current == tail) {
                    head = tail = nullptr;
                } else if (current == head) {
                    head = head->next;
                    tail->next = head;
                } else if (current == tail) {
                    tail = previous;
                    tail->next = head;
                } else {
                    previous->next = current->next;
                }
                delete current;
                cout << "Event \"" << eventName << "\" removed.\n";
                return;
            }
            previous = current;
            current = current->next;
        } while (current != head);

        cout << "Event \"" << eventName << "\" not found.\n";
    }

    void showNextEvent() {
        if (head == nullptr) {
            cout << " No upcoming events.\n";
            return;
        }
        if (currentEvent == nullptr)
            currentEvent = head;

        cout << " Next Event: " << currentEvent->eventName << "\n";
        currentEvent = currentEvent->next;
    }

    void displayAllEvents() {
        if (head == nullptr) {
            cout << " No events in the calendar.\n";
            return;
        }

        EventNode* current = head;
        int index = 1;
        cout << "\n All Scheduled Events:\n";
        do {
            cout << index++ << ". " << current->eventName << endl;
            current = current->next;
        } while (current != head);
    }
};

int main() {
    CircularCalendar calendar;
    int choice;
    string eventName;

    do {
        cout << "\n===== CIRCULAR CALENDAR MENU =====\n";
        cout << "1. Add Event\n";
        cout << "2. Remove Event\n";
        cout << "3. Display All Events\n";
        cout << "4. Show Next Event\n";
        cout << "5. Exit\n";
        cout << "Choose an option (1-5): ";
        cin >> choice;
        cin.ignore(); // To handle getline after cin

        switch (choice) {
            case 1:
                cout << "Enter event name: ";
                getline(cin, eventName);
                calendar.addEvent(eventName);
                break;
            case 2:
                cout << "Enter event name to remove: ";
                getline(cin, eventName);
                calendar.removeEvent(eventName);
                break;
            case 3:
                calendar.displayAllEvents();
                break;
            case 4:
                calendar.showNextEvent();
                break;
            case 5:
                cout << "Exiting Calendar.Goodbye!\n";
                break;
            default:
                cout << "Invalid choice.Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
