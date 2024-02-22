/*
 * usb_uart.c
 *
 *  Created on: 28 Ara 2022
 *      Author: AdminPC
 */
#include <string.h>
#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>

#include "USBCDCD.h"

void usb_uart(char *msg)
{
    USBCDCD_waitForConnect(BIOS_WAIT_FOREVER);
    USBCDCD_sendData((unsigned char*)msg, strlen(msg), BIOS_WAIT_FOREVER);
}


