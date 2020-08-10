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
		if(option1==1)//상품관리
		{
			while(option3==0)
			{
				option2=setting_select();
				switch(option2)
				{
				case 1://상품추가하기
					cout<<"시작-상품관리-상품 추가하기\n";
					start.add_product();
					option2=0;
					break;
				case 2://상품목록보기
					cout<<"시작-상품관리-상품 목록 보기\n";
					start.print_VM();
					break;
				case 3://종료
					option1=option2=0;
					option3=1;
					cout<<"시작-상품관리-종료\n";
					cout<<"상품관리를 종료합니다.\n";
					break;
				}
			cout<<endl;
			}
		}
		else if(option1==2)//상품판매
		{
			while(option3==0)
			{
				option2=sale_select();
				switch(option2)
				{
				case 1:
					cout<<"시작-상품판매-장바구니에 상품추가\n";
					start.insert_SC();
					break;
				case 2:
					cout<<"시작-상품판매-장바구니에 상품삭제\n";
					start.delete_SC();
					break;
				case 3:
					cout<<"시작-상품판매-장바구니 보기\n";
					start.print_SC();
					break;
				case 4:
					cout<<"시작-상품판매-결제\n";
					start.payment();
					break;
				case 5:
					option1=option2=0;
					option3=1;
					cout<<"시작-상품판매-판매취소\n";
					cout<<"상품판매를 취소합니다.\n";
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
			cout<<"잘못 입력하셨습니다. 다시 입력해주세요.\n";
		cout<<"시작\n1. 상품관리\n2. 상품판매\n3. 종료\n";
		cout<<"번호를 선택하세요. : ";
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
			cout<<"잘못 입력하셨습니다. 다시 입력해주세요.\n";
		cout<<"시작-상품판매\n1. 장바구니에 상품 추가\n2. 장바구니서 상품 삭제\n3. 장바구니 보기\n4. 결제\n5. 판매취소\n";
		cout<<"번호를 선택하세요. : ";
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
			cout<<"잘못 입력하셨습니다. 다시 입력해주세요.\n";
		cout<<"시작-상품관리\n1. 상품 추가하기\n2. 상품 목록 보기\n3. 종료\n";
		cout<<"번호를 선택하세요. : ";
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