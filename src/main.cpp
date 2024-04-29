#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "floodfill.h"
#include "maze.h"
#include "queue.h"

void setup() {
    Serial.begin(BAUDRATE);

    Serial.println(F("MOTORLAB 1.0"));
}

void loop() {
}
