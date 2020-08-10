// header 추가
#include <stdio.h>
#include <string.h>
#include <mysql.h>
#include <unistd.h> 
#include <pthread.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <wait.h>

// DB 파트
#define DB_HOST "152.149.43.194"
#define DB_USER "root"
#define DB_PASS "rlaelql"
#define DB_NAME "carpoly"

// Arduino 파트
#define BAUDRATE B115200
#define MODEMDEVICE "/dev/ttyACM0"
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1
volatile int STOP=FALSE; 

// 전역변수 선언
int eme=0;
int singo = 0;
int ardutemp = 0;
int power_flag=0;
int lock_flag=0;
char car_number[10];
char user_name[10];
char user_name_t[10];
char permit[10];
char permit_t[10];
char lock_s[3];
char login[3];
char car_number[10];
char user_name[10];
char power_s[10];
/* lock_t는 db에서 가져온 값이 최신값인지 
확인하기 위한 데이터로 처음에는 임의값 3을 넣음*/
char lock_t[3] ="3";
int timer_re = 0;
// 쓰레드 선언
pthread_t threads[10];
// camera&touch
int isTouch=0;
int isCamera = 0;
int temp_camera=0;

// 함수 선언
void clearlcd(void);
void emelcd(void);
void emeinsert(void);
void * touch(void * arg);
void * camera(void * arg);
void buzz(void);
void bbibbo(void);
void timer(void);
void fuel(void);
void dipsw(void);
void keysw(void);
void arduino(void);
void updated(int a);
void lock_check(void);
void power_check(void);

// DB
MYSQL *connection = NULL;
MYSQL_RES *sql_result;
MYSQL_ROW sql_row;

/*Text LCD를 초기화*/
void clearlcd(void)
{
	system("./tlcdpermit r");
	system("./tlcdpermit c 1 1 2 15");	
	sleep(1);
} // clearlcd

/*eme 상황별로 Text LCD 출력*/
void emelcd(void)
{
	if (eme == 0) // normal state
	{
		clearlcd();
		system("./tlcdpermit w 1 WelcomeCarPoly");
		system("./tlcdpermit w 2 Normal_State");
		system("./tlcdpermit c 1 1 2 15");
	} // if 
	if(eme == 1) // emergency state (stop state)
	{
		clearlcd();	
		system("./tlcdpermit w 1 EmergencyState1");
		system("./tlcdpermit w 2 Contact_Insu");
		system("./tlcdpermit c 1 1 2 15");
	} // else if
	if(eme == 2) // emergency state (drive state)
	{
		clearlcd();	
		system("./tlcdpermit w 1 EmergencyState2");
		system("./tlcdpermit w 2 Contact_119Insu");
		system("./tlcdpermit c 1 1 2 15");
	} // else if
} // emelcd

/*사고발생시 사고상황을 DB에 쏴줌*/
void emeinsert(void)
{
	char query[100];
	int nQueryStat;
	
	strcpy(query,"insert into emergency values (\"");
	strcat(query,user_name);
	strcat(query,"\",\"");
	strcat(query,car_number);
	strcat(query,"\",\"");
	if(eme == 1) // emergency state (stop state)
	{
		strcat(query,"1");
	} // if
	else if (eme==2) // emergency state (drive state)
	{
		strcat(query,"2");
	} // else if
	strcat(query,"\")");
	// DB에 쏴줄 쿼리문 작성

	nQueryStat = mysql_query(connection, query); // 쿼리문 전송
	if(nQueryStat != 0)
	{
		printf("Mysql query error %s\n", mysql_error(connection));
		printf("err");
	} //if
} // emeinsert

