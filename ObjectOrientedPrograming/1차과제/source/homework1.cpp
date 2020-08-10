//#homework1.cpp
//#############
//    main 
//#############
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <conio.h>
// 구현에 필요한 헤더
#include "My.h"
// 각 Class들이 선언되어 있는 헤더
using namespace std;
# pragma warning(disable : 4996)
// getch함수를 구현하기 위한 정의

int main()
{
	Product P;
	Menu M;
	SaleProduct S;
	//Class 선언
	string str,str1;//파일을 읽어와 Product 객체의 변수에 적용할 때 필요한 string 변수
	int price;//파일을 읽어와 Product 객체의 변수에 적용할 때 필요한 int 변수
	string input1; //상품명을 입력받기 위한 string 변수
	int input2; //수량입력을 위한 변수
	
	int i=0;//파일 읽어오는 과정에 필요
	
	ifstream Data;//파일 열기
	Data.open("Product.dat",ios::in); //파일 읽기
	
	while(1)
	{
	Data>>str;
	if(str1==str)
	{break;}
	Data>>price;
	str1=str;
	P.inputProduct(str,price,i++);
	}//Product 객체에 파일을 읽어와 저장.

	while(1)
	{
	system("cls");//화면정리
	switch(M.Salelist())
	{
	case 1://전체상품 목록보기
		P.display();
		getch();
		break;
	case 2://판매상품 입력하기
		{
		cout<<"판매목록에 추가하실 상품명을 입력해주세요."<<endl;
		cin>>input1;
		if(P.Checking(input1)==0)
		{
			cout<<"입력하신 상품이 존재하지 않습니다."<<endl;
			getch();
			break;
		}
		cout<<"판매목록에 추가하실 상품의 수량을 입력해주세요."<<endl;
		cin>>input2;			
		S.enterSaleProduct(input1,input2,P.priceinfor(input1));
		cout<<"판매목록에 추가되었습니다."<<endl;
		getch();
		break;
		}
		
	case 3://판매상품 삭제하기
		{
		cout<<"판매목록에서 제거하실 상품명을 입력해주세요."<<endl;
		cin>>input1;
		S.deleteSaleProduct(input1);
		getch();
		break;
		}
	case 4://판매상품 목록보기
		S.display(0);
		getch();
		break;
	case 5://종료
		S.display(1);
		return 0;
	default://그외다른 입력시
		cout<<"잘못 입력하셨습니다.\n처음부터 다시 시작해주세요.\n";
		getch();
	}
	}//while문
	Data.close();//파일 닫기
	return 0;
}