#ifndef _RotaryEncoder_h
#define _RotaryEncoder_h


#define DIR_NONE 0x00           // No complete step yet.
#define DIR_CW   0x10           // Clockwise step.
#define DIR_CCW  0x20           // Anti-clockwise step.
#define R_START     0x3
#define R_CW_BEGIN  0x1
#define R_CW_NEXT   0x0
#define R_CW_FINAL  0x2
#define R_CCW_BEGIN 0x6
#define R_CCW_NEXT  0x4
#define R_CCW_FINAL 0x5

const unsigned char ttable[8][4] = {
    {R_CW_NEXT,  R_CW_BEGIN,  R_CW_FINAL,  R_START},                // R_CW_NEXT
    {R_CW_NEXT,  R_CW_BEGIN,  R_CW_BEGIN,  R_START},                // R_CW_BEGIN
    {R_CW_NEXT,  R_CW_FINAL,  R_CW_FINAL,  R_START | DIR_CW},       // R_CW_FINAL
    {R_START,    R_CW_BEGIN,  R_CCW_BEGIN, R_START},                // R_START
    {R_CCW_NEXT, R_CCW_FINAL, R_CCW_BEGIN, R_START},                // R_CCW_NEXT
    {R_CCW_NEXT, R_CCW_FINAL, R_CCW_FINAL, R_START | DIR_CCW},      // R_CCW_FINAL
    {R_CCW_NEXT, R_CCW_BEGIN, R_CCW_BEGIN, R_START},                // R_CCW_BEGIN
    {R_START,    R_START,     R_START,     R_START}                 // ILLEGAL
};


using CallbackFunc = void(*)();

class RotaryEncoder
{
  protected:
    const byte DT_Pin, CLK_Pin, SW_Pin;
	unsigned int state;
	bool ClickDown;
	const CallbackFunc RotaryCallback;

  public:
    RotaryEncoder(const CallbackFunc RotaryCallback, const byte DT_Pin = 2, const byte CLK_Pin = 3, const byte SW_Pin = 4) : RotaryCallback(RotaryCallback), DT_Pin(DT_Pin), CLK_Pin(CLK_Pin), SW_Pin(SW_Pin)
    {
		pinMode(DT_Pin, INPUT);
		pinMode(CLK_Pin, INPUT);
		pinMode(SW_Pin, INPUT);
		attachInterrupt(digitalPinToInterrupt(DT_Pin), this->RotaryCallback, CHANGE);
		attachInterrupt(digitalPinToInterrupt(CLK_Pin), this->RotaryCallback, CHANGE);
    }

    void setup()
    {
		state = (digitalRead(DT_Pin) << 1) | digitalRead(CLK_Pin);
    }
	
	const unsigned int GetState()
	{		
		const unsigned char pinstate = (digitalRead(DT_Pin) << 1) | digitalRead(CLK_Pin);
		state = ttable[state & 0x07][pinstate];
		return state;
	}
	
	const bool GetButtonDown()
	{
		if (!digitalRead(SW_Pin))
		{
			if (ClickDown)
			  return false;
			ClickDown = true;
			return true;
		}
		else ClickDown = false;
		return false;
	}
};
#endif