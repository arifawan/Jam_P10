
#include <Wire.h>
#include <Sodaq_DS3231.h>
#include <SPI.h> 
#include <DMD2.h>

#include <fontNew/Arabic_tahoma.h>
#include <fontNew/Font3x5.h>
#include <fontNew/SystemFont5x7.h>

SoftDMD dmd(1,1);

char weekDay[][7] = {"Ahad", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu" };
char monthYear[][4] = { "DES", "JAN", "FEB", "MAR", "APR", "MEI", "JUN", "JUL", "AGU", "SEP", "OKT", "NOV", "DES" };

void setup () 
{
    Serial.begin(57600);
    Wire.begin();
    rtc.begin();

    dmd.setBrightness(255);
    dmd.begin();

    dmd.selectFont(SystemFont5x7);
    dmd.drawString(0,0, "Test");
    
}

void loop () 
{
  DateTime now = rtc.now(); 

  int jam      = now.hour();
  int menit    = now.minute();
  int detik    = now.second();
  String hari  =weekDay[now.dayOfWeek()];
  int tgl      = now.date();
  String bulan = monthYear[now.month()];
  int thn      = now.year();
  rtc.convertTemperature();        
  int temp = rtc.getTemperature();

  dmd.clearScreen();
  dmd.selectFont(SystemFont5x7);
  String xkonv = Konversi(tgl);
  int pjg = xkonv.length() + 1;
  char kata[pjg];
  xkonv.toCharArray(kata, pjg);
  dmd.drawString(3, 1
  , kata, pjg, 0);

  dmd.selectFont(Font3x5);
  dmd.drawString(16, 0, bulan);

  dmd.selectFont(SystemFont5x7);
  String xkonv1 = Konversi(thn);
  int pjg1 = xkonv1.length() + 1;
  char kata1[pjg1];
  xkonv1.toCharArray(kata1, pjg1);
  dmd.drawString(4, 9, kata1, pjg1, 0);
  delay(3000);
  
  dmd.clearScreen();
  dmd.selectFont(SystemFont5x7);  
  String xkonv2 = Konversi(jam) + ":"+ Konversi(menit);
  int pjg2 = xkonv2.length() + 1;
  char kata2[pjg2];
  xkonv2.toCharArray(kata2, pjg2);
  dmd.drawString(1, 4, kata2, pjg2, 0);
  delay(10000);

  dmd.clearScreen();
  dmd.selectFont(Font3x5);
  dmd.drawString(8, -2, "Suhu");
  
  dmd.selectFont(SystemFont5x7);  
  String xkonv3 = Konversi(temp);
  int pjg3 = xkonv3.length() + 1;
  char kata3[pjg3];
  xkonv3.toCharArray(kata3, pjg3);
  dmd.drawString(5, 8, kata3, pjg3, 0);

  dmd.drawCircle(18,8,1);
  dmd.drawString(21, 8, "C");
  delay(2000);
}

String Konversi(int sInput) {
  if (sInput < 10){ return"0" + String(sInput);}
  else
  { return String(sInput);}
}