/*Tablet Device touchapp 처리 함수
상태에 맞는 화면출력
터치입력시 카메라호출, 거울기능
카메라 종료시 다시 상황에 맞는 화면출력*/
void * touch(void * arg)
{
	isTouch = 0; // Touch 입력시 256, 입력하기전 0으로 초기화

	while (1){
		if ( !(strcmp(lock_s, "0")) ) // lock_s = 0
		{
			if ( !(strcmp(power_s,"0")) ) // power_s = 0
			{
				if(temp_camera != 0) // camera 실행시에 5초 sleep
					sleep(5);
				isTouch = system("./touchapp 2 4"); // 터치대기
				if (isTouch == 256) // 터치하면
				{
					isTouch = 0;
					/*최초 터치시에는 카메라 쓰레드생성
					이후 터치부터는 카메라 함수 호출
					카메라 쓰레드 생성시 isCamera를 1로 만들어준다.*/
					if (temp_camera == 0 && isCamera == 0)
					{
						pthread_create(&threads[5], NULL, camera, NULL);
					} // 4th if
					else if (temp_camera == 0 && isCamera == 1)
					{
						camera(0);
					} // 4th else if
				} // 3rd if
			} // 2nd if
			else if( !(strcmp(power_s,"1")) ) // power_s = 1
			{
				if(temp_camera != 0)
					sleep(5);
				isTouch = system("./touchapp 2 5");
				if (isTouch == 256)
				{
					isTouch = 0;
					if (temp_camera == 0 && isCamera == 0)
					{
						pthread_create(&threads[5], NULL, camera, NULL);
					} // 4th if
					else if (temp_camera == 0 && isCamera == 1)
					{
						camera(0);
					} // 4th else if
				} // 3rd if
			} // 2nd else if
		} // 1st if

		else if( !(strcmp(lock_s, "1")) )// lock_s = 1
		{
			if ( !(strcmp(power_s,"0")) ) // power_s = 0
			{
				if(temp_camera != 0)
					sleep(5);
				isTouch = system("./touchapp 2 2");
				if (isTouch == 256)
				{
					isTouch = 0;
					if (temp_camera == 0 && isCamera == 0)
					{
						pthread_create(&threads[5], NULL, camera, NULL);
					} // 4th if
					else if (temp_camera == 0 && isCamera == 1)
					{
						camera(0);
					} // 4th else if
				} // 3rd if
			} // 2nd if
			else if ( !(strcmp(power_s,"1")) ) // power_s = 1
			{
				if(temp_camera != 0)
					sleep(5);
				isTouch = system("./touchapp 2 3");
				if (isTouch == 256)
				{
					isTouch = 0;
					if (temp_camera == 0 && isCamera == 0)
					{
						pthread_create(&threads[5], NULL, camera, NULL);
					} // 4th if
					else if (temp_camera == 0 && isCamera == 1)
					{
						camera(0);
					} // 4th else if
				} // 3rd else if
			} // 2nd else if
		} // 1st else if
	} // while
} // touch

/*Camera device를 실행
camera는 5초간 실행된 후 자동종료, 5초 거울 기능
최초 호출시 isCamera를 1로 바꿔서 쓰레드 중복생성방지*/
void * camera(void * arg)
{
	isCamera = 1;
	temp_camera = system( "./camera" ); // 카메라 실행중엔 temp_camera가 0이 아닌 값
	temp_camera = 0; // 카메라가 실행중이 아님
} // camera

/*사고발생시 buzzer를 실행시킨다
주행중사고, 정차중사고 상황별로 다른 경고음 실행*/
void buzz(void)
{
	while (1)
	{
		if( eme == 1 ) // 단순접촉사고(stop state)
		{
			system("./siren2");
			eme=0;
		} // if
		else if( eme == 2 ) // 주행중사고(drive state)
		{
			system("./siren");
			eme=0;
		} // else if 
	} // while
} // buzz

/*사고발생시 dot matrix 실행
번갈아가면서 깜빡거림*/
void bbibbo(void)
{
	while (1)
	{
		if( eme == 1 || eme == 2 )
		{
			system("./bbibbo");
			eme=0; 
		} // if
	} // while
} // bbibbo

