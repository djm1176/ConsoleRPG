#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Vectors.h"

class Game;

//Base class for all UI items that can be displayed on screen.
class UIElement {
	friend class UIManager;
protected:
	//The position of the Control in screen space.
	Vector m_Position;

	//The maximum size of the element, or bounds.
	Vector m_Size;

	virtual void render(Game* context) = 0;
public:
	//Describes where a Control is relative to another Control, based on user input.
	enum RelativePosition { above, below, left, right };

	UIElement(Vector position) : m_Position{ position } {}
};

//A UIElement that displays a label string.
//class Label : UIElement {
//
//
//};

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

	//Updates all elements of this manager.
	void update();
};