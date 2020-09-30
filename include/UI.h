#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Vectors.h"
#include "olcConsoleGameEngine.h"

#define LINE_VERT L'\u2502'
#define LINE_HORZ L'\u2500'
#define LINE_TL L'\u250C'
#define LINE_BL L'\u2514'
#define LINE_TR L'\u2510'
#define LINE_BR L'\u2518'

#define LINE_MID_T L'\u252C'
#define LINE_MID_B L'\u2534'
#define LINE_MID_L L'\u251C'
#define LINE_MID_R L'\u2524'

class Game;

//Base class for all UI items that can be displayed on screen.
class UIElement {
	friend class UIManager;
protected:
	//The position of the Control in screen space.
	Vector m_Position;

	//The maximum size of the element, or bounds.
	Vector m_Size;

	short m_Color;

	virtual void render(Game* context) = 0;
public:
	//Describes where a Control is relative to another Control, based on user input.
	enum RelativePosition { above, below, left, right };

	UIElement(Vector position);
};

//A UI element that displays a label string.
class Label : UIElement {


};

//A UI element that serves as a filler/background with no content.
class Panel : public UIElement {
private:
	bool m_DrawBorder;
public:
	Panel(Vector position = Vector::zero, Vector size = Vector::one, short color = BG_BLACK | FG_WHITE);
	void render(Game* context) override;

	//Set to true to draw a bordered edge around the panel. Note that the border consumes 1 internal space on all sides.
	void setBorder(bool draw);
};

//A UI element that can be navigated to by the user through input
class Control : public UIElement {
protected:
	//True if this Control has focus.
	bool m_isFocused;

	//The Control to navigate to on User Input Left.
	std::shared_ptr<Control> m_navLeft;

	//The Control to navigate to on User Input Right.
	std::shared_ptr<Control> m_navRight;

	//The Control to navigate to on User Input Up.
	std::shared_ptr<Control> m_navUp;

	//The Control to navigate to on User Input Down.
	std::shared_ptr<Control> m_navDown;

protected:
	Control(Vector position);

	//Sets whether this Control currently has focus.
	void setFocus(bool focused);

public:
	//Returns true if this Control has focus currently.
	virtual bool isFocused() const;

};

//A UI Control that performs an action when selected.
class Button : Control {


};

//A UI Control that works as a Toggle.
class RadioButton : public Control {
	friend class UIManager;
private:
	//True if this RadioButton is "checked" on
	bool m_isChecked;
	std::string m_label;

protected:
	void render(Game* context) override;

public:
	RadioButton(std::string label = "", Vector position = Vector::zero);

	//Sets the state checked state of this RadioButton.
	void setChecked(bool checked);

	//Returns true if this RadioButton is checked.
	bool isChecked() const;

	//Returns the label of this RadioButton.
	const std::string& getLabel() const;

	//Sets the RadioButton's displayed label.
	void setLabel(std::string label);

};

//A container for UI elements, such as Controls and Text Labels.
class UIManager {
private:
	//TODO: Make const pointer, so we cannot change the context? (Game* const m_context)
	Game* m_context;

	std::vector<std::shared_ptr<UIElement>> m_elements;

public:
	
	//Constructs a new UIManager, which handles all UI elements that can be displayed.
	UIManager(Game* context);
	
	//Inserts a copy of RadioButton into the manager and returns the copy.
	RadioButton& insert(RadioButton element);

	//Inserts a copy of Panel into the manager and returns the copy.
	Panel& insert(Panel element);

	//Updates all elements of this manager.
	void update();
};