/*사용자가 이용한 시간을 카운트해준다.
7segment 이용해서 초단위로 카운트한다*/
void timer(void)
{
	while(1)
	{
		system("./timer c 1 9999999");
		// 유저가 바뀌면 0으로 초기화 후 다시 카운트
		printf("new user. reset timer\n");
		system("./timer c 1 0");	
	} // while
} // timer

/*bus led로 연료양을 보여준다
특정시간마다 (시연을 위해 임의로 30초마다 줄어들게 설정해놓음)
한칸씩 점등하여 연료가 줄어들었음을 보여주고
마지막 한칸이 남으면 깜빡여서 사용자에게 알려준다.*/
void fuel(void)
{
	int a;
	system("./fuelled 0 1");
	sleep(30);
	system("./fuelled 8 0");
	sleep(30);
	system("./fuelled 7 0");
	sleep(30);
	system("./fuelled 6 0");
	sleep(30);
	system("./fuelled 5 0");
	sleep(30);
	system("./fuelled 4 0");
	sleep(30);
	system("./fuelled 3 0");
	sleep(30);
	system("./fuelled 2 0");
	sleep(30);
	
	for (a = 0; a < 60 ; a++)
	{
		system("./fuelled 0 0");
		sleep(1);
		system("./fuelled 0 1");
		sleep(1);
	} // for
	system("./fuelled 0 0");
} // fuel

/*dip switch 변화하면 해당 이벤트 처리*/
void dipsw(void)
{
	int retvalue = -1;
	int temp1 = 0 ;
	int temp2 = 0;
	
	while(1)
	{
		sleep(1);
		retvalue = system("./dipsw")/256; // dip switch 값 저장
		if(retvalue == 1) // 첫번째 올리면
		{
			/*올려놓으면 계속해서 값을 받아오기때문에 
			temp1을 ++시켜서 최초값만(temp1이 1일때만)
			power_s에 저장해줌*/
			temp1 ++;
			if(temp1 == 1)
			{
				strcpy(power_s,"1");
				system("pkill touchapp"); // 상태가 바뀌었기 때문에 상태이미지 업데이트위해
				power_check(); // power 상태 확인하는 함수 호출
			} //2nd if
			temp2 = 0;
			// 0 시동 off 1 시동 on
		} // 1st if
		else if(retvalue == 0)
		{
			temp2 ++;
			if(temp2 == 1)
			{
				strcpy(power_s,"0");
				system("pkill touchapp");
				power_check();
			} // 2nd if
			temp1 = 0;
		} // 1st else if 
	} // while
} // dipsw

/*key switch 값 변화시 이벤트 처리*/
void keysw(void)
{
	int retvalue = -1;
	
	while(1)
	{
		retvalue = system("./keysw")/256; // key switch 값 저장
		
		if(retvalue != 0) // 유저가 key matrix를 누르면 (뭐든 누르면)
		{
			eme=0; // 상황해제
			system("pkill siren");
			system("pkill siren2");
			system("./buzzertest 0");
			system("pkill bbibbo");
			// 부저와 dotmatrix 꺼줌
			singo = 1; // 신고안함
			emelcd(); // lcd화면 normal state로 바꿔줌
			//ardutemp = 0;
			printf("push : %d\n",retvalue);
			sleep(1);
		} // if
	} // while
} // keysw

