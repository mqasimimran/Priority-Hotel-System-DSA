#include <iostream>
#include <string>
#include <vector>

using namespace std;

// --- LINKED LIST NODE ---
class Node {
public:
    int room;
    int floor;
    string roomId;
    string roomType;
    string status;
    Node* next;

    Node(int r, int d, string id, string type, string stat) 
        : room(r), floor(d), roomId(id), roomType(type), status(stat), next(nullptr) {}
};

// ---  HOTEL (LINKED LIST) ---
class Hotel {
    Node* head;
    Node* tail;

public:
    Hotel() : head(nullptr), tail(nullptr) {}

    ~Hotel() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    void insertRoom(int room, int floor, string id, string type, string stat) {
        Node* newNode = new Node(room, floor, id, type, stat);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void displayMenu() const {
        cout << "\n--- Current Hotel Inventory ---\n";
        Node* temp = head;
        while (temp != nullptr) {
            cout << "[" << temp->roomId << "] Type: " << temp->roomType 
                 << " | Floor: " << temp->floor 
                 << " | Status: " << temp->status << endl;
            temp = temp->next;
        }
    }

    bool isValidAndAvailable(const string& id) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->roomId == id) {
                if (temp->status == "Available") return true;
                cout << "\nError: Room " << id << " is already occupied!" << endl;
                return false;
            }
            temp = temp->next;
        }
        cout << "\nError: Room ID not found!" << endl;
        return false;
    }
};

// --- TEMPLATE QUEUE  ---
template <typename T>
class Queue {
private:
    T* arr;
    int front, rear, capacity, size;

public:
    Queue(int c) : capacity(c), front(0), rear(-1), size(0) {
        arr = new T[capacity];
    }

    ~Queue() { delete[] arr; }

    // Deep Copy Constructor
    Queue(const Queue& other) {
        capacity = other.capacity;
        front = other.front;
        rear = other.rear;
        size = other.size;
        arr = new T[capacity];
        for (int i = 0; i < capacity; i++) arr[i] = other.arr[i];
    }

    bool isEmpty() const { return size == 0; }
    bool isFull() const { return size == capacity; }

    void enqueue(const T& item) {
        if (!isFull()) {
            rear = (rear + 1) % capacity;
            arr[rear] = item;
            size++;
        }
    }

    void dequeue() {
        if (!isEmpty()) {
            front = (front + 1) % capacity;
            size--;
        }
    }

    T* getFront() {
        return isEmpty() ? nullptr : &arr[front];
    }
};

// --- TEMPLATE STACK  ---
template <typename T>
class Stack {
private:
    T* arr;
    int top, capacity;

public:
    Stack(int c) : capacity(c), top(-1) {
        arr = new T[capacity];
    }

    ~Stack() { delete[] arr; }

    // Deep Copy Constructor for safe History viewing
    Stack(const Stack& other) {
        capacity = other.capacity;
        top = other.top;
        arr = new T[capacity];
        for (int i = 0; i <= top; i++) arr[i] = other.arr[i];
    }

    // Assignment Operator
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            delete[] arr;
            capacity = other.capacity;
            top = other.top;
            arr = new T[capacity];
            for (int i = 0; i <= top; i++) arr[i] = other.arr[i];
        }
        return *this;
    }

    bool isEmpty() const { return top == -1; }
    bool isFull() const { return top == capacity - 1; }

    void push(const T& item) {
        if (!isFull()) arr[++top] = item;
    }

    void pop() {
        if (!isEmpty()) top--;
    }

    T* peek() {
        return isEmpty() ? nullptr : &arr[top];
    }
};

// --- BOOKING REQUEST ---
class BookingRequest {
    string name, roomId, phone, priority;

public:
    BookingRequest() {}
    BookingRequest(string n, string r, string p, string pr)
        : name(n), roomId(r), phone(p), priority(pr) {}

    void display() const {
        cout << " [Request] Guest: " << name << " | Room: " << roomId 
             << " | Priority: " << priority << endl;
    }

    string getPriority() const { return priority; }
};

// --- GLOBAL MANAGERS ---
Queue<BookingRequest> highQ(10), medQ(10), lowQ(10);
Stack<BookingRequest> history(50);

void processBooking(Hotel& hotel) {
    string name, phone, roomId, priority;
    cout << "\n--- New Booking Request ---\n";
    cout << "Guest Name: "; cin.ignore(); getline(cin, name);
    cout << "Phone: "; getline(cin, phone);
    cout << "Room ID: "; getline(cin, roomId);
    cout << "Priority (High/Medium/Low): "; cin >> priority;

    if (hotel.isValidAndAvailable(roomId)) {
        BookingRequest req(name, roomId, phone, priority);
        history.push(req);

        if (priority == "High" || priority == "high") highQ.enqueue(req);
        else if (priority == "Medium" || priority == "medium") medQ.enqueue(req);
        else lowQ.enqueue(req);

        cout << "Successfully added to the processing queue." << endl;
    }
}

void runService() {
    cout << "\n--- Processing Next Available Guest ---\n";
    BookingRequest* target = nullptr;

    if (!highQ.isEmpty()) { target = highQ.getFront(); highQ.dequeue(); }
    else if (!medQ.isEmpty()) { target = medQ.getFront(); medQ.dequeue(); }
    else if (!lowQ.isEmpty()) { target = lowQ.getFront(); lowQ.dequeue(); }
    else { cout << "No pending requests." << endl; return; }

    if (target) target->display();
}

void showHistory() {
    if (history.isEmpty()) {
        cout << "No history found." << endl;
        return;
    }
    Stack<BookingRequest> temp = history; // deep copy
    cout << "\n--- Recent Activity (LIFO) ---\n";
    while (!temp.isEmpty()) {
        temp.peek()->display();
        temp.pop();
    }
}

int main() {
    Hotel hotel;
    // Initial Setup
    hotel.insertRoom(101, 1, "R101", "Deluxe", "Available");
    hotel.insertRoom(102, 1, "R102", "Suite", "Occupied");
    hotel.insertRoom(201, 2, "R201", "Standard", "Available");
    hotel.insertRoom(301, 3, "R301", "Penthouse", "Available");

    int choice;
    do {
        cout << "\n===============================";
        cout << "\n HOTEL MANAGEMENT SYSTEM (DSA)";
        cout << "\n===============================";
        cout << "\n1. Display Room Menu";
        cout << "\n2. Book a Room (Priority Queue)";
        cout << "\n3. Process Next Guest";
        cout << "\n4. View Booking History (Stack)";
        cout << "\n5. Exit";
        cout << "\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1: hotel.displayMenu(); break;
            case 2: processBooking(hotel); break;
            case 3: runService(); break;
            case 4: showHistory(); break;
            case 5: cout << "System shutting down...\n"; break;
            default: cout << "Invalid entry.\n";
        }
    } while (choice != 5);

    return 0;
}