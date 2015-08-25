//**** THIS VERSION HAS 8 OUTPUTS FOR WS2812B AND 2 OUTPUTS FOR WS2801 *******
//**** ALSO HAS A BUTTON INPUT FOR CYCLING DIFFERENT PATTERNS ****************
//****************************************************************************
//**** SINGLE CLICK TO SELECT NEXT BITMAP, ***********************************
//**************** DOUBLE TO ENABLE/DISABLE AUDIO REACTIVE MODE, *************
//****************************** HOLD TO TOGGLE ALL OUTPUTS ON/OFF ***********


//******** ONLY CHANGE THESE ******************
#define COLOR_ORDER GRB        //Shouldn't need changing - just incase your RGB channels change order
#define LINE_DELAY  42          //Delay in ms until the next pattern is displayed
#define BRIGHTNESS  160         //Overall brightness of the LEDs on a scale from 0(off)-255(max brightness)
#define MAX_BRIGHTNESS  255     //Max Brightness


#define FPS  24               //Frames per second used for the animation

const int buttonPin1=18;       //Pin to change which bitmap it is currently reading from. Tied high, acitve low. Triggered on rising edge
                               //SHOULDN'T REALLY BE CHANGED UNLESS NEEDED
                               //Need to include a 0.1uF external capacitor between this pin and GND for debouncing

#define AUDIO_PIN A9            //Shouldn't need to change. A9 analogue input

//----------------------------------------------------------
// IF NOT USING AN OUTPUT, SET LENGTH TO 0
// ALL STRING LENGTHS SHOULD ADD UP TO BITMAP IMAGE WIDTH
//----------------------------------------------------------

/*
//Anya's numbers:
#define STRING1  14           // Length of 1st string (WS2812B)
#define STRING2  110           // Length of 2nd string (WS2812B)
#define STRING3  143           // Length of 3rd string (WS2812B)
#define STRING4  143           // Length of 4th string (WS2812B)
#define STRING5  103           // Length of 5th string (WS2812B)
#define STRING6  103           // Length of 6th string (WS2812B)
#define STRING7  72            // Length of 7th string (WS2812B)
#define STRING8  72            // Length of 8th string (WS2812B)
#define STRING9  18            // Length of 9th string  (WS2801)
#define STRING10 5            // Length of 10th string (WS2801)
*/

//jonathans numbers:
#define STRING1  79           // Length of 1st string (WS2812B)
#define STRING2  79           // Length of 2nd string (WS2812B)
#define STRING3  82           // Length of 3rd string (WS2812B)
#define STRING4  82           // Length of 4th string (WS2812B)
#define STRING5  74           // Length of 5th string (WS2812B)
#define STRING6  74           // Length of 6th string (WS2812B)
#define STRING7  55            // Length of 7th string (WS2812B)
#define STRING8  55            // Length of 8th string (WS2812B)
#define STRING9  8            // Length of 9th string  (WS2801)
#define STRING10 8            // Length of 10th string (WS2801)
/*

//long numbers:
#define STRING1  100           // Length of 1st string (WS2812B)
#define STRING2  100           // Length of 2nd string (WS2812B)
#define STRING3  100           // Length of 3rd string (WS2812B)
#define STRING4  100           // Length of 4th string (WS2812B)
#define STRING5  100           // Length of 5th string (WS2812B)
#define STRING6  100           // Length of 6th string (WS2812B)
#define STRING7  100            // Length of 7th string (WS2812B)
#define STRING8  100            // Length of 8th string (WS2812B)
#define STRING9  100            // Length of 9th string  (WS2801)
#define STRING10 100            // Length of 10th string (WS2801)
*/

// pixel width : 587!!!

#define NO_OF_FILES 20
//*** MAKE SURE FILE NAMES ARE SHORT (<=5 characters excluding .bmp bit)
char* fileNames[] = {"1.bmp", "2.bmp", "3.bmp", "4.bmp", "5.bmp", "6.bmp", "7.bmp", "8.bmp", "9.bmp", "10.bmp",
                      "11.bmp", "12.bmp", "13.bmp", "14.bmp", "15.bmp", "16.bmp", "17.bmp", "18.bmp", "19.bmp", "20.bmp"}; //, "13.bmp", "14.bmp", "15.bmp", "16.bmp", "17.bmp", "18.bmp", "19.bmp", "20.bmp"};
//char* fileNames[] = {"1.bmp"};

//******************************************************
//******************************************************
//----------DON'T CHANGE VARIABLES AFTER HERE-----------
//******************************************************
//******************************************************

