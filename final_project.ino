/*
  GE109 - Tinkering Lab
  Final Project : Scoreboard using LCD Display

  by-
    2022epb1252 : Teena Ghoslya
    2022epb1253 : V Kotesh
    2022mcb1254 : Ajay Kumar
    2022mcb1255 : Akshat Nagpal   ---> tbh just this guy
    2022mcb1256 : Amitoj Singh
    2022mcb1257 : Aniruddh Muley
*/

#include <LiquidCrystal.h>
#include <time.h>

const int rs_pin = 8;
const int enable_pin = 9;
const int d4 = 10, d5 = 11, d6 = 12, d7 = 13;     //4 bytes of display information.
LiquidCrystal lcd(rs_pin, enable_pin, d4, d5, d6, d7);

class Button{
//OverRancid#0590
public:
  Button(int pin_number, int update_type, int* variable);
  void update();
  void reset();
  bool CheckStateUpdate();
  int getPin();
private:
  int pin, type;
  bool state;
  int *dependency; //variable that the button controls 
};

long sec=0, mins=0;
const char* overrancid = "OverRancid#0590 ";
int score_1=0, score_2=0;

Button team_1(6, 1, &score_1);
Button team_2(7, 1, &score_2);
Button reset_button(5, 0, nullptr);

void setup() {
  lcd.begin(16, 2);
  pinMode(team_1.getPin(), INPUT);
  pinMode(team_2.getPin(), INPUT);
  pinMode(reset_button.getPin(), INPUT);
  display_overrancid();
}

int server = 1;
bool selected = false;
void loop() {
  lcd.setCursor(0, 1);

  if(team_1.CheckStateUpdate()){
    team_1.update();
    server = 1;
  }

  if (team_2.CheckStateUpdate()){
    team_2.update();
    server = 2;
  }

  if (reset_button.CheckStateUpdate())
    reset_button.update();
  
  //get potentiometer reading and use if-else to map it to display format.
  int pV = analogRead(A0);

  if(pV<=341){
    if(selected)
      display_football();
    else{
      lcd.setCursor(0, 0);
      lcd.print("   -FOOTBALL-   "); 
      lcd.setCursor(0, 1);
      lcd.print("                ");
    }
  }
  else if(341<pV && pV<=682){
    if(selected)
      display_badminton();
    else{
      lcd.setCursor(0, 0);
      lcd.print("  -BADMINTON-   "); 
      lcd.setCursor(0, 1);
      lcd.print("                ");
    }    
  }
  else if(682<pV){
    if(selected)
      display_badminton();
    else{
      lcd.setCursor(0, 0);
      lcd.print("    -TENNIS-    "); 
      lcd.setCursor(0, 1);
      lcd.print("                ");
    }    
  } 
}

void display_football(){
  lcd.setCursor(0, 0);
  lcd.print("GER"); 
  delay(100);
  sec++;
  if(sec==60){
   	mins++;
    sec=0;
  }
  if(mins==90){
    sec=0;
  }
  lcd.setCursor(6, 0);
  if(mins<10){
 	lcd.print('0');
  }
 	
  lcd.print(mins);

  lcd.print(":");

  if(sec<10){
 	  lcd.print('0');
  }
  lcd.print(sec);

  lcd.setCursor(13, 0);
  lcd.print("ESP");

  lcd.setCursor(1, 1);
  lcd.print(score_1);

  lcd.setCursor(7,1);
  if(mins<=45){
    lcd.print("1ST");
  }
  else if(mins!=90){
  	lcd.print("2ND");
  }
  else{
  	lcd.print("FT");
  }
  
  lcd.setCursor(14, 1);
  lcd.print(score_2);
}

int matches_won_p1 = 0 , matches_won_p2 = 0;
void display_badminton(){
  lcd.setCursor(0, 0);
  lcd.print("AKS |");
  lcd.print(matches_won_p1);
  lcd.print("|");

  lcd.setCursor(0, 1);
  lcd.print("ANI |");
  lcd.print(matches_won_p2);
  lcd.print("|");

  if(max(matches_won_p1, matches_won_p2)==2){
    lcd.setCursor(15, 0);
    lcd.print(matches_won_p1==2?"W":"L");
    lcd.setCursor(15, 1);
    lcd.print(matches_won_p2==2?"W":"L");
    return;
  }
  int x = 7 + (matches_won_p1+matches_won_p2)*3;

  lcd.setCursor(x, 0);
  if(score_1 < 10){
    lcd.print('0');
  }
  lcd.print(score_1);
  
  lcd.print(server==1?"*":" ");

  lcd.setCursor(x, 1);
  if(score_2 < 10){
    lcd.print('0');
  }
  lcd.print(score_2);
  lcd.print(server==2?"*":" ");

  int big = max(score_1, score_2), small = min(score_1, score_2);

  if((big>20 && big-small>1)||big==30){
    if(score_1==big)
      matches_won_p1++;
    else
      matches_won_p2++;

    x = 6 + (matches_won_p1+matches_won_p2)*3;
    lcd.setCursor(x, 0);
    lcd.print("|");
    lcd.setCursor(x, 1);
    lcd.print("|");

    score_1 = score_2 = 0;
    server = (matches_won_p1+matches_won_p2)%2+1;
  }
}

