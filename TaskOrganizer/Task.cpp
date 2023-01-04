#include "Task.h"
#include <iostream>

//constructor
Task::Task(time_t dueDate, int priority, int difficulty, std::string title, std::string description)
	: dueDate(dueDate), priority(priority), difficulty(difficulty), title(title), description(description) {}

//default
Task::Task()
{
	dueDate = 0;
	priority = 0;
	difficulty = 0;
	title = "New Task";
	description = "Description";
}

//getters and setters 
time_t Task::GetDueDate() const 
{ 
	return dueDate; 
}

void Task::SetDueDate(time_t _dueDate) 
{ 
	dueDate = _dueDate; 
}

int Task::GetPriority() const 
{ 
	return priority; 
}

void Task::SetPriority(int _priority) 
{ 
	priority = _priority;
}

int Task::GetDifficulty() const 
{ 
	return difficulty; 
}
void Task::SetDifficulty(int _difficulty) 
{ 
	difficulty = _difficulty; 
}

std::string Task::GetTitle() const 
{ 
	return title; 
}

void Task::displayToConsole() const
{
	std::cout << "********** TASK **********\n";
	std::cout << GetTitle() << "\n";
	std::cout << " - " << GetDescription() << "\n";
	std::cout << std::to_string(GetDueDate()) << "\n";
	std::cout << "Priority:\t" << GetPriority() << "\n";
	std::cout << "Difficulty:\t" << GetDifficulty() << "\n\n";
}

void Task::SetTitle(std::string _title) 
{ 
	title = _title; 
}

std::string Task::GetDescription() const 
{ 
	return description; 
}

void Task::SetDescription(std::string _description) 
{ 
	description = _description; 
}
