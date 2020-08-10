/*
2010년 2학기 컴퓨터프로그래밍
		-설계과제1-
		2010. 9 28
		정태선교수님
		20102020268
		정보컴퓨터공학부
		박준영
*/

#include<stdio.h>


int main(void)
{	
	//변수 선언
	int YEAR_CAR;
	int YEAR_DRIVE;
	int INS;
	int INS_BEFORE;
	int INS_LAST;
	int CAR_NEW;
	int CAR_TRUE;
	char MODEL;
	float DC;
    float PER;
	
	//지시사항 입력
	printf("<자동차보험료계산프로그램>\n");
	printf("밑에 지시되는 사항을 입력해주세요\n");
	printf("모델 : ");
	scanf("%c",&MODEL);//모델 입력
	printf("연식 : ");
	scanf("%d",&YEAR_CAR);//연식 입력
	printf("운전경력 : ");
	scanf("%d",&YEAR_DRIVE);//운전경력 입력
	printf("대물배상 : ");
	scanf("%d",&INS);//대물배상 입력
	
	//계산식
	CAR_NEW = 50000000-(MODEL-65)*15000000; //신차가격계산
	PER = 70-MODEL;							//모델과 연식에 따라 달라지는 감소율
	DC = (CAR_NEW*PER*(2010-YEAR_CAR))/100; //신차가격 - 실제가격
	CAR_TRUE = CAR_NEW-DC;					//실제가격계산
	INS_BEFORE = 90000+(INS*50000)+(CAR_TRUE*0.02);		//할인전 보험료계산
	INS_LAST = INS_BEFORE-(INS_BEFORE*0.03*YEAR_DRIVE); //운전경력에 따라 할인된 보험료(최종)
	//1000원미만 절삭 
	CAR_TRUE = (CAR_TRUE/1000)*1000;
	INS_BEFORE = (INS_BEFORE/1000)*1000;
	INS_LAST = (INS_LAST/1000)*1000;
	//결과 출력
	printf("==================\n");
	printf("==보험료계산결과==\n");
	printf("==================\n");
	printf("신차 차량금액 : %d\n",CAR_NEW);//신차가격
	printf("실제 차량금액 : %d\n",CAR_TRUE);//실차가격
	printf("할인전 보험료 : %d\n",INS_BEFORE);//할인전보험료
	printf("최종   보험료 : %d\n",INS_LAST);//최종보험료

	return 0;
}