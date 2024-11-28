#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <thread>

//Data structures
struct Task {
    int id;
    std::string title;
    std::string category; // e.g., Daily, Weekly, Monthly, Yearly
    std::string deadline; // Format: YYYY-MM-DD
    std::string description;
    bool completed;
};
//user Profile
struct UserProfile {
    std::string username;
    std::string password;
    std::vector<Task> tasks;
};
//profile management
UserProfile createProfile() {
    UserProfile user;
    std::cout << "Create a Profile\n";
    std::cout << "Enter Username: ";
    std::cin >> user.username;
    std::cout << "Enter Password: ";
    std::cin >> user.password;
    std::cout << "Profile Created Successfully!\n";
    return user;
}
//Authentication
bool authenticate(const UserProfile& user) {
    std::string username, password;
    std::cout << "Login to your Profile\n";
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;

    if (username == user.username && password == user.password) {
        std::cout << "Login Successful!\n";
        return true;
    }
    std::cout << "Invalid Credentials. Try Again.\n";
    return false;
}
//Add task
void addTask(UserProfile& user) {
    Task task;
    task.id = user.tasks.size() + 1; // Auto-increment task ID
    std::cin.ignore(); // Clear input buffer
    std::cout << "Enter Task Title: ";
    std::getline(std::cin, task.title);
    std::cout << "Enter Task Category (Daily/Weekly/Monthly/Yearly): ";
    std::getline(std::cin, task.category);
    std::cout << "Enter Task Deadline (YYYY-MM-DD): ";
    std::getline(std::cin, task.deadline);
    std::cout << "Enter Task Description: ";
    std::getline(std::cin, task.description);
    task.completed = false;
    user.tasks.push_back(task);
    std::cout << "Task Added Successfully!\n";
}
//Remove Task
void removeTask(UserProfile& user) {
    int taskId;
    std::cout << "Enter Task ID to Remove: ";
    std::cin >> taskId;

    auto it = std::remove_if(user.tasks.begin(), user.tasks.end(),
        [taskId](const Task& task) { return task.id == taskId; });

    if (it != user.tasks.end()) {
        user.tasks.erase(it, user.tasks.end());
        std::cout << "Task Removed Successfully!\n";
    }
    else {
        std::cout << "Task Not Found!\n";
    }
}
//Display Task
void displayTasks(const UserProfile& user) {
    if (user.tasks.empty()) {
        std::cout << "No Tasks Found.\n";
        return;
    }

    std::cout << std::setw(5) << "ID"
        << std::setw(20) << "Title"
        << std::setw(15) << "Category"
        << std::setw(15) << "Deadline"
        << std::setw(10) << "Status\n";

    for (const auto& task : user.tasks) {
        std::cout << std::setw(5) << task.id
            << std::setw(20) << task.title
            << std::setw(15) << task.category
            << std::setw(15) << task.deadline
            << std::setw(10) << (task.completed ? "Done" : "Pending") << "\n";
    }
}
//Time saving statistics
void timeSavingInsights(const UserProfile& user) {
    int completed = 0;
    for (const auto& task : user.tasks) {
        if (task.completed) completed++;
    }
    int total = user.tasks.size();
    std::cout << "Total Tasks: " << total << "\n";
    std::cout << "Completed Tasks: " << completed << "\n";
    if (total > 0) {
        std::cout << "Completion Rate: " << (completed * 100 / total) << "%\n";
    }
}
//csv file saving
void saveTasksToCSV(const UserProfile& user, const std::string& filename) {
    std::ofstream file(filename);

    if (!file) {
        std::cerr << "Error creating file!\n";
        return;
    }

    file << "ID,Title,Category,Deadline,Description,Status\n";
    for (const auto& task : user.tasks) {
        file << task.id << ","
            << "\"" << task.title << "\","
            << task.category << ","
            << task.deadline << ","
            << "\"" << task.description << "\","
            << (task.completed ? "Completed" : "Pending") << "\n";
    }

    file.close();
    std::cout << "Tasks saved to " << filename << " successfully!\n";
}
//Mainmenu
int main() {
    UserProfile user = createProfile();
    if (!authenticate(user)) return 1;

    int choice;
    while (true) {
        std::cout << "\n--- OmniPlanner Menu ---\n"
            << "1. Add Task\n"
            << "2. Remove Task\n"
            << "3. Display Tasks\n"
            << "4. Time-Saving Insights\n"
            << "5. Save Tasks to CSV\n"
            << "6. Exit\n"
            << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            addTask(user);
            break;
        case 2:
            removeTask(user);
            break;
        case 3:
            displayTasks(user);
            break;
        case 4:
            timeSavingInsights(user);
            break;
        case 5:
            saveTasksToCSV(user, "tasks.csv");
            break;
        case 6:
            std::cout << "Exiting OmniPlanner. Goodbye!\n";
            return 0;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    }
}
