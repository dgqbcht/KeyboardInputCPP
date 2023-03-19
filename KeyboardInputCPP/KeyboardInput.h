#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>

#define MAX_LENGTH		512

#define FG_BLACK		0
#define FG_BLUE			1
#define FG_GREEN		2
#define FG_LAKEBLUE		3
#define FG_RED			4
#define FG_PURPLE		5
#define FG_YELLOW		6
#define FG_WHITE		7
#define FG_GRAY			8
#define FG_LIGHTBLUE	9
#define FG_LIGHTGREEN	10
#define FG_CYAN			11
#define FG_LIGHTRED		12
#define FG_LAVENDER		13
#define FG_LIGHTYELLOW	14
#define FG_BRIGHTWHITE	15

#define BG_BLUE			16
#define BG_GREEN		32
#define BG_LAKEBLUE		48
#define BG_RED			64
#define BG_PURPLE		80
#define BG_YELLOW		96
#define BG_WHITE		112
#define BG_GRAY			128
#define BG_LIGHTBLUE	144
#define BG_LIGHTGREEN	160
#define BG_CYAN			176
#define BG_LIGHTRED		192
#define BG_LAVENDER		208
#define BG_LIGHTYELLOW	224
#define BG_BRIGHTWHITE	240

using namespace std;

class KeyboardInput {
private:
	static string getString(const string field, const int min, const int max, const int top, const int left, const bool password);
	static bool isNumber(const string value);
public:
	static string getInput(const bool password);
	static string getString(const string field, const int min, const int max);
	static string getString(const string field, const int min, const int max, const int top, const int left);
	static string getPassword(const int min, const int max);
	static string getPassword(const int min, const int max, const int top, const int left);
	static double getNumber(const string field, const double min, const double max);
	static double getNumber(const string field, const double min, const double max, const int top, const int left);
	static void setOutputColor(int background, int foreground);
	static void resetOutputColor();
};
