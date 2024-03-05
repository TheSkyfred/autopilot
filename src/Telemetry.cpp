// TELEMETRY INITIALIZATION :


Void telemetry_init() {


};


Void telemetry_update(){

//ping-pong to check if telemetry is available

if (TestMode) {

telemetry_receive ();


//in test mode, if telemetry is lost, we go directly to the approach point
if (telemetry_isavailable = 0) {


};


//

}
//For TestMode Receive telemetry and check if 

};



void telemetry_receive () {

//we check if the cruise speed is modified by telemetry
if (cruise_speed != telemetry_speed) {
		cruise_speed = telemetry_speed;
	}



}



//INTERNET CODE BELOW :

/*
#include <esp_now.h>
#include <WiFi.h>

//TELEMETRY SIGNAL : faire un ping pong

//Fill the MAC adress of the reciever board
uint8_t RxMACaddress[] = { 0x40, 0x22, 0xD8, 0xE7, 0x79, 0x54 };


//defining the data messages we want to sent to reciever
typedef struct struct_message {
  int battery_level;
  float temp;
  float current_BME280_altitude;
  float current_GPS_Speed;
  int d;
  float current_GPS_Altitude;

} struct_message;
struct_message sentData;


void Telemetry_init() {
  WiFi.mode(WIFI_STA);
 //-------------------------------------------------------------------------------------
  esp_now_register_send_cb(OnDataSent);
  //-------------------------------------------------------------------------------------
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, RxMACaddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  //-------------------------------------------------------------------------------------
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

//-------------------------------------------------------------------------------------
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)  //callback function
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
//-------------------------------------------------------------------------------------

void Telemetry_send() {

//données à envoyer

  //-------------------------------------------------------------------------------------
  esp_err_t result = esp_now_send(RxMACaddress, (uint8_t *)&sentData, sizeof(sentData));
  //-------------------------------------------------------------------------------------
  if (result == ESP_OK) Serial.println("Sent with success");
  else Serial.println("Error sending the data");
  //-------------------------------------------------------------------------------------
  delay(500);

}




// SUITE


void init_telemetry(void) {
	SerialOpen(TELEMETRY_SERIAL, TELEMETRY_BAUD);
}

void write_FrSky8(uint8_t Data) {
	SerialWrite(TELEMETRY_SERIAL, Data);
}

void check_FrSky_stuffing(uint8_t Data) //byte stuffing
		{
	if (Data == 0x5E) {
		write_FrSky8(0x5D);
		write_FrSky8(0x3E);
	} else if (Data == 0x5D) {
		write_FrSky8(0x5D);
		write_FrSky8(0x3D);
	} else {
		write_FrSky8(Data);
	}
}

void write_FrSky16(uint16_t Data) {
	uint8_t Data_send;
	Data_send = Data;
	check_FrSky_stuffing(Data_send);
	Data_send = Data >> 8 & 0xff;
	check_FrSky_stuffing(Data_send);
}

static void sendDataHead(uint8_t Data_id) {
	write_FrSky8(Protocol_Header);
	write_FrSky8(Data_id);
}

static void sendDataTail(void) {
	write_FrSky8(Protocol_Tail);
}

//*********************************************************************************
//-----------------   Telemetrie Data   ------------------------------------------   
//*********************************************************************************


// Distance to home and NumSats
void send_Temperature(void) {
/*
#if BARO
	int16_t Data_Temperature1;
	Data_Temperature1 = (baroTemperature + 50) / 100;
	sendDataHead(ID_Temperature1);
	write_FrSky16(Data_Temperature1);
#endif
*/


/*

#if GPS
	// Distance to home as Temperature 1
	sendDataHead(ID_Temperature1);
	write_FrSky16(f.GPS_FIX_HOME ? GPS_distanceToHome : 0); // Distance to home

	//int16_t Data_NumSats;
	//if (f.GPS_FIX && GPS_numSat > 0) {
		//Data_NumSats = GPS_numSat;
		sendDataHead(ID_Temperature2); // Number of satellites as Temperature 2
		write_FrSky16(GPS_numSat);
	//}
#endif
}

// RPM
void send_RPM(void) {
	sendDataHead(ID_RPM);
	if ((f.BARO_MODE
#if GPS
			|| f.GPS_BARO_MODE
#endif
			) && f.ARMED) {

		write_FrSky16(targetVario / 3);
	} else {
		write_FrSky16(rcCommand[THROTTLE] / 3);
	}
}

// RPM is interpreted as Return distance to home Position in Meter
/* void inline send_RPM(void) {
#if GPS
	uint16_t Data_RPM;
	if (f.GPS_FIX && GPS_numSat >= 3) {
		Data_RPM = GPS_distanceToHome; // Distance to home alias RPM
		sendDataHead(ID_RPM);
		write_FrSky16(Data_RPM);
	}
#endif
} */

