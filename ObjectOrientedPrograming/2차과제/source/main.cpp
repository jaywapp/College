#include <iostream>
using namespace std;
#include "All.h"
#include <fstream>
#include <cstdlib>
#include <conio.h>
int setting_or_sale();
int sale_select();
int setting_select();
int numbering(string str);
void main()
{
	All start("catalog.dat");
	int option1=0,option2=0,option3=0;
	while(1)
	{
		option1=0;
		option2=0;
		option3=0;
		option1=setting_or_sale();
		if(option1==1)//��ǰ����
		{
			while(option3==0)
			{
				option2=setting_select();
				switch(option2)
				{
				case 1://��ǰ�߰��ϱ�
					cout<<"����-��ǰ����-��ǰ �߰��ϱ�\n";
					start.add_product();
					option2=0;
					break;
				case 2://��ǰ��Ϻ���
					cout<<"����-��ǰ����-��ǰ ��� ����\n";
					start.print_VM();
					break;
				case 3://����
					option1=option2=0;
					option3=1;
					cout<<"����-��ǰ����-����\n";
					cout<<"��ǰ������ �����մϴ�.\n";
					break;
				}
			cout<<endl;
			}
		}
		else if(option1==2)//��ǰ�Ǹ�
		{
			while(option3==0)
			{
				option2=sale_select();
				switch(option2)
				{
				case 1:
					cout<<"����-��ǰ�Ǹ�-��ٱ��Ͽ� ��ǰ�߰�\n";
					start.insert_SC();
					break;
				case 2:
					cout<<"����-��ǰ�Ǹ�-��ٱ��Ͽ� ��ǰ����\n";
					start.delete_SC();
					break;
				case 3:
					cout<<"����-��ǰ�Ǹ�-��ٱ��� ����\n";
					start.print_SC();
					break;
				case 4:
					cout<<"����-��ǰ�Ǹ�-����\n";
					start.payment();
					break;
				case 5:
					option1=option2=0;
					option3=1;
					cout<<"����-��ǰ�Ǹ�-�Ǹ����\n";
					cout<<"��ǰ�ǸŸ� ����մϴ�.\n";
					start.reset_SC2();
					break;
				}
			cout<<endl;
			}
		}
		else if(option1==3)
			return;
	cout<<endl;
	}
}

int setting_or_sale()
{
	fflush(stdin);
	int temp=0;
	string str;
	int i=0;
	while(temp!=1 && temp!=2 && temp!=3)
	{
		if(i!=0)
			cout<<"�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���.\n";
		cout<<"����\n1. ��ǰ����\n2. ��ǰ�Ǹ�\n3. ����\n";
		cout<<"��ȣ�� �����ϼ���. : ";
		cin>>str;
		i++;
		temp=numbering(str);
	}
	fflush(stdin);
	return temp;
}
int sale_select()
{
	fflush(stdin);
	int temp=0;
	string str;
	int i=0;
	while(temp!=1 && temp!=2 && temp!=3 && temp!=4 && temp!=5)
	{
		if(i!=0)
			cout<<"�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���.\n";
		cout<<"����-��ǰ�Ǹ�\n1. ��ٱ��Ͽ� ��ǰ �߰�\n2. ��ٱ��ϼ� ��ǰ ����\n3. ��ٱ��� ����\n4. ����\n5. �Ǹ����\n";
		cout<<"��ȣ�� �����ϼ���. : ";
		cin>>str;
		i++;
		temp=numbering(str);
	}
	fflush(stdin);
	return temp;
}
int setting_select()
{
	fflush(stdin);
	int temp=0;
	string str;
	int i=0;
	while(temp!=1 && temp!=2 && temp!=3)
	{
		if(i!=0)
			cout<<"�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���.\n";
		cout<<"����-��ǰ����\n1. ��ǰ �߰��ϱ�\n2. ��ǰ ��� ����\n3. ����\n";
		cout<<"��ȣ�� �����ϼ���. : ";
		cin>>str;
		i++;
		temp=numbering(str);
	}
	fflush(stdin);
	return temp;
}
int numbering(string str)
{
	int intValue = atoi(str.c_str());
	return intValue;
}