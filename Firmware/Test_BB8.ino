

// AIRPAD
/* ############################################################ 
 *  By: Gianluca Pugliese 
 *  BQlabs
 *  Android App for Controller:  https://play.google.com/store/apps/details?id=com.br3.udpctl&hl=th
 *  Hardware Micro Controller: NodeMCU V2 (ESP8266-12)
  
 *  Based on the awesome job of Vittaysak Rujivorakul
 *########################################################### */


 
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <Servo.h>
#include <Oscillator.h>



#define N_OSCILLATORS 8

#define TRIM_RR -11
#define TRIM_RL -15
#define TRIM_YR -13
#define TRIM_YL -6
#define TRIM_SR 15
#define TRIM_SL 0
#define TRIM_AR 6
#define TRIM_AL 0


#define PIN_RR 4
#define PIN_RL 5
#define PIN_YR 6
#define PIN_YL 7
#define PIN_SR 2
#define PIN_SL 8
#define PIN_AR 3
#define PIN_AL 9

Oscillator osc[N_OSCILLATORS];


 /* Set SSID and Password of your AP . */


const char *ssid = "AirPad";
const char *password = "";

ESP8266WebServer server(80);


String cmd="1";

//  http://192.168.4.1 in a web browser


void handleRoot() {
  cmd=server.arg("cmd");

  
  // get cmd parameter from url :  http://192.168.4.1/?cmd=1

  
  checkcommand();

  server.send(200, "text/html", "<h1>AirPad connected</h1>" + cmd);
}



void setup() {
  delay(1000);
  Serial.begin(9600);

    osc[0].attach(PIN_RR);
    osc[1].attach(PIN_RL);
    osc[2].attach(PIN_YR);
    osc[3].attach(PIN_YL);
    osc[4].attach(PIN_SR);
    osc[5].attach(PIN_SL);
    osc[6].attach(PIN_AR);
    osc[7].attach(PIN_AL);/**/

    osc[0].SetTrim(TRIM_RR);
    osc[1].SetTrim(TRIM_RL);
    osc[2].SetTrim(TRIM_YR);
    osc[3].SetTrim(TRIM_YL);
    osc[4].SetTrim(TRIM_SR);
    osc[5].SetTrim(TRIM_SL);
    osc[6].SetTrim(TRIM_AR);
    osc[7].SetTrim(TRIM_AL);/**/

 
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
   
  server.handleClient();
}



void forward(int steps, int T)
 {
   delay(10);
 //  Serial.println("forward");
   
 

    int A[8]= {15, 15, 25, 25, 20, 20, 15, 15};
    int O[8] = {0, 0, 0, 0, -60, 60, -30, 30};
    double phase_diff[8] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90),
                            DEG2RAD(270), DEG2RAD(270), DEG2RAD(0), DEG2RAD(0)};

    for(int i=0;i<steps;i++) oscillate(A,O, T, phase_diff);
}


 void back()
 {
   delay(10);
  // Serial.println("back");
 

 }



 void left()
 {
  delay(10);
 // Serial.println("left");
 
 }

 
 void right()
 {
  delay(10);
 // Serial.println("Right");
 

 }

void Stop()
 {
  delay(10);
 // Serial.println("Stop");
 
  
 }


void love()
 {
  delay(10);
 // Serial.println("love");
 
/*
**************************
- PUT YOUR MOVEMENT HERE -
**************************
*/
 
 }


void fire()
 {
  delay(10);
 // Serial.println("fire");
 
/*
**************************
- PUT YOUR MOVEMENT HERE -
**************************
*/
 
 }


void skull()
 {
  delay(10);
 // Serial.println("skull");
 
/*
**************************
- PUT YOUR MOVEMENT HERE -
**************************
*/
 
 }


void plus()
 {
  delay(10);
 // Serial.println("plus");
 
/*
**************************
- PUT YOUR MOVEMENT HERE -
**************************
*/
 
 }


void punch()
 {
  delay(10);
 // Serial.println("punch");
 
/*
**************************
- PUT YOUR MOVEMENT HERE -
**************************
*/
 
 }


void mask()
 {
  delay(10);
 // Serial.println("mask");
 
/*
**************************
- PUT YOUR MOVEMENT HERE -
**************************
*/
 
 }






 void checkcommand()
 {
    
   int cm = cmd.toInt();
   switch(cm){
    
    
//UP
    case 1:     forward(0,0);      
    break;
    
//DOWN
    case 2:      back();      
    break;


//STOP
    case 5:  Stop();                              
    break;


//LEFT
    case 3:  left();    
    break;


//RIGH
    case 4:  right();   
    break;


//HEART
    case 6:  love();   
    break;


//FIRE
    case 7:  fire();   
    break;


//SKULL
    case 8:  skull();   
    break;


//PLUS
    case 9:  plus();   
    break;

//PUNCH
    case 10:  punch();   
    break;


//MASK
    case 11:  mask();   
    break;

    }

 }


 void oscillate(int A[N_OSCILLATORS], int O[N_OSCILLATORS], int T, double phase_diff[N_OSCILLATORS]){
  for (int i=0; i<8; i++) {
    osc[i].SetO(O[i]);
    osc[i].SetA(A[i]);
    osc[i].SetT(T);
    osc[i].SetPh(phase_diff[i]);
  }
  double ref=millis();
   for (double x=ref; x<T+ref; x=millis()){
     for (int i=0; i<8; i++){
        osc[i].refresh();
     }
  }
}

