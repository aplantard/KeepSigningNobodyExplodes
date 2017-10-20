// 3 buttons game
const int initialSetup[] = {0, 0, 0};
int winningSetup[] = {0, 0, 0};

// Combinaisons
const int buttonTable[8][6] = {
  {1,0,1,1,1,0},
  {1,1,1,0,0,1},
  {0,0,0,1,0,0},
  {1,1,0,0,0,1},
  {1,0,0,0,1,0},
  {0,1,0,0,1,1},
  {0,1,1,1,1,1},
  {0,0,1,1,0,1}
};

const int buttonPins[] = {A2,A3,A4};
const int ledPins[] = {11,10,9};

const int buttonGameWinningLed = 39;

int buttons[] = {0,0,0};

int previousButtonRead[] = {0,0,0};

int wonButtonGame = 0;
//
/*void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
  initButtonGame("XXX");
}

void loop()
{
  updateButtonGame();
  delay(10);
}*/
bool getWinButtonGame()
{
  return wonButtonGame;
}

void initButtonGame(String code)
{
  // Init with serial
  int serial[] = {0,0,0};
  for(int i =0;i<3;i++)
  {
      if(code[i]=='X')
      {
        serial[i]=1;
      }
  }
  for(int i = 0;i<8;i++)
  {
    if(serial[0]==buttonTable[i][0] && serial[1]==buttonTable[i][1] && serial[2]==buttonTable[i][2])
    {
      winningSetup[0] = buttonTable[i][3];
      winningSetup[1] = buttonTable[i][4];
      winningSetup[2] = buttonTable[i][5];
      return;
    }
  }
  //
  wonButtonGame = 0;
  pinMode(buttonPins[0], INPUT);
  pinMode(buttonPins[1], INPUT);
  pinMode(buttonPins[2], INPUT);
  pinMode(ledPins[0], OUTPUT);
  pinMode(ledPins[1], OUTPUT);
  pinMode(ledPins[2], OUTPUT);

  pinMode(buttonGameWinningLed,OUTPUT);
  
  buttons[0] = initialSetup[0];
  buttons[1] = initialSetup[1];
  buttons[2] = initialSetup[2];
}

void updateButtonGame()
{
  if(!wonButtonGame)
  {
      for(int i=0;i<3;i++)
      {
        int buttonRead = digitalRead(buttonPins[i]);
        if (buttonRead && !previousButtonRead[i]) {
          buttons[i] = !buttons[i];
        }

        digitalWrite(ledPins[i], buttons[i]);
        previousButtonRead[i] = buttonRead;
      }
  }
  if(!wonButtonGame&&checkWinningButtonGame())
  {
     wonButtonGame = 1;
  }
  if(wonButtonGame)
  {
    drawButtonGameWinningFeedback();
  }
}

bool checkWinningButtonGame()
{
  for(int i =0;i<3;i++)
  {
   if(buttons[i]!=winningSetup[i])
     return false;
  }
  return true;
}

void drawButtonGameWinningFeedback()
{
 for(int i = 0;i<3;i++)
 {
   digitalWrite(ledPins[i],millis()%2000>1000);
 }
 pinMode(buttonGameWinningLed,OUTPUT);
 digitalWrite(buttonGameWinningLed,HIGH);
}
