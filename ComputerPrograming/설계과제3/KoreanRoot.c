#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int NumofLocal();//지역의 번호를 소개해주는 함수.
void intro();//게임소개를 출력하는 함수
void inputplayer(int* c);//인원수 입력 함수
void move_inNPI(int* NPI);//무인도의 경우Player말의 이동함수
int move(int player,int* a,int* dic);//Player 말의 이동함수
int dice();//주사위함수
int money(int player);//1바퀴돌때마다 월급지급함수
int total_pass(int Build,int Pass);//총 통행료 계산함수.
void turn(char *Nu,int i);//순서 알림함수
void movingprint(int dic,int playerplace,int i);//이동 지점의 출력함수.
void infor_place(int a); //걸린칸의 지역이나 복불복설명
void buyLocal(char YorN, int* playermoney,int* Localorder, int Localprice,int i);//지역을 구매할때 사용하는 함수
void Pay_Process(int* v_total_pass,int* Host_money,int* Guest_money,int* have_ticket,int Local_Pay,int Local_build);//칸에 걸렸을때 통행료를 계산하는 함수.
void Pay_block(int Local_order,int Local_build,int Local_Pay);//걸린 칸의 기본통행료와 건물유무를 알려주는 함수
void build_selection(int* Local_build,int Local_Pay,int* playermoney);//건물건설함수
void board(int player[4][4], int c,int i,int* b);//상황판 함수
int Expensive(int Local[40][4],int playernumber);//소지한 지역중에 가장 비싼 지역을 골라내는 함수
void Cruze(int* playermoney);//플레이어가  크루즈 칸에 도달했을때 진행하는 함수
void Welfare(int* playermoney,int* Welfare_money);//플레이어가  사회복지기금칸에 도달했을때 진행하는 함수
void Space(int* playermoney,int* playerplace);
void ChanceSelection(int* playerplace, int* playermoney,int* Localorder,int* Localprice, int* playernumber,int* welfare,int* have_ticket,int* player_island);//Chance함수를 고르는 함수
void Chance1(int* playermoney,int* playernumber);//병원비지불
void Chance2(int* playermoney,int* playernumber);//복권당첨
void Chance3(int* playerplace, int* playermoney,int* playernumber,int* player_island);//독도로가시오
void Chance4(int* playerplace,int* playermoney,int* playernumber);//관광여행<제주도>
void Chance5(int* playermoney,int* playernumber);//과속운전 벌금
void Chance6(int* playermoney);//해외유학
void Chance7(int* playermoney);//연금혜택
void Chance8(int* playerplace,int* playernumber);//이사가시오
void Chance9(int* playermoney,int* playerplace);//고속도로
void Chance10(int* playermoney);//우승
void Chance11(int* playermoney,int* playerplace);//유람선여행(랜덤의지역에 떨어짐)
void Chance12(int* playerplace,int* playermoney);//관광여행<부산>
void Chance13(int* playermoney);//생일축하
void Chance14(int* playermoney);//장학금
void Chance15(int* playermoney);//노벨평화상
void Chance16(int* playerplace, int* playermoney,int* playernumber);//관광여행<서울>
void Chance17(int* playermoney, int* Localorder, int* Localprice);//반액대매출
void Chance18(int* playerplace, int* playermoney,int* playernumber);//우주여행 초청장
void Chance19(int* playermoney,int* welfare);//사회복지기금배당
void Chance20(int* have_ticket);//우대권

//----------------------------------------Local
int Start();
int Uijeongbu();
int Anyang();
int Kangchon();
int Choonchune();
int Jeju();
int Deakwanryung();
int Jeeli();
int Hanra();
int KoreanAir();
int Koomi();
int Deagu();
int Welfare_infor();
int Andong();
int Pohang();
int Kyungjoo();
int Ulsan();
int Busan();
int Haeundae();
int Changwon();
int Deajun();
int Spacetravel();
int Mokpo();
int Naroho();
int Gwangju();
int Suwon();
int Incheon();
int Bakdoo();
int Seoul();
int Cruze_infor();
int Dokdo();
int Saemankm();
int Yungkwang();
int Boryung();
int Chunan();

