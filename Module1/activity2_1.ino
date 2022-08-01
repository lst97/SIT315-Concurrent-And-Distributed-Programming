
// Set the PIN number
const uint8_t BTN_PIN = 2;
const uint8_t LED_PIN = 13;

//Init button and led state.
uint8_t buttonPrevState = LOW;
uint8_t ledState = LOW;

// Setup
void setup()
{
  // Init pin input for btn
  pinMode(BTN_PIN, INPUT_PULLUP);
  // Init pin output for led
  pinMode(LED_PIN, OUTPUT);
  // Start serial monitor channel
  Serial.begin(9600);
}

void loop()
{
  // read if the btn press
  uint8_t buttonState = digitalRead(BTN_PIN);
  
  // print status
  Serial.print(buttonState);
  Serial.print(buttonPrevState);
  Serial.print(ledState);
  Serial.println("");
  
  
  // if the state change
  if(buttonState != buttonPrevState)
  {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }
  
  buttonPrevState = buttonState;
    
  // sleep for 0.5 second
  delay(500);
}
