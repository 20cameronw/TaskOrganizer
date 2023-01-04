#pragma once

#include "Task.h"
#include <ctime>

//this class hold methods for operating with a list of tasks
//implemented via singly linked list
class TaskList
{
private:
	struct Node
	{
		Task task;
		Node* next;

		Node(Task task) : task(task), next(nullptr) {}
	};

	Node* head;
	int size;

public:
	TaskList() : head(nullptr), size(0) {}

	void addTask(Task);
	void deleteTask(int);
	void editTask(int, Task);
	Task& getTask(int);
	int getSize() const;
	void displayTasks() const;
	int getTasksPerDay(int, int, int);
	void save(std::string);
	void load(std::string);
	TaskList* sortByPriority() const;
	TaskList* sortByDueDate() const;
	TaskList* sortByDifficulty() const;
	TaskList* sortByDay() const;
};

