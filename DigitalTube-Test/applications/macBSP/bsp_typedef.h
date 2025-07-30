/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-05-15     teati       the first version
 */
#ifndef APPLICATIONS_MACSYS_INC_BSP_TYPEDEF_H_
#define APPLICATIONS_MACSYS_INC_BSP_TYPEDEF_H_

#include "bsp_sys.h"


// 以下为移植时必须需要的结构体等的初始化---------------------------------------------------------------------------------------------------------
typedef struct {
    rt_uint8_t  Empty;                           // 空值
    rt_uint8_t  kprintf_cnt;                     // 用于打印序列
    rt_uint8_t  OldMode;                         // 老化模式
    //------------------------------------------------------------


}RecordStruct;
extern RecordStruct Record;






typedef enum
{
    AI12_KEY_NONE = 0,
    AI12_KEY_1,
    AI12_KEY_2,
    AI12_KEY_3,
    AI12_KEY_4,
    AI12_KEY_5,
    AI12_KEY_6,
    AI12_KEY_7,
    AI12_KEY_8,
    AI12_KEY_9,
    AI12_KEY_10,
    AI12_KEY_11,
    AI12_KEY_12
} AI12_Key_t;


typedef enum
{
    TM1629A_A = 0,
    TM1629A_B,
    TM1638_A
} TM16xxSelect;






#endif /* APPLICATIONS_MACSYS_INC_BSP_TYPEDEF_H_ */
