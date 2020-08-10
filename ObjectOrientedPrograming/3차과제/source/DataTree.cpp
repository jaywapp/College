#include "DataTree.h"

void DataTree::setAccess(string _access)
{
	my_Access = _access;
}
string DataTree::getAccess()
{
	return my_Access;
}
void DataTree::insert(string _name, string _mode)
{
	if(WriteCheck(cwd)==false)
		return;
	if(search(_name)!=NULL)
	{
		cout<<"There is a file that same name in cwd! retry!\n";
		return;
	}
	Root *temp = new Directory(_name,_mode);
	temp->Parent = cwd;
	temp->setRoute(temp->Parent->getRoute().append("/").append(temp->getName()));
	if ( cwd->Child_head == NULL )
    {
        cwd->Child_head = temp;
		cwd->Child_tail = temp;
    }
    else
    {
		cwd->Child_tail->Next = temp;
        cwd->Child_tail = temp;
    }
	return;
};
void DataTree::insert(string _name, string _mode, string _window)
{
	/*
	string str = routeCWD(cwd);
	str.append(_name);
	*/
	if(WriteCheck(cwd)==false)
		return;
	if(search(_name)!=NULL)
	{
		cout<<"There is a file that same name in cwd! retry!\n";
		return;
	}
	Root *temp = new Data(_name,_mode,_window);
	temp->Parent = cwd;
	temp->setRoute(temp->Parent->getRoute().append("/").append(temp->getName()));
	if ( cwd->Child_head == NULL )
    {
        cwd->Child_head = temp;
		cwd->Child_tail = temp;
    }
    else
    {
		cwd->Child_tail->Next = temp;
        cwd->Child_tail = temp;
    }
	return;
};
void DataTree::desert(string _name)
{
	if(WriteCheck(cwd)==false)
		return;
	Root *temp=NULL;
	
	temp = searchChild(_name); // 삭제대상 전의 Node
	if(temp!=NULL)
	{
		if(temp == cwd)//head가 삭제대상
		{
			temp = cwd->Child_head;
			cwd->Child_head = temp ->Next;
			delete temp;
			return; 
		}
		else // 그외
		{
			if(temp->Next == cwd->Child_tail)
			{
				cwd->Child_tail = temp;
				return;
			}
			temp->Next = temp->Next->Next;
			return;
		}
	}
};
Root* DataTree::search(string _name)
{
	Root* temp;
	if(cwd->Child_head!=NULL)
	{
		temp = cwd->Child_head;
		while(1)
		{
			if(temp->getName()==_name)
				return temp;
			else if(temp == cwd->Child_tail)
				return NULL;
			temp=temp->Next;
		}
		return NULL;
	}
	else
		return NULL;
}
Root* DataTree::searchChild(string _name)
{
	Root* temp;
	if(cwd->Child_head!=NULL)
	{
		temp = cwd->Child_head;
		if(temp->getName()==_name)
			return cwd;
		while(1)
		{
			if(temp->Next->getName()==_name)
				return temp;
			else if(temp->Next == cwd->Child_tail)
				return NULL;
			temp=temp->Next;
		}
		return NULL;
	}
	else
		return NULL;
}
bool DataTree::ReadCheck(Root* R)
{
	if(my_Access=="+rw")
		return true;
	if(R->getMode() =="+w")
	{
		cout<<"Wrong Access authority!"<<endl;
		return false;
	}
	return true;
};
bool DataTree::WriteCheck(Root* R)
{
	if(my_Access=="+rw")
		return true;
	if(R->getMode() =="+r")
	{
		cout<<"Wrong Access authority!"<<endl;
		return false;
	}
	return true;
}
void DataTree::printInfor(string _name)
{
	Root* temp = NULL;
	temp = search(_name);
	if(temp != NULL)
	{
		if(ReadCheck(temp) == false)
			return;
		temp->printSelection();
	}
	else 
		cout<<"Error! Can not find."<<endl;

	return; 
};
void DataTree::moveDir(string _name)
{
	if(cwd!=start)
	{
		if(_name == "..") //parent로 가는 경우.
		{
			if(ReadCheck(cwd->Parent)==true)
			{
				cwd = cwd->Parent;
				return;
			}
		}
		else if(_name == "/")
		{
			if(ReadCheck(start)==true)
			{
				cwd = start;
				return;
			}
		}
	}
	if (search(_name) != NULL) //하위 폴더로 가는 경우
	{
		if(ReadCheck(search(_name))==true)
		{
			if(search(_name)->getWindow()!="\0")
			{
				cout<<"Error! Wrong selection. That is not directory"<<endl;
				return;
			}
			cwd=search(_name);
			return;
		}
	}
	else // 하위 폴더목록에 찾고자하는 파일이 없을 경우
	{
		cout<<"Can not find directory!"<<endl;
	}
}
void DataTree::ChangeMode(string _name,string _mode)
{
	if(WriteCheck(cwd)==false)
	{
		return;
	}
	search(_name)->setMode(_mode);
}
void DataTree::veiw()
{
	int i=1;
	Root* temp;
	if(cwd->Parent!=NULL)
		cout<<"Parent\t: "<<cwd->Parent->getName()<<endl;
	cout<<"cwd\t: "<<cwd->getName()<<endl;
	if(cwd->Child_head==NULL)
	{
		cout<<"There is no file"<<endl;
		return;
	}
	temp = cwd ->Child_head;
	while(1)
	{
		cout<<i<<". "<<temp->getName()<<endl;
		if(temp == cwd->Child_tail)
			break;
		temp=temp->Next;
		i++;
	}
}
void DataTree::ChangeContent(string _name, string _window)
{
	if(WriteCheck(cwd)==false)
	{
		return;
	}
	search(_name)->setWindow(_window);
}
void DataTree::printCWD(Root* A)
{
	Root* temp = A;
	if(temp!= start)
	{
		printCWD(temp->Parent);
	}
	cout<<"/"<<temp->getName();
}
void DataTree::Save(Root* A)
{
	Root* temp;
	temp = A;
	printRoute(temp);
	if(temp->Child_head!=NULL)
		Save(temp->Child_head);

	if(temp->Next!=NULL)
		Save(temp->Next);
	else 
		return;
}
void DataTree::printRoute(Root* A)
{
	Fileout<<A->getRoute()<<A->getMode();
	if(A->getWindow()!="")
		Fileout<<" "<<A->getWindow()<<endl;
	else
		Fileout<<endl;
}
void DataTree::Load()
{
	string line;
	string* Component; // [0] -> 경로 [1] -> windows_name
	string* temp;
	string* str;
	string start_mode;
	string window="";
	int i=0;
	while( getline(Filein, line) )
	{
		string plus="+", slash="/";
		Component = StringSplit(line," "); // route - window_filename
		temp = StringSplit(Component[0],"/"); // route list - filename+mode
		str = StringSplit(temp[ScaningLast(temp)],"+"); // filename mode
		string filename = str[0];
		string mode = plus.append(str[1]);
		window = Component[1];
		if(i==0) // root생성
		{
			temp = StringSplit(filename,"+");
			start = new Directory(filename,mode);
			start->setRoute(slash.append(temp[0]));
			i=1;
		}
		else
		{
			Loading(temp,1,filename,mode,window);
		}
		cwd = start;
	};
}
void DataTree::Loading(string* temp,int count,string filename,string mode, string window)
{

	if(search(temp[count])==NULL)
	{
		if(window=="")
		{	
			insert(filename,mode);		
			return;
		}
		else
		{
			insert(filename,mode,window);	
			return;
		}
	}
	else
	{
		cwd=search(temp[count]);
		Loading(temp,count+1,filename,mode,window);
	}
	return;
}
int DataTree::ScaningLast(string* str)
{
	int i = 0;
	while(1)
	{
		if(str[i]=="")
			return i-1;
		i++;
	}
}
string* DataTree::StringSplit(string strOrigin, string strTok)
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
 