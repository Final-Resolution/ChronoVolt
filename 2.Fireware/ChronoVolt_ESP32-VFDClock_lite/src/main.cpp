#include <Arduino.h>
#include <ArduinoJson.h>
#include <OneButton.h>
#include <Ticker.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h> // Include NTPClient library
#include <TimeLib.h>   // Include Arduino time library
#include "time.h"      // 为了使用tm结构体
#include "FutabaVFD.h"
#include <pitches.h>     //音调库
#include <DIP-Arduino.h> //DIP开关库
#include <I2C_BM8563.h>

// 函数声明
void wifi_connect();
// void vfd_rolldisplay();
void clock_ararm();
void get_randomTime();
void VFD_welcome();
void beep(int note, int duration);
void beep_music();
void set_rtc_time();
void get_rtc_time();

#define LED_PIN 25

#define Buzzer_Pin 14

int melody[] = {
    NOTE_E5, NOTE_D5, NOTE_FS4, NOTE_GS4,
    NOTE_CS5, NOTE_B4, NOTE_D4, NOTE_E4,
    NOTE_B4, NOTE_A4, NOTE_CS4, NOTE_E4,
    NOTE_A4};

int durations[] = {
    8, 8, 4, 4,
    8, 8, 4, 4,
    8, 8, 4, 4,
    2};

I2C_BM8563 rtc(I2C_BM8563_DEFAULT_ADDRESS, Wire);

const char *ntpServer = "ntp3.aliyun.com";

const char *ssid = "XXXXXX";
const char *password = "XXXXXXXX";

// 定义网络连接标志，联网为1，离线为0
int NET_FLAG = 0;

// WIFI尝试连接时间，减少以测试离线模式，单位(秒)
#define WIFI_RETRY_COUNT 30

unsigned long previousMillis = 0;
unsigned long interval = 30000;