/*아두이노 센싱값을 보드로 받아와서
사고발생시 이벤트를 처리해줌*/
void arduino(void)
{
	int fd,c, res=0;
	struct termios oldtio,newtio;
	char buf[255];
        
	fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY ); 
	if (fd <0) {perror(MODEMDEVICE); exit(-1); }
        
	tcgetattr(fd,&oldtio); /* save current port settings */
        
	bzero(&newtio, sizeof(newtio));
	newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
	newtio.c_iflag = IGNPAR;
	newtio.c_oflag = 0;
      
	/* set input mode (non-canonical, no echo,...) */
	newtio.c_lflag = 0;     
	newtio.c_cc[VTIME] = 0;   /* inter-character timer unused */
	newtio.c_cc[VMIN] = 5;   /* blocking read until 5 chars received */
        
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd,TCSANOW,&newtio);
            
	while (STOP==FALSE) {       /* loop for input */
		res = read(fd,buf,255);/* returns after 5 chars have been input */
		buf[res]=0;               /* so we can printf... */
		
		/*최초 센싱값을 eme에 정수형으로 저장해준다*/
		if (res != 0)
		{
			ardutemp++;
		} // if
		if (ardutemp == 1)
		{
			eme=atoi(buf);
		} // if
		fflush(stdin);
		
		emelcd(); // 사고발생 text lcd에 상황 출력
		sleep(9);
		if(singo == 0)
		{
			emeinsert(); // DB에 사고상황을 알려줌
		} // if
		eme=0;
		singo = 0;
		
		if (buf[0]=='z') STOP=TRUE;
	} // while
	
	tcsetattr(fd,TCSANOW,&oldtio);
} // arduino

/*상태변경시 DB에 쿼리를 쏴줌*/
void updated(int a)
{	
	// a의 값
	// 1 == lock state
	// 2 == power state
	char query[100];
	int nQueryStat;
	printf("update\n");

	if(a==1) // lock state 변경
	{
		lock_flag=1;
		//update carstate set locstate = '1' where carnum='19gu1025'
		strcpy(query,"update carstate SET locstate = '");
		strcat(query,lock_s);
		strcat(query,"' where carnum = '");
		strcat(query,car_number);
		strcat(query,"'");
		
		nQueryStat = mysql_query(connection, query);
		
		if(nQueryStat != 0)
		{
			printf("Mysql query error %s\n", mysql_error(connection));
			printf("err");
		} // 2nd if
		
		printf("Update Lock state!\n");
	} // 1st if

	if(a==2) // power state 변경
	{
		printf("\n\npower state change!!!!!!!!!!!!!!!!!!!!!\n\n\n");
		power_flag=1;
		strcpy(query,"update carstate SET power = '");
		strcat(query,power_s);
		strcat(query,"' where carnum = '");
		strcat(query,car_number);
		strcat(query,"'");
		
		nQueryStat = mysql_query(connection, query);
		if(nQueryStat != 0)
		{
			printf("Mysql query error %s\n", mysql_error(connection));
			printf("err");
		} // 2nd if

		if( !(strcmp(power_s, "0")))
		{
			strcpy(query,"update carstate SET et = current_timestamp where carnum = '");
			strcat(query,car_number);
			strcat(query,"'");

			nQueryStat = mysql_query(connection, query);
			if(nQueryStat != 0)
			{
				printf("Mysql query error %s\n", mysql_error(connection));
				printf("err");
			} // 3rd if

		} // 2nd if
		else if ( !(strcmp(power_s, "1")))
		{
			strcpy(query,"update carstate SET st = current_timestamp, et = NULL where carnum = '");
			strcat(query,car_number);
			strcat(query,"'");

			nQueryStat = mysql_query(connection, query);
			if(nQueryStat != 0)
			{
				printf("Mysql query error %s\n", mysql_error(connection));
				printf("err");
			} // 3rd if
		} // 2nd else if
		printf("Update power state!\n");
	} // 1st if
} // updated

