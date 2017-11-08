#include <LiquidCrystal_I2C.h>

#define NOTE_DS8 4978

extern volatile unsigned long timer0_overflow_count;
int pushButton = 4;
int counter = 0;

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  Serial.begin(9600);
  pinMode(pushButton, INPUT);

}

void loop() {
  int buttonState = digitalRead(pushButton);
  if (buttonState) {
    randomNegMssg();
    resetCurrentTime();
    timer();
  } else {
    randomPosMssg();
    delay(5000);
    displayCurrentTime();
    delay(3000);
  }
  delay(1000);
}

void resetCurrentTime () {
  //dit reset de timer
  timer0_overflow_count = 0;
}

void displayCurrentTime () {
  // deze functie zorgt ervoor dat je de tijd ziet waarvan je hebt gezeten
  lcd.clear();
  lcd.print(( timer0_overflow_count)/60000);
  lcd.print(" minuten still gezeten");
}

void randomPosMssg() 
{
  //deze functie zorgt voor een willekeurig positief bericht
  int randomNum = random(4);
  if ( randomNum == 3)
  {
    lcd.clear();
    lcd.println("Goed zo!");
  }
    else if (randomNum == 2)
  { 
    lcd.clear();
    lcd.println("Lekker pik!");
  }
    else
  {
    lcd.clear();
    lcd.println("Zitte blijve!");
    }
}

void randomNegMssg()
// deze functie zorgt voor een willekeurig negatief bericht
{
  int randomNum = random(4);
    if ( randomNum  == 3)
  {
    lcd.clear();
    lcd.println("Stop maar!");
  }
    else if (randomNum  == 2)
    { 
    lcd.clear();  
    lcd.println("Zit!");
    }
    else
  {
    lcd.clear();
    lcd.println("Kap is joh!");
    }
  
}

void timer() {
 //deze functie zorgt ervoor dat de melodie na 10 seconden gaat afspelen
  int buttonState = digitalRead(pushButton);
  Serial.println("test");
    if (buttonState) 
 {
      delay(1000);
      counter++;
      Serial.println(counter);
  } 
    else 
  {
      
  }
  
  if (counter == 10) 
  {
    playNegativeMelody ();
  }

}

void playNegativeMelody () {
  // deze functie zorgt voor het negatieve geluidje
  int melody[] = { NOTE_DS8, NOTE_DS8, NOTE_DS8, NOTE_DS8 };

  int noteDurations[] = { 1, 1, 1, 1};
  
  for (int thisNote = 0; thisNote < 4; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(8);
  }
}




