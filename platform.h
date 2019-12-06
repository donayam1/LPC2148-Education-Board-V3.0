#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#define USE_BOARD

#ifdef USE_BOARD
#include <lpc214x.h>
#else
#include <lpc213x.h>
#endif 

#endif 
