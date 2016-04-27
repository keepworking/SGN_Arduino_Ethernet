#include "SGN_Arduino_Ethernet.h"

dotori::dotori(char *sencode){
	senCode = sencode;
}

void dotori::printcode(){
	DEBUG_PRINT(senCode);
}

//입력 변수형별 전송 데이터 타입 정리.
int dotori::sendvalue(int val){
	return request(&val,atInt);
}

int dotori::sendvalue(float val){
	return request(&val,atFloat);
}

int dotori::sendvalue(long val){
	return request(&val,atLong);
}

int dotori::sendvalue(double val){
	return request(&val,atDouble);
}


//데이터 타입과 함께 void 포인터 사용. 서버에 데이터 전송.
int dotori::request(void *val,int type){
	unsigned long now = millis();
	if(state != 0){
		if(now <= sTime){
			unsigned long lastTime = 0xffffffff - sTime;
			if(!(lastTime + now > REST)){
				return WAIT;
			}
		}else if(now - sTime < REST){
			return WAIT;
		}
	}

	
	if (client.connect(SERVER, 80)) {
		DEBUG_PRINT("connected");
		client.print("GET /iot/iot_up.php?");
		client.print("uid=");client.print("admin");
		client.print("&dc=");client.print(dev.devCode);
		client.print("&sc=");client.print(senCode);
		client.print("&sv=");client.print(MACHTYPE(val,type));
		client.print(" HTTP/1.0\r\n");
		client.print("Host:veyrobotics.cafe24.com \r\n");
		client.print("User-Agent: sgnhiArduinoEthernet\r\n");
		client.print("Connection: close\r\n");
		/*client.print("Accept-Encoding: gzip\r\n");
		client.print("Accept-Charset: ISO-8859-1,*;q=0.7\r\n");
		client.print("Cache-Control: no-cache\r\n");
		client.print("Accept-Language: de,en;q=0.7,en-us;q=0.3\r\n");
		client.print("Referer: http://google.com/\r\n");*/
		client.println();
		client.stop();
		state = 1;
		sTime = now;
	}
	else {
  		DEBUG_PRINT("connection failed");
  		return ERROR;
  	}
  	return OK;
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
