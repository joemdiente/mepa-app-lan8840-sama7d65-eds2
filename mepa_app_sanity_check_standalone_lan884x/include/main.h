/*
 * Copyright (C) 2026 Microchip Technology Inc.
 *
 * Author: Joemel John A. Diente <joemeljohn.diente@microchip.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <https://www.gnu.org/licenses/>.
 *
 */
#ifndef __MAIN_
#define __MAIN_

// *****************************************************************************
// *****************************************************************************
// Section: Global Variables
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include "microchip/ethernet/phy/api.h"
#include "microchip/ethernet/board/api.h"
// *****************************************************************************
// *****************************************************************************
// Section: Macros and Constant defines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: MEPA Structs
// *****************************************************************************
// *****************************************************************************

typedef struct {
    mepa_callout_t callout;
    mepa_callout_ctx_t callout_ctx;
    mepa_board_conf_t board_conf;
    mepa_device_t *phy;
} appl_inst_t;

#endif /*__MAIN_*/