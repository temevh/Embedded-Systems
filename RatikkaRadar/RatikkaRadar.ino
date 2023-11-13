#include <LiquidCrystal.h>


const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int buttonPin = 7;

int buttonState = 0;
int lastButtonState = LOW;

unsigned long previousMillis = 0;
const long interval = 1000;  

static int seconds = 0;
static int minutes = 0;
static int hours = 12;
static int day = 0; // 0 represents Monday, 1 for Tuesday, and so on

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  lcd.begin(16, 2); // Initializing the LCD with 16 columns and 2 rows
}

void displayTime(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis;
  
 

   seconds = (seconds + 1) % 60;
  if (seconds == 0) {
    minutes = (minutes + 1) % 60;
    if (minutes == 0) {
      hours = (hours + 1) % 24;
      if (hours == 0) {
        day = (day + 1) % 7; // Update day, 7 days in a week
      }
    }
  }

  lcd.setCursor(0, 0);
  switch (day) {
    case 0:
      lcd.print("Ma ");
      break;
    case 1:
      lcd.print("Ti ");
      break;
    case 2:
      lcd.print("Ke ");
      break;
    case 3:
      lcd.print("To ");
      break;
    case 4:
      lcd.print("Pe ");
      break;
    case 5:
      lcd.print("La ");
      break;
    case 6:
      lcd.print("Su ");
      break;
  }

  if (hours < 10) {
    lcd.print("0");
  }
  lcd.print(hours);
  lcd.print(":");
  if (minutes < 10) {
    lcd.print("0");
  }
  lcd.print(minutes);
  lcd.print(":");
  if (seconds < 10) {
    lcd.print("0");
  }
  lcd.print(seconds);

  }
}

void showHervanta(){

  if (day >= 0 && day <= 4 ){
      int currentTimeInMinutes = hours * 60 + minutes;

    // Time of the first tram (5:26 in the morning)
    int firstTramTime = 5 * 60 + 26;  // Convert to minutes from midnight

    // Calculate the time difference between current time and the first tram
    int timeDifference = currentTimeInMinutes - firstTramTime;

    // Calculate time until the next tram
    int timeUntilNextTram = 7 - (timeDifference % 7);

    // Print time until the next tram

    Serial.print("Time until next tram: ");
    Serial.print(timeUntilNextTram);
    Serial.println(" minutes");

    lcd.setCursor(0, 0);
    lcd.print("Keskusta: ");
    lcd.print(timeUntilNextTram-2);
    lcd.print(" min");
    lcd.setCursor(0, 1);
    lcd.print("Hervanta: ");
    lcd.print(timeUntilNextTram);
    lcd.print(" min");
    delay(3000);

    lcd.setCursor(0, 1);
    lcd.print("                 ");
    lcd.setCursor(0, 0);
    lcd.print("                 "); 
    return;

  }else{
    Serial.println("LaSu");
  }
  
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH && lastButtonState == LOW) {
    showHervanta();
  }

  lastButtonState = buttonState;
  displayTime();

}
