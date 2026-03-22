#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

// إعداد الشاشة
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

#define BUZZER_PIN 25 // منفذ الطنان الصوتي (Buzzer)

unsigned long startTime;
int frame = 0;
int vib = 0; 

void setup() {
  u8g2.begin();
  pinMode(BUZZER_PIN, OUTPUT);
  startTime = millis();
}

// =========================================================
// دالة رسم الطالب في حجمه الطبيعي (ينظر للكاميرا)
// =========================================================
void drawStudentNormal(int x, int y) {
  u8g2.drawBox(x + 5, y + 2, 8, 7); 
  u8g2.drawBox(x + 3, y + 9, 12, 5); 
  
  u8g2.drawLine(x + 4, y + 1, x + 13, y + 1); 
  u8g2.drawLine(x + 4, y + 2, x + 4, y + 5); 
  u8g2.drawLine(x + 13, y + 2, x + 13, y + 5); 

  u8g2.setDrawColor(0);
  u8g2.drawPixel(x + 6, y + 4); 
  u8g2.drawPixel(x + 11, y + 4); 
  u8g2.drawLine(x + 8, y + 6, x + 9, y + 6); 
  u8g2.setDrawColor(1);

  u8g2.drawFrame(x + 5, y + 3, 3, 3);
  u8g2.drawFrame(x + 10, y + 3, 3, 3);
  u8g2.drawLine(x + 8, y + 4, x + 9, y + 4); 
}

// =========================================================
// المشهد الأول: باص من الجانب
// =========================================================
void drawDetailedSideBus(int bX, int bY) {
  u8g2.drawLine(0, 58, 128, 58);
  for(int i=0; i<128; i+=15) u8g2.drawLine((i-(frame*4)%15), 62, (i-(frame*4)%15)+5, 62);
  
  u8g2.drawRFrame(bX, bY, 95, 26, 3); 
  u8g2.drawLine(bX+95, bY, bX+105, bY+12); 
  u8g2.drawLine(bX+105, bY+12, bX+105, bY+26); 
  u8g2.drawLine(bX, bY+26, bX+105, bY+26); 
  
  for(int i=0; i<4; i++) {
    u8g2.drawRFrame(bX + 4 + (i*21), bY + 3, 18, 14, 2); 
  }
  u8g2.drawFrame(bX+88, bY+3, 14, 14); 

  drawStudentNormal(bX + 25, bY + 3);

  u8g2.drawDisc(bX + 22, bY + 26, 6); 
  u8g2.drawDisc(bX + 82, bY + 26, 6); 
  u8g2.setDrawColor(0);
  u8g2.drawDisc(bX + 22, bY + 26, 3); 
  u8g2.drawDisc(bX + 82, bY + 26, 3); 
  u8g2.setDrawColor(1);

  u8g2.drawRBox(bX+15, bY-9, 16, 9, 2); 
  u8g2.drawRBox(bX+35, bY-11, 22, 11, 3); 
  u8g2.drawBox(bX+60, bY-6, 14, 6); 
  u8g2.drawLine(bX+5, bY, bX+80, bY); 

  u8g2.setFont(u8g2_font_5x7_tf);
  u8g2.drawStr(2, 10, "Leaving Holiday Behind...");
}

// =========================================================
// المشهد الثاني: الـ Zoom (الوجه الأمامي والدموع المزدوجة)
// =========================================================
void drawZoomedStudent() {
  int x0 = 10, y0 = vib;

  u8g2.drawRFrame(x0, y0, 110, 60, 4); 
  u8g2.drawLine(x0+2, y0, x0+2, y0+60); 
  for(int i=0; i<128; i+=4) {
    for(int j=0; j<64; j+=4) {
      if ((i < x0 || i > x0+110) || (j < y0 || j > y0+60)) {
         if ((i+j) % 2 == 0) u8g2.drawPixel(i,j); 
      }
    }
  }

  int hX = x0 + 35; 
  int hY = y0 + 10; 

  u8g2.drawRBox(hX, hY, 40, 32, 4); 
  u8g2.drawBox(hX - 2, hY - 2, 44, 8); 
  u8g2.drawBox(hX - 4, hY + 6, 6, 16); 
  u8g2.drawBox(hX + 38, hY + 6, 6, 16); 

  u8g2.setDrawColor(0);
  u8g2.drawFrame(hX + 4, hY + 12, 12, 10); 
  u8g2.drawFrame(hX + 24, hY + 12, 12, 10); 
  u8g2.drawLine(hX + 16, hY + 15, hX + 24, hY + 15); 
  
  u8g2.drawBox(hX + 8, hY + 15, 4, 4); 
  u8g2.drawBox(hX + 28, hY + 15, 4, 4); 
  
  u8g2.drawLine(hX + 16, hY + 26, hX + 24, hY + 26);
  u8g2.drawPixel(hX + 15, hY + 27);
  u8g2.drawPixel(hX + 25, hY + 27);

  int elapsedCloseUp = millis() - startTime - 6000;
  int tear1_Y = map(elapsedCloseUp % 1500, 0, 1500, hY+22, hY+40);
  int tear2_Y = map((elapsedCloseUp + 750) % 1500, 0, 1500, hY+22, hY+40);

  u8g2.drawBox(hX + 9, tear1_Y, 2, 4); 
  u8g2.drawBox(hX + 29, tear2_Y, 2, 3); 
  u8g2.setDrawColor(1);

  u8g2.drawBox(hX - 15, hY + 34, 70, 20); 
  u8g2.setDrawColor(0);
  u8g2.drawLine(hX + 5, hY + 32, hX + 35, hY + 32); 
  u8g2.setDrawColor(1);
  
  u8g2.drawRBox(hX - 5, y0 + 50, 14, 6, 2); 
  u8g2.drawRBox(hX + 31, y0 + 50, 14, 6, 2); 
}

