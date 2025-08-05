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
    rt_uint16_t Number_CountDown;                // 倒计时
    rt_uint16_t Number_Press;                    // 按压数
    rt_uint16_t Number_Correct;                  // 正确计数
    rt_uint16_t Number_Error;                    // 错误计数

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
    TM1629A_SEG_1 = 1,
    TM1629A_SEG_2,
    TM1629A_SEG_3,
    TM1629A_SEG_4,
    TM1629A_SEG_5,
    TM1629A_SEG_6,
    TM1629A_SEG_7,
    TM1629A_SEG_8,
    TM1629A_SEG_9,
    TM1629A_SEG_10,
    TM1629A_SEG_11,
    TM1629A_SEG_12,
    TM1629A_SEG_13,
    TM1629A_SEG_14,
    TM1629A_SEG_15,
    TM1629A_SEG_16,
} TM1629x_SEG_SELECT;





typedef enum
{
    TM1629A_A = 0,
    TM1629A_B,
    TM1638_A
} TM16xxSelect;






#endif /* APPLICATIONS_MACSYS_INC_BSP_TYPEDEF_H_ */
