/*------------------------------------------------------------------------------
 * Name:    UART.h
 * Purpose: UART definitions
 *------------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2004-2013 KEIL - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#ifndef __UART_H
#define __UART_H

#include "RTL.h"
#include <stdint.h>

/*-----------------------------------------------------------------------------
 * ENUMERATOR and STRUCTURE DEFINITIONS
 *----------------------------------------------------------------------------*/
 
/* Control Lines */
#define UART_CONTROL_LINE_RTS_Pos   0   /* request to send  control line      */
#define UART_CONTROL_LINE_RTS_Msk  (1 << UART_CONTROL_LINE_RTS_Pos)
#define UART_CONTROL_LINE_DTR_Pos   0   /* request to send  control line      */
#define UART_CONTROL_LINE_DTR_Msk  (1 << UART_CONTROL_LINE_DTR_Pos)

/* Status Lines */
#define UART_STATUS_LINE_CTS_Pos    0   /* clear to send control line         */
#define UART_STATUS_LINE_CTS_Msk   (1 << UART_STATUS_LINE_CTS_Pos)
#define UART_STATUS_LINE_DCD_Pos    1   /* data carrier detect                */
#define UART_STATUS_LINE_DCD_Msk   (1 << UART_STATUS_LINE_DCD_Pos)
#define UART_STATUS_LINE_DSR_Pos    2   /* data set ready                     */
#define UART_STATUS_LINE_DSR_Msk   (1 << UART_STATUS_LINE_DSR_Pos)
#define UART_STATUS_LINE_RI_Pos     3   /* ring indicator                     */
#define UART_STATUS_LINE_RI_Msk    (1 << UART_STATUS_LINE_RI_Pos)

/* Communication Errors */
#define UART_FRAMING_ERROR_Pos      0
#define UART_FRAMING_ERROR_Msk     (1 << UART_FRAMING_ERROR_Pos)
#define UART_PARITY_ERROR_Pos       1
#define UART_PARITY_ERROR_Msk      (1 << UART_PARITY_ERROR_Pos)
#define UART_OVERRUN_ERROR_Pos      2
#define UART_OVERRUN_ERROR_Msk     (1 << UART_OVERRUN_ERROR_Pos)

/* Parity enumerator */
typedef enum {
  UART_PARITY_NONE    = 0,
  UART_PARITY_ODD     = 1,
  UART_PARITY_EVEN    = 2,
  UART_PARITY_MARK    = 3,
  UART_PARITY_SPACE   = 4
} UART_Parity;

/* Stop Bits enumerator */
typedef enum {
  UART_STOP_BITS_1    = 0,
  UART_STOP_BITS_1_5  = 1,
  UART_STOP_BITS_2    = 2
} UART_StopBits;

/* Data Bits enumerator */
typedef enum {
  UART_DATA_BITS_5    = 5,
  UART_DATA_BITS_6    = 6,
  UART_DATA_BITS_7    = 7,
  UART_DATA_BITS_8    = 8,
  UART_DATA_BITS_16   = 16
} UART_DataBits;

/* Flow control enumerator */
typedef enum {
  UART_FLOW_CONTROL_NONE     = 0,
  UART_FLOW_CONTROL_RTS_CTS  = 1,
  UART_FLOW_CONTROL_XON_XOFF = 2
} UART_FlowControl;

/* UART Port Properties structure */
typedef struct {
  uint32_t           Baudrate;
  UART_DataBits      DataBits;
  UART_Parity        Parity;
  UART_StopBits      StopBits;
  UART_FlowControl   FlowControl;
} UART_Configuration;


 
/*-----------------------------------------------------------------------------
 * FUNCTION PROTOTYPES
 *----------------------------------------------------------------------------*/

/* UART driver function prototypes */
extern int32_t  UART_Initialize                  (void);
extern int32_t  UART_Uninitialize                (void);
extern int32_t  UART_Reset                       (void);
extern int32_t  UART_SetConfiguration            (UART_Configuration *config);
extern int32_t  UART_GetConfiguration            (UART_Configuration *config);
extern int32_t  UART_WriteData                   (uint8_t *data, uint16_t size);
extern int32_t  UART_ReadData                    (uint8_t *data, uint16_t size);
extern int32_t  UART_GetChar                     (void);
extern int32_t  UART_PutChar                     (uint8_t ch);
extern int32_t  UART_DataAvailable               (void);
extern int32_t  UART_SetControlLineState         (uint16_t ls, uint16_t msk);
extern uint16_t UART_GetControlLineState         (             uint16_t msk);
extern int32_t  UART_GetStatusLineState          (void);
extern int32_t  UART_GetCommunicationErrorStatus (void);
extern int32_t  UART_SetBreak                    (void);
extern int32_t  UART_ClearBreak                  (void);
extern int32_t  UART_GetBreak                    (void);

#endif /* __UART_H */
