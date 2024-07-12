#include <Arduino.h>

uint8_t din = 23;   // DA
uint8_t clk = 18;   // CK
uint8_t cs = 5;     // CS
uint8_t Reset = 19; // RS
uint8_t en = 12;    // EN

void write_6302(unsigned char w_data)
{
  unsigned char i;
  for (i = 0; i < 8; i++)
  {
    digitalWrite(clk, LOW);
    if ((w_data & 0x01) == 0x01)
    {
      digitalWrite(din, HIGH);
    }
    else
    {
      digitalWrite(din, LOW);
    }
    w_data >>= 1;
    digitalWrite(clk, HIGH);
  }
  // Serial.printf("write_6302");
  delayMicroseconds(1);
}

void VFD_cmd(unsigned char command)
{
  digitalWrite(cs, LOW);
  write_6302(command);
  digitalWrite(cs, HIGH);
  delayMicroseconds(5);
  // Serial.printf("S1201_show\n");
}

// VFD显示
void S1201_show(void)
{
  digitalWrite(cs, LOW);  // 开始传输
  write_6302(0xe8);       // 地址寄存器起始位置
  digitalWrite(cs, HIGH); // 停止传输
  // Serial.printf("VFD_cmd\n");
}

// 初始化VFD
void VFD_init()
{
  // SET HOW MANY digtal numbers
  digitalWrite(cs, LOW);
  write_6302(0xe0);
  delayMicroseconds(5);
  write_6302(0x07); // 8 digtal
  digitalWrite(cs, HIGH);
  delayMicroseconds(5);

  // set bright
  digitalWrite(cs, LOW);
  write_6302(0xe4);
  delayMicroseconds(5);
  write_6302(0xff); // leve 255 max  （16进制：0x00~0xff）
  digitalWrite(cs, HIGH);
  delayMicroseconds(5);
  // Serial.printf("VFD_init\n");
}

// 设置屏幕亮度
void VFD_bright(char level)
{
  digitalWrite(cs, LOW);
  write_6302(0xe4);
  delayMicroseconds(5);
  write_6302(level);
  digitalWrite(cs, HIGH);
  delayMicroseconds(5);
}

/******************************
  在指定位置打印一个字符(用户自定义,所有CG-ROM中的)
  x:0~7;chr:要显示的字符编码
*******************************/
void S1201_WriteOneChar(unsigned char x, unsigned char chr)
{
  digitalWrite(cs, LOW); // 开始传输
  write_6302(0x20 + x);  // 地址寄存器起始位置
  write_6302(chr + 0x30);
  digitalWrite(cs, HIGH); // 停止传输
  S1201_show();
  // Serial.printf("S1201_WriteOneChar\n");
}

/*
 改进版
 (x,chr)
 x:显示该字符的位置0-7
 chr:该字符的ASCII
 */
void S1201_WriteOneChar1(unsigned char x, unsigned char chr)
{
  digitalWrite(cs, LOW); // 开始传输
  write_6302(0x20 + x);  // 地址寄存器起始位置
  write_6302(chr);
  digitalWrite(cs, HIGH); // 停止传输
  S1201_show();
}

/******************************
  在指定位置打印字符串
  (仅适用于英文,标点,数字)
  x:0~7;str:要显示的字符串
*******************************/
void S1201_WriteStr(unsigned char x, char *str)
{
  digitalWrite(cs, LOW); // 开始传输
  write_6302(0x20 + x);  // 地址寄存器起始位置
  while (*str)
  {
    write_6302(*str); // ascii与对应字符表转换
    str++;
  }
  digitalWrite(cs, HIGH); // 停止传输
  S1201_show();
  // Serial.printf("S1201_WriteStr\n");
}

/*
 在指定位置打印字符串
 (x,str)
 x:显示该字符串的位置0-7
 str:要显示的字符串
 */
void S1201_WriteStr1(int x, String str)
{
  for (int i = 0; i < str.length(); i++)
  {
    S1201_WriteOneChar1(i + x, str.charAt(i));
  }
}

// VFD清屏
void S1201_clear()
{
  for (int i = 0; i < 8; i++)
  {
    S1201_WriteOneChar1(i, 16);
  }
}

// VFD淡入效果
// pertime 控制每次调整亮度的间隔（调整淡入快慢）
void VFD_FadeIn(byte pertime)
{
  for (int i = 0; i < 255; i++)
  {
    VFD_bright(i); // 字符淡入效果
    delay(pertime);
  }
}

// VFD淡出效果
// pertime 控制每次调整亮度的间隔（调整淡出快慢）
void VFD_FadeOut(byte pertime)
{
  for (int i = 255; i >= 0; i--)
  {
    VFD_bright(i); // 字符淡出效果
    delay(pertime);
  }
}

// VFD乱码效果
// bit 要乱码的位
void VFD_RDnum(char bit)
{
  for (size_t i = 0; i < 15; i++)
  {
    S1201_WriteStr1(bit, String(i + 48));
    delay(8);
  }
}

// 设置VFD的开关
// status VFD的开关
void VFD_Display_status(bool status)
{
}

// VFD待机模式
// mode 待机模式开启关闭
void VFD_Standby_mode(bool mode)
{
}

void Charloop1(String str)
{
  // char a[] = {"ASDFGHJK"};
  char a[50];
  str.toCharArray(a, 50);
  unsigned char w;
  for (w = 0; w < 8; w++)
  {
    S1201_WriteOneChar1(w, a[w]);
    delay(300);
  }
}
