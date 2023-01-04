#pragma once

#include <functional>
#include <string>
#include <vector>
#include "Task.h"

//This class is for a simple button
//A button also represents a day on the calendar (hence numberOfTasks)
class Button {
private:
	int x;
	int y;
	int width;
	int height;
	std::string text;
	int textOffsetX;
	int textOffsetY;
	float color[3];
	int numberOfTasks;
	// The callback function to be called when the button is clicked
	std::function<void(std::string)> onclick;

	void* font;

public:
	Button(int x, int y, int width, int height, std::string text, float r, float g, float b);
	Button(int x, int y, int width, int height, std::string text, float r, float g, float b, void* font);
	// Set the callback function that should be called when the button is clicked
	void SetOnClick(const std::function<void(std::string)>& onclick_) { onclick = onclick_; }
	// Draw the button
	void Draw();
	// Check if the mouse is currently over the button
	bool IsMouseOver(int, int);
	int GetX();
	int GetY();
	void SetColor(float r, float g, float b);
	void Click();
	void SetNumberOfTasks(int);
	void setTextOffsetY(int);
};
