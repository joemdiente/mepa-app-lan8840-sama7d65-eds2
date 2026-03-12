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
// Header file for linux_mdio.c

#ifndef _LINUX_MDIO_H_
#define _LINUX_MDIO_H_

// Headers
#include "microchip/ethernet/phy/api.h"
#include <stdbool.h>

#define BOOL bool

#define T_D(format, ...) MEPA_trace(MEPA_TRACE_GRP_GEN, MEPA_TRACE_LVL_DEBUG, __FUNCTION__, __LINE__, __FILE__, format, ##__VA_ARGS__);
#define T_I(format, ...) MEPA_trace(MEPA_TRACE_GRP_GEN, MEPA_TRACE_LVL_INFO, __FUNCTION__, __LINE__, __FILE__, format, ##__VA_ARGS__);
#define T_W(format, ...) MEPA_trace(MEPA_TRACE_GRP_GEN, MEPA_TRACE_LVL_WARNING, __FUNCTION__, __LINE__, __FILE__, format, ##__VA_ARGS__);
#define T_E(format, ...) MEPA_trace(MEPA_TRACE_GRP_GEN, MEPA_TRACE_LVL_ERROR, __FUNCTION__, __LINE__, __FILE__, format, ##__VA_ARGS__);
#define T_N(format, ...) MEPA_trace(MEPA_TRACE_GRP_GEN, MEPA_TRACE_LVL_NOISE, __FUNCTION__, __LINE__, __FILE__, format, ##__VA_ARGS__);

// Function prototypes
int mdio_initialize(char* mdio_bus, uint8_t* phy_id);
int mdio_test_code(void);
mepa_rc mdio_read (struct mepa_callout_ctx *ctx, uint8_t addr, uint16_t *value);
mepa_rc mdio_write (struct mepa_callout_ctx *ctx, uint8_t addr, uint16_t value);

#endif /*_LINUX_MDIO_H_*/