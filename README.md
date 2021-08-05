# Rotary_Encoder_KY-040_Fixed
This is a state version of reading a KY-040, It offers full accuracy unlike other solutions.


Usage Example:
```c++
#include "RotaryEncoder.h"

int Counter = 0, LastCount = 0; //uneeded just for test
void RotaryChanged(); //we need to declare the func above so Rotary goes to the one below

RotaryEncoder Rotary(&RotaryChanged, 2, 3, 4); // Pins 2 (DT), 3 (CLK), 4 (SW)

void RotaryChanged()
{
  const unsigned int state = Rotary.GetState();
  
  if (state & DIR_CW)  
    Counter++;
    
  if (state & DIR_CCW)  
    Counter--;    
}

void setup()
{
  Rotary.setup();  
  Serial.begin(9600);  
  Serial.println("Rotary Encoder Tests");  
}

void loop()
{
  if (Rotary.GetButtonDown())  
    Serial.println("Yay button down!!!");    

  if (LastCount != Counter)  
  {
    Serial.println(Counter);    
    LastCount = Counter;    
  }
}
```

Credits:

OwnProx

BoolRules: (Original Idea) https://forum.arduino.cc/t/wiring-of-ky-040-rotary-encoder-plus-demo-code/235847/18
