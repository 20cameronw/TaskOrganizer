#pragma once

#include <string>

class FormBox
{
private:
	int x; 
	int y; 
	int width; 
	int height; 
	int borderWidth;
	int id;
	std::string text;
	float borderColor[3];
	void* font;

public:
	FormBox(int x, int y, int width, int height, std::string text, void* _font, int id);
	void SetColor(float, float, float);
	void Draw() const;
	bool IsMouseOver(int, int) const;
	void UpdateText(std::string);
};

