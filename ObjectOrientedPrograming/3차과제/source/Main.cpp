/*
11/27 8:35 PM
남은 기능 : DataTree내의 Save, Load함수 구현하기
*/

#include <iostream>
#include <string>

using namespace std;

#include "Root.h"
#include "Directory.h"
#include "Data.h"
#include "DataTree.h"
string* StringSplit(string strOrigin, string strTok);
int instruction(string* name, string* window_name, string *access);
void main()
{
	int ins;
	string name,access,window_name;
	DataTree tree;
	int temp;
	cout<<"Select mode! :| 1. Super User || 2. User |\nYour Selection : ";
	cin>>temp;
	if(temp==1)
		tree.setAccess("+rw");
	fflush(stdin);
	while(1)
	{
		tree.veiw();
		ins=instruction(&name,&window_name,&access);
		fflush(stdin);
		switch(ins)
		{
		case 1:
			tree.insert(name,access,window_name);
			break;
		case 2:
			tree.desert(name);
			break;
		case 3:
			tree.insert(name,access);
			break;
		case 4:
			tree.printInfor(name);
			break;
		case 5:
			tree.moveDir(name);
			break;
		case 6:
			tree.ChangeMode(name,access);
			break;
		case 7:
			tree.ChangeContent(name,window_name);
			break;
		case 8:
			tree.printCWD(tree.cwd);
			cout<<endl;
			break;
		default:
			return;
		}
		cout<<endl;
	}
}


int instruction(string* name, string* window_name, string *access)
{
	cout<<"Input instruction!"<<endl;
	string str;
	string temp1,temp2,temp3,temp4;
	string mode;
	char a[100];
	while(1)
	{
		cin.getline(a,100);
		str = a;
		string *token = StringSplit(str," ");
		mode = token[1];
		temp2 = token[2];
		temp3 = token[3];
		temp4 = token[4];
		if(mode=="new")
		{
			if(temp2 != "+rw" && temp2 !="+r"&& temp2!="+w")
				temp2 = "+rw";
			*access=temp2;
			*name=temp3;
			*window_name=temp4;
			return 1;
		}
		else if(mode=="del")
		{
			*name=temp2;
			return 2;
		}
		else if(mode=="mkdir")
		{
			*access=temp2;
			*name=temp3;
			return 3;
		}
		else if(mode=="disp")
		{
			*name=temp2;
			return 4;
		}
		else if(mode=="chdir")
		{
			*name=temp2;
			return 5;
		}
		else if(mode=="chmod")
		{
			*access=temp2;
			*name=temp3;
			return 6;
		}
		else if(mode=="chcon")
		{
			*name=temp2;
			*window_name=temp3;
			return 7;
		}
		else if(mode=="cwd")
		{
			return 8;
		}
		else if(mode=="exit")
			return 0;
		else
		{
			cout<<"error! retry!"<<endl;
		}
	}

};

string* StringSplit(string strOrigin, string strTok)
{
    int cutAt;                            //자르는위치
    int index     = 0;                    //문자열인덱스
    string* strResult = new string[5];  //결과return 할변수

    //strTok을찾을때까지반복
    while ((cutAt = strOrigin.find_first_of(strTok)) != strOrigin.npos)
    {
        if (cutAt > 0)  //자르는위치가0보다크면(성공시)
        {
         strResult[index++] = strOrigin.substr(0, cutAt);  //결과배열에추가
        }
        strOrigin = strOrigin.substr(cutAt+1);  //원본은자른부분제외한나머지
        }
	           if(strOrigin.length() > 0)  //원본이아직남았으면
        {
        strResult[index++] = strOrigin.substr(0, cutAt);  //나머지를결과배열에추가
    }

 return strResult;  //결과return
 }
