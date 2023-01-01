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
#include "FormBox.h"
#include "Form.h"
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <fstream>
#include <gl/glut.h>

//globals
const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 500;
const int WINDOW_POS_X = 100;
const int WINDOW_POS_Y = 100;
const int CALENDAR_X_OFFSET = 60;
const int CALENDAR_Y_OFFSET = 130;
const int CALENDAR_BUTTON_SIZE = 50;
const int CALENDAR_BUTTON_PADDING = 5;
int CURRENT_MONTH;
int CURRENT_YEAR;
int TOTAL_WEEKS;
int By;
const std::string taskFile = "C:\\Users\\camer\\source\\repos\\TaskOrganizer\\TaskOrganizer\\taskFile.txt";
const std::string dayNames[] = { "Sun", "Mon", "Tue", 
	"Wed", "Thu", "Fri", "Sat" };
const std::string monthNames[] = { "January", "February", 
	"March", "April", "May", "June", "July", "August", 
	"September", "October", "November", "December" };
const std::string header = "Task Organizer";
void* font = GLUT_BITMAP_9_BY_15;
void* smallFont = GLUT_BITMAP_8_BY_13;
int mainWindow;
std::vector<Button> calendarButtons;
std::vector<Button> UIButtons;
TaskList taskList;


//prototypes
void mainWindowDisplayCallback();
void drawText();
void drawButtons();
void createCalendarButtons(int, int);
void createUIButtons();
int getFirstDayOfWeek(int, int);
int getDaysInMonth(int);
tm getCurrentTime();
void drawCalendarText();
void clickCalendarDay(std::string);
void mouseCallback(int, int, int, int);
void switchMonth(std::string);



int main(int argc, char** argv)
{
	//init glut settings
	glutInit(&argc, argv);

	taskList.load(taskFile);

	taskList.displayTasks();

	taskList.save(taskFile);

	CURRENT_MONTH = getCurrentTime().tm_mon + 1;
	CURRENT_YEAR = getCurrentTime().tm_year + 1900;

	

	//taskList.save(taskFile);
	
	//init a glut window
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
	mainWindow = glutCreateWindow("Task Organizer");
	glutDisplayFunc(mainWindowDisplayCallback);
	glutMouseFunc(mouseCallback);
	glClearColor(.1, .1, .1, 0);
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);

	createCalendarButtons(CURRENT_MONTH, CURRENT_YEAR);
	createUIButtons();

	glutMainLoop();

	return -1;
}

void mainWindowDisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT);

	drawButtons();
	drawCalendarText();
	drawText();


	glFlush();
}

void drawText()
{
	/*
	int x = WINDOW_WIDTH / 2 - 25;
	int y = WINDOW_HEIGHT - 25;

	glRasterPos2d(x, y);

	for (auto c : header)
	{
		glutBitmapCharacter(font, c);
	}*/
}

void drawButtons()
{
	for (auto button : calendarButtons)
	{
		button.Draw();
	}
	for (auto button : UIButtons)
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
	//start calendarButtons on first day column
	int currentCol = firstDay;
	int currentRow = (firstDay == 0) ? 6 : 5;
	TOTAL_WEEKS = ((numDaysInMonth + firstDay - 1) / 7) + 1;
	std::cout << "Weeks for " << month << ", " << year << ": " << TOTAL_WEEKS << "\n";
	//calculate where the bottom line y of the box should be
	By = (TOTAL_WEEKS == 6) ? CALENDAR_Y_OFFSET - (CALENDAR_BUTTON_PADDING + CALENDAR_BUTTON_SIZE) - 20 : CALENDAR_Y_OFFSET - 20;
	By = (TOTAL_WEEKS != 4) ? By : CALENDAR_Y_OFFSET + (CALENDAR_BUTTON_PADDING + CALENDAR_BUTTON_SIZE) - 20;

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
		button.SetOnClick(clickCalendarDay);
		button.SetNumberOfTasks(taskList.getTasksPerDay(month, dayCount, year));
		if (dayCount == getCurrentTime().tm_mday && CURRENT_MONTH - 1 == getCurrentTime().tm_mon && CURRENT_YEAR - 1900 == getCurrentTime().tm_year) button.SetColor(0.17, 0.53, 1.00);
		calendarButtons.push_back(button);
		currentCol++;
	}


}