/*lock state 체크해서 lock 상태 변동시의 event 처리*/
void lock_check(void)
{
	int nQueryStat;
	int flag1 = 0;
	int flag2 = 0;
	printf("lock_user check\n");
	//////////////////////////////////////// 상시 LOCK 상태 확인 후 처리하는 부분 ////////////////////////////////
	// thread 화 시켜야함
	while(1)
	{
		//printf("\n\lock start\n\n");
		sleep(3);
		nQueryStat = mysql_query(connection, "SELECT * FROM board WHERE 1");
		if(nQueryStat != 0)
		{
			printf("Mysql query error %s\n", mysql_error(connection));
			printf("err");
		} // if
	
		// sql 값을 넣음
		sql_result = mysql_store_result(connection);
		while((sql_row = mysql_fetch_row(sql_result)) != NULL)
		{		
				// 변수에 넣음
				strcpy(user_name_t, sql_row[0]);
				strcpy(car_number, sql_row[1]);
				// db에서 lock 확인
				strcpy(lock_t, sql_row[2]);
				strcpy(permit, sql_row[3]);
		} // while

		//printf("\n\n\nlock_t state : %s\n\n\n",lock_t);
		//printf("\n\n\nlock_s state : %s\n\n\n",lock_s);			
		printf(" user _ after %s before %s \n",user_name_t,user_name);
		printf(" permit _ after %s before %s \n",permit,permit_t);

		//새로운 사용자 체크
		if( (strcmp(user_name, user_name_t)))
		{
			//printf("\n\n change user! : %s -> %s\n\n", user_name_t, user_name);
			strcpy(user_name,user_name_t);
			system("pkill timer"); // 새로 timer 시작하기 위해
		} // if

		if ( (strcmp(permit, permit_t)) )
		{	
		//	printf("\n\n change permit! : %s -> %s \n\n",permit_t, permit);
			strcpy(permit_t, permit);	
			//사용자 변경에 따른 이미지 교체
			if( !(strcmp(permit,"1")))
			{
				printf("\n\nyou owner!\n\n\n");
				sleep(1);
				system("./oledlogo d owner.img");		
			} // 2nd if

			if( !(strcmp(permit,"0")))
			{
				printf("\n\nyou guest!\n\n\n");
				sleep(1);
				system("./oledlogo d guest.img");
			} // 2nd if
		} // 1st if
		

		//lock 상태 체크
		if( strcmp(lock_t,"0") == 0)
		{
			flag1 = 0;
		} // if
		else
		{
			flag1 = 1;
		} // else 
		
		if (strcmp(lock_s,"0") == 0)
		{
			flag2 = 0;
		} // if
		else
		{
			flag2 = 1;
		} // else
		
		if (flag1 != flag2)
		{	
			strcpy(lock_s, lock_t);
			
			if (flag1 == 0)
			{
				printf("lock state : LOCK\n");
				updated(1);
				system("pkill touchapp"); // 상태변동에 따른 화면 이미지 변경위해
			} // 2nd if
			else if(flag1 == 1)
			{
				printf("lock state : LOCK\n");
				updated(1);
				system("pkill touchapp");
			} // 2nd else if
		} // 1st if
	} // while
} // lock_check

/*power state 체크해서 power 상태 변동시의 event 처리*/
void power_check(void)
{
	// dip switch로 받은 power state로 full color led 제어
	if( strcmp(power_s,"0") == 0 )
	{
		system("./engineled 0 255 0 0");
		updated(2);
		// 페리보드 상태 업데이트
	} // if
	else if( strcmp(power_s,"1") == 0 )
	{
		system("./engineled 0 255 255 0");
		updated(2);
		// 페리보드 상태 업데이트
	} // else if
} // power_check


