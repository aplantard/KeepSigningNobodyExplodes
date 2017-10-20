void setup() {

  Serial.begin(9600);

  LCD_init();
  Pot_init();
  initButtonGame(LCD_getSerial());
  initCableGame();
}

void loop() {
  LCD_update();

  if(!LDC_getEchecBool() && !LDC_getWinBool())
  {
     // Ajouter ici les fonctions update des modules
     Pot_update();
     updateButtonGame();
     updateCableGame();

     if(getWinButtonGame() && Pot_getWinBool() && getWinCableGame() )
     {
       LCD_winScreen();
     }
  }
}