// =========================================================
// المشهد الثالث: لافتة النهاية الدرامية (انتهت العطلة!)
// =========================================================
void drawEndSign(unsigned long elapsed) {
  // اللافتة تسقط من الأعلى بسرعة خلال ثانية واحدة
  int signY = map(elapsed, 10000, 10500, -40, 20);
  if (signY > 20) signY = 20; // تتوقف في منتصف الشاشة

  // السلاسل الحديدية التي تمسك اللافتة
  u8g2.setDrawColor(1);
  for(int i=0; i<signY; i+=4) {
    u8g2.drawCircle(20, i, 1);
    u8g2.drawCircle(108, i, 1);
  }

  // خلفية اللافتة الصلبة
  u8g2.drawRBox(8, signY, 112, 28, 4);
  
  // حفر الإطار الداخلي باللون الأسود
  u8g2.setDrawColor(0);
  u8g2.drawRFrame(10, signY + 2, 108, 24, 2);
  
  // النص العريض والصادم
  u8g2.setFont(u8g2_font_8x13B_tf); // خط عريض وواضح
  u8g2.drawStr(14, signY + 18, "HOLIDAY OVER!");
  u8g2.setDrawColor(1);
}

// =========================================================
// حلقة التشغيل والمؤثرات الصوتية الشاملة
// =========================================================
void loop() {
  u8g2.clearBuffer();
  frame++;
  vib = (frame % 2 == 0) ? 1 : 0; 
  
  unsigned long elapsed = millis() - startTime;
  
  int bX = 10; 
  int bY = 28 + vib; 

  if (elapsed < 5000) {
    // 1. المشهد الجانبي (المحرك)
    bX = 10;
    drawDetailedSideBus(bX, bY);
    if (frame % 8 == 0) tone(BUZZER_PIN, 100, 30); 
  } 
  else if (elapsed < 6000) {
    // 2. حركة الكاميرا (الزوم)
    bX = map(elapsed, 5000, 6000, 10, 30); 
    drawDetailedSideBus(bX, bY);
    int zoomFreq = map(elapsed, 5000, 6000, 150, 800); 
    tone(BUZZER_PIN, zoomFreq, 20);
  } 
  else if (elapsed < 10000) { 
    // 3. مشهد الدموع
    drawZoomedStudent();
    int elapsedCloseUp = elapsed - 6000;
    if (elapsedCloseUp % 1500 < 30) tone(BUZZER_PIN, 1200, 40); 
    if ((elapsedCloseUp + 750) % 1500 < 30) tone(BUZZER_PIN, 1000, 30); 
  } 
  else if (elapsed < 14000) {
    // 4. المشهد الختامي الصادم (سقوط اللافتة)
    drawZoomedStudent(); // إبقاء الطالب كخلفية
    drawEndSign(elapsed);
    
    // مؤثر صوتي لارتطام اللافتة القوي (بين 10.5 ثانية و 10.6 ثانية)
    if (elapsed > 10500 && elapsed < 10600) {
      tone(BUZZER_PIN, 50, 100); // صوت (Thud!) منخفض التردد
    }
  } 
  else {
    // إعادة الدورة السينمائية من البداية بعد 14 ثانية
    startTime = millis(); 
  }

  u8g2.sendBuffer();
  delay(30); 
}