// FOR WS2812B
#define LED_PIN1     2        //Pin of 1st string
#define LED_PIN2     5        //Pin of 2nd string 2 and 4 accidentally swapped on Jonathans outfit
#define LED_PIN3     4        //Pin of 3rd string
#define LED_PIN4     3        //Pin of 4th string
#define LED_PIN5     6        //Pin of 5th string
#define LED_PIN6     7        //Pin of 6th string
#define LED_PIN7     8        //Pin of 7th string
#define LED_PIN8     9        //Pin of 8th string
//FOR WS2801
#define LED_DATA_PIN1  14
#define LED_DATA_PIN2  15
#define LED_CLOCK_PIN1 16
#define LED_CLOCK_PIN2 17

#include <Audio.h>
#include <Wire.h>
#include <FastLED.h>
#include <SD.h>
#include <SPI.h>
#include "ClickButton.h"
ClickButton button1(buttonPin1, LOW, CLICKBTN_PULLUP);

// GUItool: begin automatically generated code
AudioInputAnalog         adc1(AUDIO_PIN);           //xy=164,95
AudioAnalyzePeak         peak1;          //xy=317,123
AudioAnalyzeFFT256       fft256;
AudioConnection          patchCord1(adc1, peak1);
AudioConnection          patchCord2(adc1,fft256);
// GUItool: end automatically generated code

//FFT audio mode
float scale = 60.0*32.0; // The scale sets how much sound is needed in each frequency range to show full brightness
float level = 0; // Value holding one frequency band
int shown = 0;// holds the value in case id quickly drops

//Gui
bool guiOn = true;
bool laserOn = true;
bool peakDetected = false;

File myFile;

elapsedMillis timeElapsed; // These special variable types automatically increase as time elapses. 
unsigned int interval = 1000/FPS; // delay in milliseconds between frames

long height = 1;
long bitmapOffset = 0x36;
long filePosition = 0;
int currentFrame = 0;
int currentSample = -1;

int presses=0;
int imageNo=0;
int ifbreak=0;
int onoff=1;
int time=0;
int audioMode=0;
int monoPeak;
int previousPeak;
int lineNo = 0;

#define SDchipSelect 10       //chip select for SD card --53 on mega, 10 on 328
#define WSchipSelect 5       //chip select for WS2801
#define serialDebug 0        //whether or not to output what's read

unsigned int NUM_LEDS = STRING1+STRING2+STRING3+STRING4+STRING5+STRING6+STRING7+STRING8+STRING9+STRING10;
unsigned int LASER_OFFSET = STRING1+STRING2+STRING3+STRING4+STRING5+STRING6+STRING7+STRING8;
CRGB leds[STRING1+STRING2+STRING3+STRING4+STRING5+STRING6+STRING7+STRING8+STRING9+STRING10];

//*********SETUP*************

void setup(){
    AudioMemory(4);
  
    Serial.begin(115200);   
    Serial.println("Start");
    
    //pinMode(SWITCH_PIN, INPUT_PULLUP);
    //attachInterrupt(SWITCH_PIN, ISR, FALLING);
    
    //IN THE FORMAT (LEDS, START FROM INDEX, SUB STRING LENGTH) 
    if(STRING1!=0){FastLED.addLeds<WS2812B, LED_PIN1, COLOR_ORDER>(leds, 0, STRING1);}
    if(STRING2!=0){FastLED.addLeds<WS2812B, LED_PIN2, COLOR_ORDER>(leds, STRING1, STRING2);}
    if(STRING3!=0){FastLED.addLeds<WS2812B, LED_PIN3, COLOR_ORDER>(leds, STRING1+STRING2, STRING3);}
    if(STRING4!=0){FastLED.addLeds<WS2812B, LED_PIN4, COLOR_ORDER>(leds, STRING1+STRING2+STRING3, STRING4);}
    if(STRING5!=0){FastLED.addLeds<WS2812B, LED_PIN5, COLOR_ORDER>(leds, STRING1+STRING2+STRING3+STRING4, STRING5);}
    if(STRING6!=0){FastLED.addLeds<WS2812B, LED_PIN6, COLOR_ORDER>(leds, STRING1+STRING2+STRING3+STRING4+STRING5, STRING6);}
    if(STRING7!=0){FastLED.addLeds<WS2812B, LED_PIN7, COLOR_ORDER>(leds, STRING1+STRING2+STRING3+STRING4+STRING5+STRING6, STRING7);}
    if(STRING8!=0){FastLED.addLeds<WS2812B, LED_PIN8, COLOR_ORDER>(leds, STRING1+STRING2+STRING3+STRING4+STRING5+STRING6+STRING7, STRING8);}
    if(STRING9!=0){FastLED.addLeds<WS2801, LED_DATA_PIN1, LED_CLOCK_PIN1, COLOR_ORDER>(leds, STRING1+STRING2+STRING3+STRING4+STRING5+STRING6+STRING7+STRING8, STRING9);}
    if(STRING10!=0){FastLED.addLeds<WS2801, LED_DATA_PIN2, LED_CLOCK_PIN2, COLOR_ORDER>(leds, STRING1+STRING2+STRING3+STRING4+STRING5+STRING6+STRING7+STRING8+STRING9, STRING10);}

    
    // Setup button timers (all in milliseconds / ms)
    // (These are default if not set, but changeable for convenience)
    button1.debounceTime   = 250;   // Debounce timer in ms
    button1.multiclickTime = 50;  // Time limit for multi clicks
    button1.longClickTime  = 1000; // time until "held-down clicks" register
    
    //FastLED.setBrightness(BRIGHTNESS);
    
    
      Serial.print("Initializing SD card...");
      pinMode(SDchipSelect, OUTPUT);   //required for SPI to work
      pinMode(WSchipSelect, OUTPUT);   //required for WS2801 'spi' to work
      if (!SD.begin(SDchipSelect)) {
        Serial.println("Card failed, or not present");
        return;
      }
      Serial.println("card initialized.");

      //nextSample();
      //loadBMPinfo(imageNo); 
      
}

