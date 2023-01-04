#pragma once

#include <string>
#include <ctime>

class Task
{
private:
	time_t dueDate;
	// priority level of the task, from 1 (lowest) to 10 (highest)
	int priority;
	// difficulty level of the task, from 1 (easiest) to 10 (hardest)
	int difficulty;
	std::string title;
	std::string description;

public:
	Task(time_t dueDate, int priority, int difficulty, std::string title, std::string description);
	Task();


	//getters 
	time_t GetDueDate() const;            
	int GetPriority() const;
	int GetDifficulty() const;
	std::string GetDescription() const;
	std::string GetTitle() const;
	void displayToConsole() const;

	//setters
	void SetDueDate(time_t dueDate);
	void SetPriority(int priority);
	void SetTitle(std::string title);
	void SetDifficulty(int difficulty);
	void SetDescription(std::string description);
};
