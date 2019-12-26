//Learned Bluetooth connection process from https://exploreembedded.com/wiki/Setting_up_Bluetooth_HC-05_with_Arduino

#include <SoftwareSerial.h>
SoftwareSerial EEBlue(8, 12); //RX | TX

int rotes_lichts_stift = 11;
int grunes_lichts_stift = 10;
int blaues_lichts_stift = 9;

int index = 0;
char color_sequence[9];

void setup() {
	pinMode(rotes_lichts_stift, OUTPUT);
	pinMode(blaues_lichts_stift, OUTPUT);
	pinMode(grunes_lichts_stift, OUTPUT);

	Serial.begin(9600);
	EEBlue.begin(9600);
	Serial.println("The bluetooth gates are open.");
}

void loop() {
	//Wenn es Daten von bluetooth gibt
	if (EEBlue.available()) {
		Serial.println(index % 9);
		color_sequence[index++ % 9] = EEBlue.read();
		if (index % 9 == 0) {

			String rot_sequence_string = "";
			for (int i = 0; i < 3; i++)
				rot_sequence_string += color_sequence[i];

			String grun_sequence_string = "";
			for (int i = 3; i < 6; i++)
				grun_sequence_string += color_sequence[i];

			String blau_sequence_string = "";
			for (int i = 6; i < 9; i++)
				blau_sequence_string += color_sequence[i];
				
			int rot_sequence = rot_sequence_string.toInt();
			int grun_sequence = grun_sequence_string.toInt();
			int blau_sequence = blau_sequence_string.toInt();

			rgb_color(rot_sequence, grun_sequence, blau_sequence);
//			for (int i = 0; i < 9; i++) {
//				Serial.print(color_sequence[i]);
//			}
			
			Serial.println(rot_sequence_string);
		}
	}

	//Wenn es Daten von den Terminal gibt
	if (Serial.available()) {
		EEBlue.write(Serial.read());
	}
	
//	rgb_color(255, 0, 0);
//	delay(1000);
//	rgb_color(0, 255, 0);
//	delay(1000);
//	rgb_color(0, 0, 255);
//	delay(1000);
}

void rgb_color(int rot, int grun, int blau) {
	analogWrite(rotes_lichts_stift, rot);
	analogWrite(grunes_lichts_stift, grun);
	analogWrite(blaues_lichts_stift, blau);
//	Serial.print("Red: ");
//	Serial.print(rot);
//	Serial.print(", Green: ");
//	Serial.print(grun);
//	Serial.print(", Blau: ");
//	Serial.println(blau);
}
