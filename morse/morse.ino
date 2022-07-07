#define LED 12

#define SERIAL_SPEED 9600

#define DASH 2000
#define DOT 500

const char *letters[] = {
	".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
	".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
	"...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
};

const char *numbers[] = {
	"-----", ".----", "..---", "...--", "....-", ".....", "-....",
	"--...", "---..", "----."
};

void serialPrepare() {
	Serial.begin(SERIAL_SPEED);
	Serial.println("Welcome to Arduino morse code encoder");
}

void setup() {
	serialPrepare();
	pinMode(LED, OUTPUT);
}

void playSignal(int len) {
	digitalWrite(LED, HIGH);
	delay(len);
	digitalWrite(LED, LOW);
	delay(DOT);
}

void morse(const char *code) {
	Serial.println(code);
	unsigned int i = 0;
	while (code[i]) {
		int code_len = (code[i] == '.') ? DOT : DASH;
		playSignal(code_len);
		i++;
	}
}

void loop() {
	while (Serial.available()) {	
		char ch;
		ch = Serial.read();
		if ('A' <= ch && ch <= 'Z') { // capital letters
			morse(letters[ch - 'A']);
		}
		if ('a' <= ch && ch <= 'z') { // minuscule letters
			morse(letters[ch - 'a']);
		}
		if ('0' <= ch && ch <= '9') { // numbers
			morse(numbers[ch - '0']);
		}
		if (ch == ' ') {
			delay(DASH); // delay between words
		}
	}
}

