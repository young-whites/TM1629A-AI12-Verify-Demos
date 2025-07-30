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






//---------------------------------------------------------------------------------------


/* ---------- 共阳段码表（低电平亮） ---------- */
static const uint8_t seg_code[] = {
    0xC0, // 0
    0xF9, // 1
    0xA4, // 2
    0xB0, // 3
    0x99, // 4
    0x92, // 5
    0x82, // 6
    0xF8, // 7
    0x80, // 8
    0x90  // 9
};

//---------------------------------------------------------------------------------------

void TM1629A_Delay_us(uint32_t us);
void TM1629A_Write_Byte(TM16xxSelect chip , rt_uint8_t data);
void TM1629A_Write_CMD(TM16xxSelect chip , rt_uint8_t cmd);
void TM1629A_Init(TM16xxSelect chip);
void TM1629A_Digital_Tube_Clear(TM16xxSelect chip);
void TM1629A_Digital_Tube_Set_Brightness(TM16xxSelect chip, rt_uint8_t level);
void TM1629A_Digital_Tube_ScanNumber(TM16xxSelect chip,uint8_t *digits);
void TM1629A_Digital_Tube_ShowDigit(TM16xxSelect chip, uint8_t pos, uint8_t val);

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
  * @param  tube 数码管选择
  *         data 需要写入的数据
  * @retval void
  * @note   这个工程板载了2个TM1629A芯片，因此这个写单个字节函数通过选型进行公用
  */
/* 发送 1 字节（低位先行） */
void TM1629A_Write_Byte(TM16xxSelect chip , rt_uint8_t data)
{
    if(chip == TM1629A_A){
        for(rt_uint8_t i = 0; i < 8; i++)
        {
            TM1629A_A_CLK_L();
            if(data & 0x01){
                TM1629A_A_DIO_H();
            }
            else {
                TM1629A_A_DIO_L();
            }
            data >>= 1;
            TM1629A_Delay_us(5);
            TM1629A_A_CLK_H();
            TM1629A_Delay_us(5);
        }
    }
}



/**
  * @brief  TM1629A Chip send one byte(cmd) and select tube to write
  * @param  tube 数码管选择
  *         cmd 指令数据
  * @retval void
  * @note   STB引脚被拉低后，写入的第一个字节作为指令，STB引脚拉高后，CLK时许被忽略
  */
void TM1629A_Write_CMD(TM16xxSelect chip , rt_uint8_t cmd)
{
    if(chip == TM1629A_A){
        TM1629A_A_STB_L();
        TM1629A_Write_Byte(chip, cmd);
        TM1629A_A_STB_H();
    }
}



/**
  * @brief  TM1629A Chip Initialization
  * @param  void
  * @retval void
  * @note
  */
void TM1629A_Init(TM16xxSelect chip)
{
    if(chip == TM1629A_A){
        // 自动地址增加
        TM1629A_Write_CMD(chip, 0x40);
        // 显示开，亮度7
        TM1629A_Write_CMD(chip, 0x88);
    }
}



/**
 * @brief  TM1629A 控制 4×3 位共阳数码管显示数字
 * @param  tube : 选芯片 A/B
 * @param  *digits : 长度 12 的数组，元素为 0~9 或 0xFF（熄灭）
 * @retval void
 * @note   硬件：GRID1~8 接 8 段，SEG0~11 接 12 位公共端
 */
void TM1629A_Digital_Tube_ScanNumber(TM16xxSelect chip,uint8_t *digits)
{
    uint8_t buf[12];          // 12 位显存
    uint8_t i;

    /* 1. 把索引转成真正的段码；0xFF 表示熄灭（全高） */
    for (i = 0; i < 12; i++)
    {
        if (digits[i] <= 9)
            buf[i] = seg_code[digits[i]];
        else
            buf[i] = 0xFF;    // 熄灭
    }

    /* 2. 固定地址模式写 12 字节 */
       TM1629A_Write_CMD(chip, 0x44);   // 固定地址模式（命令 0x44）
       for (i = 0; i < 12; i++)
       {
           if (chip == TM1629A_A)
           {
               TM1629A_A_STB_L();
               TM1629A_Write_Byte(chip, 0xC0 | i); // 地址 0xC0+addr
               TM1629A_Write_Byte(chip, buf[i]);
               TM1629A_A_STB_H();
           }
       }
       /* 3. 回到自动地址模式，方便后续清屏/刷新 */
       TM1629A_Write_CMD(chip, 0x40);
}




/**
 * @brief  指定第 pos 位显示数字 val
 * @param  tube : TM1629A_A / TM1629A_B
 * @param  pos  : 1~12  （1 表示最左边那位）
 * @param  val  : 0~9   （>9 视为熄灭）
 */
static uint8_t shadow[12] = {0xFF};   // 12 位显存，初值全灭
void TM1629A_Digital_Tube_ShowDigit(TM16xxSelect chip, uint8_t pos, uint8_t val)
{
    if (pos == 0 || pos > 12) return;          // 越界保护

    uint8_t idx = pos - 1;                     // 转成 0~11
    shadow[idx] = (val <= 9) ? seg_code[val]   // 查段码
                             : 0xFF;           // 熄灭

    /* 把整包 12 字节写回芯片（固定地址模式） */
    TM1629A_Write_CMD(chip, 0x44);             // 固定地址
    for (uint8_t i = 0; i < 12; i++)
    {
        if (chip == TM1629A_A)
        {
            TM1629A_A_STB_L();
            TM1629A_Write_Byte(chip, 0xC0 | i);
            TM1629A_Write_Byte(chip, shadow[i]);
            TM1629A_A_STB_H();
        }
    }
    TM1629A_Write_CMD(chip, 0x40);             // 恢复自动地址
}






/**
  * @brief  TM1629A Control digital tube off
  * @param  void
  * @retval void
  * @note
  */
void TM1629A_Digital_Tube_Clear(TM16xxSelect chip)
{
    /* 本次共有4个3位数码管，合计12位，因此初始化12个元素的清除数组 */
    rt_uint8_t clear_buf[12] = { 0xFF };
    TM1629A_Digital_Tube_ScanNumber(chip,clear_buf);
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
  * @brief  This thread entry is used for NixieTube scanning
  * @retval void
  */
void NixieTube_Thread_entry(void* parameter)
{
//    uint8_t num[12] = {1,2,3, 4,5,6, 7,8,9, 0,1,2};  // 从左到右 12 位

    TM1629A_Init(TM1629A_A);
    TM1629A_Digital_Tube_Set_Brightness(TM1629A_A,7);
    for(;;)
    {
        TM1629A_Write_Byte(TM1629A_A,0x09);
//        TM1629A_Digital_Tube_ShowDigit(TM1629A_A,1,8);
//        TM1629A_Digital_Tube_ShowDigit(TM1629A_A,2,8);
//        TM1629A_Digital_Tube_ShowDigit(TM1629A_A,3,8);
//        TM1629A_Digital_Tube_ShowDigit(TM1629A_A,4,8);
//        TM1629A_Digital_Tube_ShowDigit(TM1629A_A,5,8);
//        TM1629A_Digital_Tube_ShowDigit(TM1629A_A,6,8);
//        TM1629A_Digital_Tube_ScanNumber(TM1629A_A, num);
//        TM1629A_Digital_Tube_Clear(TM1629A_A);
        rt_thread_mdelay(50);
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


