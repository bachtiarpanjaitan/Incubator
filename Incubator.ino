#include <LiquidCrystal.h>

const int RS = 8;
const int EN = 9;
const int d4 = 4;
const int d5 = 5;
const int d6 = 6;
const int d7 = 7;
const int BL = 10;
int led = 38;

int menuLevel = 0;
int menusize = 1;
int suhuValue = 28;
int lembabValue = 15;
String pilih[] = {"TEMPERATURE","HUMIDITY"};
int posMen = 0;
bool flagMenu = false;
bool btnOk = false;
  
LiquidCrystal lcd (RS,EN,d4,d5,d6,d7);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("UP/DOWN for MENU");
}

/**
 * Cetak String
 */
void cetak(int col, int row, String text, bool clr=false){
  if(clr==true)lcd.clear();
  lcd.setCursor(col,row);
  lcd.print(text);
}

/**
 * Penentuan Posisi Menu
 */
void menu(){
  if(posMen>menusize){
    posMen =1;
  }
  if(posMen<0){
    posMen = 0; 
  }
  cetak(0,0,"------MENU------",true);
  cetak(0,1,pilih[posMen]);
}

void menusuhu(){
  cetak(0,0,"SET TEMPERATURE :", true);

}

void menulembab(){
  cetak(0,0,"SET HUMIDITY :", true);

}

/**
 * Deteksi Nilai Event Tombol
 * 
 */
int tombol(){
  int hasil;
  int x;
  x = analogRead(0);
  if(x<60){         //kanan
    hasil = 0;
  }else if(x<200){  //atas
    hasil = 1;
  }else if(x<400){  //bawah
    hasil = 2;
  }else if(x<600){  //kiri
    hasil = 3;
  }else if(x<800){  //select
    hasil = 4;
  }
  return(hasil);
}

void loop() {
  if(tombol() == 1 && menuLevel == 0){
    menu();
    if(posMen >0){
      posMen -= 1;
      delay(150);
    }
  }else if(tombol() == 2 && menuLevel == 0){
    menu();
     if(posMen <1){
      posMen += 1;
      delay(150);
    }
  }

  if(posMen == 0  && menuLevel ==0){
    if(tombol() == 4){
       menusuhu(); 
       menuLevel = 1; 
    }
  }

  if(posMen == 1  && menuLevel ==0){
    if(tombol() == 4){
       menulembab(); 
       menuLevel = 1; 
    }
  }

  if(posMen == 0 && menuLevel == 1){
    if(tombol() == 1)suhuValue +=1;
    if(tombol() == 2)suhuValue -=1;
    cetak(0,1, String(suhuValue)+ " C");
  }

  if(posMen == 1 && menuLevel == 1){
    if(tombol() == 1)lembabValue +=1;
    if(tombol() == 2)lembabValue -=1;
    cetak(0,1, String(lembabValue)+ " RH");
  }

  if(tombol() == 3){
    cetak(0,0,"TEMP  :" + String(suhuValue)+ " C",true);
    cetak(0,1,"HUMID :" + String(lembabValue)+ " RH");
    menuLevel = 0;
    posMen = 1;
  }
  Serial.println(posMen);
  delay(250);
}



