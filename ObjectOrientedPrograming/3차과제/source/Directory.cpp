#include "Directory.h"

Directory::Directory(string _name, string _mode)
{
	name = _name;
	mode = _mode;
}
void Directory::setName(string _name)
{
	name = _name;
	return;
}
void Directory::setMode(string _mode)
{
	mode = _mode;
	return;
}
string Directory::getName()
{
	return name;
}
string Directory::getMode()
{
	return mode;
}
void Directory::setWindow(string _window)
{
	return;
}
string Directory::getWindow()
{
	return "";
}

void Directory::printSelection()
{
	Root* temp;
	temp = Child_head;
	cout<<route<<endl;
	cout<<mode<<" "<<name<<endl;
	if(temp ==NULL)
	{
		cout<<"Enmpy directory!"<<endl;
		return;
	}
	while(1)
	{	
		if(temp->getWindow()=="")
			temp->printInfor();
		if(temp == Child_tail)
		{
			cout<<endl;
			break;
		}
		temp = temp->Next;
	}
	temp = Child_head;
	
	while(1)
	{	
		if(temp->getWindow()!="")
			temp->printInfor();
		if(temp == Child_tail)
		{
			cout<<endl;
			break;
		}
		temp = temp->Next;
	}
	return;
}

void Directory::printInfor()
{
	string str;
	str.append(name);
	str.append("/");
	str.append(mode);
	cout<<str<<"\t";
	return;
}
