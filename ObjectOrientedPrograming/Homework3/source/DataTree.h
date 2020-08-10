#ifndef DATATREE_H
#define DATATREE_H
#include <iostream>
#include <string>
#include "Root.h"
#include "Directory.h"
#include "Data.h"
#include <fstream>
using namespace std;

class DataTree
{
public:
	DataTree()
	{
		my_Access="+rw";
		Filein.open("_filesystem.dat",ios::in);
		Load();
		my_Access="";
		Filein.close();
	};
	~DataTree()
	{
		Fileout.open("_filesystem.dat",ios::out);
		Save(start);
		Fileout.close();
	};
	ifstream Filein;
	ofstream Fileout;
	void insert(string _name, string mode); // WriteCheck
	void insert(string _name, string mode, string _window); // WriteCheck
	void desert(string _name); // WriteCheck
	void printInfor(string _name); //ReadCheck
	void setAccess(string _access);
	string getAccess();
	bool ReadCheck(Root* R); 
	bool WriteCheck(Root* R);
	void moveDir(string _name); // ReadCheck
	void ChangeMode(string _name,string _mode); // WriteCheck
	void ChangeContent(string _name, string _window);
	void printCWD(Root* A);
	void veiw();
	void printRoute(Root* A);
	void Save(Root* A);
	void Loading(string* temp,int count,string filename,string mode, string window);
	void Load();
	Root* searchChild(string _name); //찾은 Root의 전 Root pointer를 출력 , delete에 사용.
	Root* search(string _name); // 찾은 Root pointer를 출력
	int ScaningLast(string* str);
	string* StringSplit(string strOrigin, string strTok);
	
	Root* start;
	Root* cwd;

private:
	string my_Access;
};

#endif