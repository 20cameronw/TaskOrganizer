#include "TaskList.h"
#include <fstream>
#include <ctime>
#include <iostream>
#include <string>

//adds a new task to the list sorted by date
void TaskList::addTask(Task task) 
{
    Node* newNode = new Node(task);
    if (head == nullptr || head->task.GetDueDate() > task.GetDueDate()) 
    {
        newNode->next = head;
        head = newNode;
    }
    else 
    {
        Node* current = head;
        while (current->next != nullptr && current->next->task.GetDueDate() <= task.GetDueDate()) 
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    size++;
}


void TaskList::deleteTask(int index) 
{
    if (index < 0 || index >= size) 
        return;

    Node* current = head;
    if (index == 0) 
    {
        head = head->next;
        delete current;
    }
    else 
    {
        Node* previous = nullptr;
        for (int i = 0; i < index; i++)
        {
            previous = current;
            current = current->next;
        }
        previous->next = current->next;
        delete current;
    }
    size--;
}

void TaskList::editTask(int index, Task task)
{
    /*
    Task& target = getTask(index);
    target = task; */

    //OR

    deleteTask(index);
    addTask(task);
}

Task& TaskList::getTask(int index)
{
    Node* current = head;
    for (int i = 0; i < index; i++) 
    {
        current = current->next;
    }
    return current->task;
}

int TaskList::getSize() const
{
    return size;
}

void TaskList::displayTasks() const
{
    Node* current = head;
    while (current != nullptr)
    {
        current->task.displayToConsole();
        current = current->next;
    }
}

int TaskList::getTasksPerDay(int month, int day, int year)
{
  int count = 0;
  
  Node* current = head;
  while (current != nullptr)
  {
    time_t dueDate = current->task.GetDueDate();
    // Convert the due date to a tm struct
    struct tm timeStruct;
    localtime_s(&timeStruct, &dueDate);
    // Check if the due date of the task is on the same day as the given time
    //std::cout << "\nComparing: " << timeStruct.tm_mon << " == " << month << "\n";
    if (timeStruct.tm_mday == day &&
        timeStruct.tm_mon == month - 1 && //tm_mon stored as 0 - 11
        timeStruct.tm_year == year - 1900) //tm_year stored as # since 1900
    {
      count++;
    }
    current = current->next;
  }
  return count;
}

void TaskList::save(std::string file)
{
    std::fstream outFile(file);

    for (int i = 0; i < size; i++)
    {
        Task currentTask = getTask(i);
        outFile << currentTask.GetTitle() << std::endl;
        outFile << currentTask.GetDescription() << std::endl;
        time_t date = currentTask.GetDueDate();
        struct tm timeStruct;
        localtime_s(&timeStruct, &date);
        outFile << timeStruct.tm_year << " " << timeStruct.tm_mon << " "
            << timeStruct.tm_mday << " " << timeStruct.tm_hour << " " 
            << timeStruct.tm_min << std::endl;
        outFile << currentTask.GetPriority() << std::endl;
        outFile << currentTask.GetDifficulty() << std::endl;
        if (i != size - 1)
            outFile << std::endl;
    }

    outFile.close();
}

void TaskList::load(std::string file)
{
    //std::cout << "Beginning loading sequence...\n";
    std::ifstream inFile(file);

    while (!inFile.eof())
    {
        //std::cout << "Begin load object...\n";
        std::string title, description, year, mon, day, hour, min, prior, diffi, empty;
        int priority, difficulty;
        
        std::getline(inFile, title);
        //std::cout << "Loaded title...\n";
        std::getline(inFile, description);
        //std::cout << "Loaded descr...\n";
        inFile >> year >> mon >> day >> hour >> min;
        std::getline(inFile, empty);
        //std::cout << "Loaded time...\n";
        std::getline(inFile, prior);
        //std::cout << "Loaded prior...\n";
        std::getline(inFile, diffi);
        //std::cout << "Loaded diffi...\n";
        std::getline(inFile, empty);
        //std::cout << "Loaded diffi...\n";
        struct tm timeStruct;
        timeStruct.tm_year = stoi(year);
        timeStruct.tm_mon = stoi(mon);
        timeStruct.tm_mday = stoi(day);
        timeStruct.tm_hour = stoi(hour);
        timeStruct.tm_min = stoi(min);
        timeStruct.tm_sec = 0;
        time_t dueDate = mktime(&timeStruct);

        std::cout << "Loaded task due at:\n\tMonth: " << timeStruct.tm_mon + 1
            << "\n\tDay: " << timeStruct.tm_mday << "\n\tYear: " << timeStruct.tm_year + 1900 << "\n";
        //std::cout << "time_t obj...\n";
        Task currentTask(dueDate, stoi(prior), stoi(diffi), title, description);
        //std::cout << "created task obj...\n";
        addTask(currentTask);
    }

    inFile.close();
}