elapsedMillis fps;

//************MAIN LOOP*************

void loop() { 

  checkButton();

  if(timeElapsed > interval){

        setGuiLeds();
        
        if(audioMode==2){
          //calculateSoundLevel();
        }
        
        if(beatDetected){ 
         // initSample();
        }
        else{
           //nextLEDFrame();
        }
         
         timeElapsed = 0;       // reset the counter to 0 so the counting starts over..
  }
} 

//********************************


void loadBMPinfo(int file) {
    
    if (!SD.exists(fileNames[file])) {
        setLedsOff();
        return;
    }
    
    byte heightByte[4]; 
    height = 0; //start with a zero'd signed long, 4 bytes.
    myFile.close();  
    myFile = SD.open(fileNames[file], FILE_READ);
    //Serial.print("BitmapOffsetStart:");
    //Serial.println(bitmapOffset,HEX);
    myFile.seek(0x16); //goto start byte of bitmap height 
    
    for (int i = 0; i < 4; i++){  //height is a 4 byte integer stored in reverse byte order
      heightByte[i] = myFile.read();
    } //end for grab
    
    for (int i = 3; i > 0; i--){ //3 2 1 not zero
      height = height | heightByte[i]; //add the i'th byte
      height = height << 8;            //bitshift everything 1 byte left
    }
    height = height | heightByte[0]; 
    myFile.seek(0xA);
    bitmapOffset = myFile.read();
    
    Serial.print("BitmapOffset:");   //debug if the bitmap data offset is correct
    Serial.println(bitmapOffset,HEX);
    Serial.print("Height:");
    Serial.println(height);
} 

void nextSample() {
  
  currentSample = (currentSample + 1) % NO_OF_FILES;
  loadBMPinfo(currentSample); //check the file for output
  initSample(); 
}

void initSample() { //Played also when it is in sample mode, for every beat 
  timeElapsed = 0;
  currentFrame = 0;
  setFrame(0);
}

void streamSdToLED() {
  
    //loop through each line in the file, then spit it out.
    for(lineNo=0; lineNo<height;lineNo++) {
     
        checkButton();

        if(guiOn){
          setGuiLeds();
        }
        else{
          calculateSoundLevel();
          setFrame(lineNo);
        }
      
                              
        if (serialDebug) {
        Serial.println("EOL"); //end of each line
        }
        
        
        for(time=0; time<=LINE_DELAY; time++){
            delay(1);            
            //detectPeak();
        }

        
        if(peakDetected){peakDetected=false; lineNo=0;}

        FastLED.show(); //fastspi output
        button1.Update();
    }    
} 


void checkButton() {
    
    button1.Update();
    
     if(button1.clicks != 0) presses = button1.clicks;
      
        if(presses == 1){  //Single short click
            presses=0;

            if(guiOn){
              nextSample();
              guiOn = false;
            }
            else{
              //loadNextImage();
              guiOn = true;
           }
             
        }
        
        else if(presses == 2){    //Double short click
            presses=0;
            Serial.println("DOUBLE click");
            audioMode = (audioMode+1)%3;
        }

        else if(presses == 3){    //Triple short click
            presses=0;
            Serial.println("Triple click");
            laserOn = !laserOn;
        }
      
       else if(presses == -1){    //Single long press
           presses=0;
           onoff=0;
           setLedsOff();
           
           while(onoff==0){
             button1.Update();
             if(button1.clicks==-1){onoff=1;}
           }
        }
}

