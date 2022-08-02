// C++ code
//

const byte LED_PIN = 13;
const byte METER_PIN = A4;

/* Example code with timer intyerrutp that will create an interruption each 
 *  500ms using timer1 and prescalar of 256.
Calculations (for 500ms): 
  System clock 16 Mhz and Prescalar 256;
  Timer 1 speed = 16Mhz/256 = 62.5 Khz    
  Pulse time = 0.5/62.5 Khz =  8us  
  Count up to = 500ms / 8us = 62500 (so this is the value the OCR register should have)*/  


double MAX_FREQ = 2.0;
double TIMER_FREQ_SEC = 0;
double previousPotemtiometerValue = 0;

void setFreqFromPotentiometer(double value){
  TIMER_FREQ_SEC = value * 0.001953125;
}

double getValueFromPotentiometer(){
  return analogRead(METER_PIN);
}
void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(METER_PIN, INPUT);
      
  Serial.begin(9600);
  
  startTimer(TIMER_FREQ_SEC);
}

void loop()
{
  double value = getValueFromPotentiometer() + 1;
  if (value != previousPotemtiometerValue){
    Serial.print("Potemtionmeter Changed!\n");
    setFreqFromPotentiometer(value);
    startTimer(TIMER_FREQ_SEC);
    previousPotemtiometerValue = value;
  }
}

int calcFrequency(double second){
  double sysClock = 16.0;
  double prescalar = 256.0;
  double timer1Speed = (sysClock / prescalar) * 1000;
  double pulseTime = ((1.0 / second) / timer1Speed) * 1000;
  return (500.0 / pulseTime) * 1000;
}

void startTimer(double second){
  noInterrupts();
  // using Timer1
  TCCR1A = 0;			//Reset entire TCCR1A register
  TCCR1B = 0;			//Reset entire TCCR1B register
  TCCR1B |= B00000100;		//Set CS12 to 1 so we get Prescalar = 256
  TIMSK1 |= B00000010;        //Set OCIE1A to 1 so we enable compare match A
  
  OCR1A = calcFrequency(second);
  Serial.print("Set Timer\n");
  interrupts();
}


ISR(TIMER1_COMPA_vect){
  TCNT1  = 0;                  //First, set the timer back to 0 so it resets for next interrupt
  Serial.print("Interrupt\n"); 
  digitalWrite(LED_PIN, digitalRead(LED_PIN) ^ 1);
}

