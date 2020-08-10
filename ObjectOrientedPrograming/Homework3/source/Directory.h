#ifndef DIRECTORY
#define DIRECTORY

#include <iostream>
#include <string>
#include "Root.h"


using namespace std;
class Directory : public Root
{
public:
	Directory();
	Directory(string _name, string _mode) ;
	void setName(string _name);
	void setMode(string _mode);
	void setWindow(string _window);
	string getName();
	string getMode();
	string getWindow();
	void printInfor();
	void printSelection();
private:
	string name;
	string mode;
};

#endif