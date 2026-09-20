#ifndef _MAIN_H
#define _MAIN_H

#define _XTAL_FREQ 12000000UL

#include <xc.h>

#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config BOREN = OFF
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#include "src/func.h"

#endif /* _MAIN_H */