int main()
{
	int player[4][4];//유저들의 위치와 돈상태
	// player[4][4] 배열
	// user  place(1)  money(2) ticket(3) Nopeople(4)
	// 1
	// 2
	// 3
	// 4
	int a=0,b=0,c=0,d=0,k,dic,j,select=0;
	int NPI=0;
	int welfare=0;
	//a,b,c,d,k은 반복문을 제어할때 쓰는 변수,dic은 난수를 받는변수,select는 건물건설여부를 물을때 쓰는변수
	char Nu,YorN;//Nu는 엔터를 받아내는 변수,YorN는 Y와N를 받아내는변수
	int Local[40][4];
	int v_total_pass=0;//기본통행료에 건물이 있을때 더해진 금액; 총금액
	//Local[4][0]=소유자 번호
	//Local[4][1]=건물유무 1-콘도 2-빌딩 3-호텔 0-건물없음
	//Local[4][2]=지역의가격
	//Local[4][3]=기본통행료(건물이하나도없을때)
	srand(time(NULL));//rand함수를 쓰기위해 선언해주는 함수
	intro();//게임에대한설명
	inputplayer(&c);//함께할 인원수 결정
	scanf("%c",&Nu);//엔터입력
	// 초기화부분 ------------------------------------------

	for(int i=0;i<c;i++)//player위치의 초기화
	{
		player[i][0]=0;
		player[i][3]=0;
	}
	for(int i=0;i<c;i++)//player돈의 초기화
	{
		player[i][1]=5000000;
	}
	for(int i=0;i<c;i++)//player의 소유 우대권 갯수
	{
		player[i][2]=0;
	}
	for(int i=0;i<40;i++)//Local; 
	{
		Local[i][0]=0;//소유자 초기화
		Local[i][1]=0;//건물유무 초기화
		Local[i][2]=(i+1)*5000;//지역가격 설정
		Local[i][3]=(i+1)*300;//기본통행료 설정
	}



	//시작부분-------------------------------------------------------
	while(b==0)//
	{	
		for(int i=0;i<c;i++)//플레이어의 순서
		{
			turn(&Nu,i);
			if(player[i][3]!=0)
			{
				move_inNPI(&NPI);
				if(NPI==1)
				{
					player[i][3]=0;
				}
				else if(NPI==2)
				{
					player[i][3]=player[i][3]-1;

				}
			}
			else
			{
				player[i][0]=move(player[i][0],&a,&dic);
				movingprint(dic,player[i][0],i);
			}
			if(a==1)//a가 1이면 한바퀴 완주표시, 월급받기위해
			{
				printf("\a한 바퀴를 완주하셧습니다. 20만원을 지급받으십시오\n");
				player[i][1]=money(player[i][1]);
				a=0;
			}//if
			for(a=0;a<40;a++)//지역 구매, 건설 파트시작
			{//여기서 a는 각 칸을 의미함
				//int placeCheck(in
				if(player[i][0]==a)//player i 의 위치가 a가 될때
				{
					if(Local[a][0]==0 && a%10!=5 && a!=11 && a!=8 && a!=29 && a!=20 && a!=31)//a번째 Local의 소유자가 없을때
					{
						while(1)//잘못입력했을때 되물음을 위해 반복문선언
						{
							infor_place(a);

							printf("구매하시겠습니까?(Y/N)");
							fflush(stdin);
							scanf("%c",&YorN);
							buyLocal(YorN,&player[i][1],&Local[a][0],Local[a][2],i);
							if(YorN=='N' || YorN=='n' || YorN=='Y' || YorN=='y')
							{
								fflush(stdin);
								break;//제대로대답했을때 반복문을빠져나가기위한 break문
							}//else if(YorN)
						}//while(1)
					}//if(Local[a][0]==0)

					else if(Local[a][0]!=0 && Local[a][0]!=i+1 && a%10!=5 && a!=11 && a!=8 && a!=29 && a!=20 && a!=31)
					{//a번째 Local의 소유자가 있고, 그 소유자가 본인이 아닐때
						infor_place(a);
						Pay_block(Local[a][0],Local[a][1],Local[a][3]);
						k=Local[a][0]-1;
						Pay_Process(&v_total_pass,&player[k][1],&player[i][1],&player[i][2],Local[a][3],Local[a][1]);
						fflush(stdin);
						scanf("%c",&Nu);
					}//else if(Local[a][0]!=0 && Local[a][0]!=i+1)
					else if(Local[a][0]==i+1 && a%10!=5 && a!=11 && a!=8 && a!=29  && a!=20 && a!=31)//그땅이 본인의 땅일때.
					{
						infor_place(a);
						if(Local[a][1]!=0)//그리고 건물이 없을 때.
						{
							build_selection(&Local[a][1],Local[a][2],&player[i][2]);
						}
					}//else if(Local[a][0]==i+1)
					else if(a%10==5)//복불복 칸에 걸렸을때.
					{
						j=Expensive(Local,i+1);
						ChanceSelection(&player[i][0],&player[i][1],&Local[j][0],&Local[j][3],&i,&welfare,&player[i][2],&player[i][3]);
					}
					else if(a==11)
					{
						infor_place(a);
						if(NPI==2)
						{
							player[i][3]-1;
						}
						else if(NPI==0)
						{
							player[i][3]=2;
						}
					}
					else if(a==8 || a==29)
					{
						infor_place(a);
						Cruze(&player[i][1]);
					}
					else if(a==20)
					{
						infor_place(a);
						Welfare(&player[i][1],&welfare);
					}
					else if(a==31)
					{
						infor_place(a);
						Space(&player[i][1],&player[i][0]);
					}
				}

			}

			board(player,c,i,&b);
		}
	}
}//main----------------------------------

