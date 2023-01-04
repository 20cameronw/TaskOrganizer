#include "Form.h"

Form::Form(Task* task)
{ //(int x, int y, int width, int height, std::string text, int id)
	this->task = task;
	selectedBox = 0;
	FormBox titleBox(500, 450, 100, 35, task->GetTitle(), 0);
	FormBox dueDateBox(500, 375, 200, 35, std::to_string(task->GetDueDate()), 1);
	FormBox descriptionBox(500, 300, 200, 100, task->GetDescription(), 2);
	FormBox priorityBox(500, 175, 100, 35, std::to_string(task->GetPriority()), 3);
	FormBox difficultyBox(650,  175, 100, 35, std::to_string(task->GetDifficulty()), 4);

	formBoxes.push_back(titleBox);
	formBoxes.push_back(dueDateBox);
	formBoxes.push_back(descriptionBox);
	formBoxes.push_back(priorityBox);
	formBoxes.push_back(difficultyBox);
}

Form::Form()
{
	this->task = new Task();
	selectedBox = 0;
	FormBox titleBox(500, 450, 100, 35, task->GetTitle(), 0);
	FormBox dueDateBox(500, 375, 200, 35, std::to_string(task->GetDueDate()), 1);
	FormBox descriptionBox(500, 300, 200, 100, task->GetDescription(), 2);
	FormBox priorityBox(500, 175, 100, 35, std::to_string(task->GetPriority()), 3);
	FormBox difficultyBox(650, 175, 100, 35, std::to_string(task->GetDifficulty()), 4);

	formBoxes.push_back(titleBox);
	formBoxes.push_back(dueDateBox);
	formBoxes.push_back(descriptionBox);
	formBoxes.push_back(priorityBox);
	formBoxes.push_back(difficultyBox);
}

void Form::Draw() const
{
	for (auto it : formBoxes)
	{
		it.Draw();
	}
}