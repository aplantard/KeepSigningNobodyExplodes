#include "TinkerKit.h"

TKPotentiometer pot(I0);
TKPotentiometer pot2(I1);

const int Pot_Led = 43;

const int Pot_k = 7;
const int Pot_j = 3;
const int Pot_i = 2;

int Pot_NbValue = 4;

bool Pot_FirstLoop = true;

int Pot_InitialPot1;
int Pot_InitialPot2;

bool Pot_winBool = false;

bool Pot_getWinBool(){
  return Pot_winBool;
}

void Pot_init() {
  // put your setup code here, to run once:
  pinMode(Pot_Led, OUTPUT);
  //Serial.begin(9600);
  Pot_InitialPot1 = Pot_readStep(pot.read(),Pot_NbValue);
  Pot_InitialPot2 = Pot_readStep(pot2.read(),Pot_NbValue);
}

void Pot_update() {
  // put your main code here, to run repeatedly:
  if((((((Pot_InitialPot2+Pot_j)%Pot_NbValue)*Pot_NbValue+((Pot_InitialPot1+Pot_i)%Pot_NbValue))+Pot_k)%(int)(pow(Pot_NbValue,2)))==((Pot_readStep(pot2.read(),Pot_NbValue)*Pot_NbValue+Pot_readStep(pot.read(),Pot_NbValue)))%(int)(pow(Pot_NbValue,2))){
    digitalWrite(Pot_Led, HIGH);
    Pot_winBool = true;
  }
  else{
    digitalWrite(Pot_Led, LOW);
    Pot_winBool = false;
  }  
}

int Pot_readStep(int potValue, int steps){
  int pas = 1024/steps;
  for(int i=1;i<=steps;i++){
    if(potValue<=i*pas){
      return i;
    }
  }
}

