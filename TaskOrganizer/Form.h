#pragma once

#include "FormBox.h"
#include "Task.h"
#include <vector>

class Form
{
private:
	Task* task;
	std::vector<FormBox> formBoxes;
	int selectedBox;

public:
	Form(Task*); //if task is given then we are editing that task
	Form();		 //if task not given we are creating a new one 

	void selectTask(int);

};

