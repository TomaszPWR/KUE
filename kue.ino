// Pin connections for 7-segment display
const int digitPins[] = {2, 3, 4, 5};   // Common digit pins (anode)
const int segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};   // Segment pins (cathode)

// Define initial time values
int hours = 0;
int minutes = 0;

// Button pins
const int button1Pin = A0;
const int button2Pin = A1;
const int button3Pin = A2;

// Button state variables
int button1State = HIGH;
int button2State = HIGH;
int button3State = HIGH;
int lastButton1State = HIGH;
int lastButton2State = HIGH;
int lastButton3State = HIGH;

void setup() {
  // Set digit pins as outputs
  for (int i = 0; i < sizeof(digitPins) / sizeof(digitPins[0]); i++) {
    pinMode(digitPins[i], OUTPUT);
  }

  // Set segment pins as outputs
  for (int i = 0; i < sizeof(segmentPins) / sizeof(segmentPins[0]); i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  // Set button pins as inputs with internal pull-up resistors
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);
}

void loop() {
  // Read the button states
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  button3State = digitalRead(button3Pin);

  // Check if button 1 is pressed
  if (button1State != lastButton1State) {
    if (button1State == LOW) {
      // Increment the hours
      hours++;
      if (hours > 99) {
        hours = 0;
      }
    }
    delay(50);  // Debounce delay
  }

  // Check if button 2 is pressed
  if (button2State != lastButton2State) {
    if (button2State == LOW) {
      // Increment the minutes
      minutes++;
      if (minutes > 59) {
        minutes = 0;
      }
    }
    delay(50);  // Debounce delay
  }

  // Check if button 3 is pressed
  if (button3State != lastButton3State) {
    if (button3State == LOW) {
      // Reset the time to 00:00
      hours = 0;
      minutes = 0;
    }
    delay(50);  // Debounce delay
  }

  // Update the display
  displayTime(hours, minutes);

  // Save the current button states
  lastButton1State = button1State;
  lastButton2State = button2State;
  lastButton3State = button3State;
}

// Function to display the time on the 4-digit 7-segment display
void displayTime(int hours, int minutes) {
  // Extract the digits
  int digit1 = hours / 10;
  int digit2 = hours % 10;
  int digit3 = minutes / 10;
  int digit4 = minutes % 10;

  // Set the digit patterns
  byte digitPatterns[] = {
    getDigitPattern(digit1),
    getDigitPattern(digit2),
    getDigitPattern(digit3),
    getDigitPattern(digit4)
  };

  // Display the digits
  for (int digit = 0; digit < sizeof(digitPins) / sizeof(digitPins[0]); digit++) {
    displayDigit(digit, digitPatterns[digit]);
  }
}

// Function to get the binary pattern for a digit
byte getDigitPattern(int digit) {
  const byte digitPatterns[] = {
    B11111100,   // Binary pattern for digit 0
    B01100000,   // Binary pattern for digit 1
    B11011010,   // Binary pattern for digit 2
    B11110010,   // Binary pattern for digit 3
    B01100110,   // Binary pattern for digit 4
    B10110110,   // Binary pattern for digit 5
    B10111110,   // Binary pattern for digit 6
    B11100000,   // Binary pattern for digit 7
    B11111110,   // Binary pattern for digit 8
    B11110110    // Binary pattern for digit 9
  };

  if (digit >= 0 && digit <= 9) {
    return digitPatterns[digit];
  }

  return 0;  // Return 0 pattern for invalid digits
}

// Function to display a digit on a specific digit position
void displayDigit(int digit, byte pattern) {
  // Turn off all digit pins
  for (int i = 0; i < sizeof(digitPins) / sizeof(digitPins[0]); i++) {
    digitalWrite(digitPins[i], HIGH);
  }

  // Set the segment pattern for the current digit
  for (int i = 0; i < 8; i++) {
    digitalWrite(segmentPins[i], bitRead(pattern, i));
  }

  // Enable the current digit
  digitalWrite(digitPins[digit], LOW);

  // Delay to hold the digit for a short period of time
  delay(5);
}
