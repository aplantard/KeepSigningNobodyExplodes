
// Cable game
int cableWinningSetup[] = {0, 0, 0};
const int cablePins[] = {49,51,53};
const int cableGameWinningLedPin = 41;

// Combinaisons
const int cableTable[8][6] = {
  {0,0,0,0,1,1},
  {0,0,1,1,0,0},
  {0,1,0,1,0,1},
  {1,0,0,0,0,0},
  {0,1,1,0,1,0},
  {1,1,0,1,1,1},
  {1,1,1,1,1,0},
  {1,0,1,0,0,1}
};

// Last time cable configuration was not ok (losing config)
float lastTimeCablesNotOk = 0;
// Time needed to stay in the winning config to win
float cableGameTimeToWin = 100;

int wonCableGame = 0;
//
/*void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
  initCableGame();
}

void loop()
{
  updateCableGame();
  delay(10);
}*/

bool getWinCableGame()
{
  return wonCableGame;
}

void initCableGame()
{
  wonCableGame = 0;
  pinMode(cablePins[0], INPUT);
  pinMode(cablePins[1], INPUT);
  pinMode(cablePins[2], INPUT);
  pinMode(cableGameWinningLedPin,OUTPUT);
  cableInitWiningSetup();
}

void updateCableGame()
{
  if(!wonCableGame&&checkWinningCableGame() && millis()-lastTimeCablesNotOk>cableGameTimeToWin)
  {
     wonCableGame = 1;
  }
  if(wonCableGame)
  {
    drawCableGameWinningFeedback();
  }
}

bool checkWinningCableGame()
{
      for(int i=0;i<3;i++)
      {
        int cableRead = digitalRead(cablePins[i]);
        if (cableRead != cableWinningSetup[i])
        {
          lastTimeCablesNotOk = millis();
          return false;
        }
      }
  return true;
}
void cableInitWiningSetup()
{
  for(int i = 0;i<8;i++)
  {
    if(digitalRead(cablePins[0])==cableTable[i][0] && digitalRead(cablePins[1])==cableTable[i][1] && digitalRead(cablePins[2])==cableTable[i][2])
    {
      cableWinningSetup[0] = cableTable[i][3];
      cableWinningSetup[1] = cableTable[i][4];
      cableWinningSetup[2] = cableTable[i][5];
      return;
    }
  }
}
void drawCableGameWinningFeedback()
{
  digitalWrite(cableGameWinningLedPin,HIGH);
}
