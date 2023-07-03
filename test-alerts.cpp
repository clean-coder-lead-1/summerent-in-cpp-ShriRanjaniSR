#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits - Too Low") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
}

TEST_CASE("infers the breach according to limits - Normal") {
  REQUIRE(inferBreach(12, 12, 30) == NORMAL);
}

TEST_CASE("infers the breach according to limits - Too High") {
  REQUIRE(inferBreach(12, 0, 10) == TOO_HIGH);
}

TEST_CASE("classify temperature breach according to limits - High Active - Too Low") {
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, -1) == TOO_LOW);
}

TEST_CASE("classify temperature breach according to limits - High Active - Normal") {
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 30) == NORMAL);
}

TEST_CASE("classify temperature breach according to limits - High Active - Too High") {
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 50) == TOO_HIGH);
}

TEST_CASE("classify temperature breach according to limits - Medium Active - Too Low") {
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -1) == TOO_LOW);
}

TEST_CASE("classify temperature breach according to limits - Medium Active - Normal") {
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 30) == NORMAL);
}

TEST_CASE("classify temperature breach according to limits - Medium Active - Too High") {
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 45) == TOO_HIGH);
}

TEST_CASE("classify temperature breach according to limits - Passive - Too Low") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -1) == TOO_LOW);
}

TEST_CASE("classify temperature breach according to limits - Passive - Normal") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 30) == NORMAL);
}

TEST_CASE("classify temperature breach according to limits - Passive - Too High") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 45) == TOO_HIGH);
}

TEST_CASE("checkAndAlert Controller") {
  BatteryCharacter batteryChar{PASSIVE_COOLING,"BrandA"};
  checkAndAlert(TO_CONTROLLER, batteryChar, 50);
}

TEST_CASE("checkAndAlert Email - Too Low") {
  BatteryCharacter batteryChar{PASSIVE_COOLING,"BrandB"};
  checkAndAlert(TO_EMAIL, batteryChar, -5);
}

TEST_CASE("checkAndAlert Email - Too High") {
  BatteryCharacter batteryChar{PASSIVE_COOLING,"BrandC"};
  checkAndAlert(TO_EMAIL, batteryChar, 40);
}

TEST_CASE("checkAndAlert Email - Normal") {
  BatteryCharacter batteryChar{PASSIVE_COOLING,"BrandD"};
  checkAndAlert(TO_EMAIL, batteryChar, 20);
}
