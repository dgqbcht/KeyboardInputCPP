#include "KeyboardInput.h"

void testGetInput();
void testGetString();
void testGetPassword();
void testGetNumber();
void testColor();

int main() {
	//testGetInput();
	//testGetString();
	//testGetPassword();
	//testGetNumber();
	testColor();
	return EXIT_SUCCESS;
}

/*
 * test function getInput
 */
void testGetInput() {
	// visible mode
	string content = KeyboardInput::getInput(false);
	cout << "Length of visible input is: " << content.length() << endl;
	cout << "Visible Input is: " << content << endl;
	// invisible mode
	content = KeyboardInput::getInput(true);
	cout << "Length of invisible input is: " << content.length() << endl;
	cout << "Invisible Input is: " << content << endl;
}

/*
 * test function getString
 */
void testGetString() {
	int min = 4;
	int max = 8;
	int top = 1;
	int left = 4;
	string content = KeyboardInput::getString("username", min, max, top, left);
	cout<<"\033["<<left<<"CLength of input is: "<<content.length()<<endl;
	cout << "\033[" << left << "CVisible input is: " << content << endl;
}

/*
 * test function getPassword
 */
void testGetPassword() {
	int min = 4;
	int max = 8;
	int top = 1;
	int left = 4;
	string content = KeyboardInput::getPassword(min, max, top, left);
	cout << "\033[" << left << "CLength of input is: " << content.length() << endl;
	cout << "\033[" << left << "CVisible input is: " << content << endl;
}

/*
 * test function getNumber
 */
void testGetNumber() {
	double min = -273.15;
	double max = 300;
	int top = 1;
	int left = 4;
	double value = KeyboardInput::getNumber("temperature", min, max, top, left);
	printf("The value is: %f\n", value);
}

/*
 * test functoion setOutputColor and resetOutputColor
 */
void testColor() {
	printf("This is a original message.\n");
	KeyboardInput::setOutputColor(BG_LIGHTYELLOW, FG_BLUE);
	printf("This is a message after color changed.\n");
	KeyboardInput::setOutputColor(BG_WHITE, FG_BLACK);
	printf("This is a message after color changed again.\n");
	KeyboardInput::resetOutputColor();
	printf("This is a message after color reset.\n");
}