// Fuel level
void send_Fuel(void) {
#if defined(POWERMETER)
	uint16_t Data_Fuel;
	if ((pMeter[PMOTOR_SUM] < (pAlarm / 4)) || (pAlarm == 0))
	Data_Fuel = 100;
	else if (pMeter[PMOTOR_SUM] < (pAlarm / 2))
	Data_Fuel = 75;
	else if (pMeter[PMOTOR_SUM] < (3 * pAlarm / 4))
	Data_Fuel = 50;
	else if (pMeter[PMOTOR_SUM] < pAlarm)
	Data_Fuel = 25;
	else
	Data_Fuel = 0;
	sendDataHead(ID_Fuel_level);
	write_FrSky16(Data_Fuel);
#endif
}

// Cell voltage 
void send_cell_volt(void) // Data compatibel to FrSky FLVS-01 voltage sensor
		{
#if defined(VBAT_CELLS)
	uint16_t Data_Volt;
	uint16_t temp;
	static uint8_t cell_counter = 0;
	// the resolution of analog.vbatcells results in only one decimal (eg 3.70V or 3.80V and nothing in between)
	// TODO: improve resolution of analog.vbatcells
	temp = 50 * analog.vbatcells[cell_counter];
	Data_Volt = (temp << 8) + (temp >> 8) + (cell_counter << 4);
	if (++cell_counter >= VBAT_CELLS_NUM)
	cell_counter = 0;
	sendDataHead(ID_Volt);
	write_FrSky16(Data_Volt);
#endif
}

// Altitude
void send_Altitude(void) {
#if defined(TELEMETRY_ALT_BARO) and BARO
#if defined(FRSKY_FLD02)
	int16_t Data_altitude;
	//Data_altitude = (alt.estAlt + 50) / 100;
	Data_altitude = alt.estAlt / 100;
	sendDataHead(ID_GPS_Altitude_bp);
	//write_FrSky16(GPS_HDOP); // HDOP as gps altitude
	write_FrSky16(Data_altitude); // estAlt as gps altitude

	sendDataHead(ID_Altitude_bp);
	write_FrSky16(Data_altitude);

	//Data_altitude = abs(alt.estAlt - (int32_t)Data_altitude * 100);
	//sendDataHead(ID_Altitude_ap);
	//write_FrSky16(Data_altitude);

#endif
#if defined OPENTX
	int16_t Data_altitude_bp, Data_altitude_ap;
	Data_altitude_bp = alt.estAlt / 100;
	sendDataHead(ID_Altitude_bp);
	write_FrSky16(Data_altitude_bp);
	Data_altitude_ap = alt.estAlt - Data_altitude_bp * 100;
	sendDataHead(ID_Altitude_ap);
	write_FrSky16(Data_altitude_ap);
#endif
#endif
#if defined(TELEMETRY_ALT_GPS) and GPS
#if defined(FRSKY_FLD02)
#if not defined(TELEMETRY_ALT_BARO)
	int16_t Data_altitude;
	if (f.GPS_FIX && GPS_numSat >= 4) {
		Data_altitude = GPS_altitude;
		sendDataHead(ID_Altitude_bp);
		write_FrSky16(Data_altitude);
	}
#endif
#else
	int16_t Data_GPS_altitude_bp;
	uint16_t Data_GPS_altitude_ap;
	if (f.GPS_FIX && GPS_numSat >= 4) {
		Data_GPS_altitude_bp = GPS_altitude;
		Data_GPS_altitude_ap = 0;
		sendDataHead(ID_GPS_Altitude_bp);
		write_FrSky16(Data_GPS_altitude_bp);
		sendDataHead(ID_GPS_Altitude_ap);
		write_FrSky16(Data_GPS_altitude_ap);
	}
#endif
#endif
}