//----------------------------------------------------
int move(int player,int* a,int* dic)//플레이어의 이동을 계산해주는 함수
{

	int temp;

	temp=dice();
	*dic=temp;
	player=player+temp;
	if(player>40)
	{
		player=player-40;//지역 및 복불복 칸의 총수
		*a=1;
	}
	return player;
}
void move_inNPI(int* NPI)
{
	int dice_NPI1,dice_NPI2;
	dice_NPI1=(rand()%6)+1;
	dice_NPI2=(rand()%6)+1;

	printf("주사위를 던지겠습니다.!!\n");
	printf("첫번째 주사위는 %d 두번째 주사위는 %d로\n",dice_NPI1,dice_NPI2);
	if(dice_NPI1==dice_NPI2)
	{
		
		printf("같은 숫자가 나왔습니다. 탈출하세요!\n");	
		*NPI=1;
	}
	else if(dice_NPI1!=dice_NPI2)
	{
		printf("다른 숫자가 나왔습니다. 다음 턴에 다시도전하세요\n");
		*NPI=2;

	}
}


int money(int player)
{
	player=player+200000; //한바퀴 돌았을때, 월급 20만원
	return player;
}
int dice() //두개의 난수를 만들어내고 같으면 재귀하는
{
	int a,b;
	int result;
	char Nu;
	a=(rand()%6)+1;
	b=(rand()%6)+1;
	if(a!=b)
		printf("주사위 A : %d, 주사위 B : %d\n",a,b);
	result = a+b;
	if(a==b)
	{

		printf("주사위 A : %d, 주사위 B : %d\n주사위가 %d와 %d로 숫자가 같습니다. 한번더 돌리세요",a,b,a,b);
		scanf("%c",&Nu);
		return result+dice();
	}
	return result;
	//return 11;
}
void inputplayer(int *c)
{
	int b;
	while(1)
	{
		printf("함께하실 인원수를 입력하세요(2명~4명) :");
		scanf("%d",c);
		b=*c;
		if(b==2 || b==4 || b==3)
		{
			printf("%d명이서 게임을 시작하겠습니다.\n",b); 
			break;
		}
		else
		{
			printf("잘못입력하셨습니다.\n\n");
			*c=0;
		}
	}
}
void intro()
{
	printf("================================\n");
	printf("===========Korean Root==========\n");
	printf("=====================by.K G G===\n");
	printf("본 게임의 저작권은 KGG에 있음을 선포합니다.\n");
	printf("본 게임은 한국을 알리기위해 제작되었으며,\n");
	printf("상업 및 기타용도로 사용되지 않음을 알립니다.\n");
	printf("원활한 게임을 위하여 최대화버튼을 눌러주세요.\n");
	printf("\n\n");
}

