# Priority Hotel Management System (DSA)
**Developed by:** Muhammad Qasim Imran
**University:** University of Management and Technology (UMT)

## 🚀 Project Overview
This system is a robust demonstration of custom-engineered data structures used to solve real-world logistical challenges. It manages hotel room inventory and processes guest bookings through a multi-level priority system, ensuring that high-priority requests are handled first.

## 🛠 Data Structures & Logic
Rather than using standard libraries, this project implements custom-built templates to demonstrate a deep understanding of memory management and algorithmic efficiency:

* **Linked List:** Used to manage the hotel's room inventory, allowing for dynamic insertion and efficient traversal of room records.
* **Custom Stack Template:** Implemented to track booking history. It follows the LIFO (Last-In, First-Out) principle, allowing users to view the most recent activity.
* **Multi-Level Priority Queues:** Guest requests are sorted into three distinct queues (High, Medium, and Low). The system processes guests based on these priority tiers to simulate a real-world VIP/Standard service flow.
* **Memory Safety (Rule of Three):** The custom templates include deep-copy constructors and destructors to prevent memory leaks and ensure robust data handling.

## 💻 Tech Stack
* **Language:** C++
* **Concepts:** Template Programming, Dynamic Memory Management, Pointers, Linked Lists, Stacks, and Queues.
* **Architecture:** Modular and Encapsulated Class Design.

## 📸 Key Features
1.  **Inventory Management:** View current room availability and status.
2.  **Priority Processing:** Automatically handle guests based on their importance level.
3.  **Activity History:** Review previous bookings in reverse chronological order.
4.  **Validation Engine:** Prevents duplicate bookings or assignments to occupied rooms.

## ⚙️ How to Run
1. Clone this repository to your local machine.
2. Compile the source code using any C++ compiler (e.g., `g++ Project.cpp -o HotelSystem`).
3. Run the executable to start the management console.
