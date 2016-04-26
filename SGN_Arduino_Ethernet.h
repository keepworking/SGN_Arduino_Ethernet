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

#define MACHTYPE(v,t) (t == atInt?*(int*)v:(t == atFloat?*(float*)v:(t == atDouble?*(double*)v:(t == atLong?*(long*)v:0))))


#ifdef DEBUG
 #define DEBUG_PRINT(x) Serial.println(x)
#else
 #define DEBUG_PRINT(x)
#endif


class dotori {
public:
	dotori(char *sencode);
	void printcode();
	void sendvalue(int val);
	void sendvalue(float val);
	void sendvalue(long val);
	void sendvalue(double val);
	//void sendvalue(void *val);
private:
	char* senCode;
	void request(void *val,int type);
};

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
