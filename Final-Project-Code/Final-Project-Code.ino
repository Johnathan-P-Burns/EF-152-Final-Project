//Initialize global variables


void setup() {
  Serial.begin(9600); //DEBUG SERIAL for computer
  Serial1.beign(9600); //Fingerprint sensor serial
}

void loop() {
  Serial.println("DEBUG SERIAL");
  delay(1000);
}

//Function to check if the fingerprint of the user matches the hard-coded trusted ones
bool checkFingerprint() {
  
}

