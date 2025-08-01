/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-07-17     18452       the first version
 */
#include "bsp_sys.h"


//---------------------------------------------------------------------------------------
#define TM1629A_A_CLK_H()      HAL_GPIO_WritePin(TM1629A_A_CLK_GPIO_Port, TM1629A_A_CLK_Pin, GPIO_PIN_SET)
#define TM1629A_A_CLK_L()      HAL_GPIO_WritePin(TM1629A_A_CLK_GPIO_Port, TM1629A_A_CLK_Pin, GPIO_PIN_RESET)
#define TM1629A_A_DIO_H()      HAL_GPIO_WritePin(TM1629A_A_DIO_GPIO_Port, TM1629A_A_DIO_Pin, GPIO_PIN_SET)
#define TM1629A_A_DIO_L()      HAL_GPIO_WritePin(TM1629A_A_DIO_GPIO_Port, TM1629A_A_DIO_Pin, GPIO_PIN_RESET)
#define TM1629A_A_STB_H()      HAL_GPIO_WritePin(TM1629A_A_STB_GPIO_Port, TM1629A_A_STB_Pin,  GPIO_PIN_SET)
#define TM1629A_A_STB_L()      HAL_GPIO_WritePin(TM1629A_A_STB_GPIO_Port, TM1629A_A_STB_Pin,  GPIO_PIN_RESET)

//---------------------------------------------------------------------------------------
#define DIRG_0_ADDR     0xC0
#define DIRG_1_ADDR     0xC1
#define DIRG_2_ADDR     0xC2
#define DIRG_3_ADDR     0xC3
#define DIRG_4_ADDR     0xC4
#define DIRG_5_ADDR     0xC5
#define DIRG_6_ADDR     0xC6
#define DIRG_7_ADDR     0xC7

//---------------------------------------------------------------------------------------

const rt_uint8_t number_code[10] = {
        0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f
};



const rt_uint8_t tube_sequence_buf[]={

};
//---------------------------------------------------------------------------------------



/**
  * @brief  Delay function(uint:ms)
  * @param  us 微妙数
  * @retval void
  */
void TM1629A_Delay_us(uint32_t us)
{
    for(; us; us--) __NOP();
}


/**
  * @brief  TM1629A Chip send one byte and select tube to write
  * @param  chip 选择指定芯片
  *         data 需要写入的数据
  * @retval void
  * @note   这个工程板载了2个TM1629A芯片，因此这个写单个字节函数通过选型进行公用
  */
/* 发送 1 字节（低位先行） */
void TM1629A_Write_Byte(TM16xxSelect chip , rt_uint8_t data)
{
    if(chip == TM1629A_A)
    {
        for(rt_uint8_t i = 0; i < 8; i++)
        {
            TM1629A_A_CLK_L();
            if(data & 0x01){
                TM1629A_A_DIO_H();
            }
            else {
                TM1629A_A_DIO_L();
            }
            TM1629A_Delay_us(5);
            TM1629A_A_CLK_H();
            TM1629A_Delay_us(5);
            data >>= 1;
        }
    }
}





/**
  * @brief  TM1629A Chip display off/on
  * @param  ctrl_cmd ：  0 --> off
  *                  :  1 --> on
  * @retval void
  * @note
  */
void TM1629A_Display_CTRL(TM16xxSelect chip, rt_uint8_t ctrl_cmd)
{
#define TM1629A_DISPLAY_ON_CMD  0x8F // 显示开,亮度7
#define TM1629A_DISPLAY_OFF_CMD 0x87 // 显示关,亮度7
    if(chip == TM1629A_A)
    {
        if(ctrl_cmd == 0){
            TM1629A_Write_CMD(chip, TM1629A_DISPLAY_ON_CMD);
        }
        else if(ctrl_cmd == 1){
            TM1629A_Write_CMD(chip, TM1629A_DISPLAY_OFF_CMD);
        }
    }
}






