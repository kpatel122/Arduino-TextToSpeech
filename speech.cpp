/*
Speech.cpp - A library for speech synthesis with a XFS5152CE
Copyright (c) 2019 Kunal Patel

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

This permission notice shall be included in all copies or 
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/


#include "Arduino.h"
#include "Speech.h"

 

CSpeech::CSpeech(int rx,int tx, int baud):ss(rx,tx)
{
  options = "[x0][t6][v5][s6][m51][g2][h2][n1]";
  ss.begin(baud);
  
}
 
void CSpeech::speak(String message)
{
  
  messageString =options + message;

  // Length (with one extra character for the null terminator)
  stringLength = messageString.length() + 1; 

  // Copy it over 
  messageString.toCharArray(messageBuffer, stringLength);
  sendMessagetoSpeechModule();
}

void CSpeech::sendMessagetoSpeechModule()
{
  ss.write(0xFD);
  ss.write((byte)0x0);
  ss.write(2 + strlen(messageBuffer));
  ss.write(0x01);
  ss.write((byte)0x0);
  ss.write(messageBuffer);
}

void CSpeech::waitForSpeech(unsigned long timeout = 60000) {
  unsigned long start = millis();
  bool done = false;
  while ( ! done && (millis() - start) < timeout ) {
    while ( ss.available() ) {
      if ( ss.read() == 0x4F ) {
        Serial.println("0x4F"); //tmp
        done = true;
        break;
      }
    }
  }
}



