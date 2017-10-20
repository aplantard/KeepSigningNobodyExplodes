#include <LiquidCrystal.h>

float LCD_timerInit = 600; //in second

LiquidCrystal LCD_ecran(32,30,28,26,24,22);
int LCD_currentCursorPosition = 15;

boolean LCD_echecBool = false;
boolean LCD_winBool = false;

float LCD_seconds = 0;

static unsigned long LCD_lastTick = 0;

String LCD_serialNumber = "";

/*void setup() {
  LCD_init();
}

void loop() {
  LCD_update();
}*/

void LCD_init(){
    
   LCD_ecran.begin(16,2);
   LCD_ecran.clear();

   LCD_ecran.setCursor(0, 0);
   for (int i = 0; i <= 16; i++){
       LCD_ecran.print(char(255));
   }

   LCD_seconds = 0;
   LCD_lastTick = 0;
   LCD_currentCursorPosition = 15;
   LCD_echecBool = false;

   LCD_serialNumber = LCD_GenerateSerialNumber();
   LCD_ecran.setCursor(6, 1);
   LCD_ecran.print(LCD_serialNumber);

}

void LCD_update(){

  if (!LCD_echecBool && !LCD_winBool &&(millis() - LCD_lastTick >= 1000)) {

      LCD_lastTick = millis();
      LCD_seconds++;

      int barToUnfill = LCD_timerBarToUnfill();
      for(int i = 0; i < barToUnfill; i++){
         LCD_ecran.setCursor(LCD_currentCursorPosition, 0);
         LCD_ecran.print(" ");
         LCD_currentCursorPosition --;
      }

      if(LCD_currentCursorPosition == -1){
        LCD_echecScreen();
      }
  }
}

bool LDC_getEchecBool(){
  return LCD_echecBool;
}
bool LDC_getWinBool(){
  return LCD_winBool;
}

int LCD_timerBarToUnfill(){
  
   float percentageComplete = (LCD_seconds / LCD_timerInit);  //  Pourcentage de completion du timer (entre 0 et 1)
   float percentageComplete16 = 0 + (percentageComplete - 0) * (16 - 0) / (1 - 0);   // Remap du pourcentage entre 0 et 15

   int inverseComplete = 16 - int(percentageComplete16);

   int totalUnfill = (LCD_currentCursorPosition + 1) - inverseComplete;

   return totalUnfill; 
}

String LCD_GenerateSerialNumber(){
  
   String result = "";

   for (int i=0; i< 3; i++){

      randomSeed(analogRead(A13+i));

      int randNumber = random(2);
      if(randNumber == 0){
          result += "O";
      }
      else{
          result += "X";
      }
   }
  
   return result;
}

String LCD_getSerial()
{
  return LCD_serialNumber;
}

void LCD_echecScreen() {
    LCD_ecran.clear();
  
    LCD_echecBool = true;
  
    LCD_ecran.setCursor(5, 0);
    LCD_ecran.print("X");
    LCD_ecran.setCursor(10, 0);
    LCD_ecran.print("X");
    
    LCD_ecran.setCursor(3, 1);
    LCD_ecran.print("|");
    LCD_ecran.setCursor(4, 1);
    LCD_ecran.print("-");
    LCD_ecran.setCursor(5, 1);
    LCD_ecran.print("-");
    LCD_ecran.setCursor(5, 1);
    LCD_ecran.print("-");
    LCD_ecran.setCursor(6, 1);
    LCD_ecran.print("-");
    LCD_ecran.setCursor(7, 1);
    LCD_ecran.print("-");
    LCD_ecran.setCursor(8, 1);
    LCD_ecran.print("-");
    LCD_ecran.setCursor(9, 1);
    LCD_ecran.print("-");  
    LCD_ecran.setCursor(10, 1);
    LCD_ecran.print("-");
    LCD_ecran.setCursor(11, 1);
    LCD_ecran.print("-");
    LCD_ecran.setCursor(12, 1);
    LCD_ecran.print("|");
}

void LCD_winScreen() {
    LCD_ecran.clear();

    LCD_winBool = true;
    
    LCD_ecran.setCursor(5, 0);
    LCD_ecran.print("^");
    LCD_ecran.setCursor(10, 0);
    LCD_ecran.print("^");
    
    LCD_ecran.setCursor(3, 1);
    LCD_ecran.print("|");
    LCD_ecran.setCursor(4, 1);
    LCD_ecran.print("_");
    LCD_ecran.setCursor(5, 1);
    LCD_ecran.print("_");
    LCD_ecran.setCursor(5, 1);
    LCD_ecran.print("_");
    LCD_ecran.setCursor(6, 1);
    LCD_ecran.print("_");
    LCD_ecran.setCursor(7, 1);
    LCD_ecran.print("_");
    LCD_ecran.setCursor(8, 1);
    LCD_ecran.print("_");
    LCD_ecran.setCursor(9, 1);
    LCD_ecran.print("_");  
    LCD_ecran.setCursor(10, 1);
    LCD_ecran.print("_");
    LCD_ecran.setCursor(11, 1);
    LCD_ecran.print("_");
    LCD_ecran.setCursor(12, 1);
    LCD_ecran.print("|");
}
