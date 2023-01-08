#include "Form.h"
#include <string>
#ifdef _WIN32
	#include <gl/glut.h>
#else
	#include <GLUT/glut.h>
#endif

Form::Form(Task* task)
{ //(int x, int y, int width, int height, std::string text, int id)
	this->task = task;
	selectedBox = 0;
	FormBox titleBox(500, 450, 100, 35, task->GetTitle(), 0);
	time_t dueDateSeconds = task->GetDueDate();
	struct tm date;
	localtime_s(&date, &dueDateSeconds);
	FormBox dueDateDayBox(500, 375, 50, 35, std::to_string(date.tm_mday), 1);
	FormBox dueDateMonthBox(560, 375, 50, 35, std::to_string(date.tm_mon + 1), 2);
	FormBox dueDateYearBox(620, 375, 50, 35, std::to_string(date.tm_year + 1900), 3);
	FormBox descriptionBox(500, 300, 200, 100, task->GetDescription(), 4);
	FormBox priorityBox(500, 175, 100, 35, std::to_string(task->GetPriority()), 5);
	FormBox difficultyBox(650,  175, 100, 35, std::to_string(task->GetDifficulty()), 6);

	formBoxes.push_back(titleBox);
	formBoxes.push_back(dueDateDayBox);
	formBoxes.push_back(dueDateMonthBox);
	formBoxes.push_back(dueDateYearBox);
	formBoxes.push_back(descriptionBox);
	formBoxes.push_back(priorityBox);
	formBoxes.push_back(difficultyBox);
}

Form::Form()
{
	this->task = new Task();
	selectedBox = 0;
	FormBox titleBox(500, 450, 100, 35, task->GetTitle(), 0);
	time_t dueDateSeconds = task->GetDueDate();
	struct tm date;
	localtime_s(&date, &dueDateSeconds);
	FormBox dueDateDayBox(500, 375, 50, 35, std::to_string(date.tm_mday), 1);
	FormBox dueDateMonthBox(560, 375, 50, 35, std::to_string(date.tm_mon + 1), 2);
	FormBox dueDateYearBox(620, 375, 50, 35, std::to_string(date.tm_year + 1900), 3);
	FormBox descriptionBox(500, 300, 200, 100, task->GetDescription(), 4);
	FormBox priorityBox(500, 175, 100, 35, std::to_string(task->GetPriority()), 5);
	FormBox difficultyBox(650, 175, 100, 35, std::to_string(task->GetDifficulty()), 6);

	formBoxes.push_back(titleBox);
	formBoxes.push_back(dueDateDayBox);
	formBoxes.push_back(dueDateMonthBox);
	formBoxes.push_back(dueDateYearBox);
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
	std::string title = "Title";
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2i(540, 460);
	for (auto c : title)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
	}

    std::string DDMMYYYY = "DD/MM/YYYY";
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(540, 385);
    for (auto c : DDMMYYYY)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    std::string description = "Description";
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(540, 310);
    for (auto c : description)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    std::string priority = "Priority";
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(540, 185);
    for (auto c : priority)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    std::string difficulty = "Difficulty";
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(690, 185);
    for (auto c : difficulty)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
}