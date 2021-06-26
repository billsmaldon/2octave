int clockPin = 2;
int dataPin = 3;
int messageReady = 4;

unsigned char midiMessage[3];

#define note_on  0x90
#define note_off 0x80
#define control_change 0xB0
#define program_change 0xC0
#define pitch_bend 0xE0

unsigned char midi_command = 0;

unsigned char note = 64;
unsigned char velocity = 127;
unsigned char channel = 0;
unsigned char programNumber = 0;
unsigned char controlNumber = 0;
unsigned char controlValue = 0;
signed int pitchBend = 0; //must convert 2 bytes to a signed int!

unsigned char LSB = 0;  //LSB of pitch bend
unsigned char MSB = 0;  //MSB of pitch bend

void setup() {
  pinMode(clockPin,INPUT);
  pinMode(dataPin,INPUT);
  pinMode(messageReady,INPUT);
  Serial.begin(57600);
}

void loop() {

  midiMessage[0] = 0;
  midiMessage[1] = 0;
  midiMessage[2] = 0;
  
  //read 3 bytes
  while(digitalRead(messageReady)==0) {;} //wait for messageReady = 1
  
    for(unsigned char i=0;i<3;i++) { //iterate over 3 bytes

        for(unsigned char ii=0;ii<8;ii++) { //iterate over 8 bits
          
          while (digitalRead(clockPin) == 0) {;} //wait for HIGH clock
          midiMessage[i] |= (digitalRead(dataPin) << ii); //LSB first
          while (digitalRead(clockPin) == 1) {;} //wait fow LOW clock
          
        }
        
    }

  while(digitalRead(messageReady)==1) {;} //wait for messageReady = 0

  //serial monitor test prints
  //Serial.println("Hello World");
  //Serial.println(2048, DEC);
  //Serial.println(1024, DEC);
  //Serial.println(midiMessage[0], BIN);
  //Serial.println(midiMessage[1], DEC);
  //Serial.println(midiMessage[2], DEC);

  //bitmask midi channel and command
  channel = (midiMessage[0] & 0x0F) + 1;
  midi_command = midiMessage[0] & 0xF0; 

  //usbMIDI.send_now();
  
   //decode command
  switch (midi_command) {
    case note_off:
      note = midiMessage[1];
      velocity = midiMessage[2];
      usbMIDI.sendNoteOff(note, 0, channel);
      break;
    case note_on:
      note = midiMessage[1];
      velocity = midiMessage[2];
      usbMIDI.sendNoteOn(note, velocity, channel);
      break;
    case control_change:
      controlNumber = midiMessage[1];
      controlValue = midiMessage[2];
      usbMIDI.sendControlChange(controlNumber, controlValue, channel);
      break;
    case program_change:
      programNumber = midiMessage[1];
      usbMIDI.sendProgramChange(programNumber, channel);
      break;
    case pitch_bend:
      //convert 2 bytes to an int here!
      LSB = midiMessage[1];
      MSB = midiMessage[2];
      pitchBend = (MSB << 7) - 8192;
      Serial.println(pitchBend, DEC);
      usbMIDI.sendPitchBend(pitchBend, channel);
      break;
    default:
      break; 
  }
  
  
  while (usbMIDI.read()) {
    // ignore incoming messages
  }
  
}
