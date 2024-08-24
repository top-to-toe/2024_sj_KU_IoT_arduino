const int buzz = 11;

// 556655305533200556655305323100 <------- 학교종
// 12331356501233135650653653221235500 <-- 퐁당퐁당
// 532155505321666064327770554231005321555053216660643255556542100 <---- 징글벨
// 503330333035123044443333222120500

const int  notes[] = { 262, 294, 330, 349, 392, 440, 494, 523 };
const char codes[] = "CDEFGABC"; // = { C, D, E, F, G, A, B, C };
const int  tempo   = 200;

void setup() { 
  Serial.begin(9600);
  Serial.println(">> play music~ <<");
} 

void loop() {
  if(Serial.available() > 0)
  {
    char ch = Serial.read();

    player(ch, tempo);
  }
}

void player(char ch, int tm)
{
  if(ch >= '1' && ch <= '8')    // if(ch >= 49 && ch <= 56)
  {
    Serial.print(codes[(ch-'0')-1]);  // '1'-'0' = 49-48 = 1
    Serial.print(" ");
    tone(buzz, notes[(ch-'0')-1]);
    delay(tm);
  }
  else if(ch == '0')
  {
    delay(tm);
    Serial.println();
  }
  else;
  
  noTone(buzz);
}
