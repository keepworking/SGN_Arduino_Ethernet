#ifndef SGNHI
#define SGNHI

#include "SPI.h"
#include "Ethernet.h"
#if ARDUINO < 100
  #include "WProgram.h"
#else
    #include "Arduino.h"
#endif

#define SERVER "veyrobotics.cafe24.com"

#define atInt 1
#define atFloat 2
#define atDouble 3
#define atLong 4

// sendvalue 함수용 반환값 정의
#define OK 0 // 서버에 데이터 전송.
#define WAIT 1 // 서버에 전송한지 대기시간이 지나지 않음, 좀더 뒤에 전송 요망.
#define ERROR 2 // 웹사이트에 접속 실패.

#define MACHTYPE(v,t) (t == atInt?*(int*)v:(t == atFloat?*(float*)v:(t == atDouble?*(double*)v:(t == atLong?*(long*)v:0))))

#define REST 1200000

//#define DEBUG

#ifdef DEBUG
 #define DEBUG_PRINT(x) Serial.println(x)
#else
 #define DEBUG_PRINT(x)
#endif

//Serial 인터페이스 - 추후 스마트폰을 이용한 초기설정 이 목적







// 아직 감도 안잡힘..

class dotori {
public:
	dotori(char *sencode);
	void printcode();
	int sendvalue(int val);
	int sendvalue(float val);
	int sendvalue(long val);
	int sendvalue(double val);
	//void sendvalue(void *val);
private:
	unsigned long sTime;
	char* senCode;
	int request(void *val,int type);
	int state = 0;
};




//장치 메인 객체 사용자가 추가할 필요 x
class sgnDev {
public:
	char* ID;
	char* devCode;
	void init(char *id,char *devCode,IPAddress local_ip);
private:

	
	byte mac[6] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

};

extern sgnDev dev;

extern EthernetClient client;


#endif
