#include <LiquidCrystal.h>

LiquidCrystal ecran(12,11,5,4,3,2);
int i = 100;

void setup() {
  // put your setup code here, to run once:
  ecran.begin(16,2);
  ecran.clear();
  ecran.print(i,DEC);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(millis()%1000 == 0){
    i--;
     ecran.clear();
    ecran.print(i,DEC);
  }

}
