//#homework1.cpp
//#############
//    main 
//#############
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <conio.h>
// ������ �ʿ��� ���
#include "My.h"
// �� Class���� ����Ǿ� �ִ� ���
using namespace std;
# pragma warning(disable : 4996)
// getch�Լ��� �����ϱ� ���� ����

int main()
{
	Product P;
	Menu M;
	SaleProduct S;
	//Class ����
	string str,str1;//������ �о�� Product ��ü�� ������ ������ �� �ʿ��� string ����
	int price;//������ �о�� Product ��ü�� ������ ������ �� �ʿ��� int ����
	string input1; //��ǰ���� �Է¹ޱ� ���� string ����
	int input2; //�����Է��� ���� ����
	
	int i=0;//���� �о���� ������ �ʿ�
	
	ifstream Data;//���� ����
	Data.open("Product.dat",ios::in); //���� �б�
	
	while(1)
	{
	Data>>str;
	if(str1==str)
	{break;}
	Data>>price;
	str1=str;
	P.inputProduct(str,price,i++);
	}//Product ��ü�� ������ �о�� ����.

	while(1)
	{
	system("cls");//ȭ������
	switch(M.Salelist())
	{
	case 1://��ü��ǰ ��Ϻ���
		P.display();
		getch();
		break;
	case 2://�ǸŻ�ǰ �Է��ϱ�
		{
		cout<<"�ǸŸ�Ͽ� �߰��Ͻ� ��ǰ���� �Է����ּ���."<<endl;
		cin>>input1;
		if(P.Checking(input1)==0)
		{
			cout<<"�Է��Ͻ� ��ǰ�� �������� �ʽ��ϴ�."<<endl;
			getch();
			break;
		}
		cout<<"�ǸŸ�Ͽ� �߰��Ͻ� ��ǰ�� ������ �Է����ּ���."<<endl;
		cin>>input2;			
		S.enterSaleProduct(input1,input2,P.priceinfor(input1));
		cout<<"�ǸŸ�Ͽ� �߰��Ǿ����ϴ�."<<endl;
		getch();
		break;
		}
		
	case 3://�ǸŻ�ǰ �����ϱ�
		{
		cout<<"�ǸŸ�Ͽ��� �����Ͻ� ��ǰ���� �Է����ּ���."<<endl;
		cin>>input1;
		S.deleteSaleProduct(input1);
		getch();
		break;
		}
	case 4://�ǸŻ�ǰ ��Ϻ���
		S.display(0);
		getch();
		break;
	case 5://����
		S.display(1);
		return 0;
	default://�׿ܴٸ� �Է½�
		cout<<"�߸� �Է��ϼ̽��ϴ�.\nó������ �ٽ� �������ּ���.\n";
		getch();
	}
	}//while��
	Data.close();//���� �ݱ�
	return 0;
}