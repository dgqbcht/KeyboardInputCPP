#include "KeyboardInput.h"

/*
 * accept input from keyboard,
 * only visible character is permitted.
 * enable password mode with argument [true]
 */
string KeyboardInput::getInput(const bool password) {
	int code;
	char key;
	int position = 0;
	string input;
	while (true) {
		// get a keyboard input
		code = _getch();
		// deal with function key, such as F1 to F12
		if (code == 0 || code == -32 || code == 224) {
			code = _getch();
		}
		// deal with enter, end loop
		else if (code == 13) {
			cout << endl;
			break;
		}
		// deal with backspace, remove the last input character
		else if (code == 8) {
			// if the length of the input is larger than 0
			if (position > 0) {
				position--;
				cout << "\b \b";
				input = input.substr(0, position);
			}
		}
		// only visible character is permitted 
		else if (code >= 32 && code <= 126) {
			key = (char)code;
			// if the length of the input is less than limit length
			if (position < MAX_LENGTH) {
				if (password) {
					cout << "*";
				}
				else {
					cout << key;
				}
				input += key;
				position++;
			}
			// if the length of the input equals to limit length
			else {
				if (!password) {
					cout << "\b \b" << key;
				}
				input[position] = key;
			}
		}
	}
	return input;
}

/*
 * get input string,
 * with field information,
 * and limited length between min and max.
 * display content start with [top] line below previous line,
 * and after [left] blank characters.
 * input is visible when password is [false],
 * and is invisible when password is [true].
 * run looply until the limitation is satisfied.
 */
string KeyboardInput::getString(const string field, const int min, const int max, const int top, const int left, const bool password) {
	string input;
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(output, &csbi);
	csbi.dwCursorPosition.X = left;
	csbi.dwCursorPosition.Y = csbi.dwCursorPosition.Y + top;
	while (true) {
		SetConsoleCursorPosition(output, csbi.dwCursorPosition);
		cout << "Please input " << field << "(" << min << " - " << max << " characters):";
		input = KeyboardInput::getInput(password);
		int length = (int)input.length();
		if (length < min || length > max) {
			csbi.dwCursorPosition.Y++;
			SetConsoleCursorPosition(output, csbi.dwCursorPosition);
			cout << "The " << field << " should have " << min << " - " << max << " characters." << endl;
			csbi.dwCursorPosition.Y++;
			SetConsoleCursorPosition(output, csbi.dwCursorPosition);
			cout << "Your input has " << length << " characters. Try agian." << endl;
			csbi.dwCursorPosition.Y++;
		}
		else {
			break;
		}
	}
	return input;
}

/*
 * get input string,
 * with visible input, 
 * field information,
 * and limited length between min and max.
 * run looply until the limitation is satisfied.
 */
string KeyboardInput::getString(const string field, const int min, const int max) {
	return KeyboardInput::getString(field, min, max, 0, 0, false);
}

/*
 * get input string,
 * with visible input,
 * field information,
 * and limited length between min and max.
 * display content start with [top] line below previous line,
 * and after [left] blank characters.
 * run looply until the limitation is satisfied.
 */
string KeyboardInput::getString(const string field, const int min, const int max, const int top, const int left) {
	return KeyboardInput::getString(field, min, max, top, left, false);
}

/*
 * get input password,
 * with invisible input [*],
 * and limited length between min and max.
 * run looply until the limitation is satisfied.
 */
string KeyboardInput::getPassword(const int min, const int max) {
	return KeyboardInput::getString("password", min, max, 0, 0, true);
}

/*
 * get input password,
 * with invisible input [*],
 * and limited length between min and max.
 * display content start with [top] line below previous line,
 * and after [left] blank characters.
 * run looply until the limitation is satisfied.
 */
string KeyboardInput::getPassword(const int min, const int max, const int top, const int left) {
	return KeyboardInput::getString("password", min, max, top, left, true);
}

/*
 * determine whether the content of string is a number.
 */
bool KeyboardInput::isNumber(const string value) {
	int i = 0;
	int dot = 0;
	if (value[0] == '-') {
		i = 1;
	}
	for (; i < value.length(); i++) {
		if (!isdigit(value[i])) {
			if (value[i] == '.') {
				dot++;
			}
			else {
				return false;
			}
		}
	}

	if (dot > 1) {
		return false;
	}
	return true;
}

/*
 * get number input,
 * with field information,
 * and limited value between min and max.
 * display content start with [top] line below previous line,
 * and after [left] blank characters.
 * run looply until the limitation is satisfied.
 */
double KeyboardInput::getNumber(const string field, const double min, const double max, const int top, const int left) {
	string input;
	double value;
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(output, &csbi);
	csbi.dwCursorPosition.X = left;
	csbi.dwCursorPosition.Y = csbi.dwCursorPosition.Y + top;
	while (true) {
		SetConsoleCursorPosition(output, csbi.dwCursorPosition);
		cout << "Please input " << field << " (" << min << " to " << max << "):";
		input = getInput(false);
		csbi.dwCursorPosition.Y++;
		SetConsoleCursorPosition(output, csbi.dwCursorPosition);
		if (isNumber(input)) {
			value = stod(input);
			if (value < min || value > max) {
				cout << "The " << field << " should be between " << min << " to " << max << "." << endl;
				csbi.dwCursorPosition.Y++;
				SetConsoleCursorPosition(output, csbi.dwCursorPosition);
				cout << "Your input is " << value << ". Try agian." << endl;
				csbi.dwCursorPosition.Y++;
			}
			else {
				break;
			}
		}
		else {
			cout << "Your input is not a number. Try agian." << endl;
			csbi.dwCursorPosition.Y++;
		}
	}
	return value;
}

/*
 * get number input,
 * with field information,
 * and limited value between min and max.
 * run looply until the limitation is satisfied.
 */
double KeyboardInput::getNumber(const string field, const double min, const double max) {
	return KeyboardInput::getNumber(field, min, max, 0, 0);
}

/*
 * change output color,
 * available background color is in KeyboardInput.h, start with BG_
 * available foreground color is in KeyboardInput.h, start with FG_
 */
void KeyboardInput::setOutputColor(int background, int foreground) {
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(output, background | foreground);
}

/*
 * reset output color to black background and white foreground
 */
void KeyboardInput::resetOutputColor() {
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(output, FG_WHITE);
}