// Course
void send_Course(void) {
//#if not defined(FRSKY_FLD02)
#if defined TELEMETRY_COURSE_GPS and GPS
	uint16_t Data_Course_bp;
	uint16_t Data_Course_ap;
	if (f.GPS_FIX && GPS_numSat >= 4) {
		Data_Course_bp = GPS_ground_course / 10;
		Data_Course_ap = GPS_ground_course - Data_Course_bp * 10;
		sendDataHead(ID_Course_bp);
		write_FrSky16(Data_Course_bp);
		sendDataHead(ID_Course_ap);
		write_FrSky16(Data_Course_ap);
	}
#elif defined TELEMETRY_COURSE_MAG and MAG
	uint16_t Data_Course_bp;
	//uint16_t Data_Course_ap;
	Data_Course_bp = att.heading;
	//Data_Course_ap = 0;
	sendDataHead(ID_Course_bp);
	write_FrSky16(Data_Course_bp);
	//sendDataHead(ID_Course_ap);
	//write_FrSky16(Data_Course_ap);
#endif
//#endif
}

// GPS speed
void send_GPS_speed(void) {
#if GPS
	uint16_t Data_GPS_speed_bp;
	uint16_t Data_GPS_speed_ap;
	uint16_t temp;
	if (f.GPS_FIX && GPS_numSat >= 3) {
#if defined KILOMETER_HOUR                                        // OPENTX specific format in kilometers per hour => factor 36/100 (will be devided by 10 later)
		temp = (GPS_speed * 36) / 10;
#else                                                             // FRSKY specific format in knots => factor ~50 (will be devided by 10 later)
		temp = (GPS_speed * 40) / 203;
#endif
		Data_GPS_speed_bp = temp / 100;          // here comes the devision by 10
		//Data_GPS_speed_ap = temp - Data_GPS_speed_bp * 100;
		sendDataHead(ID_GPS_speed_bp);
		write_FrSky16(Data_GPS_speed_bp);
		//sendDataHead(ID_GPS_speed_ap);
		//write_FrSky16(Data_GPS_speed_ap);
	}
#endif
}

// GPS position
void send_GPS_longitude(void) {
#if GPS
	uint16_t Data_Longitude_bp;
	uint16_t Data_Longitude_ap;
	uint16_t Data_E_W;
	uint32_t temp, rest, decimal;
	if (f.GPS_FIX && GPS_numSat >= 3) {
		temp = abs(GPS_coord[LON]);
#if defined(COORDFORMAT_DECIMALMINUTES)
		decimal = temp / 10000000;
		temp -= decimal * 10000000;
		temp *= 6;
		rest = temp;
		temp /= 1000000;
		rest -= temp * 1000000;
		Data_Longitude_bp = decimal * 100 + temp;
		Data_Longitude_ap = rest / 100;
#else
		decimal = temp / 100000;
		rest = temp - decimal * 100000;
		Data_Longitude_bp = decimal;
		Data_Longitude_ap = rest / 10;
#endif
		Data_E_W = GPS_coord[LON] < 0 ? 'W' : 'E';
		sendDataHead(ID_Longitude_bp);
		write_FrSky16(Data_Longitude_bp);
		sendDataHead(ID_Longitude_ap);
		write_FrSky16(Data_Longitude_ap);
		sendDataHead(ID_E_W);
		write_FrSky16(Data_E_W);
	}
#endif
}

void send_GPS_latitude(void) {
#if GPS
	uint16_t Data_Latitude_bp;
	uint16_t Data_Latitude_ap;
	uint16_t Data_N_S;
	uint32_t temp, rest, decimal;
	if (f.GPS_FIX && GPS_numSat >= 3) {
		temp = abs(GPS_coord[LAT]);
#if defined(COORDFORMAT_DECIMALMINUTES)
		decimal = temp / 10000000;
		temp -= decimal * 10000000;
		temp *= 6;
		rest = temp;
		temp /= 1000000;
		rest -= temp * 1000000;
		Data_Latitude_bp = decimal * 100 + temp;
		Data_Latitude_ap = rest / 100;
#else
		decimal = temp / 100000;
		rest = temp - decimal * 100000;
		Data_Latitude_bp = decimal;
		Data_Latitude_ap = rest / 10;
#endif
		Data_N_S = GPS_coord[LAT] < 0 ? 'S' : 'N';
		sendDataHead(ID_Latitude_bp);
		write_FrSky16(Data_Latitude_bp);
		sendDataHead(ID_Latitude_ap);
		write_FrSky16(Data_Latitude_ap);
		sendDataHead(ID_N_S);
		write_FrSky16(Data_N_S);
	}
#endif
}

