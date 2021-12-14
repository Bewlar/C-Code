/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * Author: Alex Beaulier beaulier@pdx.edu
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "STM_MY_LCD16X2.h"
#include "MY_NRF24.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint8_t flag = 0;
// this interrupts changes flag to 1 as soon as the uint8_t buff[] is full
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

	flag = 1;

}
// function to calculate checksum of the NMEA sentence
// -4, but not -3 because the NMEA sentences are delimited with \r\n, and there also is the invisible \r in the end
int nmea0183_checksum(char *msg) {

	int checksum = 0;
	int j = 0;

	// the first $ sign and the last two bytes of original CRC + the * sign
	for (j = 1; j < strlen(msg) - 4; j++) {
		checksum = checksum ^ (unsigned) msg[j];
	}

	return checksum;
}

char *strdup (const char *s)
{
  size_t len = strlen (s) + 1;
  void *new = malloc (len);
  if (new == NULL)
    return NULL;
  return (char *) memcpy (new, s, len);
}

char *mystrsep(char **stringp, const char *delim) {
    char *rv = *stringp;
    if (rv) {
        *stringp += strcspn(*stringp, delim);
        if (**stringp)
            *(*stringp)++ = '\0';
        else
            *stringp = 0; }
    return rv;
}

//Needed to convert lat long from deg | minutes.decimal minutes to deg//
float latlonConverter(char *dg, char *minutes){
	float convertedvalue;
	convertedvalue = atof(dg);
	convertedvalue = convertedvalue + (atof(minutes)/60);
	return convertedvalue;
}
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	//static uint8_t REG_LIDAR = 0x03;
	//uint8_t BUF[12];
	//HAL_StatusTypeDef LidarReturn;
	//int16_t val;
	uint8_t cmd[1];
	uint8_t data[2]={10};
	float Latitude1;
	float Longitude1;
  float LatitudeTarget;
	float LongitudeTarget;
	
	
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
	
	//LCD TEST CODE
	LCD1602_Begin4BIT(RS_LCD_GPIO_Port, RS_LCD_Pin, ENABLE_LCD_Pin, D4_GPIO_Port, D4_Pin, D5_Pin, D6_Pin, D7_Pin);  //D0_GPIO_Port, D0_Pin, D1_Pin, D2_Pin, D3_Pin,
	
	//Math
	#ifndef M_PI
	#define M_PI 3.1415926535897932f
	#endif
	
	
	//TURN ON 100m RADIO TRANSMITTER
	uint64_t TXPipeAddress = 0x11223344AA;
	NRF24_begin(CE_PIN_GPIO_Port, CSN_PIN_Pin, CE_PIN_Pin, hspi1);
	NRF24_stopListening(); //Incase was in receive mode
	NRF24_openWritingPipe(TXPipeAddress); 
	NRF24_setAutoAck(false);
	NRF24_setChannel(52);
	NRF24_setPayloadSize(32);
	NRF24_setDataRate(RF24_250KBPS);
	char myTxData[32];
	
	//GPS DATA CONSTRUCTS
	uint8_t buff[255];
	char buffStr[255];
	char nmeaSnt[80];
	char *rawSum;
	char smNmbr[3];


	// The Equator has a latitude of 0�,
	//the North Pole has a latitude of 90� North (written 90� N or +90�),
	//and the South Pole has a latitude of 90� South (written 90� S or -90�)
	char *latRaw;
	char latDg[3];
	char latMS[8];
	char *hemNS;

	// longitude in degrees (0� at the Prime Meridian to +180� eastward and -180� westward)
	// that is why 3
	char *lonRaw;
	char lonDg[4];
	char lonMS[8];
	char *hemEW;
	
	/**
	char *utcRaw; // raw UTC time from the NMEA sentence in the hhmmss format
	char strUTC[9]; // UTC time in the readable hh:mm:ss format
	char hH[3]; // hours
	char mM[3]; // minutes
	char sS[3]; // seconds*/ //Taken out to free up the stack. Had memory leak issues strdup and still large amounts of code to add...
	uint8_t cnt = 0;
	HAL_UART_Receive_DMA(&huart1, buff, 255);
	
	char *token, *string;
	string = malloc(255*sizeof(char));

	//COMPASS CONSTRUCTS (NEO6M) //https://stackoverflow.com/questions/52274197/i2c-with-stm32f4-using-hmc5883l
	uint8_t DataMagX[2];
	volatile uint16_t Xaxis = 0;
	uint8_t DataMagY[2];
	volatile uint16_t Yaxis = 0;
	uint8_t DataMagZ[2];
	volatile uint16_t Zaxis = 0;
	// HMC5883l - ADDRESS
	#define HMC5883l_ADDRESS (0x1E << 1)
	// CONTROL REG A
	#define HMC5883l_Enable_A (0x78)
	// CONTROL REG B
	#define HMC5883l_Enable_B (0xA0)
	// MODE REGISTER
	#define HMC5883l_MR (0x00)
	// HMC5883l - MSB / LSB ADDRESSES
	#define HMC5883l_ADD_DATAX_MSB (0x03)
	#define HMC5883l_ADD_DATAX_LSB (0x04)
	#define HMC5883l_ADD_DATAZ_MSB (0x05)
	#define HMC5883l_ADD_DATAZ_LSB (0x06)
	#define HMC5883l_ADD_DATAY_MSB (0x07)
	#define HMC5883l_ADD_DATAY_LSB (0x08)
	// SUM (MSB + LSB) DEFINE
	#define HMC5883l_ADD_DATAX_MSB_MULTI (HMC5883l_ADD_DATAX_MSB | 0x80)
	#define HMC5883l_ADD_DATAY_MSB_MULTI (HMC5883l_ADD_DATAY_MSB | 0x80)
	#define HMC5883l_ADD_DATAZ_MSB_MULTI (HMC5883l_ADD_DATAZ_MSB | 0x80) 
	
	uint8_t RegSettingA = HMC5883l_Enable_A;
	uint8_t RegSettingB = HMC5883l_Enable_B;
	uint8_t RegSettingMR = HMC5883l_MR;
	
	Xaxis = 0;
	Yaxis = 0;
	Zaxis = 0;
	
	//Declination offset 15.0833 deg | 0.2632532471 radians | East(CW) //Volatile settings to watch variables
	volatile float CompassHeadingRadians;
	volatile float CompassHeadingDegrees;
	float DeclinationAngleRadians = 0.2632532471; //See mag cal website magnetic-declination.com | Converted deg/*minutes into radians | This is an offset due to earths mag fields
	
	//Initialize Compass
	HAL_I2C_Mem_Write(&hi2c1, HMC5883l_ADDRESS, 0x00 , 1, &RegSettingA , 1, 100);
	HAL_I2C_Mem_Write(&hi2c1, HMC5883l_ADDRESS, 0x01 , 1, &RegSettingB , 1, 100);
	HAL_I2C_Mem_Write(&hi2c1, HMC5883l_ADDRESS, 0x02 , 1, &RegSettingMR , 1, 100);

	//LIDAR DATA CONSTRUCTS
	volatile int distance;
	volatile float distancefloated;
	float earthRadius = 6358.137; //km
	char LCDBuffer[17];
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
while (1){
    /* USER CODE BEGIN 3 */
		//GPS DATA ACQUISITION IF BUFFER READY
		if (flag == 1) { // interrupt signals that the buffer buff[300] is full

                            			/*

                            			 $ - Start delimiter
                            			 * - Checksum delimiter
                            			 , - Field delimiter

                            			 1. $GNGLL log header
                            			 2. Latitude (Ddmm.mm) [The Equator has a latitude of 0�, the North Pole has a latitude of 90� North (written 90� N or +90�)]
                            			 3. Latitude direction (N = North, S = South)
                            			 4. Longitude (DDDmm.mm) [0� at the Prime Meridian to +180� eastward and -180� westward]
                            			 5. Longitude direction (E = East, W = West)
                            			 6. UTC time status of position (hours/minutes/seconds/decimal seconds) hhmmss
                            			 7. Data status: A = Data valid, V = Data invalid
                            			 8. Positioning system mode indicator
                            			 9. *xx Checksum
                            			 10. [CR][LF] Sentence terminator. In C \r\n (two characters).
                            			  or \r Carriage return
                            			  or \n Line feed, end delimiter

                            			 */

                            			memset(buffStr, 0, 255);

                            			sprintf(buffStr, "%s", buff);

                            			// if we want to display the incoming raw data
                            			//HAL_UART_Transmit(&huart2, buff, 255, 70);

                            			// splitting the buffStr by the "\n" delimiter with the mystrsep() C function
                            			// see http://www.manpagez.com/man/3/mystrsep/
                            			
                            			string = buffStr;
                            			// actually splitting the string by "\n" delimiter
                            			while ((token = mystrsep(&string, "\n")) != NULL) {
																		memset(nmeaSnt, 0, 80);

                            				sprintf(nmeaSnt, "%s", token);
																		

																		//SCAN FOR SPECIFIC GPS STATEMENTS THAT HAVE LAT LON DATA
																		//REFERENCED http://aprs.gids.nl/nmea/#gll for GPS commands
																		//GPGSV Doesn't contain any data, only satellite info
																		/*if ((strstr(nmeaSnt, "$GPGSV") != 0) && strlen(nmeaSnt) > 46 && strstr(nmeaSnt, "*") != 0) {
																			rawSum = strstr(nmeaSnt, "*");
																		}*/
																		if ((strstr(nmeaSnt, "$GPGLL") != 0) && strlen(nmeaSnt) > 46 && strstr(nmeaSnt, "*") != 0) {

                            					rawSum = strstr(nmeaSnt, "*");
                            					memcpy(smNmbr, &rawSum[1], 2);
                            					smNmbr[2] = '\0';
                            					uint8_t intSum = nmea0183_checksum(nmeaSnt);
                            					char hex[2];
                            					// "%X" unsigned hexadecimal integer (capital letters)
                            					sprintf(hex, "%X", intSum);

                            					// checksum data verification, if OK, then we can really trust
                            					// the data in the the NMEA sentence
                            					if (strstr(smNmbr, hex) != NULL) {

                            						//if we want display good $GNGLL NMEA sentences
                            						//HAL_UART_Transmit(&huart2, nmeaSnt, 50, 70);
                            						//HAL_UART_Transmit(&huart2, (uint8_t*) "\n", 1, 200);

                            						cnt = 0;

                            						// splitting the good NMEA sentence into the tokens by the comma delimiter
                            						for (char *pV = strtok(nmeaSnt, ","); pV != NULL; pV = strtok(NULL, ",")) {

                            							switch (cnt) {
                            							case 1:
                            								latRaw = strdup(pV);
                            								break;
                            							case 2:
                            								hemNS = strdup(pV);
                            								break;
                            							case 3:
                            								lonRaw = strdup(pV);
                            								break;
                            							case 4:
                            								hemEW = strdup(pV);
                            								break;
                            							}

                            							cnt++;

                            						}  // end for()

                            						memcpy(latDg, &latRaw[0], 2);
                            						latDg[2] = '\0';

                            						memcpy(latMS, &latRaw[2], 7);
                            						latMS[7] = '\0';

                            						memcpy(lonDg, &lonRaw[0], 3);
                            						lonDg[3] = '\0';

                            						memcpy(lonMS, &lonRaw[3], 7);
                            						lonMS[7] = '\0';
                            						char strLonMS[7];
                            						sprintf(strLonMS, "%s", lonMS);
																				
																				free((void*)latRaw);
																				free((void*)lonRaw);
																				free((void*)hemEW);
																				free((void*)hemNS);
																				
																				Latitude1 = latlonConverter(latDg,latMS);
																				Longitude1 = latlonConverter(lonDg,lonMS);
                            					} // end of of the checksum data verification

                            				
																		}
																		else if ((strstr(nmeaSnt, "$GPRMC") != 0) && strlen(nmeaSnt) > 46 && strstr(nmeaSnt, "*") != 0) {

                            					rawSum = strstr(nmeaSnt, "*");
                            					memcpy(smNmbr, &rawSum[1], 2);
                            					smNmbr[2] = '\0';
                            					uint8_t intSum = nmea0183_checksum(nmeaSnt);
                            					char hex[2];
                            					// "%X" unsigned hexadecimal integer (capital letters)
                            					sprintf(hex, "%X", intSum);

                            					// checksum data verification, if OK, then we can really trust
                            					// the data in the the NMEA sentence
                            					if (strstr(smNmbr, hex) != NULL) {

                            						//if we want display good $GNGLL NMEA sentences
                            						//HAL_UART_Transmit(&huart2, nmeaSnt, 50, 70);
                            						//HAL_UART_Transmit(&huart2, (uint8_t*) "\n", 1, 200);

                            						cnt = 0;

                            						// splitting the good NMEA sentence into the tokens by the comma delimiter
                            						for (char *pV = strtok(nmeaSnt, ","); pV != NULL; pV = strtok(NULL, ",")) {

                            							switch (cnt) {
                            							case 3:
                            								latRaw = strdup(pV);
                            								break;
                            							case 4:
                            								hemNS = strdup(pV);
                            								break;
                            							case 5:
                            								lonRaw = strdup(pV);
                            								break;
                            							case 6:
                            								hemEW = strdup(pV);
                            								break;
                            							}

                            							cnt++;

                            						}  // end for()

                            						memcpy(latDg, &latRaw[0], 2);
                            						latDg[2] = '\0';

                            						memcpy(latMS, &latRaw[2], 7);
                            						latMS[7] = '\0';

                            						memcpy(lonDg, &lonRaw[0], 3);
                            						lonDg[3] = '\0';

                            						memcpy(lonMS, &lonRaw[3], 7);
                            						lonMS[7] = '\0';
                            						char strLonMS[7];
                            						sprintf(strLonMS, "%s", lonMS);
																				
																				free((void*)latRaw);
																				free((void*)lonRaw);
																				free((void*)hemEW);
																				free((void*)hemNS);

																				Latitude1 = latlonConverter(latDg,latMS);
																				Longitude1 = latlonConverter(lonDg,lonMS);
                            					} // end of of the checksum data verification

                            				
																		}
																		/*else if ((strstr(nmeaSnt, "$GPGSA") != 0) && strlen(nmeaSnt) > 46 && strstr(nmeaSnt, "*") != 0) {

                            					rawSum = strstr(nmeaSnt, "*");
                            					memcpy(smNmbr, &rawSum[1], 2);
                            					smNmbr[2] = '\0';
                            					uint8_t intSum = nmea0183_checksum(nmeaSnt);
                            					char hex[2];
                            					// "%X" unsigned hexadecimal integer (capital letters)
                            					sprintf(hex, "%X", intSum);

                            					// checksum data verification, if OK, then we can really trust
                            					// the data in the the NMEA sentence
                            					if (strstr(smNmbr, hex) != NULL) {

                            						//if we want display good $GNGLL NMEA sentences
                            						//HAL_UART_Transmit(&huart2, nmeaSnt, 50, 70);
                            						//HAL_UART_Transmit(&huart2, (uint8_t*) "\n", 1, 200);

                            						cnt = 0;

                            						// splitting the good NMEA sentence into the tokens by the comma delimiter
                            						for (char *pV = strtok(nmeaSnt, ","); pV != NULL; pV = strtok(NULL, ",")) {

                            							switch (cnt) {
                            							case 1:
                            								latRaw = strdup(pV);
                            								break;
                            							case 2:
                            								hemNS = strdup(pV);
                            								break;
                            							case 3:
                            								lonRaw = strdup(pV);
                            								break;
                            							case 4:
                            								hemEW = strdup(pV);
                            								break;
                            							case 5:
                            								utcRaw = strdup(pV);
                            								break;
                            							}

                            							cnt++;

                            						}  // end for()

                            						memcpy(latDg, &latRaw[0], 2);
                            						latDg[2] = '\0';

                            						memcpy(latMS, &latRaw[2], 7);
                            						latMS[7] = '\0';

                            						memcpy(lonDg, &lonRaw[0], 3);
                            						lonDg[3] = '\0';

                            						memcpy(lonMS, &lonRaw[3], 7);
                            						lonMS[7] = '\0';
                            						char strLonMS[7];
                            						sprintf(strLonMS, "%s", lonMS);

                            						//converting the UTC time in the hh:mm:ss format
                            						memcpy(hH, &utcRaw[0], 2);
                            						hH[2] = '\0';

                            						memcpy(mM, &utcRaw[2], 2);
                            						mM[2] = '\0';

                            						memcpy(sS, &utcRaw[4], 2);
                            						sS[2] = '\0';

                            						strcpy(strUTC, hH);
                            						strcat(strUTC, ":");
                            						strcat(strUTC, mM);
                            						strcat(strUTC, ":");
                            						strcat(strUTC, sS);
                            						strUTC[8] = '\0';
                            					} // end of of the checksum data verification

                            				
																		}*/
                            				else if ((strstr(nmeaSnt, "$GPGGA") != 0) && strlen(nmeaSnt) > 46 && strstr(nmeaSnt, "*") != 0) {

                            					rawSum = strstr(nmeaSnt, "*");
                            					memcpy(smNmbr, &rawSum[1], 2);
                            					smNmbr[2] = '\0';
                            					uint8_t intSum = nmea0183_checksum(nmeaSnt);
                            					char hex[2];

                            					// "%X" unsigned hexadecimal integer (capital letters)
                            					sprintf(hex, "%X", intSum);

                            					// checksum data verification, if OK, then we can really trust
                            					// the data in the the NMEA sentence
                            					if (strstr(smNmbr, hex) != NULL) {

                            						//if we want display good $GNGLL NMEA sentences
                            						//HAL_UART_Transmit(&huart2, nmeaSnt, 50, 70);
                            						//HAL_UART_Transmit(&huart2, (uint8_t*) "\n", 1, 200);

                            						cnt = 0;

                            						// splitting the good NMEA sentence into the tokens by the comma delimiter
                            						for (char *pV = strtok(nmeaSnt, ","); pV != NULL; pV = strtok(NULL, ",")) {

                            							switch (cnt) {
                            							case 2:
                            								latRaw = strdup(pV);
                            								break;
                            							case 3:
                            								hemNS = strdup(pV);
                            								break;
                            							case 4:
                            								lonRaw = strdup(pV);
                            								break;
                            							case 5:
                            								hemEW = strdup(pV);
                            								break;
                            							}

                            							cnt++;

                            						}  // end for()

                            						memcpy(latDg, &latRaw[0], 2);
                            						latDg[2] = '\0';

                            						memcpy(latMS, &latRaw[2], 7);
                            						latMS[7] = '\0';

                            						memcpy(lonDg, &lonRaw[0], 3);
                            						lonDg[3] = '\0';

                            						memcpy(lonMS, &lonRaw[3], 7);
                            						lonMS[7] = '\0';
                            						char strLonMS[7];
                            						sprintf(strLonMS, "%s", lonMS);
																				
																				free((void*)latRaw);
																				free((void*)lonRaw);
																				free((void*)hemEW);
																				free((void*)hemNS);

																				Latitude1 = latlonConverter(latDg,latMS);
																				Longitude1 = latlonConverter(lonDg,lonMS);
																				/* DEBUG TRANSMIT TO SERIAL TERMINAL WINDOW CHECK
                            						HAL_UART_Transmit(&huart2, (uint8_t*) hemNS, 1, 200);
                            						HAL_UART_Transmit(&huart2, (uint8_t*) " ", 1, 200);
                            						HAL_UART_Transmit(&huart2, (uint8_t*) latDg, 2, 200);
                            						HAL_UART_Transmit(&huart2, (uint8_t*) "\241", 1, 200);
                            						HAL_UART_Transmit(&huart2, (uint8_t*) latMS, 7, 200);
                            						HAL_UART_Transmit(&huart2, (uint8_t*) "\', ", 3, 200);

                            						HAL_UART_Transmit(&huart2, (uint8_t*) hemEW, 1, 200);
                            						HAL_UART_Transmit(&huart2, (uint8_t*) " ", 1, 200);
                            						HAL_UART_Transmit(&huart2, (uint8_t*) lonDg, 3, 200);
                            						HAL_UART_Transmit(&huart2, (uint8_t*) "\241", 1, 200);
                            						HAL_UART_Transmit(&huart2, (uint8_t*) strLonMS, strlen(strLonMS), 200);
                            						HAL_UART_Transmit(&huart2, (uint8_t*) "\', UTC: ", 8, 200);

                            						HAL_UART_Transmit(&huart2, (uint8_t*) strUTC, 8, 200);
                            						HAL_UART_Transmit(&huart2, (uint8_t*) "\n", 1, 200);
																				*/
                            					} // end of of the checksum data verification

                            				} // end of $GNGLL sentences selection
																		else if ((strstr(nmeaSnt, "$GNGLL") != 0) && strlen(nmeaSnt) > 49 && strstr(nmeaSnt, "*") != 0) {

                            					rawSum = strstr(nmeaSnt, "*");

                            					memcpy(smNmbr, &rawSum[1], 2);

                            					smNmbr[2] = '\0';

                            					uint8_t intSum = nmea0183_checksum(nmeaSnt);

                            					char hex[2];

                            					// "%X" unsigned hexadecimal integer (capital letters)
                            					sprintf(hex, "%X", intSum);

                            					// checksum data verification, if OK, then we can really trust
                            					// the data in the the NMEA sentence
                            					if (strstr(smNmbr, hex) != NULL) {

                            						//if we want display good $GNGLL NMEA sentences
                            						//HAL_UART_Transmit(&huart2, nmeaSnt, 50, 70);
                            						//HAL_UART_Transmit(&huart2, (uint8_t*) "\n", 1, 200);

                            						cnt = 0;

                            						// splitting the good NMEA sentence into the tokens by the comma delimiter
                            						for (char *pV = strtok(nmeaSnt, ","); pV != NULL; pV = strtok(NULL, ",")) {

                            							switch (cnt) {
                            							case 1:
                            								latRaw = strdup(pV);
                            								break;
                            							case 2:
                            								hemNS = strdup(pV);
                            								break;
                            							case 3:
                            								lonRaw = strdup(pV);
                            								break;
                            							case 4:
                            								hemEW = strdup(pV);
                            								break;
                            							}

                            							cnt++;

                            						}  // end for()

                            						memcpy(latDg, &latRaw[0], 2);
                            						latDg[2] = '\0';

                            						memcpy(latMS, &latRaw[2], 7);
                            						latMS[7] = '\0';

                            						memcpy(lonDg, &lonRaw[0], 3);
                            						lonDg[3] = '\0';

                            						memcpy(lonMS, &lonRaw[3], 7);
                            						lonMS[7] = '\0';
                            						char strLonMS[7];
                            						sprintf(strLonMS, "%s", lonMS);
																				
																				free((void*)latRaw);
																				free((void*)lonRaw);
																				free((void*)hemEW);
																				free((void*)hemNS);

																				Latitude1 = latlonConverter(latDg,latMS);
																				Longitude1 = latlonConverter(lonDg,lonMS);
																				/* DEBUG TRANSMIT TO SERIAL TERMINAL WINDOW CHECK
                            						HAL_UART_Transmit(&huart2, (uint8_t*) hemNS, 1, 200);
                            						HAL_UART_Transmit(&huart2, (uint8_t*) " ", 1, 200);
                            						HAL_UART_Transmit(&huart2, (uint8_t*) latDg, 2, 200);
                            						HAL_UART_Transmit(&huart2, (uint8_t*) "\241", 1, 200);
                            						HAL_UART_Transmit(&huart2, (uint8_t*) latMS, 7, 200);
                            						HAL_UART_Transmit(&huart2, (uint8_t*) "\', ", 3, 200);

                            						HAL_UART_Transmit(&huart2, (uint8_t*) hemEW, 1, 200);
                            						HAL_UART_Transmit(&huart2, (uint8_t*) " ", 1, 200);
                            						HAL_UART_Transmit(&huart2, (uint8_t*) lonDg, 3, 200);
                            						HAL_UART_Transmit(&huart2, (uint8_t*) "\241", 1, 200);
                            						HAL_UART_Transmit(&huart2, (uint8_t*) strLonMS, strlen(strLonMS), 200);
                            						HAL_UART_Transmit(&huart2, (uint8_t*) "\', UTC: ", 8, 200);

                            						HAL_UART_Transmit(&huart2, (uint8_t*) strUTC, 8, 200);
                            						HAL_UART_Transmit(&huart2, (uint8_t*) "\n", 1, 200);
																				*/
                            					} // end of of the checksum data verification

                            				} // end of $GNGLL sentences selection

                            			} // end of splitting the buffStr by the "\n" delimiter with the mystrsep() C function
																	//free(string);

                            			flag = 0; // we are ready to get new data from the sensor

                            		} // end of one interrupt/full-buffer cycle for GPS DATA

		
															
		//LIDAR DATA ACQUISITION
		cmd[0]=0x04;
		HAL_I2C_Mem_Write(&hi2c1, 0x62<<1,0x00, 1, cmd,1,10);
    cmd[0]=0x8f;
    HAL_I2C_Master_Transmit(&hi2c1,0x62<<1,cmd, 1,10);  
    HAL_I2C_Master_Receive(&hi2c1, 0x62<<1, data,2,10);
		distance = (data[0]<<8)|(data[1]);
		//x cm * 1km/100000cm -> kmeter conversion
		distancefloated = (float)distance/100000; 
		HAL_Delay(50);
		
		//COMPASS DATA ACQUISITION
		// RECEIVE X_axis
		HAL_I2C_Mem_Read(&hi2c1,HMC5883l_ADDRESS,HMC5883l_ADD_DATAX_MSB_MULTI,1,DataMagX,2,100);
		Xaxis = ((DataMagX[1]<<8) | DataMagX[0])/660.f;
		// RECEIVE Y_axis
		HAL_I2C_Mem_Read(&hi2c1,HMC5883l_ADDRESS,HMC5883l_ADD_DATAY_MSB_MULTI,1,DataMagY,2,100);
		Yaxis = ((DataMagY[1]<<8) | DataMagY[0])/660.f;
		// RECEIVE Z_axis
		HAL_I2C_Mem_Read(&hi2c1,HMC5883l_ADDRESS,HMC5883l_ADD_DATAZ_MSB_MULTI,1,DataMagZ,2,100);
		Zaxis = ((DataMagZ[1]<<8) | DataMagZ[0])/660.f;
		
		//Compute the mag offset with actual heading
		CompassHeadingRadians = atan2(Xaxis,Yaxis);
		CompassHeadingRadians += DeclinationAngleRadians; //Added additional offset for the sensor pcb placement in prototype
		//Correct heading to sign convention
		if(CompassHeadingRadians < 0)
			CompassHeadingRadians += 2*M_PI;
		if(CompassHeadingRadians > 2*M_PI)
			CompassHeadingRadians -= 2*M_PI;
		CompassHeadingDegrees = CompassHeadingRadians * 180/M_PI;
		
		//distancefloated = 0; //Test 1km
		//CompassHeadingRadians = 90/M_PI; //Test
		//COMPUTE NEW GPS COORDINATE
		//Found Haversine Formula -> https://www.movable-type.co.uk/scripts/latlong.html | https://en.wikipedia.org/wiki/Haversine_formula
		//Note not stable throughout the earth due to non-spherical shape and mag field adjustments required. 
		//Could implement a mag lookup table for constant cal depending on current gps lock
		LatitudeTarget = asin(sin(Latitude1*M_PI /180) * cos(distancefloated/earthRadius) + cos(Latitude1*M_PI/180) * sin(distancefloated/earthRadius) * cos(CompassHeadingRadians))*180/M_PI;
		LongitudeTarget = Longitude1 + atan2((sin(CompassHeadingRadians)* sin(distancefloated/earthRadius) * cos(Latitude1*M_PI /180)) , (cos(distancefloated/earthRadius) - sin(Longitude1*M_PI/180) * sin(LatitudeTarget*M_PI /180)));
	
		
		
		
		//DISPLAY GPS COORDINATE ON LCD //LatitudeTarget, LongitudeTarget
		sprintf(LCDBuffer,"LAT%2.10f",LatitudeTarget);
		LCD1602_setCursor(1,1);
		LCD1602_print(LCDBuffer);
		sprintf(LCDBuffer,"LON%3.9f",LongitudeTarget);
		LCD1602_setCursor(0,1);
		LCD1602_print(LCDBuffer);
		
		//WIFI TRANSMIT (latitude1,longitude1); 
		//TRANSMIT DATA TO COMPUTER
		sprintf(myTxData,"LAT%2.9fLON%3.9f",LatitudeTarget,LongitudeTarget);//Took 1 precision from lat for EOL terminator
		NRF24_write(myTxData,32);
    NRF24_write(myTxData,32);
  }/* USER CODE END 3 */
   
} /* USER CODE END WHILE */

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, CSN_PIN_Pin|CE_PIN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, ENABLE_LCD_Pin|RS_LCD_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, D0_Pin|D1_Pin|D2_Pin|D3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, D4_Pin|D5_Pin|D6_Pin|D7_Pin
                          |LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : CSN_PIN_Pin CE_PIN_Pin */
  GPIO_InitStruct.Pin = CSN_PIN_Pin|CE_PIN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : ENABLE_LCD_Pin RS_LCD_Pin */
  GPIO_InitStruct.Pin = ENABLE_LCD_Pin|RS_LCD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : D0_Pin D1_Pin D2_Pin D3_Pin */
  GPIO_InitStruct.Pin = D0_Pin|D1_Pin|D2_Pin|D3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : D4_Pin D5_Pin D6_Pin D7_Pin
                           LED1_Pin LED2_Pin LED3_Pin LED4_Pin */
  GPIO_InitStruct.Pin = D4_Pin|D5_Pin|D6_Pin|D7_Pin
                          |LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