void createUIButtons()
{
	//set the x and y coords for next and previous month buttons
	int previousButtonX = CALENDAR_X_OFFSET + 15;
	int previousButtonY = 50;
	int nextButtonX = (CALENDAR_BUTTON_PADDING + CALENDAR_BUTTON_SIZE) * 7 + CALENDAR_X_OFFSET - 90;
	int nextButtonY = 50;

	//create next month and previous month buttons
	Button nextButton(nextButtonX, nextButtonY, 75, 40, "Next", .1, .1, .8, smallFont);
	Button previousButton(previousButtonX, previousButtonY, 75, 40, "Previous", .1, .1, .8, smallFont);
	nextButton.SetOnClick(switchMonth);
	previousButton.SetOnClick(switchMonth);
	UIButtons.push_back(nextButton);
	UIButtons.push_back(previousButton);
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
void drawCalendarText()
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
		for (int j = 0; j < (int)dayNames[i].length(); j++)
		{
			glutBitmapCharacter(smallFont, dayNames[i][j]);
		}

		// update the position for the next day of the week
		x += (CALENDAR_BUTTON_PADDING + CALENDAR_BUTTON_SIZE);
	}

	std::string monthName = monthNames[CURRENT_MONTH - 1];
	x = CALENDAR_X_OFFSET + ((7 * (CALENDAR_BUTTON_PADDING + CALENDAR_BUTTON_SIZE)) / 2) - 70;
	y = CALENDAR_Y_OFFSET + 5 * (CALENDAR_BUTTON_PADDING + CALENDAR_BUTTON_SIZE) + 40;

	glRasterPos2i(x, y);
	//write the month name at the top
	std::string monthTitle = monthNames[CURRENT_MONTH - 1] + " " + std::to_string(CURRENT_YEAR);
	for (auto c : monthTitle)
	{
		glutBitmapCharacter(font, c);
	}

	//draw a box around the calendar
	int Lx = CALENDAR_X_OFFSET - 20; //left x
	int Ty = CALENDAR_Y_OFFSET + 5 * (CALENDAR_BUTTON_PADDING + CALENDAR_BUTTON_SIZE) + 75; //top y
	int Rx = CALENDAR_X_OFFSET + (CALENDAR_BUTTON_PADDING + CALENDAR_BUTTON_SIZE) * 7 + 15; // right x
	//bottom y (By) declared globally and calulated in createCalendarButtons
	glColor3f(.9, .9, .9);
	glBegin(GL_LINE_LOOP);
		//top left
		glVertex2f(Lx, Ty); 
		//bottom left
		glVertex2f(Lx, By);
		//bottom right
		glVertex2f(Rx, By);
		//top right
		glVertex2f(Rx, Ty);
	glEnd();
}

//TODO: this function should open a new window with the tasks for that day
void clickCalendarDay(std::string id)
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
		for (auto button : calendarButtons)
		{
			if (button.IsMouseOver(x, WINDOW_HEIGHT - y))
			{
				button.Click();
				break;
			}
		}

		for (auto button : UIButtons)
		{
			if (button.IsMouseOver(x, WINDOW_HEIGHT - y))
			{
				button.Click();
				break;
			}
		}
		
	}
}

void switchMonth(std::string direction)
{
	calendarButtons.clear();
	if (direction == "Next")
	{
		CURRENT_MONTH += 1;
		if (CURRENT_MONTH >= 13)
		{
			CURRENT_MONTH = 1;
			CURRENT_YEAR++;
		}
	} 
	else if (direction == "Previous")
	{
		CURRENT_MONTH -= 1;
		if (CURRENT_MONTH <= 0)
		{
			CURRENT_MONTH = 12;
			CURRENT_YEAR--;
		}
	}
	createCalendarButtons(CURRENT_MONTH, CURRENT_YEAR);
	mainWindowDisplayCallback();
	
}


tm getCurrentTime()
{
	time_t currentTime;
	struct tm localTime;
	time(&currentTime);                  
	localtime_s(&localTime, &currentTime); 
	return localTime;
}

