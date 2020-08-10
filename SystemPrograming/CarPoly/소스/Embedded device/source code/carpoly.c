// header �߰�
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

// DB ��Ʈ
#define DB_HOST "152.149.43.194"
#define DB_USER "root"
#define DB_PASS "rlaelql"
#define DB_NAME "carpoly"

// Arduino ��Ʈ
#define BAUDRATE B115200
#define MODEMDEVICE "/dev/ttyACM0"
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1
volatile int STOP=FALSE; 

// �������� ����
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
/* lock_t�� db���� ������ ���� �ֽŰ����� 
Ȯ���ϱ� ���� �����ͷ� ó������ ���ǰ� 3�� ����*/
char lock_t[3] ="3";
int timer_re = 0;
// ������ ����
pthread_t threads[10];
// camera&touch
int isTouch=0;
int isCamera = 0;
int temp_camera=0;

// �Լ� ����
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

/*Text LCD�� �ʱ�ȭ*/
void clearlcd(void)
{
	system("./tlcdpermit r");
	system("./tlcdpermit c 1 1 2 15");	
	sleep(1);
} // clearlcd

/*eme ��Ȳ���� Text LCD ���*/
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

/*���߻��� ����Ȳ�� DB�� ����*/
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
	// DB�� ���� ������ �ۼ�

	nQueryStat = mysql_query(connection, query); // ������ ����
	if(nQueryStat != 0)
	{
		printf("Mysql query error %s\n", mysql_error(connection));
		printf("err");
	} //if
} // emeinsert