void setGuiLeds() 
{

  for(int i=0; i < NUM_LEDS; i++) 
  {
      leds[i].b=0;
      leds[i].g=0;
      leds[i].r=0;
  }

  unsigned int J_2 = STRING1;  
  unsigned int J_5 = STRING1+STRING2+STRING3+STRING4;
  unsigned int J_6 = J_5 + STRING5;

  int numLeds = currentSample + 1;
  for(int i=0; i < numLeds; i++) 
  {
     if(audioMode==0){
        leds[J_2 + i].b = BRIGHTNESS;
        leds[J_5 + i].b = BRIGHTNESS;
        leds[J_6 + i].b = BRIGHTNESS;
     }
     else if(audioMode==1){
        leds[J_2 + i].g = BRIGHTNESS;
        leds[J_5 + i].g = BRIGHTNESS;
        leds[J_6 + i].g = BRIGHTNESS;
     }

     else if(audioMode==2){
        leds[J_2 + i].r = BRIGHTNESS;
        leds[J_5 + i].r = BRIGHTNESS;
        leds[J_6 + i].r = BRIGHTNESS;
     }
  }

  FastLED.show(); //fastspi output
}

void setFrame(int frameIndex) {

  if(frameIndex < 0 || frameIndex >= height){
    return;
  }

  
   filePosition = bitmapOffset+ (frameIndex *(NUM_LEDS * 3) );
   myFile.seek(filePosition);//get to data
   memset(leds, 0, NUM_LEDS * 3);//blank the array
  
    //something went wrong, myFile should not return -1 here.
      if (!myFile){ 
          Serial.println("the card broke"); 
          return;
      }
      
     int brightness = BRIGHTNESS;
     if(audioMode==2){
        brightness = BRIGHTNESS*shown/MAX_BRIGHTNESS;
      }
      //read an entire line to leds[]
      for(int i=0; i < NUM_LEDS; i++) {

        leds[i].b = myFile.read();
        leds[i].g= myFile.read();
        leds[i].r= myFile.read();  
         
        if(i<LASER_OFFSET){
          leds[i].b = leds[i].b*brightness/MAX_BRIGHTNESS;
          leds[i].g = leds[i].g*brightness/MAX_BRIGHTNESS; 
          leds[i].r = leds[i].r*brightness/MAX_BRIGHTNESS;
        }
        else{
          if(!laserOn){
            leds[i].b = 0;
            leds[i].g = 0; 
            leds[i].r = 0;
          }
        }

        FastLED.show(); //fastspi output
        
        if (serialDebug) {
            Serial.print(leds[i].r,HEX);  
            Serial.print(":");
            Serial.print(leds[i].g,HEX);  
            Serial.print(":");
            Serial.print(leds[i].b,HEX);  
            Serial.print(",");
          }
      }
}

void loadNextImage()
{
    lineNo = 0;
    imageNo= (imageNo+1)%NO_OF_FILES;
    loadBMPinfo(imageNo);
    Serial.println("***NEXT IMAGE***");
}

void calculateSoundLevel()
{
    if (fft256.available()) 
    {
         level = fft256.read(4,10); ///Low band frequency
         //int val = level * scale;
         int val = zmap(level, 0, 0.1, 30, MAX_BRIGHTNESS, true);
         //val = 100;
         //Serial.println(val);  
         if (val > MAX_BRIGHTNESS) val = MAX_BRIGHTNESS;
  
          if (val >= shown) {
             shown = val;
           } 
          else  {
              if (shown > 0) shown = shown - 10;
  
          }
      }
}

bool beatDetected() 
{
  if(audioMode!=1){ 
      return false;
  }
  
  if (peak1.available()) 
  {
      int monoPeak = peak1.read() * 30.0 + 1;
      Serial.println(monoPeak);
      if(monoPeak>=13)
      {
        return true;
      }
   }

   return false;
}


void nextLEDFrame() {

   if(guiOn){
      setGuiLeds();
    }
    else{
       currentFrame = (currentFrame + 1) % height;   
      int index = height - currentFrame - 1;
      setFrame(currentFrame);
   }
       
} 

float setLedsOff(){

      for(int i=0; i < NUM_LEDS; i++) {
              leds[i].b=0;
              leds[i].g=0;
              leds[i].r=0;
           }
     FastLED.show();

}

float zmap(float input, float inMin, float inMax, float outMin, float outMax, bool _clamp){

      float out = (input-inMin)/(inMax-inMin)*(outMax-outMin)+outMin;

      if(_clamp){
        out = clamp(out, outMin, outMax);
      }
      
      return out;

}


float clamp(float value, float valueMin, float valueMax){

      float out = value;
      
      if(value > valueMax){
        out = valueMax;
      }

      if(value < valueMin){
        out = valueMin;
      }
      
    return out;
}