int total_pass(int Build,int Pass)
{
	int result;
	result=(Build*50000)+Pass;
	return result;
}
void turn(char *Nu,int i)
{
	printf("\n★★★Player%d님의 순서!!★★★\n",i+1);
	printf("player %d님 주사위를 돌리시겠습니까? 돌리시려면 Enter키를 눌러주세요",i+1);
	scanf("%c",Nu);
}
void movingprint(int dic,int playerplace,int i)
{
	printf("%d칸 이동하겠습니다.\n",dic);
	printf("player%d님의 현재위치 : %d\n",i+1,playerplace);
}
void infor_place(int a)
{
	//printf("지금 도착한 곳은 Local[%d]입니다. 현재 주인이 아무도 없습니다.\n",a);
	/* 칸별 지역,황금열쇠가 정해지면 위 printf를 없애고 switch문으로 칸별함수사용.
	*/	
	printf("\n");
	switch(a)
	{
	case 0 : Start();
		break;
	case 1 : Uijeongbu();//의정부
		break;
	case 2 : Anyang();
		break;
	case 3 : Kangchon();
		break;
	case 4 : Choonchune();
		break;
		
	case 6 : Jeju();
		break;
	case 7 : Deakwanryung();
		break;
	case 8 : Cruze_infor();
		break;
	case 9 : Saemankm();
		break;
	case 10 : Jeeli();
		break;
	case 11 : Dokdo();
		break;
	case 12 : Yungkwang();
		break; 
	case 13 : Boryung();
		break;
	case 14 : Hanra();
		break;
	
	case 16 : KoreanAir();
		break;
	case 17 : Chunan();
		break;
	case 18 : Koomi();
		break;
	case 19 : Deagu();
		break;
	case 20 : Welfare_infor();
		break; 
	case 21 : Andong();
		break; 
	case 22 : Pohang();
		break; 
	case 23 : Kyungjoo();
		break; 
	case 24 : Ulsan();
		break; 
	
	case 26 : Busan();
		break;
	case 27 : Haeundae();
		break; 
	case 28 : Changwon();
		break;
	case 29 : Cruze_infor();
		break;
	case 30 : Deajun();
		break; 
	case 31 : Spacetravel();
		break;
	case 32 : Mokpo();
		break; 
	case 33 : Naroho();
		break; 
	case 34 : Gwangju();
		break; 
	case 36 : Suwon();
		break; 
	case 37 : Incheon();
		break; 
	case 38 : Bakdoo();
		break; 
	case 39 : Seoul();
		break; 
	}


}
void buyLocal(char YorN, int* playermoney,int* Localorder, int Localprice,int i)
{   
	if(YorN=='Y' || YorN=='y')
	{

		*playermoney=*playermoney-Localprice;
		*Localorder=i+1;
		fflush(stdin);
		printf("이 지역은 이제 Player%d님의 지역입니다.\n",i+1);

	}//if(YorN)
	else if(YorN=='N' || YorN=='n')
	{
		fflush(stdin);
	}//else if(YorN)
	else
	{
		printf("잘못 입력하셨습니다. 다시 입력해주십시오.\n");
		//break가 없으므로 다시 반복
	}//else
}
void Pay_block(int Local_order,int Local_build,int Local_Pay)
{
	printf("이 땅은 Player%d의 땅입니다.\n",Local_order);
	printf("기본통행료는 %d원이고,",Local_Pay);
	switch(Local_build)//건물유무를 알려주기위해
	{
	case 0 :printf("건물은 없습니다.\n");
		break;
	case 1 :printf("건물은 콘도가 있습니다.\n");
		break;
	case 2 :printf("건물은 빌딩이 있습니다.\n");
		break;
	case 3 :printf("건물은 호텔이 있습니다.\n");
		break;
	}//switch
}
void Pay_Process(int* v_total_pass,int* Host_money,int* Guest_money,int* have_ticket,int Local_Pay,int Local_build)
{
	char YorN;
	if(*have_ticket!=0)
	{
		printf("우대권이 있으십니다. 사용하시겠습니까? (Y/N) : ");
		scanf("%c",&YorN);
		if(YorN=='Y' || YorN=='y')
		{
			printf("우대권을 1개 사용하여 %d개가 남았습니다.\n",*have_ticket-1);
			*have_ticket=*have_ticket-1;

		}
		else if(YorN=='N' || YorN=='n')
		{
			*v_total_pass=total_pass(Local_build,Local_Pay);//통행료계산과정 total_pass함수는 계산함수
			printf("총 통행료는 %d 입니다.\n",*v_total_pass);
			*Guest_money=*Guest_money-*v_total_pass;//지역에걸린사람돈 차감
			*Host_money=*Host_money+*v_total_pass;//그지역의주인돈 상승
		}
	}
	else
	{
		*v_total_pass=total_pass(Local_build,Local_Pay);//통행료계산과정 total_pass함수는 계산함수
		printf("총 통행료는 %d 입니다.\n",*v_total_pass);
		*Guest_money=*Guest_money-*v_total_pass;//지역에걸린사람돈 차감
		*Host_money=*Host_money+*v_total_pass;//그지역의주인돈 상승
	}
}
void build_selection(int* Local_build,int Local_Pay,int* playermoney)
{
	char YorN,Nu;
	int select;

	printf("건물을 지으시겠습니까?(Y/N) : ");
	scanf("%c",&YorN);
	if(YorN=='Y'||YorN=='y')
	{
		printf("지으실 건물을 선택하세요.\n 1.콘도 2.별장 3.호텔  - > ");
		scanf("%d",&select);
		while(select==0)//잘못입력했을때 다시묻기위해
		{
			switch(select)
			{
			case 1: 
				*Local_build=1;
				*playermoney=*playermoney-(Local_Pay*0.5);
				printf("콘도를 지으셨습니다.\n");
				break;
			case 2: 
				*Local_build=2;
				printf("빌딩를 지으셨습니다.\n");
				*playermoney=*playermoney-(Local_Pay*1);
				break;
			case 3:
				*Local_build=3;
				*playermoney=*playermoney-(Local_Pay*1.5);
				printf("호텔를 지으셨습니다.\n");
				break;
			default : 
				printf("다시입력해주세요\n");
				select=0;//select가 다시 0이 됬으므로 반복
			}
		}
		if(YorN=='N'||YorN=='n')
		{
			printf("건물을 짓지 않고 넘어갑니다.\n");
			fflush(stdin);
			scanf("%c",&Nu);
		}//if(YorN=='N')
		else//오류
		{

		}
	}
}
void board(int player[4][4], int c,int i,int* b)//상황판 함수
{
	char Nu;
	printf("------------------------------------------------------------------------------\n");
	printf("### 현재상황 ###\n");
	printf("User Place money\n");
	for(int i=0;i<c;i++)//처음에 입력받은 인원수 만큼 돌림
	{
		printf("player%d %d %d원\n",i+1,player[i][0],player[i][1]);
	}

	printf("------------------------------------------------------------------------------\n");
	scanf("%c",&Nu);
	system("cls");
	NumofLocal();
	for(int i=0;i<c;i++)//돈이 10000000이 넘는 지 확인하기위해 돌리는 반복문
	{
		if(player[i][1]>=10000000)  //10000000대신 최종 목표 액수 선정가능
		{
			*b=1;//b가 1이 되면 그때의 i+1번째 플레이어가 승자가 됨.
			printf("축하합니다. Player%d님이 승리하셧습니다.****\n",i+1);
		}
	} 
}
int Expensive(int Local[40][4],int playernumber)
{//Local[i][2]
	int res=0,i;

	for(i=39;i>=0;i--)
	{
		if(Local[i][3]==playernumber && i%8!=0)
		{
			res=i;
			break;
		}
	}
	return res;
}
//------------------------------------------------------------------
//chance 함수시작
void ChanceSelection(int* playerplace, int* playermoney,int* Localorder,int* Localprice, int* playernumber,int* welfare,int* have_ticket,int* player_island)
{
	char Nu;
	int ran_num;


	printf("복불복!!!!!!!!!!!!!!카드를 랜덤으로 뽑겠습니다.\n 아무키나 눌러주세요^^");
	scanf("%c",&Nu);
	//ran_num=(rand()%20)+1;
	ran_num=4;

	switch(ran_num)
	{
	case 1 :Chance1(*&playermoney,*&playernumber);
		break;
	case 2 :Chance2(*&playermoney,*&playernumber);
		break;
	case 3 :Chance3(*&playerplace,*&playermoney,*&playernumber,*&player_island);
		break;
	case 4 :Chance4(*&playerplace,*&playermoney,*&playernumber);
		break;
	case 5 :Chance5(*&playermoney,*&playernumber);
		break;
	case 6 :Chance6(*&playermoney);
		break;
	case 7 :Chance7(*&playermoney);
		break;
	case 8 :Chance8(*&playerplace,*&playernumber);
		break;
	case 9 :Chance9(*&playermoney,*&playerplace);
		break;
	case 10 :Chance10(*&playermoney);
		break;
	case 11 :Chance11(*&playermoney,*&playerplace);
		break;
	case 12 :Chance12(*&playerplace,*&playermoney);
		break; 
	case 13 :Chance13(*&playermoney);
		break;
	case 14 :Chance14(*&playermoney);
		break;
	case 15 :Chance15(*&playermoney);
		break;
	case 16 :Chance16(*&playerplace,*&playermoney,*&playernumber);
		break;
	case 17 :Chance17(*&playermoney,*&Localorder,*&Localprice);
		break;
	case 18 :Chance18(*&playerplace,*&playermoney,*&playernumber);
		break;
	case 19 :Chance19(*&playermoney,*&welfare);
		break;
	case 20 :Chance20(*&have_ticket);
		break;
	}
}

