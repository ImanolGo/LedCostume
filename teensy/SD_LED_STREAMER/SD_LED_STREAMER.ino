//******** ONLY CHANGE THESE ******************
#define COLOR_ORDER GRB        //Shouldn't need changing - just incase your RGB channels change order
#define CHIPSET     WS2812B    //Choose your chipset
#define NUM_LEDS    600         //No. of LEDs in your strip - should tally with the image width
#define LINE_DELAY  42         //Delay in ms until the next pattern is displayed
#define BRIGHTNESS  255        //Overall brightness of the LEDs on a scale from 0(off)-255(max birghtness)

#define FPS  24               //Frames per second used for the animation

#define NO_OF_FILES 6

//*** MAKE SURE FILE NAME IS SHORT (<=5 characters excluding .bmp bit)
char fileName[30] = "3.bmp";
char* fileNames[] = {"6.bmp", "2.bmp", "3.bmp", "4.bmp", "5.bmp", "1.bmp"};
bool loopMode[] = {false, false, false, true, true, true};

//**********************************************

#include <elapsedMillis.h>

#define LED_PIN     5
#define LED_CLK     4
#include <FastLED.h>
#include <SD.h>
#include <SPI.h>

File myFile;

elapsedMillis timeElapsed; // These special variable types automatically increase as time elapses. 
unsigned int interval = 1000/FPS; // delay in milliseconds between frames

long height = 1;
long bitmapOffset = 0x36;
long filePosition = 0;
int currentFrame = 0;
int currentSample = -1;
bool loopVisual = false;
bool isPlaying = false;

#define SDchipSelect 10       //chip select for SD card --53 on mega, 10 on 328
#define WSchipSelect 5       //chip select for WS2801
#define serialDebug 0        //whether or not to output whats read

CRGB leds[NUM_LEDS];

//************SETUP*************

void setup(){
    Serial.begin(115200);
    
    //delay(2000);
    
    Serial.println("Start");
    
    FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    
    FastLED.setBrightness(BRIGHTNESS);
    
    
      Serial.print("Initializing SD card...");
      pinMode(SDchipSelect, OUTPUT);   //required for SPI to work
      pinMode(WSchipSelect, OUTPUT);   //required for WS2801 'spi' to work
      if (!SD.begin(SDchipSelect)) {
        Serial.println("Card failed, or not present");
        return;
      }
      Serial.println("card initialized.");

      nextSample();     
}

//************MAIN LOOP*************

void loop() { 

  if (timeElapsed > interval && isPlaying) {       
      nextLEDFrame();
      timeElapsed = 0;       // reset the counter to 0 so the counting starts over...
  }
} 

//************FUNCTIONS*************

void nextSample() {
  
  currentSample = (currentSample + 1) % NO_OF_FILES;
  loadBMPinfo(currentSample); //check the file for output
  loopVisual = loopMode[currentSample];
  initSample(); 
}

void initSample() { //Played also when it is in sample mode, for every beat
  isPlaying = true; 
  timeElapsed = 0;
  currentFrame = 0;
  setFrame(0);
}

void loadBMPinfo(int file) {
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

void nextLEDFrame() {
   
    currentFrame = (currentFrame + 1) % height;

    if(currentFrame == 0 && !loopVisual){ // Sample Mode - Don't loop
      isPlaying = false;
      return;
    }
   
    int index = height - currentFrame - 1;
    setFrame(index);
   
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
      
      //read an entire line to leds[]
      for(int i=0; i < NUM_LEDS; i++) {
          leds[i].b=myFile.read();
          leds[i].g=myFile.read();
          leds[i].r=myFile.read();   
                 
          if (serialDebug) {
            Serial.print(leds[i].r,HEX);  
            Serial.print(":");
            Serial.print(leds[i].g,HEX);  
            Serial.print(":");
            Serial.print(leds[i].b,HEX);  
            Serial.print(",");
          }
          
      }  
  
      FastLED.show(); //fastspi output
}


void streamSdToLED() {
  
    //loop through each line in the file, then spit it out.
    for(int lineNo=0; lineNo<height;lineNo++) {
        
        filePosition = bitmapOffset+ (lineNo *(NUM_LEDS * 3) );
        myFile.seek(filePosition);//get to data
        memset(leds, 0, NUM_LEDS * 3);//blank the array
        
        //something went wrong, myFile should not return -1 here.
        if (!myFile){ 
            Serial.println("the card broke"); 
        }
        
        //read an entire line to leds[]
        for(int i=0; i < NUM_LEDS; i++) {
            leds[i].b=myFile.read();
            leds[i].g=myFile.read();
            leds[i].r=myFile.read();   
                   
            if (serialDebug) {
              Serial.print(leds[i].r,HEX);  
              Serial.print(":");
              Serial.print(leds[i].g,HEX);  
              Serial.print(":");
              Serial.print(leds[i].b,HEX);  
              Serial.print(",");
            }
            
        }  
        
        if (serialDebug) {
        Serial.println("EOL"); //end of each line
        }
        delay(LINE_DELAY);
        FastLED.show(); //fastspi output
    }    
} 

