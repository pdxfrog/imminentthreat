#include <fix_fft.h>

#include <Time.h>

/*
  Reads from an analog input and performs Fast Fourier Transform on 256 point samples
  at an interval of approximately 1.4 seconds.

 */
 

// These constants won't change.  They're used to give names
// to the pins used:
const int ANALOG_IN = A0;  // Analog input pin that the potentiometer is attached to
const int ALERT_OUT = 13; // Analog output pin that the LED is attached to

int dataIndex;
unsigned long time;
unsigned long sampleTime;
char data[256];  //Presumably one byte
char fftIm[256];
bool firstLoop;
char fftAvgOld[128];
char fftAvg[256];
const byte acceptableAboveThreshold = 1;
byte aboveThreshold;
const char threshold = 4;
byte numAlerts;
void setup() {
  // initialize serial communications at 9600 bps:
  firstLoop = true;
  dataIndex=0;
  numAlerts = 0;
  time = millis();
  sampleTime = 0;
  pinMode(ALERT_OUT, OUTPUT);
  digitalWrite(ALERT_OUT, LOW);
  Serial.begin(115200);
}

void loop() {
  time = millis();  // Current time (since program start)
  //Get the data
  if(time-sampleTime >= 1){
    sampleTime = time;
    fftIm[dataIndex] = 0;
    data[dataIndex]=analogRead(ANALOG_IN); 
    dataIndex++;  
  }
  // Do stuff with the data
  if(dataIndex >= 256){
    //Serial.println(time);
    aboveThreshold = 0;
    fix_fft(data,fftIm,8,0);  // Perform FFT with all zeroes for the 
    for(dataIndex = 0; dataIndex<128; dataIndex++){
      data[dataIndex] = sqrt(data[dataIndex]*data[dataIndex]+fftIm[dataIndex]*fftIm[dataIndex]); 
      fftAvg[dataIndex] += data[dataIndex];
      if(!firstLoop){
        fftAvg[dataIndex] >>=1;
        if((fftAvgOld[dataIndex] - fftAvg[dataIndex])> threshold ||
          (fftAvg[dataIndex] - fftAvgOld[dataIndex])> threshold){
            aboveThreshold++; 
        }
      }
      fftAvgOld[dataIndex] = fftAvg[dataIndex];
      Serial.print('0'+fftAvg[dataIndex]);
      Serial.print(' ');
    }
    if(numAlerts >= 1){
        digitalWrite(ALERT_OUT, LOW); 
        numAlerts = 0;
    }
    if(aboveThreshold > acceptableAboveThreshold){
        digitalWrite(ALERT_OUT, HIGH);
        numAlerts++;
    }
    
    Serial.println();
    dataIndex = 0;
    if(firstLoop){
      //Serial.println("End First Loop");
      firstLoop = false; 
    }
  }

 // analogWrite(analogOutPin, outputValue);

}