// 时间相关定义
int timeHours, timeMinute, timeSecond, timeMonth, timeMonthDay, timeYear;
String timeWeekDay, timeMonthName, timeDate, timeMonth0, timeMonthDay0;
String weekArray[] = {"Sun", "Mon", "Tues", "Wed", "Thur", "Fri", "Sat"};
// Week Days
String weekDays[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
// Month names
String months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

// 格式化时间变量
String format_time = "00:00:00";
char format_time0[100];
String format_data = "3333/33/33";
char format_data0[100];

String randNumber;
int a = 25;
int b = 61;
int c = 61;

// 按钮设置
OneButton button1(15, true);
OneButton button2(16, true);
OneButton button3(17, true);

// DIP开关设置
uint8_t dipSwitchPins[] = {26, 27}; // 定义DIP开关引脚
DIPSwitch dipSwitch(dipSwitchPins, 2);

void setup()
{
  Serial.begin(115200);

  // 配置WS2812B PIN
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // 配置蜂鸣器引脚
  pinMode(Buzzer_Pin, OUTPUT);

  // VFD 初始化
  pinMode(clk, OUTPUT);
  pinMode(din, OUTPUT);
  pinMode(cs, OUTPUT);
  pinMode(Reset, OUTPUT);
  digitalWrite(Reset, LOW);
  delayMicroseconds(5);
  digitalWrite(Reset, HIGH);
  VFD_init();

  // Init I2C
  Wire.begin();

  // Init RTC
  rtc.begin();

  // 连接wifi
  S1201_WriteStr(0, "WIFI ...");
  wifi_connect();
  if (WiFi.status() == WL_CONNECTED)
  {
    S1201_WriteStr(0, " ONLINE!");
    NET_FLAG = 1;
  }
  else
  {
    S1201_WriteStr(0, "OFFLINE!");
    NET_FLAG = 0;
  }
  delay(2000);

  switch (NET_FLAG)
  {
  case 0:              // 离线模式
    WiFi.disconnect(); // 停止连接WIFI
    break;
  case 1: // 在线模式
    // Set ntp time to local
    configTime(8 * 3600, 0, ntpServer);
    set_rtc_time();
    WiFi.disconnect(); // 停止连接WIFI,以降低功耗
    break;

  default:
    break;
  }

  // VFD欢迎动画
  VFD_welcome();

  Serial.println("Initialized");
}

void loop()
{
  unsigned long currentMillis = millis();
  // Serial.println(dipSwitch.getState()); // 读取并打印DIP开关值
  switch (dipSwitch.getState())
  {
  case 0:
    // get_NTPTime();               // 获取NTP时间
    get_rtc_time();                  // 获取本地RTC时间
    S1201_WriteStr(0, format_time0); // 显示当前时间
    get_randomTime();                // 随机时间
    clock_ararm();                   // 闹钟
    break;
  case 1:
    S1201_WriteStr(0, "-Attack-"); // 显示当前时间
    break;
  case 2:
    S1201_WriteStr(0, " -MUSIC-"); // 显示当前时间
    beep_music();
    break;
  case 3:
    S1201_WriteStr(0, " --RTC--"); // 显示当前时间
    get_rtc_time();
    break;
  default:
    break;
  }

  delay(1000);
}

// VFD显示欢迎动画
void VFD_welcome()
{
  //S1201_WriteStr(0, "--INIT--");
  Charloop1("--INIT--");
  delay(3000);
  // vfd_rolldisplay();

  S1201_clear(); // 清屏
  VFD_bright(0);
  S1201_WriteStr(0, "VFDclock");
  VFD_FadeIn(10); // VFD淡入效果
  delay(2000);
  S1201_WriteStr(0, "FinalRun");
  delay(2000);
  VFD_FadeOut(10); // VFD淡出效果
  delay(1000);
  VFD_bright(255);
  VFD_cmd(0xE9); // 全亮
  delay(1000);
}

// 随机时刻
void get_randomTime()
{
  if (format_time == "08:10:00")
  { // 每24小时进行一次随机
    a = random(0, 24);
    b = random(0, 60);
    c = random(0, 60);
  }
  String randomTime = String(a) + ":" + String(b) + ":" + String(c); // 组合随机时间
  // Serial.print("Random Time: ");
  // Serial.println(randomTime); // 打印输出随机时间

  if (timeHours == a && timeMinute == b && timeSecond == c) // 生成的随机时间与当前时间进行比对
  {
    randNumber = String(random(0, 10000000));                   // 生成随机数
    char *randNumber0 = const_cast<char *>(randNumber.c_str()); // 将随机数由String转换为char*类型
    for (int i = 0; i <= 3; i++)                                // 闪烁以加强提醒
    {
      S1201_clear(); // 清屏
      delay(300);
      S1201_WriteStr(1, "Random!!"); // 提醒进入随机时刻！！！
      delay(800);
    }
    S1201_clear();                  // 清屏
    S1201_WriteStr(0, randNumber0); // 显示随机数
    delay(random(3000, 10000));     // 显示随机数保持随机时间
  }
}

// 闹钟提醒
void clock_ararm()
{
  // 下班提醒
  if (format_time == "16:30:00")
  {
    for (int i = 0; i <= 3; i++) // 闪烁以加强提醒
    {
      S1201_clear(); // 清屏
      delay(200);
      S1201_WriteStr(0, "Go Home");
      delay(1000);
    }
    S1201_WriteStr(0, "Go Home");
    delay(3000);
  }
  // 每1min提醒当前日期
  if (timeSecond == 0)
  {
    // char *timeDate0 = const_cast<char *>(timeDate.c_str());
    S1201_WriteStr(0, format_data0);
    delay(2000);
  }
  // 每30s提醒周几
  if (timeSecond == 30)
  {
    char *timeWeekDay0 = const_cast<char *>(timeWeekDay.c_str());
    S1201_clear(); // 清屏
    S1201_WriteStr(2, timeWeekDay0);
    delay(2000);
  }
  // 每30min提醒喝水
  if (timeMinute == 30)
  {

    for (int i = 0; i <= 3; i++) // 闪烁以加强提醒
    {
      S1201_clear(); // 清屏
      delay(300);
      S1201_WriteStr(1, "Drink!");
      delay(800);
      S1201_clear(); // 清屏
      S1201_WriteStr(1, "Water!");
      delay(800);
    }
    S1201_WriteStr(0, "Drink!!!");
    delay(3000);
  }
}

// 通过普通方式连接WiFi，需定义SSID、PASSWORD
void wifi_connect()
{
  WiFi.mode(WIFI_STA);                // 设置Wifi工作模式为STA,默认为AP+STA模式
  WiFi.begin(ssid, password);         // 通过wifi名和密码连接到Wifi
  Serial.print("\r\nConnecting to "); // 串口监视器输出网络连接信息
  Serial.print(ssid);
  Serial.println(" ..."); // 显示设备正在尝试WiFi连接

  int i = 0; // 用来判定连接是否超时的累加量
             // 这里的循环用来判断是否连接成功的。连接过程中每隔500毫秒会检查一次是否连接成功，，并打一个点表示正在连接中
  // 连接成功后会给出提示，但是若60秒后还是没有连接上，则会提示超时
  while (WiFi.status() != WL_CONNECTED)
  {
    i++;
    delay(500);
    Serial.print(".");
    if (i > WIFI_RETRY_COUNT * 2)
    { // 如果还是连接不上，就判定为连接超时
      Serial.println("Connection timeout!");
      S1201_WriteStr(0, "TIMEOUT!");
      // Serial.println("Restart after 3 seconds!!!");
      delay(3000);
      WiFi.disconnect(); // 停止连接WIFI
      // ESP.restart();
      break; // 连接超时，进入离线模式
    }
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("");                // WiFi连接成功后
    Serial.println("WiFi connected!"); // 将通过串口监视器输出"连接成功"信息。
    Serial.print("IP address: ");      // 同时还将输出IP地址。这一功能是通过调用
    Serial.println(WiFi.localIP());    // WiFi.localIP()函数来实现的。该函数的返回值即IP地址。
  }
  else
  {
    Serial.println("Wifi connection failed, please try again!");
    Serial.println("Activate offline mode");
  }
}

// BEEP函数，(音调，音长)
void beep(int note, int duration)
{
  tone(Buzzer_Pin, note, duration);
  delay(duration);
}

// BEEP MUSIC函数
void beep_music()
{
  int size = sizeof(durations) / sizeof(int);

  for (int note = 0; note < size; note++)
  {
    // to calculate the note duration, take one second divided by the note type.
    // e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int duration = 1000 / durations[note];
    tone(Buzzer_Pin, melody[note], duration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);

    // stop the tone playing:
    noTone(Buzzer_Pin);
  }
}

// 从NTP对时到本地RTC
void set_rtc_time()
{
  // Get local time
  struct tm timeInfo;
  if (getLocalTime(&timeInfo))
  {
    // Set RTC time
    I2C_BM8563_TimeTypeDef timeStruct;
    timeStruct.hours = timeInfo.tm_hour;
    timeStruct.minutes = timeInfo.tm_min;
    timeStruct.seconds = timeInfo.tm_sec;
    rtc.setTime(&timeStruct);

    // Set RTC Date
    I2C_BM8563_DateTypeDef dateStruct;
    dateStruct.weekDay = timeInfo.tm_wday;
    dateStruct.month = timeInfo.tm_mon + 1;
    dateStruct.date = timeInfo.tm_mday;
    dateStruct.year = timeInfo.tm_year + 1900;
    rtc.setDate(&dateStruct);
  }
}

//  获取RTC时间
void get_rtc_time()
{
  I2C_BM8563_DateTypeDef dateStruct;
  I2C_BM8563_TimeTypeDef timeStruct;

  // Get RTC
  rtc.getDate(&dateStruct);
  rtc.getTime(&timeStruct);

  // Print RTC
  // Serial.printf("%04d/%02d/%02d %02d %02d:%02d:%02d\n",
  //             dateStruct.year,
  //             dateStruct.month,
  //             dateStruct.date,
  //             dateStruct.weekDay,
  //             timeStruct.hours,
  //             timeStruct.minutes,
  //            timeStruct.seconds);

  // Wait
  // delay(1000);

  timeHours = timeStruct.hours;
  // Serial.print("Hour: ");
  // Serial.println(timeHours);

  timeMinute = timeStruct.minutes;
  // Serial.print("Minutes: ");
  // Serial.println(timeMinute);

  timeSecond = timeStruct.seconds;
  // Serial.print("Seconds: ");
  // Serial.println(timeSecond);

  timeWeekDay = weekArray[dateStruct.weekDay];
  // Serial.print("Week Day: ");
  // Serial.println(timeWeekDay);
  sprintf(format_time0, "%02d:%02d:%02d", timeHours, timeMinute, timeSecond);
  // Serial.println(str_time0);
  format_time = String(format_time0);
  // Serial.print("Formatted Time: ");
  // Serial.println(format_time);

  // str_time = const_cast<char *>(format_time.c_str()); // 转换格式

  timeMonthDay = int(dateStruct.date);
  // Serial.print("Month day: ");
  // Serial.println(timeMonthDay);

  timeMonth = int(dateStruct.month);
  // Serial.print("Month: ");
  // Serial.println(timeMonth);

  timeMonthName = months[timeMonth - 1];
  // Serial.print("Month name: ");
  // Serial.println(timeMonthName);

  timeYear = dateStruct.year;
  // Serial.print("Year: ");
  // Serial.println(timeYear);

  // Print complete date:
  sprintf(format_data0, "%04d%02d%02d", timeYear, timeMonth, timeMonthDay);
  // Serial.println(format_data0);
  format_data = String(format_data0);
  //  Serial.print("Current date: ");
  //  Serial.println(format_data);
}
