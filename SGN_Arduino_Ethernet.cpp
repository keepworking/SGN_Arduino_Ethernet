#include "SGN_Arduino_Ethernet.h"

dotori::dotori(char *sencode){
	senCode = sencode;
}

void dotori::printcode(){
	DEBUG_PRINT(senCode);
}

//입력 변수형별 전송 데이터 타입 정리.
void dotori::set(int val){
	void * vo = &val;
	value = *(uint32_t*)vo;
	argType = atInt;
}

void dotori::set(float val){
	void * vo = &val;
	value = *(uint32_t*)vo;
	argType = atFloat;
}

void dotori::set(long val){
	void * vo = &val;
	value = *(uint32_t*)vo;
	argType = atLong;
}

void dotori::set(double val){
	void * vo = &val;
	value = *(uint32_t*)vo;
	argType = atDouble;
}


//데이터 타입과 함께 void 포인터 사용. 서버에 데이터 전송.
/*int dotori::request(void *val,int type){
	//delay(1000); 딜레이 필요없음 자꾸 밀려남.
	unsigned long now = millis();

	DEBUG_PRINT("last time.");
	DEBUG_PRINT(sTime);
	DEBUG_PRINT("now time.");
	DEBUG_PRINT(now);
	DEBUG_PRINT("value");
	DEBUG_PRINT(MACHTYPE(val,type));

	if(state != 0){
		if(now <= sTime){
			unsigned long lastTime = 0xffffffff - sTime;
			if((lastTime + now < REST)){
				return WAIT;
			}
		}else if(now - sTime < REST){
			return WAIT;
		}
	}


	if (client.connect(SERVER, 80)) {
		DEBUG_PRINT("connected");
		client.flush();
		client.print("GET /iot/iot_up.php?");
		client.print("uid=");client.print("admin");
		client.print("&dc=");client.print(dev.devCode);
		client.print("&sc=");client.print(senCode);
		client.print("&sv=");client.print(MACHTYPE(val,type));
		client.print(" HTTP/1.0\r\n");
		client.print("Host:veyrobotics.cafe24.com \r\n");
		client.print("User-Agent: sgnhiArduinoEthernet\r\n");
		client.print("Connection: close\r\n");
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
}/*

/*vvoid dotori::setvalue(void *val){
	Serial.println(*(float*) val);
}*/

void sgnDev::init(char *id,char *devcode,IPAddress local_ip){
	addr = local_ip;
	init();
	devCode = devcode;
	ID = id;
	DEBUG_PRINT(devCode);

	delay(1000);

	DEBUG_PRINT("connecting....");
}
void sgnDev::init(){
	if(Ethernet.begin(mac) == 0){
		DEBUG_PRINT("fail using dhcp");
		Ethernet.begin(mac,addr);
	}
}

void sgnDev::setRest(unsigned long rest){
	restTime = rest < REST? REST:rest;
}

int sgnDev::send(dotori mdotori, ...){//iot_up 소스코드 수정해야함 -> 수정완료.
	
	//return 1;
	//send value code 아래쪽 부터.
	unsigned long now = millis();

	if(state != 0){
		if(now <= sTime){
			unsigned long lastTime = 0xffffffff - sTime;
			if((lastTime + now < restTime)){
				return WAIT;
			}
		}else if(now - sTime < restTime){
			return WAIT;
		}
	}

	if (client.connect(SERVER, 80)) {
		DEBUG_PRINT("connected");
		//client.flush();
		client.print("GET /iot/iot_up.php?");
		client.print("uid=");client.print(ID);
		client.print("&dc=");client.print(devCode);
		int cnt = 0;
		va_list vl;
		va_start(vl,mdotori);
		for(dotori m = mdotori;m.chk == 42;m= va_arg(vl,dotori)){
			uint32_t value = m.value;
			void * vo = &m.value;
			client.print("&sc");client.print(cnt);client.print("=");
			client.print(m.senCode);
			client.print("&sv");client.print(cnt);client.print("=");
			client.print(MACHTYPE(vo,m.argType));
			//
			/*#ifdef DEBUG
			Serial.print("&sc");Serial.print(cnt);Serial.print("=");
			Serial.print(m.senCode);
			Serial.print("&sv");Serial.print(cnt);Serial.print("=");
			Serial.println(MACHTYPE(vo,m.argType));
			#endif*/
			//
			cnt++;
		}
		va_end(vl);

		client.print(" HTTP/1.0\r\n");
		client.print("Host:veyrobotics.cafe24.com \r\n");
		client.print("User-Agent: sgnhi\r\n");
		client.print("Connection: close\r\n");
		client.println();
		//Serial.println();
		state = client.status() == 0?0:1;
		//state = client.status() == 0?0:1;
		//while(client.connected());
		client.stop();
		sTime = now;

	}
	else {
		Serial.println(client.status());
		client.stop();
  		DEBUG_PRINT("connection failed");
  		DEBUG_PRINT("try to begin");
  		init();
  		state = 0;
  		return ERROR;
  	}
  	return OK;
}

sgnDev dev;

EthernetClient client;
