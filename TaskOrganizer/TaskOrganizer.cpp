/*
* Author: Cameron Weston
* Project: Task Organizer
* Description: This is the entry point for the task organizer program,
*	it uses the OpenGL Utility Toolkit for all of the rendering
*
*/
#include "Button.h"
#include "TaskList.h"
#include "Task.h"
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <fstream>
#include <gl/glut.h>

//globals
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const int WINDOW_POS_X = 100;
const int WINDOW_POS_Y = 100;
const int CALENDAR_X_OFFSET = 100;
const int CALENDAR_Y_OFFSET = 100;
const int CALENDAR_BUTTON_SIZE = 60;
const int CALENDAR_BUTTON_PADDING = 7;
const int CURRENT_MONTH = 12;
const int CURRENT_YEAR = 2022;
const std::string taskFile = "C:\\Users\\camer\\source\\repos\\TaskOrganizer\\TaskOrganizer\\taskFile.txt";
std::string dayNames[] = { "Sun", "Mon", "Tue", 
	"Wed", "Thu", "Fri", "Sat" };
std::string monthNames[] = { "January", "February", 
	"March", "April", "May", "June", "July", "August", 
	"September", "October", "November", "December" };
int mainWindow;
std::vector<Button> buttons;
TaskList taskList;


//prototypes
void mainWindowDisplayCallback();
void drawButtons();
void createCalendarButtons(int, int);
int getFirstDayOfWeek(int, int);
int getDaysInMonth(int);
int getCurrentDayOrMonth(bool);
void renderCalendarText();
void chooseDay(std::string);
void mouseCallback(int, int, int, int);

int main(int argc, char** argv)
{
	//init glut settings
	glutInit(&argc, argv);

	taskList.load(taskFile);

	taskList.displayTasks();

	taskList.save(taskFile);


	//taskList.save(taskFile);
	
	//init a glut window
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
	mainWindow = glutCreateWindow("Schedule Organizer");
	glutDisplayFunc(mainWindowDisplayCallback);
	glutMouseFunc(mouseCallback);
	glClearColor(.1, .1, .1, 0);
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);

	createCalendarButtons(CURRENT_MONTH, CURRENT_YEAR);

	glutMainLoop();

	return -1;
}

void mainWindowDisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT);

	drawButtons();
	renderCalendarText();

	glFlush();
}

void drawButtons()
{
	for (auto button : buttons)
	{
		button.Draw();
	}
}

void createCalendarButtons(int month, int year)
{
	//get number of days in current month
	int numDaysInMonth = getDaysInMonth(month);

	//get day of the week that the first day of the month falls on
	int firstDay = getFirstDayOfWeek(month, year);
	//start buttons on first day column
	int currentCol = firstDay;
	int currentRow = (firstDay == 0) ? 6 : 5;

	for (int dayCount = 1; dayCount < numDaysInMonth + 1; dayCount++)
	{
		if (currentCol % 7 == 0)
		{
			currentCol = 0;
			currentRow--;
		}
		int x = (currentCol * (CALENDAR_BUTTON_PADDING + CALENDAR_BUTTON_SIZE)) + CALENDAR_X_OFFSET;
		int y = currentRow * (CALENDAR_BUTTON_PADDING + CALENDAR_BUTTON_SIZE) + CALENDAR_Y_OFFSET;
		Button button(x, y, CALENDAR_BUTTON_SIZE, CALENDAR_BUTTON_SIZE, std::to_string(dayCount), .6, .6, .6);
		button.SetOnClick(chooseDay);
		button.setNumberOfTasks(taskList.getTasksPerDay(month, dayCount, year));
		if (dayCount == getCurrentDayOrMonth(true) && CURRENT_MONTH == getCurrentDayOrMonth(false)) button.SetColor(0.17, 0.53, 1.00);
		buttons.push_back(button);
		currentCol++;
	}
}

//returns the day of the week that the given month starts on
int getFirstDayOfWeek(int month, int year)
{
	time_t currentTime = time(nullptr);
	struct tm localTime;
	localtime_s(&localTime, &currentTime);
	localTime.tm_year = year - 1900;
	localTime.tm_mon = month - 1;
	localTime.tm_mday = 1;
	mktime(&localTime);
	return localTime.tm_wday;
}

