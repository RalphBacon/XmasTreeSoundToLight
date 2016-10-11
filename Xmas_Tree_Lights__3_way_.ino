/* 3-way Xmas Tree Lights for simple Xmas Tree Module (Banggood / Gearbest)
 *
 * We use (any) 3 PWM channels (pins 3, 5, 6, 9, 10, 11 on a Nano or Uno)
 * and can fade and flash the lights as required.
 *
 * Additionally, we can use a microphone input to flash the lights in time
 * with the 'beat'. Just like the discos of the 1980s.
 */
#include "Arduino.h"

// PWM pins to use for our 3 channels
char pwm[] = { 9, 10, 11 };

// pins for the microphone analog input
#define micAnalog A0

// Minimum LED on times, mS
#define flashOnMs 50

// An easy way to use human readable words rather than 0, 1, 2 etc as flags or states
enum mode {
	flash, fade
};

// -------------------------------------------------------------------------
// SETUP     SETUP     SETUP     SETUP     SETUP     SETUP     SETUP
// -------------------------------------------------------------------------
void setup() {
	Serial.begin(9600);

	Serial.println("Setup completed successfully.");
}

// -------------------------------------------------------------------------
// LOOP    LOOP    LOOP    LOOP    LOOP    LOOP    LOOP    LOOP    LOOP
// -------------------------------------------------------------------------
void loop() {
	// The fading value we're currently at (or starting from)
	static signed int fadeVal[] = { -100, 0, 255 };

	// Detects silence and starts the fade program
	static unsigned long silence;

	// How are we running?
	static mode runMode = flash;

	// Are we back in flash mode yet (sound detected for several cycles)?
	static int soundCount = 0;

	// Detect sound?
	if (runMode == flash) {

		// Flash mode
		for (unsigned int cnt = 0; cnt < sizeof pwm; cnt++) {
			if (micInput()) {
				flashChannel(cnt, true);

				// Make a note of when this was
				silence = millis();
			}
			else {
				flashChannel(cnt, false);

				// Have had silence for longer than minimum silent period? Switch runtime mode!
				if (millis() > silence + 1000) {
					runMode = fade;
					Serial.println("Switching to fade mode");
					break;
				}
			}
		}
	}
	else {
		// Fade mode
		for (unsigned int cnt = 0; cnt < sizeof pwm; cnt++) {
			fadeChannel(cnt, &fadeVal[cnt]);
		}

		// Check if sound is present, change runMode as required
		if (micInput()) {
			soundCount++;
			if (soundCount > 1) {
				runMode = flash;
				silence = millis();
				Serial.println("Switching to flash mode");
			}
		}else {
			soundCount = 0;
		}
	}
}

// -------------------------------------------------------------------------
// Fade the specified channel to next step.
// -------------------------------------------------------------------------
void fadeChannel(unsigned int channelNo, signed int *fadeVal) {

	// Prevents too fast a fading sequence
	static unsigned long fadeDelay[] { 15, 10, 20 }; // ms delay between each step
	static unsigned long fadeTime[] { 0, 0, 0 };

	// Don't do any fading on this channel if we have not exceeded wait time
	if (millis() > fadeTime[channelNo] + fadeDelay[channelNo]) {

		// Update the time we started this fade
		fadeTime[channelNo] = millis();

		// Get the actual value from the pointer
		signed int fade = *fadeVal;

		// Increment or decrement according to sign, speed up beyond certain brightness
		unsigned int absFade = abs(fade);
		if (absFade > 100) {
			fade = fade - 2;
		}
		else {
			fade--;
		}

		// Flip the sign bit (and hence direction) if at max or min
		if (fade > 255 || fade < -255) {
			fade = fade * -1;
			fade = fade < -255 ? -255 : fade > 255 ? 255 : fade;
		}

		// Change the LED brightness for this channel
		analogWrite(pwm[channelNo], absFade);

		// Update the value pointed to by the point *fadeVal
		*fadeVal = fade;
	}
}

// -------------------------------------------------------------------------
// Flash (sound-to-music style) the specified channel on or off
// -------------------------------------------------------------------------
void flashChannel(unsigned int channelNo, bool flashOn) {

	static unsigned long flashTime[] = { 0, 0, 0 };
	unsigned long milliTime = millis();
	if (flashOn) {
		analogWrite(pwm[channelNo], 255);
	}
	else {
		// Turn off but only if after minimum time period
		if (milliTime > flashTime[channelNo] + (flashOnMs * channelNo)) {

			// Don't turn fully off, leave a glimmer!
			analogWrite(pwm[channelNo], 2);
			flashTime[channelNo] = milliTime;
		}
	}
}

// -------------------------------------------------------------------------
// Gets microphone input, return true if sound detected
// -------------------------------------------------------------------------
bool micInput() {

	// Read the microphone input twice with a short delay
	int micVal1 = analogRead(micAnalog);
	delay(2);
	int micVal2 = abs(analogRead(micAnalog) - micVal1);

	// If we have detected sound above the threshold return true
	if (micVal2 > 2) {
		Serial.print(micVal1);Serial.print(" - ");Serial.println(micVal2);
		return true;
	}
	else {
		return false;
	}
}
