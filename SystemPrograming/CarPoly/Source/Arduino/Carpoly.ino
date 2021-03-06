#include <Thread.h>
#include <ThreadController.h>
#include <Wire.h>

//Value for Gyro Sensing

char WHO_AM_I = 0x00;
char SMPLRT_DIV= 0x15;
char DLPF_FS = 0x16;
char GYRO_XOUT_H = 0x1D;
char GYRO_XOUT_L = 0x1E;
char GYRO_YOUT_H = 0x1F;
char GYRO_YOUT_L = 0x20;
char GYRO_ZOUT_H = 0x21;
char GYRO_ZOUT_L = 0x22;
char DLPF_CFG_0 = 1<<0;
char DLPF_CFG_1 = 1<<1;
char DLPF_CFG_2 = 1<<2;
char DLPF_FS_SEL_0 = 1<<3;
char DLPF_FS_SEL_1 = 1<<4;
char itgAddress = 0x68;

//Vibration state
int vibe = -1;
//Gyro state
int gyro = -1;


int condition = -1;
// condition = 1 : stop state = only Vibration state
// condition = 2 : drive state = Vaibration state and Gyro state

// Class for MultiThread
ThreadController controll = ThreadController();

//Thread
Thread* viThread = new Thread();
Thread gyThread = Thread();

//Function for Sensing Vibration
void Vi(){
  int val;
  val=analogRead(A0);//Connect the sensor to analog pin 0      
  if(val<1000) // input vabration 
  {
    vibe= 1; //vibration state condition 
  }

}
//Fiunction for Sensing Gyro
void Gy(){
  
  int xRate, yRate, zRate;
  xRate = readX(); // x angular velocity sensing
  yRate = readY(); // y angular velocity sensing
  zRate = readZ(); // z angular velocity sensing
 /* Serial.print("x : ");
  Serial.print(xRate);
  Serial.print(" : ");
  Serial.print(xRate);
  Serial.print("x : ");
  Serial.print(xRate);*/
 if((xRate < -1000 || xRate >1000 ) || (yRate < -1000 || yRate >1000 ) || (zRate < -1000 || zRate >1000 )) // input Gyro
 {
  gyro = 1;  //gyro state condition 
 }
  
}

void setup(){
	Serial.begin(115200); 
         Wire.begin();
        
        char id=0;
        id = itgRead(itgAddress, WHO_AM_I);
        itgWrite(itgAddress, DLPF_FS, (DLPF_FS_SEL_0|DLPF_FS_SEL_1|DLPF_CFG_0));
        itgWrite(itgAddress, SMPLRT_DIV, 9);
        
        //Thread
	viThread->onRun(Vi);
	viThread->setInterval(1);
	gyThread.onRun(Gy);
	gyThread.setInterval(1);
        //Thread Controler
	controll.add(viThread);
	controll.add(&gyThread); // & to pass the pointer to it
 }

void loop(){
  
        controll.run();
        
        if(vibe == 1 && gyro != 1) // accident of stop state
        {
          Serial.println(1);
          vibe = -1; //initialize value
          condition = 1;//stop state 
          /* Send condition state to Embedded device */
          /*                                         */
          /*                                         */
          /*                                         */
        }
        else if(vibe == 1 && gyro ==1) //accident of drive state
        {
          Serial.println(2);
          vibe = -1; //initialize value
          gyro = -1; //initialize value
          condition = 2;//Drive State
          /* Send condition state to Embedded device */
          /*                                         */
          /*                                         */
          /*                                         */
          delay(10000); // 중복측정을 방지하기 위한 DELAY
          
       }
       condition = -1;  //initialize value
}


unsigned char itgRead(char address, char registerAddress)
{
  unsigned char data=0;
  Wire.beginTransmission(address);
  Wire.write(registerAddress);
  Wire.endTransmission();
  Wire.beginTransmission(address);
  Wire.requestFrom(address, 1);
  if(Wire.available()){
    data = Wire.read();
  }
  Wire.endTransmission();
  return data;
}
void itgWrite(char address, char registerAddress, char data)
{
  Wire.beginTransmission(address);
  Wire.write(registerAddress);
  Wire.write(data);
  Wire.endTransmission();
}

//Angular velocity sensing function
int readX(void)
{
  int data=0;
  data = itgRead(itgAddress, GYRO_XOUT_H)<<8;
  data |= itgRead(itgAddress, GYRO_XOUT_L);
  return data;
}
int readY(void)
{
  int data=0;
  data = itgRead(itgAddress, GYRO_YOUT_H)<<8;
  data |= itgRead(itgAddress, GYRO_YOUT_L);
  return data;
}
int readZ(void)
{
  int data=0;
  data = itgRead(itgAddress, GYRO_ZOUT_H)<<8;
  data |= itgRead(itgAddress, GYRO_ZOUT_L);
  return data;
}