int main(void)
{
	int nQueryStat;
	int flag_1 = 0;
	int flag_2 = 0;
	int flag_3 = 0;
	int flag_4 = 0;

	char test11[100];
	// 0이 lock상태임

	// lock_d는 board db에서 가져오는 값.
	char lock_d[3];
	
	char query_1[100];
	char query_2[100];
	char query_3[100];
	// db 초기화

	connection = mysql_init(NULL);
	if(connection == NULL)
	{
		printf("Mysql init fail\n");
		return -1;
	} // if

	//system("./insmodtest");
	// 페리보드 insmod
	system("./bitmap 1.bmp"); // 로그인대기화면
	// db 연결

	if(mysql_real_connect(connection, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0) == NULL)
	{
		printf("Mysql connection error : %s\n", mysql_error(connection));
		return 1;
	} // if
	printf("Successfuly connect!\n");

	// 따라서 flag_1을 이용하여 사용자가 로그인을 하였을 시에만 동작할 수 있도록 하기 위해 while을 통해 작동함
	while(flag_1 == 0)
	{
		nQueryStat = mysql_query(connection, "SELECT * FROM board WHERE 1");
		
		if(nQueryStat != 0)
		{
			printf("Mysql query error %s\n", mysql_error(connection));
			printf("err");
		} // if
	
		// sql 값을 넣음
		sql_result = mysql_store_result(connection);
	
		while((sql_row = mysql_fetch_row(sql_result)) != NULL)
		{	
		// 변수에 넣음
			strcpy(user_name, sql_row[0]);
			strcpy(car_number, sql_row[1]);
			strcpy(permit_t, sql_row[3]);
			strcpy(login, sql_row[4]);
			if( !(strcmp(login,"1")))
			{
				flag_1 = 1;
			} // if
		} // while
	} // while

	printf("\nWecome %s!\n",user_name);
	////////////////////////// cardata에서 가장 최근값을 가져오는 부분임 cardata 로그를 남기기 위한 부분//////////////////////////////////////////
	printf("\n\n %s test \n",car_number);
	
	// text lcd 초기화면 출력
	clearlcd();
	system("./tlcdpermit w 1 WelcometoCarPoly");
	system("./tlcdpermit w 2 Normal_state");

	// oled 디바이스 초기화
	system("./oledlogo i");
	if ( !(strcmp(permit_t,"1")))
	{
		// 1이면 owner
		system("./oledlogo d owner.img");
	} // if
	else
	{
		system("./oledlogo d guest.img");
	} // else

	// 중간 값이 바뀌어야 하는 코드는 이런식으로 짜야함.
	strcpy(query_1,"select * from carstate where carnum = '");
	strcat(query_1,car_number);
	strcat(query_1,"' order by st Desc limit 1");
	printf("\n\n query_1 %s\n\n",query_1);
	// 로그인한 사용자의 차량번호를 이용하여 최근 기록을 읽어 차량 상태 확인 
	nQueryStat = mysql_query(connection, query_1);
	if(nQueryStat != 0)
	{
		printf("Mysql query error %s\n", mysql_error(connection));
		printf("err");
	} // if

	printf("suceessfuly");

	sql_result = mysql_store_result(connection);

	while((sql_row = mysql_fetch_row(sql_result)) != NULL)
	{
		// 파워, lock 상태를 김넣는부분
		strcpy(power_s,sql_row[2]);
		strcpy(lock_s,sql_row[3]);
		//printf("\nthat car num is %s, user name is %s,\n power status is %s, lock status is %s, date is %s\n",sql_row[0],sql_row[1],sql_row[2],sql_row[3],sql_row[4]);
	}
	
	printf("\n\nthread start\n\n");
	pthread_create(&threads[0], NULL, lock_check, 0); //lock    
	pthread_create(&threads[1], NULL, timer, 0); //timer
	pthread_create(&threads[2], NULL, arduino, 0); //ardu
	pthread_create(&threads[3], NULL, fuel, 0); //busled
	pthread_create(&threads[4], NULL, touch, 0); //touch
	pthread_create(&threads[6], NULL, buzz, 0); //buzzer
	pthread_create(&threads[7], NULL, bbibbo, 0); //7seg
	pthread_create(&threads[8], NULL, dipsw, 0); //dipsw
	pthread_create(&threads[9], NULL, keysw, 0); //key matrix
	pthread_join(threads[0], 0);
	pthread_join(threads[1], 0);
	pthread_join(threads[2], 0);
	pthread_join(threads[3], 0);
	pthread_join(threads[4], 0);
	pthread_join(threads[6], 0);
	pthread_join(threads[7], 0);
	pthread_join(threads[8], 0);
	pthread_join(threads[9], 0);
	mysql_close(connection);
} // main