/**
  * @brief  TM1629A Set digital tube Brightness
  * @param  level: 亮度等级0~7
  *         tube : 选择控制数码管的芯片
  * @retval void
  * @note   找到寄存器手册的显示控制命令设置（用于设置亮度强度和显示使能）
  */
void TM1629A_Digital_Tube_Set_Brightness(TM16xxSelect chip, rt_uint8_t level)
{
    #define DISPLAY_RES_BASE    0x88

    if(level > 7){
        level = 7;
    }

    rt_uint8_t cmd = DISPLAY_RES_BASE | level;

    TM1629A_Write_CMD(chip, cmd);

}





/**
  * @brief  TM1629A show number
  * @param  level: 亮度等级0~7
  *         tube : 选择控制数码管的芯片
  * @retval void
  * @note   找到寄存器手册的显示控制命令设置（用于设置亮度强度和显示使能）
  */
void TM1629A_Display(TM16xxSelect chip,rt_uint8_t *tm1629a_data, rt_uint8_t )
{
    if(chip == TM1629A_A)
    {

    }
}







/**
  * @brief  This thread entry is used for NixieTube scanning
  * @retval void
  */
void NixieTube_Thread_entry(void* parameter)
{

    for(;;)
    {

//        // 固定地址模式
//        TM1629A_Write_CMD(chip, 0x44);
//        // 显示开，亮度7
//        TM1629A_Write_CMD(chip, 0x8F);
        TM1629A_A_STB_H();
        TM1629A_Delay_us(5);
        TM1629A_A_STB_L();
        TM1629A_Delay_us(5);
        TM1629A_Write_Byte(TM1629A_A, 0x44);

        TM1629A_A_STB_H();
        TM1629A_Delay_us(5);
        TM1629A_A_STB_L();
        TM1629A_Delay_us(5);
        TM1629A_Write_Byte(TM1629A_A, 0xC0);
        TM1629A_Write_Byte(TM1629A_A, 0x08);

//        TM1629A_A_STB_H();
//        TM1629A_Delay_us(5);
//        TM1629A_A_STB_L();
//        TM1629A_Delay_us(5);
//        TM1629A_Write_Byte(TM1629A_A, 0x01);
//        TM1629A_Write_Byte(TM1629A_A, 0x00);


        TM1629A_A_STB_H();
        TM1629A_Delay_us(5);
        TM1629A_A_STB_L();
        TM1629A_Delay_us(5);
        TM1629A_Write_Byte(TM1629A_A, 0xC2);
        TM1629A_Write_Byte(TM1629A_A, 0x08);

//        TM1629A_A_STB_H();
//        TM1629A_Delay_us(5);
//        TM1629A_A_STB_L();
//        TM1629A_Delay_us(5);
//        TM1629A_Write_Byte(TM1629A_A, 0x03);
//        TM1629A_Write_Byte(TM1629A_A, 0x00);

        TM1629A_A_STB_H();
        TM1629A_Delay_us(5);
        TM1629A_A_STB_L();
        TM1629A_Delay_us(5);
        TM1629A_Write_Byte(TM1629A_A, 0xC4);
        TM1629A_Write_Byte(TM1629A_A, 0x08);

//        TM1629A_A_STB_H();
//        TM1629A_Delay_us(5);
//        TM1629A_A_STB_L();
//        TM1629A_Delay_us(5);
//        TM1629A_Write_Byte(TM1629A_A, 0x05);
//        TM1629A_Write_Byte(TM1629A_A, 0x00);

        TM1629A_A_STB_H();
        TM1629A_Delay_us(5);
        TM1629A_A_STB_L();
        TM1629A_Delay_us(5);
        TM1629A_Write_Byte(TM1629A_A, 0xC6);
        TM1629A_Write_Byte(TM1629A_A, 0x08);


//        TM1629A_A_STB_H();
//        TM1629A_Delay_us(5);
//        TM1629A_A_STB_L();
//        TM1629A_Delay_us(5);
//        TM1629A_Write_Byte(TM1629A_A, 0x07);
//        TM1629A_Write_Byte(TM1629A_A, 0x00);

        TM1629A_A_STB_H();
        TM1629A_Delay_us(5);
        TM1629A_A_STB_L();
        TM1629A_Delay_us(5);
        TM1629A_Write_Byte(TM1629A_A, 0xC8);
        TM1629A_Write_Byte(TM1629A_A, 0x08);

//        TM1629A_A_STB_H();
//        TM1629A_Delay_us(5);
//        TM1629A_A_STB_L();
//        TM1629A_Delay_us(5);
//        TM1629A_Write_Byte(TM1629A_A, 0x09);
//        TM1629A_Write_Byte(TM1629A_A, 0x00);

        TM1629A_A_STB_H();
        TM1629A_Delay_us(5);
        TM1629A_A_STB_L();
        TM1629A_Delay_us(5);
        TM1629A_Write_Byte(TM1629A_A, 0xCA);
        TM1629A_Write_Byte(TM1629A_A, 0x08);

//        TM1629A_A_STB_H();
//        TM1629A_Delay_us(5);
//        TM1629A_A_STB_L();
//        TM1629A_Delay_us(5);
//        TM1629A_Write_Byte(TM1629A_A, 0x0B);
//        TM1629A_Write_Byte(TM1629A_A, 0x00);


        TM1629A_A_STB_H();
        TM1629A_Delay_us(5);
        TM1629A_A_STB_L();
        TM1629A_Delay_us(5);
        TM1629A_Write_Byte(TM1629A_A, 0xCC);
        TM1629A_Write_Byte(TM1629A_A, 0x00);

//        TM1629A_A_STB_H();
//        TM1629A_Delay_us(5);
//        TM1629A_A_STB_L();
//        TM1629A_Delay_us(5);
//        TM1629A_Write_Byte(TM1629A_A, 0x0D);
//        TM1629A_Write_Byte(TM1629A_A, 0x00);

        TM1629A_A_STB_H();
        TM1629A_Delay_us(5);
        TM1629A_A_STB_L();
        TM1629A_Delay_us(5);
        TM1629A_Write_Byte(TM1629A_A, 0xCE);
        TM1629A_Write_Byte(TM1629A_A, 0x00);

//        TM1629A_A_STB_H();
//        TM1629A_Delay_us(5);
//        TM1629A_A_STB_L();
//        TM1629A_Delay_us(5);
//        TM1629A_Write_Byte(TM1629A_A, 0x0F);
//        TM1629A_Write_Byte(TM1629A_A, 0x00);

        TM1629A_A_STB_H();
        TM1629A_Delay_us(5);
        TM1629A_A_STB_L();
        TM1629A_Delay_us(5);
        TM1629A_Write_Byte(TM1629A_A, 0x8F);

        TM1629A_A_STB_H();

        rt_thread_mdelay(2);

    }

}



/**
  * @brief  This is a Initialization for water level Check
  * @retval int
  */
int NixieTube_Thread_Init(void)
{
    rt_thread_t NixieTube_Task_Handle = RT_NULL;
    /* 创建检查一些系统状态标志的线程  -- 优先级：25 */
    NixieTube_Task_Handle = rt_thread_create("NixieTube_Thread_entry", NixieTube_Thread_entry, RT_NULL, 512, 25, 30);
    /* 检查是否创建成功,成功就启动线程 */
    if(NixieTube_Task_Handle != RT_NULL)
    {
        rt_kprintf("PRINTF:%d. NixieTube_Thread_entry is Succeed!! \r\n",Record.kprintf_cnt++);
        rt_thread_startup(NixieTube_Task_Handle);
    }
    else {
        rt_kprintf("PRINTF:%d. NixieTube_Thread_entry is Failed \r\n",Record.kprintf_cnt++);
    }

    return RT_EOK;
}
INIT_APP_EXPORT(NixieTube_Thread_Init);


