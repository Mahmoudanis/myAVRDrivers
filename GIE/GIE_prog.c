/*
 * GIE_prog.c
 *
 *  Created on: Sep 23, 2022
 *      Author: mahmo
 */
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "GIE_interface.h"
#include "GIE_CFG.h"
#include "GIE_private.h"

void GIE_vEnable (void)
{
	SET_BIT(SREG,I_BIT);
}
void GIE_vDisable (void)
{
	CLR_BIT(SREG,I_BIT);
}
