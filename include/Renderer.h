#pragma once

#include "Object.h"
#include "olcConsoleGameEngine.h"

class Renderer : public Object {
private:
	wchar_t m_char;		//The character to display
	COLOUR m_color;		//The color to display

public:

	//Constructor for a Renderer.
	Renderer(wchar_t _char = L' ', COLOUR _color = FG_GREY)
		: m_char{ _char }, m_color{ _color } {}

	wchar_t getchar() const {
		return m_char;
	}

	void setchar(wchar_t _char) {
		m_char = _char;
	}

	COLOUR getcolor() const {
		return m_color;
	}

	void setcolor(COLOUR _color) {
		m_color = _color;
	}

	//Inherited via Object
	std::string toString() const override {
		return "Renderer";
	}

	void update() override {
		
	}

};