#include <XInput.h>

String dataIn;
short selectionshort;
short messageshort;
short stickXValue;
bool stickXvalueSet;
bool desynced = false;

void setup() {
  Serial1.begin(19200);
  XInput.begin();
}

void handleDesync()
{
  dataIn = "";
  messageshort = 0;
  stickXValue = 0;
  stickXvalueSet = false;
  desynced = true;
  selectionshort = -2;
  writeAwnser();

  selectionshort = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!Serial1.available())
  {
    return;
  }
  
  readDataFromSerial1();

  if(desynced)
  {
    desynced = false;
    return;
  }

  if(selectionshort == -1)
  {
    writeAwnser();
    return;
  }

  if(selectionshort < 15)
  {
    handleButtons();
    writeAwnser();
  }

  if(selectionshort == 15 || selectionshort == 16)
  {
    handleTriggers();
    writeAwnser();
  }

  if(selectionshort == 17 || selectionshort == 18)
  {
    handleJoySticks();
    writeAwnser();
  }
}

void writeAwnser()
{
  Serial1.println(String(selectionshort));
}

void readDataFromSerial1()
{
  unsigned long StartTime = millis();
  
  boolean readFirst = true;
  
  while(true)
  { 
    if(millis() - StartTime >= 1000)
    {
      handleDesync();
      return;
    }
    
    if(!Serial1.available())
    {
      continue;
    }
    
    char temp = Serial1.read();

    if(temp == '\n')
    {
      if(readFirst)
      {
        readFirst = false;
        selectionshort = dataIn.toInt();
        dataIn = "";
        StartTime = millis();
      }
      else
      {
        messageshort = dataIn.toInt();
        dataIn = "";
        return;
      }
    }

    dataIn += temp;
  }
}

void handleButtons()
{
  if(messageshort == 1)
  {
    XInput.press(XInputControl(selectionshort));
  }
  else
  {
    XInput.release(XInputControl(selectionshort));
  }
}

void handleTriggers()
{
  XInput.setTrigger(selectionshort, messageshort);
}

void handleJoySticks()
{
  if(stickXvalueSet)
  {
    if(selectionshort == 17)
    {
      XInput.setJoystick(JOY_LEFT,stickXValue, messageshort);
    }
    else
    {
      XInput.setJoystick(JOY_RIGHT,stickXValue, messageshort);
    }

    stickXvalueSet = false;
    messageshort = 0 ;
  }
  else
  {
    stickXvalueSet = true;
    stickXValue = messageshort;
  }
}
