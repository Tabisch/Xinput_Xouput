#include <XInput.h>

String dataIn;
short selectionshort;
short messageshort;
short stickXValue;
bool stickXvalueSet;

void setup() {
  Serial1.begin(9600);
  XInput.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  readDataFromSerial1();

    handleButtons();
  
  stickXvalueSet = false;
  Serial1.print(String(selectionshort));
  Serial1.write('\n');
}

void readDataFromSerial1()
{
  boolean readFirst = true;
  
  while(true)
  { 
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

void chooseStick()
{
  
}

void handleJoySticks()
{
  if(stickXvalueSet)
  {
    Xinput.
  }
  else
  {
    
  }
}
