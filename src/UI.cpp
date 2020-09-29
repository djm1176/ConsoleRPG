#include "UI.h"
#include "Game.h"

//UIElement
void UIElement::render(Game* context) {} //Currently base class UIElement render function shouldn't do anything

//UIManager
UIManager::UIManager(Game* context) : m_context{ context } {}

void UIManager::update() {
	for (int i = 0; i < m_elements.size(); i++) {
		m_elements[i]->render(m_context);
	}
}

RadioButton& UIManager::insert(RadioButton element) {
	auto _element = std::make_shared<RadioButton>(element);
	m_elements.push_back(_element);
	return *_element;
}

//Control
Control::Control(Vector position) : m_isFocused{ false } , UIElement{ position } {

}

void Control::setFocus(bool focused) {

}

bool Control::isFocused() const {
	return false;
}

//RadioButton
RadioButton::RadioButton(std::string label, Vector position) : m_label{ label }, Control{ position } {

}

void RadioButton::render(Game* context) {
	//Render the Radio bounds
	context->Draw(m_Position.x, m_Position.y, L'(');
	context->Draw(m_Position.x + 1, m_Position.y, (m_isChecked ? L'*' : L' '));	//TODO: Abstract the filled shape?
	context->Draw(m_Position.x + 2, m_Position.y, L')');

	//Render the label
	context->DrawString(m_Position.x + 4, m_Position.y, std::wstring{ m_label.begin(), m_label.end() });
}

void RadioButton::setChecked(bool checked) {
	m_isChecked = checked;
}

bool RadioButton::isChecked() const {
	return m_isChecked;
};

const std::string& RadioButton::getLabel() const {
	return m_label;
}

void RadioButton::setLabel(std::string label) {
	m_label = label;
}
