#ifndef ROOT_H
#define ROOT_H
#include <iostream>
#include <string>
using namespace std;

class Root
{
public:
	Root()
	{
		Next = NULL;
		Parent = NULL;
		Child_head = NULL;
		Child_tail = NULL;
	};
	virtual void setName(string _name) = 0;
	virtual void setMode(string _mode) = 0;
	virtual void setWindow(string _mode) = 0;
	virtual string getName() = 0;
	virtual string getMode() = 0;
	virtual string getWindow() = 0;
	virtual void printInfor()=0;
	virtual void printSelection()=0;
	void setRoute(string _route)
	{
		route = _route;
	};
	string getRoute()
	{
		return route;
	};

	Root* Next;
	Root* Parent;
	Root* Child_head;
	Root* Child_tail;
	string route;
private:
	
};

#endif