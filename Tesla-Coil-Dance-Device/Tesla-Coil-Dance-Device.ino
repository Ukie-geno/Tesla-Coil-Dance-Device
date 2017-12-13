#include <MIDI.h>

#define pingPin 7


MIDI_CREATE_DEFAULT_INSTANCE(); 

long duration,avg;
long inches_previous=0;
long count=0;
long inches=0;

void setup() 
{
    //Serial.begin(9600);
   MIDI.begin(1);
}

void loop() 
{
  inches=READ_DISTANCE_SENSOR();
  if ((inches>=2)&&(inches<=80))
  {
    inches=map(inches,1,80,40,127);
    //Serial.println(inches);
    
    MIDI.sendNoteOn(inches, 127, 1);
    delay(500);
    MIDI.sendNoteOff(inches, 0, 1);
    delay(500);
  }
    
    
  
  
  
  

}




long microsecondsToInches(long microseconds) 
{
  // According to Parallax's datasheet for the PING))), there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance travelled by the ping, outbound and return,
  // so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) 
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}

long READ_DISTANCE_SENSOR(void)
{
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  return microsecondsToInches(duration);
  
}


