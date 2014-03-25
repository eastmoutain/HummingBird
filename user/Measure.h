/*----------------------------------------------------------------------------
 * Name:    Measure.h
 * Purpose: struct type and extern definitions for MEASURE project
 * Version: V1.00
 * Note(s): 
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2008 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------
 * History:
 *          V1.00 Initial Version
 *----------------------------------------------------------------------------*/

/* external functions: */
extern int  sendchar (int ch);           /* write character to serial port    */
extern int  getkey (void);               /* read character from serial port   */
extern void getline (char *line, int n);          /* input line               */
