#include "Data.h"

void Data::printInfor()
{
	string str;
	str.append(name);
	str.append(mode);
	cout<<str<<"\t";
	return;
}
Data::Data(string _name, string _mode, string _window)
{
	name = _name;
	mode = _mode;
	window = _window;
}
void Data::setWindow(string _window)
{
	window = _window;
	return;
}
string Data::getWindow()
{
	return window;
}
void Data::setName(string _name)
{
	name = _name;
	return;
}
void Data::setMode(string _mode)
{
	mode = _mode;
	return;
}
string Data::getName()
{
	return name;
}
string Data::getMode()
{
	return mode;
}
void Data::printSelection()
{
	cout<<route<<endl;
	cout<<window<<" "<<mode<<" "<<name<<endl;
	return;
}