/*Tablet Device touchapp ó�� �Լ�
���¿� �´� ȭ�����
��ġ�Է½� ī�޶�ȣ��, �ſ���
ī�޶� ����� �ٽ� ��Ȳ�� �´� ȭ�����*/
void * touch(void * arg)
{
	isTouch = 0; // Touch �Է½� 256, �Է��ϱ��� 0���� �ʱ�ȭ

	while (1){
		if ( !(strcmp(lock_s, "0")) ) // lock_s = 0
		{
			if ( !(strcmp(power_s,"0")) ) // power_s = 0
			{
				if(temp_camera != 0) // camera ����ÿ� 5�� sleep
					sleep(5);
				isTouch = system("./touchapp 2 4"); // ��ġ���
				if (isTouch == 256) // ��ġ�ϸ�
				{
					isTouch = 0;
					/*���� ��ġ�ÿ��� ī�޶� ���������
					���� ��ġ���ʹ� ī�޶� �Լ� ȣ��
					ī�޶� ������ ������ isCamera�� 1�� ������ش�.*/
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

/*Camera device�� ����
camera�� 5�ʰ� ����� �� �ڵ�����, 5�� �ſ� ���
���� ȣ��� isCamera�� 1�� �ٲ㼭 ������ �ߺ���������*/
void * camera(void * arg)
{
	isCamera = 1;
	temp_camera = system( "./camera" ); // ī�޶� �����߿� temp_camera�� 0�� �ƴ� ��
	temp_camera = 0; // ī�޶� �������� �ƴ�
} // camera

/*���߻��� buzzer�� �����Ų��
�����߻��, �����߻�� ��Ȳ���� �ٸ� ����� ����*/
void buzz(void)
{
	while (1)
	{
		if( eme == 1 ) // �ܼ����˻��(stop state)
		{
			system("./siren2");
			eme=0;
		} // if
		else if( eme == 2 ) // �����߻��(drive state)
		{
			system("./siren");
			eme=0;
		} // else if 
	} // while
} // buzz

/*���߻��� dot matrix ����
�����ư��鼭 �����Ÿ�*/
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

/*����ڰ� �̿��� �ð��� ī��Ʈ���ش�.
7segment �̿��ؼ� �ʴ����� ī��Ʈ�Ѵ�*/
void timer(void)
{
	while(1)
	{
		system("./timer c 1 9999999");
		// ������ �ٲ�� 0���� �ʱ�ȭ �� �ٽ� ī��Ʈ
		printf("new user. reset timer\n");
		system("./timer c 1 0");	
	} // while
} // timer

/*bus led�� ������� �����ش�
Ư���ð����� (�ÿ��� ���� ���Ƿ� 30�ʸ��� �پ��� �����س���)
��ĭ�� �����Ͽ� ���ᰡ �پ������� �����ְ�
������ ��ĭ�� ������ �������� ����ڿ��� �˷��ش�.*/
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

/*dip switch ��ȭ�ϸ� �ش� �̺�Ʈ ó��*/
void dipsw(void)
{
	int retvalue = -1;
	int temp1 = 0 ;
	int temp2 = 0;
	
	while(1)
	{
		sleep(1);
		retvalue = system("./dipsw")/256; // dip switch �� ����
		if(retvalue == 1) // ù��° �ø���
		{
			/*�÷������� ����ؼ� ���� �޾ƿ��⶧���� 
			temp1�� ++���Ѽ� ���ʰ���(temp1�� 1�϶���)
			power_s�� ��������*/
			temp1 ++;
			if(temp1 == 1)
			{
				strcpy(power_s,"1");
				system("pkill touchapp"); // ���°� �ٲ���� ������ �����̹��� ������Ʈ����
				power_check(); // power ���� Ȯ���ϴ� �Լ� ȣ��
			} //2nd if
			temp2 = 0;
			// 0 �õ� off 1 �õ� on
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

/*key switch �� ��ȭ�� �̺�Ʈ ó��*/
void keysw(void)
{
	int retvalue = -1;
	
	while(1)
	{
		retvalue = system("./keysw")/256; // key switch �� ����
		
		if(retvalue != 0) // ������ key matrix�� ������ (���� ������)
		{
			eme=0; // ��Ȳ����
			system("pkill siren");
			system("pkill siren2");
			system("./buzzertest 0");
			system("pkill bbibbo");
			// ������ dotmatrix ����
			singo = 1; // �Ű����
			emelcd(); // lcdȭ�� normal state�� �ٲ���
			//ardutemp = 0;
			printf("push : %d\n",retvalue);
			sleep(1);
		} // if
	} // while
} // keysw

/*�Ƶ��̳� ���̰��� ����� �޾ƿͼ�
���߻��� �̺�Ʈ�� ó������*/
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
		
		/*���� ���̰��� eme�� ���������� �������ش�*/
		if (res != 0)
		{
			ardutemp++;
		} // if
		if (ardutemp == 1)
		{
			eme=atoi(buf);
		} // if
		fflush(stdin);
		
		emelcd(); // ���߻� text lcd�� ��Ȳ ���
		sleep(9);
		if(singo == 0)
		{
			emeinsert(); // DB�� ����Ȳ�� �˷���
		} // if
		eme=0;
		singo = 0;
		
		if (buf[0]=='z') STOP=TRUE;
	} // while
	
	tcsetattr(fd,TCSANOW,&oldtio);
} // arduino

/*���º���� DB�� ������ ����*/
void updated(int a)
{	
	// a�� ��
	// 1 == lock state
	// 2 == power state
	char query[100];
	int nQueryStat;
	printf("update\n");

	if(a==1) // lock state ����
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

	if(a==2) // power state ����
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

/*lock state üũ�ؼ� lock ���� �������� event ó��*/
void lock_check(void)
{
	int nQueryStat;
	int flag1 = 0;
	int flag2 = 0;
	printf("lock_user check\n");
	//////////////////////////////////////// ��� LOCK ���� Ȯ�� �� ó���ϴ� �κ� ////////////////////////////////
	// thread ȭ ���Ѿ���
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
	
		// sql ���� ����
		sql_result = mysql_store_result(connection);
		while((sql_row = mysql_fetch_row(sql_result)) != NULL)
		{		
				// ������ ����
				strcpy(user_name_t, sql_row[0]);
				strcpy(car_number, sql_row[1]);
				// db���� lock Ȯ��
				strcpy(lock_t, sql_row[2]);
				strcpy(permit, sql_row[3]);
		} // while

		//printf("\n\n\nlock_t state : %s\n\n\n",lock_t);
		//printf("\n\n\nlock_s state : %s\n\n\n",lock_s);			
		printf(" user _ after %s before %s \n",user_name_t,user_name);
		printf(" permit _ after %s before %s \n",permit,permit_t);

		//���ο� ����� üũ
		if( (strcmp(user_name, user_name_t)))
		{
			//printf("\n\n change user! : %s -> %s\n\n", user_name_t, user_name);
			strcpy(user_name,user_name_t);
			system("pkill timer"); // ���� timer �����ϱ� ����
		} // if

		if ( (strcmp(permit, permit_t)) )
		{	
		//	printf("\n\n change permit! : %s -> %s \n\n",permit_t, permit);
			strcpy(permit_t, permit);	
			//����� ���濡 ���� �̹��� ��ü
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
		

		//lock ���� üũ
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
				system("pkill touchapp"); // ���º����� ���� ȭ�� �̹��� ��������
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

/*power state üũ�ؼ� power ���� �������� event ó��*/
void power_check(void)
{
	// dip switch�� ���� power state�� full color led ����
	if( strcmp(power_s,"0") == 0 )
	{
		system("./engineled 0 255 0 0");
		updated(2);
		// �丮���� ���� ������Ʈ
	} // if
	else if( strcmp(power_s,"1") == 0 )
	{
		system("./engineled 0 255 255 0");
		updated(2);
		// �丮���� ���� ������Ʈ
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
	// 0�� lock������

	// lock_d�� board db���� �������� ��.
	char lock_d[3];
	
	char query_1[100];
	char query_2[100];
	char query_3[100];
	// db �ʱ�ȭ

	connection = mysql_init(NULL);
	if(connection == NULL)
	{
		printf("Mysql init fail\n");
		return -1;
	} // if

	//system("./insmodtest");
	// �丮���� insmod
	system("./bitmap 1.bmp"); // �α��δ��ȭ��
	// db ����

	if(mysql_real_connect(connection, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0) == NULL)
	{
		printf("Mysql connection error : %s\n", mysql_error(connection));
		return 1;
	} // if
	printf("Successfuly connect!\n");

	// ���� flag_1�� �̿��Ͽ� ����ڰ� �α����� �Ͽ��� �ÿ��� ������ �� �ֵ��� �ϱ� ���� while�� ���� �۵���
	while(flag_1 == 0)
	{
		nQueryStat = mysql_query(connection, "SELECT * FROM board WHERE 1");
		
		if(nQueryStat != 0)
		{
			printf("Mysql query error %s\n", mysql_error(connection));
			printf("err");
		} // if
	
		// sql ���� ����
		sql_result = mysql_store_result(connection);
	
		while((sql_row = mysql_fetch_row(sql_result)) != NULL)
		{	
		// ������ ����
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
	////////////////////////// cardata���� ���� �ֱٰ��� �������� �κ��� cardata �α׸� ����� ���� �κ�//////////////////////////////////////////
	printf("\n\n %s test \n",car_number);
	
	// text lcd �ʱ�ȭ�� ���
	clearlcd();
	system("./tlcdpermit w 1 WelcometoCarPoly");
	system("./tlcdpermit w 2 Normal_state");

	// oled ����̽� �ʱ�ȭ
	system("./oledlogo i");
	if ( !(strcmp(permit_t,"1")))
	{
		// 1�̸� owner
		system("./oledlogo d owner.img");
	} // if
	else
	{
		system("./oledlogo d guest.img");
	} // else

	// �߰� ���� �ٲ��� �ϴ� �ڵ�� �̷������� ¥����.
	strcpy(query_1,"select * from carstate where carnum = '");
	strcat(query_1,car_number);
	strcat(query_1,"' order by st Desc limit 1");
	printf("\n\n query_1 %s\n\n",query_1);
	// �α����� ������� ������ȣ�� �̿��Ͽ� �ֱ� ����� �о� ���� ���� Ȯ�� 
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
		// �Ŀ�, lock ���¸� ��ִºκ�
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