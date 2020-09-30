#include "UI.h"
#include "Game.h"

//UIElement
UIElement::UIElement(Vector position) : m_Position{ position } {}
void UIElement::render(Game* context) {} //Currently base class UIElement render function shouldn't do anything

//UIManager
UIManager::UIManager(Game* context) : m_context{ context } {
	//Add a background
	Panel _background;
}

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

Panel& UIManager::insert(Panel element) {
	auto _element = std::make_shared<Panel>(element);
	m_elements.push_back(_element);
	return *_element;
}

//Panel
Panel::Panel(Vector position, Vector size, short color) : UIElement{ position } {
	m_Color = color;
	m_Size = size;
}

void Panel::render(Game* context) {
	//Fill
	context->Fill(
		m_Position.x,
		m_Position.y,
		m_Position.x + m_Size.x + 1,
		m_Position.y + m_Size.y + 1,
		PIXEL_SOLID, m_Color & 0x00F0);

	if (m_DrawBorder) {
		//Draw corners
		context->Draw(m_Position.x, m_Position.y, LINE_TL, m_Color);
		context->Draw(m_Position.x, m_Position.y + m_Size.y, LINE_BL, m_Color);
		context->Draw(m_Position.x + m_Size.x, m_Position.y, LINE_TR, m_Color);
		context->Draw(m_Position.x + m_Size.x, m_Position.y + m_Size.y, LINE_BR, m_Color);

		//Draw lines
		context->DrawLine(m_Position.x + 1, m_Position.y, m_Position.x + m_Size.x - 1, m_Position.y, LINE_HORZ, m_Color);
		context->DrawLine(m_Position.x + 1, m_Position.y + m_Size.y, m_Position.x + m_Size.x - 1, m_Position.y + m_Size.y, LINE_HORZ, m_Color);
		context->DrawLine(m_Position.x, m_Position.y + 1, m_Position.x, m_Position.y + m_Size.y - 1, LINE_VERT, m_Color);
		context->DrawLine(m_Position.x + m_Size.x, m_Position.y + 1, m_Position.x + m_Size.x, m_Position.y + m_Size.y - 1, LINE_VERT, m_Color);
	}
}

void Panel::setBorder(bool draw) {
	m_DrawBorder = draw;
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
