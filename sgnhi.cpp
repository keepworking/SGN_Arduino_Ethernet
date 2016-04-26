#include "sgnhi.h"

dotori::dotori(char *sencode){
	senCode = sencode;
}

void dotori::printcode(){
	DEBUG_PRINT(senCode);
}


void dotori::sendvalue(int val){
	request(&val,atInt);
}

void dotori::sendvalue(float val){
	request(&val,atFloat);
}

void dotori::sendvalue(long val){
	request(&val,atLong);
}

void dotori::sendvalue(double val){
	request(&val,atDouble);
}

void dotori::request(void *val,int type){
	if (client.connect(SERVER, 80)) {
		DEBUG_PRINT("connected");
		//DEBUG_PRINT(MACHTYPE(val,type));
		client.print("GET /iot/iot_up.php?");
		client.print("uid=");client.print("admin");
		client.print("&dc=");client.print(dev.devCode);
		client.print("&sc=");client.print(senCode);
		client.print("&sv=");client.print(MACHTYPE(val,type));
		client.print(" HTTP/1.0\r\n");
		client.print("Host:veyrobotics.cafe24.com \r\n");
		client.print("User-Agent: sgnhiArduinoEthernet\r\n");
		client.print("Connection: close\r\n");
		client.print("Accept-Encoding: gzip\r\n");
		client.print("Accept-Charset: ISO-8859-1,*;q=0.7\r\n");
		client.print("Cache-Control: no-cache\r\n");
		client.print("Accept-Language: de,en;q=0.7,en-us;q=0.3\r\n");
		client.print("Referer: http://google.com/\r\n");
		client.println();
		client.stop();
	}
	else {
  		DEBUG_PRINT("connection failed");
  	}
}

/*void dotori::sendvalue(void *val){
	Serial.println(*(float*) val);
}*/

void sgnDev::init(char *id,char *devcode,IPAddress local_ip){
	if(Ethernet.begin(mac) == 0){
		DEBUG_PRINT("fail using dhcp");
		Ethernet.begin(mac,local_ip);
	}
	devCode = devcode;
	ID = id;
	DEBUG_PRINT(devCode);

	delay(1000);

	DEBUG_PRINT("connecting....");
}

sgnDev dev;

EthernetClient client;
