#include <iostream>
#include <vector>
#include <memory>
#include <limits>

using namespace std;

// Class to represent a task
class Task {
public:
    Task(const string& desc) : description(desc), isCompleted(false) {}

    string getDescription() const { return description; }
    bool getCompletionStatus() const { return isCompleted; }
    void markAsCompleted() { isCompleted = true; }

private:
    string description;
    bool isCompleted;
};

// Class to manage the task list
class TaskManager {
public:
    void addTask() {
        string taskDescription;
        cout << "Enter the task description: ";
        cin.ignore(); // To ignore the leftover newline character from previous input
        getline(cin, taskDescription);

        tasks.push_back(make_unique<Task>(taskDescription));
        cout << "Task added successfully!" << endl;
    }

    void viewTasks() const {
        if (tasks.empty()) {
            cout << "No tasks available." << endl;
            return;
        }

        cout << "Your To-Do List:" << endl;
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". " << tasks[i]->getDescription();
            if (tasks[i]->getCompletionStatus()) {
                cout << " [Completed]";
            }
            cout << endl;
        }
    }

    void markTaskAsCompleted() {
        int taskNumber;
        cout << "Enter the task number to mark as completed: ";
        cin >> taskNumber;

        if (taskNumber > 0 && taskNumber <= tasks.size()) {
            tasks[taskNumber - 1]->markAsCompleted();
            cout << "Task marked as completed!" << endl;
        } else {
            cout << "Invalid task number!" << endl;
        }
    }

    void deleteTask() {
        int taskNumber;
        cout << "Enter the task number to delete: ";
        cin >> taskNumber;

        if (taskNumber > 0 && taskNumber <= tasks.size()) {
            tasks.erase(tasks.begin() + (taskNumber - 1));
            cout << "Task deleted successfully!" << endl;
        } else {
            cout << "Invalid task number!" << endl;
        }
    }

private:
    vector<unique_ptr<Task>> tasks;
};

int main() {
    TaskManager manager;
    int choice;

    while (true) {
        // Display menu
        cout << "\nTo-Do List Manager" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. View Tasks" << endl;
        cout << "3. Mark Task as Completed" << endl;
        cout << "4. Delete Task" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";

        // Handle invalid input
        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }

        // Perform action based on user's choice
        switch (choice) {
            case 1:
                manager.addTask();
                break;
            case 2:
                manager.viewTasks();
                break;
            case 3:
                manager.markTaskAsCompleted();
                break;
            case 4:
                manager.deleteTask();
                break;
            case 5:
                cout << "Exiting the To-Do List Manager. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
