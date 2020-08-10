#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <string>
#include "Root.h"
using namespace std;


class Data : public Root
{
public:
	Data();
	Data(string _name, string _mode, string _window);
	void setWindow(string _mode);
	void setName(string _name);
	void setMode(string _mode);
	string getWindow();
	string getName();
	string getMode();
	void printInfor();
	void printSelection();
private:
	string name;
	string mode;
	string window;
};
#endif