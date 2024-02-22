/*
 * esp8266.c
 *
 *  Created on: 28 Ara 2022
 *      Author: AdminPC
 */

#include <EK_TM4C1294XL.h>
#include <xdc/std.h>

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/knl/Event.h>
#include <ti/sysbios/knl/Semaphore.h>

#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include "usb_uart.h"

void waitForLine(UART_Handle uart, char *line_str)
{
    char tmp_char;
    int ndx;

    ndx=0;

    while(1)
    {
        UART_read(uart, &tmp_char, 1);

        line_str[ndx] = tmp_char;

        if(ndx>=1 && line_str[ndx-1]==13 && line_str[ndx]==10) {

            // end of line
            //
            line_str[ndx-1]=0;   // end of string
            return;
        }
        ndx++;
    }
}

int waitForResponse(UART_Handle uart)
{
    char lstr[200];

    while(1)
    {
        waitForLine(uart, lstr);

        if(strstr(lstr, "OK")) {
            return 1;
        }
        else if(strstr(lstr, "ERROR")) {
            return 0;
        }
    }
}

void ESP8266_enableModule(void)
{
    GPIO_write(EK_TM4C1294XL_ESP8266, 1);
}

void ESP8266_disableModule(void)
{
    GPIO_write(EK_TM4C1294XL_ESP8266, 0);
}


int turnOffEcho(UART_Handle uart)
{
    int retval;

    // write ATE0 to turn off the echo mode
    //
    UART_write(uart, "ATE0\r\n", 6);

    // wait for a while to let ESP8266 return response
    //
    retval  = waitForResponse(uart);

    return retval;
}

int setWifiMode(UART_Handle uart, int mode)
{
    char str[20];
    int retval;

    // write AT+CWMODE=? to change the Wifi mode
    //
    sprintf(str, "AT+CWMODE=%d\r\n", mode);
    UART_write(uart, str, strlen(str));

    retval = waitForResponse(uart);

    return retval;
}

int setMultipleConnections(UART_Handle uart, int enable)
{
    int retval;

    if(enable) {
        UART_write(uart, "AT+CIPMUX=1\r\n", 13);
    }
    else {
        UART_write(uart, "AT+CIPMUX=0\r\n", 13);
    }

    retval = waitForResponse(uart);

    return retval;
}

int startSoftAP(UART_Handle uart, char *ssid, char *passwd, int ch, int enc_mode)
{
    char str[70];
    int retval;

    sprintf(str, "AT+CWSAP_CUR=\"%s\",\"%s\",%d,%d\r\n", ssid, passwd, ch, enc_mode);
    UART_write(uart, str, strlen(str));

    retval = waitForResponse(uart);

    return retval;
}

int setServer(UART_Handle uart, int port)
{
    char str[50];
    int retval;

    sprintf(str, "AT+CIPSERVER=1,%d\r\n", port);
    UART_write(uart, str, strlen(str));

    retval = waitForResponse(uart);

    return retval;
}

void ESP8266_task(UArg arg1, UArg arg2)
{
    UART_Handle esp8266_uart;
    UART_Params uartParams;

    ESP8266_disableModule();
    Task_sleep(2000);
    ESP8266_enableModule();
    Task_sleep(2000);

    /*
      * start UART
      */
     UART_Params_init(&uartParams);
     uartParams.writeDataMode =  UART_DATA_BINARY;
     uartParams.readDataMode =  UART_DATA_BINARY;
     uartParams.readReturnMode = UART_RETURN_NEWLINE;
     uartParams.readEcho = UART_ECHO_OFF;
     uartParams.dataLength = UART_LEN_8;
     uartParams.parityType = UART_PAR_NONE;
     uartParams.stopBits = UART_STOP_ONE;
     uartParams.baudRate = 19200;   // sizde 115200
     esp8266_uart = UART_open(EK_TM4C1294XL_UART7, &uartParams);
     if (esp8266_uart == NULL) {

         // something terribly went wrong. abort!!!
         //
         System_abort("Error opening the UART");
     }

     turnOffEcho(esp8266_uart);
     setWifiMode(esp8266_uart,3);
     setMultipleConnections(esp8266_uart,1);
     startSoftAP(esp8266_uart, "eem449", "1111111111", 5, 4);
     setServer(esp8266_uart, 2400);

     while(1) {
         usb_uart("merhaba\n");
         Task_sleep(1000);
     }
}
