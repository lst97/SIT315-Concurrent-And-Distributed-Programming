
// Set the PIN number
const uint8_t BTN_PIN = 2;
const uint8_t LED_PIN = 13;

//Init button and led state.
uint8_t buttonPrevState = LOW;
uint8_t ledState = LOW;

// Setup
void setup()
{
  // set pinmode for btn
  pinMode(BTN_PIN, INPUT_PULLUP);
  // set pinmod for led
  pinMode(LED_PIN, OUTPUT);
  // start the serial monitor.
  Serial.begin(9600);
  
  attachInterrupt(0, pin_ISR, CHANGE);
}

void loop()
{

}

void pin_ISR(){
  // read led status
  uint8_t buttonState = digitalRead(BTN_PIN);
  
  // print the led and button status to the serial monitor.
  Serial.print(buttonState);
  Serial.print(buttonPrevState);
  Serial.print(ledState);
  Serial.println("");
  
  
  // logic
  if(buttonState != buttonPrevState)
  {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }
  
  buttonPrevState = buttonState;
    
  // Light for 0.5 sec
  delay(500);
}