// Time of arming
void send_Time(void) {
	uint16_t seconds_since_start;
	uint16_t Data_rest;
	uint16_t Data_hours;
	uint16_t Data_minutes;
	uint16_t Data_seconds;
	if (f.ARMED) {
		seconds_since_start = armedTime / 1000000;
		Data_hours = seconds_since_start / 3600;
		Data_rest = seconds_since_start - Data_hours * 3600;
		Data_minutes = Data_rest / 60;
		Data_seconds = Data_rest - Data_minutes * 60;
		sendDataHead(ID_Hour_Minute);
		write_FrSky16(Data_hours + Data_minutes * 256);
		sendDataHead(ID_Second);
		write_FrSky16(Data_seconds);
	}
}

// ACC
void send_Accel(void) {
#if ACC
	int16_t Data_Acc_X;
	int16_t Data_Acc_Y;
	int16_t Data_Acc_Z;
	Data_Acc_X = ((float) imu.accSmooth[0] / ACC_1G) * 1000;
	Data_Acc_Y = ((float) imu.accSmooth[1] / ACC_1G) * 1000;
	Data_Acc_Z = ((float) imu.accSmooth[2] / ACC_1G) * 1000;
	sendDataHead(ID_Acc_X);
	write_FrSky16(Data_Acc_X);
	sendDataHead(ID_Acc_Y);
	write_FrSky16(Data_Acc_Y);
	sendDataHead(ID_Acc_Z);
	write_FrSky16(Data_Acc_Z);
#endif
}

// Main function FrSky telemetry
void run_telemetry(void) {
	static uint32_t lastTime;
	static uint8_t tele_loop;
	if ((millis() - lastTime) > 125) {
		// Data sent every 125ms due to scheduler
		lastTime = millis();
		tele_loop++;
		switch (tele_loop) {
		case 1:
			send_Temperature(); // Distance to home and NumSats
			send_Voltage_ampere();
			//send_Accel();
			break;
		case 2:
			send_Fuel();
			send_GPS_longitude();
			break;
		case 3:
			send_GPS_speed();
			//send_Accel();
			break;
		case 4:
			send_Altitude();
			send_Course();
			break;
		case 5:
			send_Temperature(); // Distance to home and NumSats
			send_Voltage_ampere();
			//send_Accel();
			break;
		case 6:
			send_RPM();
			send_GPS_latitude();
			break;
		case 7:
			send_GPS_speed();
			//send_Accel();
			send_cell_volt();
			break;
		default:
			send_Altitude();
			send_Course();
			//send_Time();
			tele_loop = 0;
			break;
		}
		sendDataTail();
	}
}
#endif // FRSKY telemetry

#if defined(SPORT_TELEMETRY)

static short _FrSkySport_crc;
static short _currentGPSValue;

void FrSkySport_sendByte(uint8_t byte)
{
	// CRC update
	_FrSkySport_crc += byte;//0-1FF
	_FrSkySport_crc += _FrSkySport_crc >> 8;//0-100
	_FrSkySport_crc &= 0x00ff;
	_FrSkySport_crc += _FrSkySport_crc >> 8;//0-0FF
	_FrSkySport_crc &= 0x00ff;

	if ( (byte == FRSKY_START_STOP) || (byte == FRSKY_BYTESTUFF) ) {
		SerialWrite(TELEMETRY_SERIAL, FRSKY_BYTESTUFF);
		byte &= ~FRSKY_STUFF_MASK;
	}

	SerialWrite(TELEMETRY_SERIAL, byte);
}

void FrSkySport_sendCrc()
{
	FrSkySport_sendByte(0xFF - _FrSkySport_crc);
}

void FrSkySport_sendValue(uint16_t id, uint32_t value)
{
	_FrSkySport_crc = 0; // Reset CRC
	FrSkySport_sendByte(0x10);// DATA_FRAME
	uint8_t *bytes = (uint8_t*)&id;
	FrSkySport_sendByte(bytes[0]);
	FrSkySport_sendByte(bytes[1]);
	bytes = (uint8_t*)&value;
	FrSkySport_sendByte(bytes[0]);
	FrSkySport_sendByte(bytes[1]);
	FrSkySport_sendByte(bytes[2]);
	FrSkySport_sendByte(bytes[3]);
	FrSkySport_sendCrc();
}

