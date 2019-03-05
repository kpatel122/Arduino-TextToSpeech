/*
Speech.h - A library for speech synthesis with a XFS5152CE
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

#ifndef SPEECH_H
#define SPEECH_H

#include "Arduino.h"
#include <SoftwareSerial.h>



#define MAX_SPEECH_CHAR 256

class CSpeech
{
  public:
    CSpeech(int rx,int tx, int baud);
    void speak(String message);
    void waitForSpeech(unsigned long timeout = 60000);
  
  private:
    void sendMessagetoSpeechModule();

    SoftwareSerial ss; // rx, tx
    char messageBuffer[MAX_SPEECH_CHAR];
    String incoming;
    String options;
    String messageString;
    int stringLength;
    
};

#endif