void Chance1(int* playermoney,int* playernumber)
{
	printf("###복불복! 나만아니면 돼!###\n");
	printf("-병원비 지불-.\n");
	printf("당신은 다치셨습니다.\n병원에 가서 치료를 받으세요.\n병원비는 5만원입니다\n");
	*playermoney = *playermoney - 50000;
	printf("player %d님의 현재 남은 재산은 %d원.\n",*playernumber,*playermoney);

}
void Chance2(int* playermoney,int* playernumber)
{
	printf("###복불복! 나만아니면 돼!###\n");
	printf("-복권당첨(20만원)-.\n");
	printf("당신은 복권에 당첨되셨습니다.\n20만원을 받으세요.\n");
	*playermoney = *playermoney - 200000;
	printf("player %d님의 현재 남은 재산은 %d원.\n",*playernumber,*playermoney);

}
void Chance3(int* playerplace, int* playermoney,int* playernumber,int* player_island)
{
	int Nopeople=11;//무인도
	printf("###복불복! 나만아니면 돼!###\n");
	printf("-무인도-.\n");
	printf("당신은 무인도인 독도에 표류되셨습니다.\n");
	if(*playerplace>=Nopeople)
	{
		printf("출발점을 지나셔서 월급 획득!!\n");
		*playermoney=*playermoney+200000;
		printf("무인도로 이동하였습니다\n");
		*playerplace=Nopeople;
	}
	else if(*playerplace<Nopeople)
	{
		printf("무인도로 이동하였습니다\n");
		*playerplace=Nopeople;
	}
	printf("주사위 숫자가 같은 것이 나오거나 3회를 던진 후\n탈출하실 수 있습니다.");
	*player_island=2;

}
void Chance4(int* playerplace,int* playermoney,int* playernumber)
{
	int jeju=6;//제주도위치
	printf("###복불복! 나만아니면 돼!###\n");
	printf("-관광여행<제주도>-.\n");
	printf("땅에 주인이 있다면 요금을 지불하시오.\n출발지를 거쳐가실 경우에는 월급을 타시오.");
	if(*playerplace>=jeju)
	{
		printf("출발점을 지나셔서 월급 획득!!\n");
		*playermoney=*playermoney+200000;
		printf("제주도로 이동하였습니다\n");
		*playerplace=jeju;
		printf("지역은 구매하실수 없습니다.\n");
	}
	else if(*playerplace<jeju)
	{
		printf("제주도로 이동하였습니다\n");
		*playerplace=jeju;
		printf("지역은 구매하실수 없습니다.\n");
	}
	;
}
void Chance5(int* playermoney,int* playernumber)
{
	printf("###복불복! 나만아니면 돼!###\n");
	printf("-과속운전 벌금-.\n");
	printf("당신은 과속운전하다가 적발되셨습니다.\n");
	printf("벌금 5만원입니다.\n");

	*playermoney = *playermoney - 50000;
	printf("player %d님의 현재 남은 재산은 %d원\n",*playernumber,*playermoney);
}
void Chance6(int* playermoney)
{
	printf("###복불복! 나만아니면 돼!###\n");
	printf("-해외유학 자금-.\n");
	printf("당신은 해외유학 자금으로 10만원을 받으셨습니다\n");

	*playermoney = *playermoney + 100000;
	
}
void Chance7(int* playermoney)
{
	printf("###복불복! 나만아니면 돼!###\n");
	printf("-연금 혜택-.\n");
	printf("당신은 연금 혜택으로 5만원을 받으셨습니다\n");

	*playermoney = *playermoney + 50000;

}
void Chance8(int* playerplace,int* playernumber)
{
	printf("###복불복! 나만아니면 돼!###\n");
	printf("-이사-.\n");
	printf("뒤로 3칸 이사가시오\n");
	*playerplace = *playerplace - 3;
	printf("지역은 구매하실수 없습니다.\n");

}
void Chance9(int* playermoney,int* playerplace)
{
	printf("###복불복! 나만아니면 돼!###\n");
	printf("-고속도로-.\n");
	printf("고속도로를 타셨습니다. 출발지로 가서 돈을 받으세요\n");
	*playermoney = *playermoney + 200000;
	*playerplace = 0;

}
void Chance10(int* playermoney)
{
	printf("###복불복! 나만아니면 돼!###\n");
	printf("-그랑프리 우승-.\n");
	printf("당신은 그랑프리를 우승하셨습니다. 상금을 10만원을 받으세요\n");
	*playermoney = *playermoney + 100000;

}
void Chance11(int* playermoney,int* playerplace)
{
	int temp_place;
	char Nu;

	temp_place=(rand()%39)+1;
	printf("###복불복! 나만아니면 돼!###\n");
	printf("-유람선-.\n");
	printf("유람선을 타고 어떤곳으로 이동하시오. 출발지를 거칠경우 월급을 받습니다.\n");
	printf("\n이동하겠습니다.\n");
	scanf("%c",&Nu);
	fflush(stdin);
	infor_place(temp_place);
	if(*playerplace > temp_place)
	{
		*playermoney = *playermoney + 200000;
		*playerplace = temp_place;
	}
	else
	{
		*playerplace = temp_place;
	}
	

}
void Chance12(int* playerplace,int* playermoney)
{
	int temp_place = 23;

	printf("###복불복! 나만아니면 돼!###\n");
	printf("-관광여행<부산>-.\n");
	printf("부산으로 관광여행을 갑니다. 여행비 10만원을 사용합니다.\n");
	printf("지역은 구매하실수 없습니다.\n");
	*playermoney = *playermoney - 100000;
	*playerplace = temp_place;
}
void Chance13(int* playermoney)
{
	printf("###복불복! 나만아니면 돼!###\n");
	printf("-생일-.\n");
	printf("생일 축하합니다. 1천원을 받습니다\n");
	*playermoney += 1000;

}
void Chance14(int* playermoney)
{
	printf("###복불복! 나만아니면 돼!###\n");
	printf("-장학금-.\n");
	printf("당신은 학교에선 받을 수 없는 장학금 10만원을 게임에서 받습니다.\n");
	*playermoney += 100000;

}
void Chance15(int* playermoney)
{
	printf("###복불복! 나만아니면 돼!###\n");
	printf("-노벨평화상-.\n");
	printf("당신은 노벨평화상을 수상하여 30만원을 받습니다\n");
	*playermoney += 300000;

}