void FrSkySport_sendA2voltage()
{
#ifdef VBAT
	uint32_t opentx_val = (255.0 * (float)(analog.vbat / (float)FRSKY_SPORT_A2_MAX));
	FrSkySport_sendValue(FRSKY_SPORT_ADC2_ID, (opentx_val));
#endif
}

uint32_t FrSkySport_EncodeCoordinate(float latLon, bool isLat)
{
#if GPS
	uint32_t otx_coord = 0;
	if (!isLat)
	{
		otx_coord = abs(latLon); // now we have unsigned value and one bit to spare
		otx_coord = (otx_coord + otx_coord / 2) / 25 | 0x80000000;// 6/100 = 1.5/25, division by power of 2 is fast
		if (latLon < 0) otx_coord |= 0x40000000;
	}
	else {
		otx_coord = abs(latLon); // now we have unsigned value and one bit to spare
		otx_coord = (otx_coord + otx_coord / 2) / 25;// 6/100 = 1.5/25, division by power of 2 is fast
		if (latLon < 0) otx_coord |= 0x40000000;
	}
	return otx_coord;
#endif
}

void FrSkySport_sendGPSCoordinate()
{
#if GPS
	uint32_t GPSValueToSend = 0;

	if (f.GPS_FIX && GPS_numSat >= 4)
	{
		switch (_currentGPSValue)
		{
			case 0:
			GPSValueToSend = FrSkySport_EncodeCoordinate(GPS_coord[LON], false);
			_currentGPSValue = 1;
			break;
			case 1:
			GPSValueToSend = FrSkySport_EncodeCoordinate(GPS_coord[LAT], true);
			_currentGPSValue = 0;
			break;
		}
		FrSkySport_sendValue(FRSKY_SPORT_GPS_LONG_LATI_ID, GPSValueToSend);
	}
#endif
}

void FrSkySport_sendGPSAltitude()
{
#if defined(TELEMETRY_ALT_GPS) and GPS
	if (f.GPS_FIX && GPS_numSat >= 4)
	{
		FrSkySport_sendValue(FRSKY_SPORT_GPS_ALT_ID, (int32_t)(GPS_altitude)); // m???
	}
#endif
}

void FrSkySport_sendGPSSpeed() {
#if GPS
	if (f.GPS_FIX && GPS_numSat >= 4)
	{
		uint32_t speed = ((float)GPS_speed * 100);
		FrSkySport_sendValue(FRSKY_SPORT_GPS_SPEED_ID, speed); // unknown unit, just a guess
	}
#endif
}

void FrSkySport_sendAltitude()
{
#if defined(TELEMETRY_ALT_BARO) and BARO
	FrSkySport_sendValue(FRSKY_SPORT_ALT_ID, (int32_t)(alt.estAlt) * 100); // cm
#endif
}

void FrSkySport_sendHeading()
{
#if defined(TELEMETRY_COURSE_MAG) or (defined(TELEMETRY_COURSE_GPS) and GPS)
#if defined(TELEMETRY_COURSE_MAG)
	uint32_t otx_heading = (uint32_t)(att.heading + 360) % 360 * 100;
	FrSkySport_sendValue(FRSKY_SPORT_GPS_COURS_ID, otx_heading); // 1 deg = 100, 0 - 359000
#elif defined(TELEMETRY_COURSE_GPS) && defined(GPS)
	if (f.GPS_FIX && GPS_numSat >= 4)
	{
		uint32_t otx_heading = (uint32_t)(GPS_ground_course + 360) % 360 * 100;
		FrSkySport_sendValue(FRSKY_SPORT_GPS_COURS_ID, otx_heading); // 1 deg = 100, 0 - 359000
	}
#endif
#endif
}

void FrSkySport_sendACCX()
{
#ifdef ACC
	FrSkySport_sendValue(FRSKY_SPORT_ACCX_ID, imu.accSmooth[0] / 5); // unknown unit
#endif
}

void FrSkySport_sendACCY()
{
#ifdef ACC
	FrSkySport_sendValue(FRSKY_SPORT_ACCY_ID, imu.accSmooth[1] / 5); // unknown unit
#endif
}

void FrSkySport_sendACCZ()
{
#ifdef ACC
	FrSkySport_sendValue(FRSKY_SPORT_ACCZ_ID, imu.accSmooth[2] / 5); // unknown unit
#endif
}

void FrSkySport_sendAltVario()
{
#ifdef VARIOMETER
	FrSkySport_sendValue(FRSKY_SPORT_VARIO_ID, ((uint32_t)alt.vario)); // unknown unit
#endif
}


*/