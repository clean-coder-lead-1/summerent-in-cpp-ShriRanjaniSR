#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  int lowerLimit = 0;
  int upperLimit = 35;
  if( coolingType == HI_ACTIVE_COOLING)
      upperLimit = 45;
  else if( coolingType == MED_ACTIVE_COOLING)
      upperLimit = 40;
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
  BreachType breachType = classifyTemperatureBreach( batteryChar.coolingType, temperatureInC);
  if(alertTarget == TO_CONTROLLER)
    sendToController(breachType);
  else if(alertTarget == TO_EMAIL)
    sendToEmail(breachType);
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  if(breachType == TOO_LOW)
    printf("To: %s\nHi, the temperature is too low\n",recepient);
  else if(breachType == TOO_HIGH)
    printf("To: %s\nHi, the temperature is too high\n",recepient);
}
