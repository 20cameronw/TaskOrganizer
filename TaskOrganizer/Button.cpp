#include "Button.h"
#include <GL/glut.h>

Button::Button(int x, int y, int width, int height, std::string text, float r, float g, float b)
	: x(x), y(y), width(width), height(height), text(text), numberOfTasks(0)
{
	SetColor(r, g, b);
	font = GLUT_BITMAP_HELVETICA_18;
}

Button::Button(int x, int y, int width, int height, std::string text, float r, float g, float b, void* font)
	: x(x), y(y), width(width), height(height), text(text), numberOfTasks(0), font(font)
{
	SetColor(r, g, b);
}

void Button::Draw()
{
	glColor3fv(color);
	// Draw the button fill
	glBegin(GL_POLYGON);
		glVertex2i(x, y);
		glVertex2i(x + width, y);
		glVertex2i(x + width, y - height);
		glVertex2i(x, y - height);
	glEnd();

	// Draw the button outline
	glColor3f(0, 0, 0);
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
		glVertex2i(x, y);
		glVertex2i(x + width, y);
		glVertex2i(x + width, y - height);
		glVertex2i(x, y - height);
	glEnd();

	// Draw the day number
	glRasterPos2i(x + 3, y - 17);
	for (auto c : text)
	{
		glutBitmapCharacter(this->font, c);
	}

	if (numberOfTasks != 0)
	{
		std::string numTasks = std::to_string(numberOfTasks) + " tasks";
		glRasterPos2i(x + (width / 2) - 17, y - (height / 2) - 5);
		for (auto c : numTasks)
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
		}
	}
}

bool Button::IsMouseOver(int mouseX, int mouseY)
{
	return (mouseX >= x && mouseX <= x + width && mouseY <= y && mouseY >= y - height);
}

int Button::GetX()
{
	return x;
}

int Button::GetY()
{
	return y;
}

void Button::SetColor(float r, float g, float b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

void Button::Click()
{
	onclick(text);
}

void Button::SetNumberOfTasks(int num)
{
	numberOfTasks = num;
}