void display_overrancid(){
  //all aboard the OverRancid train :train:
  for(int i=15; i>-15; i--){
    if(i>=0){
      for(int j=i; j<16; j++){
        lcd.setCursor(j, 0);
        lcd.print(overrancid[j-i]);
      }
    }
    if(i<0){
      lcd.setCursor(0, 0);
      for(int j=-i; j<16; j++){
        lcd.print(overrancid[j]);
      }
    }
    delay(175);
  }
}


char *tennis_score[] = {"00", "15", "30", "40", "AD"};
int games_1 = 0, games_2 = 0;

void display_tennis(){
  lcd.setCursor(0, 0);
  lcd.print("AKS |");
  lcd.print(games_1);
  lcd.print("|");
  lcd.print(matches_won_p1);
  lcd.print("|");

  lcd.setCursor(0, 1);
  lcd.print("ANI |");
  lcd.print(games_2);
  lcd.print("|");
  lcd.print(matches_won_p2);
  lcd.print("|");

  server = (matches_won_p1+matches_won_p2)%2+1;
  if(min(matches_won_p1, matches_won_p2)>=6)
    server = (score_1+score_2)%2+1;

  if(max(games_1, games_2)==2){
    lcd.setCursor(15, 0);
    lcd.print(games_1==2?"W":"L");
    lcd.setCursor(15, 1);
    lcd.print(games_2==2?"W":"L");
    return;
  }
  if(score_1==4 && score_2==4 && min(matches_won_p1, matches_won_p2)<6)
    score_1 = score_2 = 3;

  lcd.setCursor(10, 0);
  if(min(matches_won_p1, matches_won_p2)>=6){
    if(score_1 < 10){
      lcd.print('0');
    }
    lcd.print(score_1);  
  }
  else
    lcd.print(tennis_score[score_1]);
  
  lcd.print(server==1?" *|":"  |");

  lcd.setCursor(10, 1);
    if(min(matches_won_p1, matches_won_p2)>=6){
    if(score_2 < 10){
      lcd.print('0');
    }
    lcd.print(score_2);  
  }
  else
    lcd.print(tennis_score[score_2]);

  lcd.print(server==2?" *|":"  |");

  int big = max(score_1, score_2), small = min(score_1, score_2);

  if(((big>3 && min(matches_won_p1, matches_won_p2)<6)||big>6) && big-small>1){
    lcd.setCursor(10, 0);
    lcd.print("--  ");
    lcd.setCursor(10, 1);
    lcd.print("--  ");
    if(score_1==big)
      matches_won_p1++;    
    else
      matches_won_p2++;
    score_1 = score_2 = 0;
  }

  big = max(matches_won_p1, matches_won_p2), small = min(matches_won_p1, matches_won_p2);
  if(big>5 && big-small>1 || big==7){
    lcd.setCursor(7, 0);
    lcd.print("-");
    lcd.setCursor(7, 1);
    lcd.print("-");

    if(matches_won_p1==big)
      games_1++;
    else
      games_2++;
    matches_won_p1 = matches_won_p2 = 0;
  }
}

Button::Button(int pin_number, int update_type, int* variable){
  pin = pin_number;
  type = update_type;
  dependency = variable;
}
void Button::update(){
  if(type==0)
    return global_reset_count();
  *dependency += type;
  *dependency = max(*dependency, 0);
  *dependency = min(*dependency, 99999);
}
void Button::reset(){
  *dependency = 0;
}
bool Button::CheckStateUpdate(){
  bool prevState = state;
  state = digitalRead(pin);
  return !prevState && state;
  //returns true at positive edge of button press.
}
int Button::getPin(){
  return pin;
}

void global_reset_count(){
  team_1.reset();
  team_2.reset();
  sec=mins=0;
  matches_won_p1 = matches_won_p2 = 0;
  games_1 = games_2 = 0;
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  selected^=true;
}
