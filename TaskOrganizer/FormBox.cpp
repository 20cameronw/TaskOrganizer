#include "FormBox.h"
#include <gl/glut.h>

FormBox::FormBox(int x, int y, int width, int height, std::string text, int id)
	: x(x), y(y), width(width), height(height), text(text), id(id)
{
	SetColor(0, 0, 0);
	borderWidth = 3;
	font = GLUT_BITMAP_HELVETICA_12;
}

void FormBox::SetColor(float r, float g, float b)
{
	borderColor[0] = r;
	borderColor[1] = g;
	borderColor[2] = b;
}

bool FormBox::IsMouseOver(int mouseX, int mouseY) const
{
	return (mouseX >= x && mouseX <= x + width && mouseY <= y && mouseY >= y - height);
}

void FormBox::UpdateText(std::string _text)
{
	text = _text;
	Draw();
}

void FormBox::Draw() const
{
	// Draw the button outline
	glColor3fv(borderColor);
	glLineWidth(borderWidth);
	glBegin(GL_LINE_LOOP);
		glVertex2i(x, y);
		glVertex2i(x + width, y);
		glVertex2i(x + width, y - height);
		glVertex2i(x, y - height);
	glEnd();

	//draw the text
	glRasterPos2i(x + 3,y - height / 2);
	for (auto c : text)
	{
		glutBitmapCharacter(font, c);
	}

}