#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> 
#include <limits>  
#include <fstream> 

void clearScreen()
{
    std::cout << "\033[2J\033[H";
    std::cout.flush();
}

void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

class Todo
{
private:
    // Add your private members here
    static int nextId;
    int id;
    bool completed;
    std::string description;

public:
    // Add constructor and methods here
    Todo(std::string description = "")
    {
        this->id = nextId++;
        this->description = description;
        this->completed = false;
    }
    bool isCompleted() const { return completed; }
    int getId() const { return id; }
    std::string getDescription() const { return description; }
    void markCompleted() { this->completed = true; }
    void markPending() { this->completed = false; }
    void display()
    {
        // std::cout << "[" << (completed ? "✓" : " ") << "] "
        std::cout << "[" << (completed ? "X" : " ") << "] "
                  << "Todo: " << id << " - " << description << std::endl;
    }
};

class TodoManager
{
private:
    std::vector<Todo> todos;
    std::string filename = "todos.txt"; 

public:
    void addTodo(std::string description)
    {
        Todo todo = Todo(description);
        this->todos.push_back(todo);
    }
    void markCompleted(int id)
    {
        bool found = false;
        for (Todo &todo : this->todos)
        {
            if (todo.getId() == id)
            {
                todo.markCompleted();
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "Todo with ID " << id << " not found." << std::endl;
        }
    }
    void markPending(int id)
    {
        bool found = false;
        for (Todo &todo : this->todos)
        {
            if (todo.getId() == id)
            {
                todo.markPending();
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "Todo with ID " << id << " not found." << std::endl;
        }
    }
    void displayCompleted()
    {
        bool hasCompleted = false;
        for (Todo todo : this->todos)
        {
            if (todo.isCompleted())
            {
                todo.display();
                hasCompleted = true;
            }
        }
        if (!hasCompleted) {
            std::cout << "No completed todos found." << std::endl;
        }
    }
    void displayPending()
    {
        bool hasPending = false;
        for (Todo todo : this->todos)
        {
            if (!todo.isCompleted())
            {
                todo.display();
                hasPending = true;
            }
        }
        if (!hasPending) {
            std::cout << "No pending todos found." << std::endl;
        }
    }
    void displayAll()
    {
        if (this->todos.empty()) {
            std::cout << "No todos found. Add some todos first!" << std::endl;
        } else {
            for (Todo todo : this->todos)
            {
                todo.display();
            }
        }
    }
    void saveToFile()
    {
        std::ofstream file(this->filename);
        if (!file.is_open())
        {
            std::cerr << "Error opening file for writing: " << this->filename << std::endl;
            return;
        }
        for (const Todo &todo : this->todos)
        {
            file << todo.getId() << "|" << todo.getDescription() << "|" << (todo.isCompleted() ? "1" : "0") << std::endl;
        }
        file.close();
    }
    void loadFromFile()
    {
        std::ifstream file(this->filename);
        if (!file.is_open())
        {
            std::cout << "No existing todo file found. Starting fresh." << std::endl;
            return;
        }
        this->todos.clear();
        std::string line;
        while (std::getline(file, line))
        {
            size_t pos1 = line.find('|');
            size_t pos2 = line.rfind('|');
            if (pos1 == std::string::npos || pos2 == std::string::npos || pos1 == pos2)
                continue; // Invalid line format

            int id = std::stoi(line.substr(0, pos1));
            std::string description = line.substr(pos1 + 1, pos2 - pos1 - 1);
            bool completed = (line.substr(pos2 + 1) == "1");

            Todo todo(description);
            if (completed) {
                todo.markCompleted();
            }
            this->todos.push_back(todo);
        }
        file.close();
        if (!this->todos.empty()) {
            std::cout << "Loaded " << this->todos.size() << " todos from file." << std::endl;
        }
    }
};

int Todo::nextId = 1;

int main()
{
    TodoManager manager;
    manager.loadFromFile(); 
    int choice;

    while (true)
    {
        // Display menu
        std::cout << std::flush;
        std::cout << "=== TODO LIST MANAGER ===" << std::endl;
        std::cout << "1. Add Todo" << std::endl;
        std::cout << "2. View All Todos" << std::endl;
        std::cout << "3. Mark Todo Complete" << std::endl;
        std::cout << "4. Mark Todo Pending" << std::endl;
        std::cout << "5. View Completed Todos" << std::endl;
        std::cout << "6. View Pending Todos" << std::endl;
        std::cout << "7. Exit" << std::endl;

        std::cout << std::flush;
        std::cout << "Enter choice (1-7): ";
        std::cout << std::flush;
        
        std::cin >> choice;

        // Handle user choice with switch statement
        switch (choice)
        {
        case 1:
        {
            // Get todo description from user and add it
            clearScreen();
            std::string desc;
            std::cout << "Todo description: ";
            std::cin.ignore();            // Clear newline buffer
            std::getline(std::cin, desc); // Read full line
            manager.addTodo(desc);
            std::cout << "Todo added successfully." << std::endl
                      << "Press enter to return to menu..." << std::endl;
            clearInputBuffer();  // Clear any leftover input
            std::cin.get();      // Wait for Enter
            clearScreen();
            break;
        }
        case 2:
        {
            // Display all todos
            clearScreen();
            std::cout << "[ALL TODOS]" << std::endl;
            manager.displayAll();
            std::cout << "Press enter to return to menu..." << std::endl;
            clearInputBuffer();
            std::cin.get();
            clearScreen();
            break;
        }
        case 3:
        {
            // Get todo ID from user and mark complete
            clearScreen();
            int id;
            std::cout << "ID to mark complete: ";
            std::cin >> id;
            manager.markCompleted(id);
            std::cout << "Todo marked completed." << std::endl
                      << "Press enter to return to menu..." << std::endl;
            clearInputBuffer();
            std::cin.get();
            clearScreen();
            break;
        }
        case 4:
        {
            // Get todo ID from user and mark pending
            clearScreen();
            int id;
            std::cout << "ID to mark pending: ";
            std::cin >> id;
            manager.markPending(id);
            std::cout << "Todo marked pending." << std::endl
                      << "Press enter to return to menu..." << std::endl;
            clearInputBuffer();  // Clear any leftover input
            std::cin.get();
            clearScreen();
            break;
        }
        case 5:
        {
            // Display completed todos
            clearScreen();
            std::cout << "[COMPLETED TODOS]" << std::endl;
            manager.displayCompleted();
            std::cout << "Press enter to return to menu..." << std::endl;
            clearInputBuffer();  // Clear any leftover input
            std::cin.get();      // Wait for Enter
            clearScreen();
            break;
        }
        case 6:
        {
            // Display pending todos
            clearScreen();
            std::cout << "[PENDING TODOS]" << std::endl;
            manager.displayPending();
            std::cout << "Press enter to return to menu..." << std::endl;
            clearInputBuffer();  // Clear any leftover input
            std::cin.get();      // Wait for Enter
            clearScreen();
            break;
        }
        case 7:
            manager.saveToFile();
            std::cout << "Goodbye!" << std::endl;
            return 0;
        default:
        {
            std::cout << "Invalid choice. Please try again." << std::endl;
            std::cout << "Press enter to return to menu...";
            clearInputBuffer();
            std::cin.get();
            clearScreen();
            break;
        }
        }
    }

    return 0;
}