void Chance16(int* playerplace, int* playermoney,int* playernumber)
{
	printf("###복불복! 나만아니면 돼!###\n");
	printf("-관광여행<서울>-.\n");
	printf("서울로 갑니다. 올림픽기금으로 200만원을 지불합니다.\n");
	printf("지역은 구매하실수 없습니다.\n");
	*playermoney=*playermoney-2000000;
	*playerplace=39;
}
void Chance17(int* playermoney, int* Localorder, int* Localprice)
{
	printf("###복불복! 나만아니면 돼!###\n");
	printf("-반액대매출-.\n");
	printf("본인이 가지고 있는 땅 중 최고가의 땅을 반액에 팝니다.\n");
	//switch
	*playermoney=*playermoney-(*Localprice/2);
	*Localorder=0;
}
void Chance18(int* playerplace, int* playermoney,int* playernumber)
{
	int block=0;

	printf("###복불복! 나만아니면 돼!###\n");
	printf("-우주여행초청장-.\n");
	printf("이동하고 싶은 지역으로 이동하실 수 있습니다.\n");
	printf("이동시 출발점을 지나면 월급을 받습니다\n");
	printf("이동하시고 싶은 지역의 번호를 입력해주세요 : ");
	scanf("%d",&block);
	if(*playerplace>=block)
	{
		printf("출발점을 지나셔서 월급 획득!!\n");
		*playermoney=*playermoney+200000;
		printf("원하시는 지역으로 이동하였습니다\n");
		*playerplace=block;
		printf("지역은 구매하실수 없습니다.\n");
	}
	else if(*playerplace<block)
	{
		printf("원하시는 지역으로 이동하였습니다\n");
		*playerplace=block;
		printf("지역은 구매하실수 없습니다.\n");
	}
	
}
void Chance19(int* playermoney,int* welfare)
{
	printf("###복불복! 나만아니면 돼!###\n");
	printf("-사회복지기금-.\n");
	printf("현재까지 모인 사회복지기금을 배당받습니다.\n");
	printf("현재 모인 사회복지기금은 %d원입니다.\n",*welfare);
	*playermoney=*playermoney+*welfare;
	*welfare=0;

}
void Chance20(int* have_ticket)
{
	printf("###복불복! 나만아니면 돼!###\n");
	printf("-우대권-.\n");
	printf("어느 지역을 가던 통행료를 면제받는 우대권입니다.\n");
	printf("우대권사용시 소멸되며 매매 및 양도는 되지 않습니다.\n");
	*have_ticket=*have_ticket+1;
	printf("귀하가 가지고 있는 우대권은 총 %d개 입니다.\n",*have_ticket);

}
void Cruze(int* playermoney)
{
		*playermoney=*playermoney-200000;
}
void Welfare(int* playermoney, int* Welfare_money)
{
	*playermoney=*playermoney-50000;
	*Welfare_money=*Welfare_money+50000;
}
void Space(int* playermoney,int* playerplace)
{
	int want=0;
	char Nu;
	printf("가고싶은 지역을 입력하세요 : ");
	scanf("%d",&want);
	
	*playermoney=*playermoney-200000;
	*playerplace=want;
	printf("\n이동하겠습니다. \n");
	scanf("%c",&Nu);
}
int Start()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("Start.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Uijeongbu()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("의정부.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Anyang()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("Anyang.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Kangchon()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("Kangchon.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Choonchune()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("Choonchune.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Jeju()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("Jeju.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Deakwanryung()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("Deakwanryung.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Jeeli()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("Jeeli.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Hanra()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Hanra.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int KoreanAir()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("KoreanAir.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Koomi()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Koomi.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Deagu()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Deagu.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Welfare_infor()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Welfare.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Andong()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Andong.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Pohang()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Pohang.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Kyungjoo()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Kyungjoo.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Ulsan()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Ulsan.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Busan()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Busan.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Haeundae()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Haeundae.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Changwon()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Changwon.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Deajun()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Deajun.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Spacetravel()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Spacetravel.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Mokpo()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Mokpo.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Naroho()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Naroho.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Gwangju()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Gwangju.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Suwon()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("Suwon.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Incheon()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("Incheon.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Bakdoo()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("Bakdoo.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Seoul()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("Seoul.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int NumofLocal()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("NumofLocal.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Dokdo()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("독도.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Cruze_infor()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("크루저.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Saemankm()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("새만금.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Yungkwang()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("영광.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Boryung()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("보령.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Chunan()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("천안.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}