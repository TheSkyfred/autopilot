//THIS FILE IS FOR THE LED & BUZZER

#include <ToneESP32.h>
#include "def.h"

ToneESP32 buzzer(BUZZER_PIN, BUZZER_CHANNEL);

void tonetest() {
  buzzer.tone(NOTE_C4, 250);
  buzzer.tone(NOTE_D4, 250);
  buzzer.tone(NOTE_E4, 250);
  buzzer.tone(NOTE_F4, 250);
  buzzer.tone(NOTE_G4, 250);
  buzzer.tone(NOTE_A4, 250);
  buzzer.tone(NOTE_B4, 250);
  buzzer.tone(NOTE_C5, 250);
  delay(250);
  buzzer.tone(NOTE_C5, 250);
  buzzer.tone(NOTE_B4, 250);
  buzzer.tone(NOTE_A4, 250);
  buzzer.tone(NOTE_G4, 250);
  buzzer.tone(NOTE_F4, 250);
  buzzer.tone(NOTE_E4, 250);
  buzzer.tone(NOTE_D4, 250);
  buzzer.tone(NOTE_C4, 250);
  buzzer.noTone();
}