//getDaysInMonth returns the number of days in the given month
int getDaysInMonth(int month)
{
	int numDaysInMonth = 0;
	switch (month - 1)
	{
	case 0: //January
	case 2: //March
	case 4: //May
	case 6: //July
	case 7: //August
	case 9: //October
	case 11: //December
		numDaysInMonth = 31;
		break;
	case 3: //April
	case 5: //June
	case 8: //September
	case 10: //November
		numDaysInMonth = 30;
		break;
	case 1: //February
		numDaysInMonth = 28;
		break;
	default:
		return -1;
	}
	return numDaysInMonth;
}

/*
* renderCalendarText renders the days of the week and month name text 
* It also draws a box around the calendar
* All reference constants are global and refer to the 
*	buttons' size, padding, and pos
*/
void renderCalendarText()
{
	// set the color of the text
	glColor3f(1.0, 1.0, 1.0);

	// set the position of the text
	int x = CALENDAR_X_OFFSET + (CALENDAR_BUTTON_SIZE / 3) - 4;
	int y = CALENDAR_Y_OFFSET + 5 * (CALENDAR_BUTTON_PADDING + CALENDAR_BUTTON_SIZE) + 10;

	// write the days of the week in a row
	for (int i = 0; i < 7; i++)
	{
		glRasterPos2i(x, y);

		// write the current day of the week
		for (int j = 0; j < dayNames[i].length(); j++)
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, dayNames[i][j]);
		}

		// update the position for the next day of the week
		x += (CALENDAR_BUTTON_PADDING + CALENDAR_BUTTON_SIZE);
	}

	std::string monthName = monthNames[CURRENT_MONTH - 1];
	x = CALENDAR_X_OFFSET + ((7 * (CALENDAR_BUTTON_PADDING + CALENDAR_BUTTON_SIZE)) / 2) - 50;
	y = CALENDAR_Y_OFFSET + 5 * (CALENDAR_BUTTON_PADDING + CALENDAR_BUTTON_SIZE) + 40;

	glRasterPos2i(x, y);
	//write the month name at the top
	for (int i = 0; i < monthNames[CURRENT_MONTH - 1].length(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, monthNames[CURRENT_MONTH - 1][i]);
	}

	//draw a box around the calendar
	glColor3f(.9, .9, .9);
	glBegin(GL_LINE_LOOP);
		//top left
		glVertex2f(CALENDAR_X_OFFSET - 20, 
			CALENDAR_Y_OFFSET + 5 * (CALENDAR_BUTTON_PADDING + CALENDAR_BUTTON_SIZE) + 75); 
		//bottom left
		glVertex2f(CALENDAR_X_OFFSET - 20, CALENDAR_Y_OFFSET - 20);
		//bottom right
		glVertex2f(CALENDAR_X_OFFSET + (CALENDAR_BUTTON_PADDING + CALENDAR_BUTTON_SIZE) * 7 + 15, CALENDAR_Y_OFFSET - 20);
		//top right
		glVertex2f(CALENDAR_X_OFFSET + (CALENDAR_BUTTON_PADDING + CALENDAR_BUTTON_SIZE) * 7 + 15, 
			CALENDAR_Y_OFFSET + 5 * (CALENDAR_BUTTON_PADDING + CALENDAR_BUTTON_SIZE) + 75);
	glEnd();
}

//TODO: this function should open a new window with the tasks for that day
void chooseDay(std::string id)
{
	std::cout << id << std::endl;
}

/*
* mouseCallback is called when an event with the mouse occurs
* 
* I use it to check if the user has pressed any calendar buttons
*/
void mouseCallback(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		for (auto button : buttons)
		{
			if (button.IsMouseOver(x, WINDOW_HEIGHT - y))
			{
				button.click();
				break;
			}
		}
	}
}

/*
* bool dayOrMonth:
*		function returns the day if this is true
*		returns the month (1 - 12) if false
* 
*/
int getCurrentDayOrMonth(bool dayOrMonth)
{
	time_t currentTime;
	struct tm localTime;
	time(&currentTime);                  
	localtime_s(&localTime, &currentTime); 
	int day = localTime.tm_mday;  
	int month = localTime.tm_mon;
	return (dayOrMonth) ? day : month + 1;
}