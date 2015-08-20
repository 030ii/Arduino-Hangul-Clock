

#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 6 

Adafruit_NeoPixel strip = Adafruit_NeoPixel(40, PIN, NEO_GRB + NEO_KHZ800);
uint32_t color = strip.Color(232, 101, 12); // 주황 
uint32_t colorPINK = strip.Color(232, 12, 93); // 핑크 
uint32_t colorBLUE = strip.Color(12, 48, 232); // 파랑 

void setup() {
  Serial.begin(9600);
  #if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  strip.begin();
  strip.show();
  while (!Serial) ; // 시리얼 통신이 가능할 때까지 대기한다.
  delay(200);
}

void loop() {
  tmElements_t tm; // RTC 객체 선언

  if (RTC.read(tm)) { //RTC 모듈로 부터 데이터가 들어온다면
    
    int hours = tm.Hour; //시(hour) 데이터를 hours 변수에 담는다.
    int minutes = tm.Minute; //분(minute) 데이터를 minutes 변수에 담는다.
    int seconds = tm.Second; //초(second) 데이터를 seconds 변수에 담는다.

    // 시, 분, 초 출력
    Serial.print(hours);
    Serial.print("\t");
    Serial.print(minutes);
    Serial.print("\t");
    Serial.println(seconds);
    
   
    // 1분에 한번씩 led 초기화
    if((minutes%1)==0 && seconds ==0){ 
    ledReset();
    }

  ampmFilter(hours); // 오전 오후 LED 출력 
    hoursFilter(hours,minutes); // 시(hour) LED 출력
    minutesFilter(minutes); // 분(minute) LED 출력
    strip.show();
  }
  else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } 
    else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }
  delay(1000);
}


void ampmFilter(int hours){
  // 오전 
  if(hours >= 0 && hours <= 11){
    strip.setPixelColor(9,colorPINK);
    strip.setPixelColor(8,colorPINK);}
  // 오후
  else if(hours >= 12 && hours <= 23){
    strip.setPixelColor(10,colorBLUE);
    strip.setPixelColor(11,colorBLUE);}
  else;
}

void hoursFilter(int hours,int minutes){
  if(hours == 0 || hours == 12){  //00:00
    strip.setPixelColor(5,color);
    strip.setPixelColor(14,color);
    strip.setPixelColor(19,color);}
  else if(hours == 1 || hours == 13){ // 1:00
    strip.setPixelColor(4,color);
    strip.setPixelColor(19,color);}
  else if(hours == 2 || hours == 14){ // 2:00
    strip.setPixelColor(14,color);
    strip.setPixelColor(19,color);}
  else if(hours == 3 || hours == 15){ // 3:00
    strip.setPixelColor(6,color);
    strip.setPixelColor(19,color);}
  else if(hours == 4 || hours == 16){
    strip.setPixelColor(13,color);
    strip.setPixelColor(19,color);}    
  else if(hours == 5 || hours == 17){
    strip.setPixelColor(15,color);
    strip.setPixelColor(16,color);
    strip.setPixelColor(19,color);}  
  else if(hours == 6 || hours == 18){
    strip.setPixelColor(3,color);
    strip.setPixelColor(16,color);
    strip.setPixelColor(19,color);} 
  else if(hours == 7 || hours == 19){
    strip.setPixelColor(1,color);
    strip.setPixelColor(0,color);
    strip.setPixelColor(19,color);}   
  else if(hours == 8 || hours == 20){
    strip.setPixelColor(3,color);
    strip.setPixelColor(2,color);
    strip.setPixelColor(19,color);}
  else if(hours == 9 || hours == 21){
    strip.setPixelColor(17,color);
    strip.setPixelColor(18,color);
    strip.setPixelColor(19,color);}     
  else if(hours == 10 || hours == 22){
    strip.setPixelColor(5,color);
    strip.setPixelColor(19,color);} 
  else if(hours == 11 || hours == 23){
    strip.setPixelColor(5,color);
    strip.setPixelColor(4,color);
    strip.setPixelColor(19,color);} 
  else if(hours == 12 || hours == 24){
    strip.setPixelColor(5,color);
    strip.setPixelColor(14,color);
    strip.setPixelColor(19,color);}
  else ;      
}

// 오전  세열한여덞일곱  9  8     6  5  4  3  2  1  0
// 오후  네두다섯아홉시  10 11    13 14 15 16 17 18 19 
// 오사삼이십일이삼사오  29 28 27 26 25 24 23 22 21 20
//        육칠팔구분                 35 36 37 38 39

void minutesFilter(int minutes){

  int minutesBy1 = minutes%10; // 0~9
  int minutesBy10 = minutes/10; // 0~5

  // 일의 자리 
  if(minutesBy1 == 1){ // 1분 
    strip.setPixelColor(24,color);
    strip.setPixelColor(39,color);}
  else if(minutesBy1 == 2){ // 2분 
    strip.setPixelColor(23,color);
    strip.setPixelColor(39,color);}
  else if(minutesBy1 == 3){ // 3분 
    strip.setPixelColor(22,color);
    strip.setPixelColor(39,color);}
  else if(minutesBy1 == 4){ // 4분 
    strip.setPixelColor(21,color);
    strip.setPixelColor(39,color);}
  else if(minutesBy1 == 5){ // 5분 
    strip.setPixelColor(20,color);
    strip.setPixelColor(39,color);}
  else if(minutesBy1 == 6){ // 6분 
    strip.setPixelColor(35,color);
    strip.setPixelColor(39,color);}
  else if(minutesBy1 == 7){ // 7분 
    strip.setPixelColor(36,color);
    strip.setPixelColor(39,color);}
  else if(minutesBy1 == 8){ // 8분 
    strip.setPixelColor(37,color);
    strip.setPixelColor(39,color);}
  else if(minutesBy1 == 9){ // 9분 
    strip.setPixelColor(38,color);
    strip.setPixelColor(39,color);}
  else;


  // 10의 자리 
  if(minutesBy10 == 1){ // 10분 
    if(minutesBy1 == 0){
      strip.setPixelColor(39,color);}
    strip.setPixelColor(25,color);}
  else if(minutesBy10 == 2){ // 20분 
    if(minutesBy1 == 0){
      strip.setPixelColor(39,color);}
    strip.setPixelColor(26,color);
    strip.setPixelColor(25,color);}
  else if(minutesBy10 == 3){ // 30분 
    if(minutesBy1 == 0){
      strip.setPixelColor(39,color);}
    strip.setPixelColor(27,color);
    strip.setPixelColor(25,color);}
  else if(minutesBy10 == 4){ // 40분 
    if(minutesBy1 == 0){
      strip.setPixelColor(39,color);}
    strip.setPixelColor(28,color);
    strip.setPixelColor(25,color);}
  else if(minutesBy10 == 5){ // 50분 
    if(minutesBy1 == 0){
      strip.setPixelColor(39,color);}
    strip.setPixelColor(29,color);
    strip.setPixelColor(25,color);}
}

void ledReset(){
for(int i=0;i<40;i++){
    strip.setPixelColor(i,0,0,0);
    strip.show();
  }
}
