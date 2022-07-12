int DS_Pin=48;
int SHCP_Pin=44;
int STCP_Pin=46;
const int Reed_PinH = 39;
const int Reed_PinL = 37;
const int PushButton_U = 52;
const int PushButton_D = 50;
const int sv_a = 38;
const int sv_b = 36;
const int clutchSwitch = 53;
int counter = 0;
int Reed_HIGH;
int Reed_LOW;
int upshift;
int downshift;
int clutch;

int digits [6][8]{
{0,0,1,1,0,0,0,0}, //digit 1
{0,1,1,0,1,1,0,1}, //digit 2
{0,1,1,1,1,0,0,1}, //digit 3
{0,0,1,1,0,0,1,1}, //digit 4
{0,1,0,1,1,0,1,1}, //digit 5
{0,1,0,1,1,1,1,1}, //digit 6
};

void setup() {
 pinMode(DS_Pin, OUTPUT);
 pinMode(STCP_Pin, OUTPUT);
 pinMode(SHCP_Pin, OUTPUT);
 pinMode(Reed_PinH, INPUT);
 pinMode(Reed_PinL, INPUT);
 pinMode(PushButton_D, INPUT);
 pinMode(PushButton_U, INPUT);
 pinMode(clutchSwitch, INPUT);
 pinMode(sv_a, OUTPUT);
 pinMode(sv_b, OUTPUT);
}
void DisplayDigit(int Digit){
  digitalWrite(STCP_Pin, LOW);
  for(int i=7; i>=0; i--){
    digitalWrite(SHCP_Pin, LOW);
    if (digits[Digit][i]==1)digitalWrite(DS_Pin, LOW);
    if (digits[Digit][i]==0)digitalWrite(DS_Pin, HIGH);
    digitalWrite(SHCP_Pin, HIGH);
  }
digitalWrite(STCP_Pin, HIGH);
}
clutch = digitalRead(clutchSwitch);
upshift = digitalRead(PushButton_U);
downshift = digitalRead(PushButton_D);

Reed_HIGH = digitalRead(Reed_PinH);
Reed_LOW  = digitalRead(Reed_PinL);

void gearShift(int clutch, int upshift, int downshift){
  if (clutch == HIGH & upshift == HIGH){
    digitalWrite(sv_a, HIGH);
    delay(1000);
    digitalWrite(sv_a, LOW);
}
if (upshift == LOW){
    digitalWrite(sv_a, LOW);
  }
if (clutch == HIGH & downshift == HIGH){
    digitalWrite(sv_b, HIGH);
    delay(1000);
    digitalWrite(sv_b, LOW);
  }
if (downshift == LOW){
    digitalWrite(sv_b, LOW);
  }
if (clutch == LOW){
  digitalWrite(sv_a, LOW);
  digitalWrite(sv_b, LOW);
}
}

void GearCounter(int Reed_HIGH,int Reed_LOW){
  if (Reed_HIGH == HIGH & Reed_LOW == LOW){
  counter = counter + 1;
  DisplayDigit(counter);
}

if (Reed_HIGH == LOW & Reed_LOW == HIGH){
  counter = counter - 1;
  DisplayDigit(counter);
  }

if (Reed_HIGH == HIGH & Reed_LOW == HIGH){
    DisplayDigit(1);
}

if (Reed_HIGH == LOW & Reed_LOW == LOW){
    counter = counter;
    DisplayDigit(counter);
}
}

void loop() {

gearShift(clutch, upshift, downshift);
GearCounter(Reed_HIGH, Reed_LOW)

}
