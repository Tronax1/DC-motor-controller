
char val = 101;    //    HEX/Char/DEC    0x65 / 'e' / 101 .  (ASCII table) 
String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";

String html_1 = R"=====(
<!DOCTYPE html>
<html>
 <head>
 <meta name='viewport' content='width=device-width, initial-scale=1.0'/>
 <meta charset='utf-8'>
 <style>
  body {font-size:140%;} 
  #main {display: table; margin: auto;  padding: 0 10px 0 10px; } 
  h2 {text-align:center; } 
  h3 {text-align:center; } 
  h4 {text-align:center; } 
  .button { padding:10px 10px 10px 10px; width:100%;  background-color: #50FF50; font-size: 120%;}
 </style>

 <title>Embedded Sys Course</title>
</head>
<body>
 <div id='main'>
  <h2>Embedded System Course</h2>
  <h3>Final Project</h3>
  <h4>Jason Godwin</h4>
  <h4>Jorge Villareal</h4>
  <h4>Alberto Carlos Perez</h4>
)=====";

String html_2 = "";

String html_4 = R"=====(
  </div>
 </body>
</html>
)=====";


#include <ESP8266WiFi.h>

char ssid[] = "OrangeLion";       //  your network SSID (name)
char pass[] = "Prakyhc26Y";                //  your network password
 
WiFiServer server(80);           //Port 80 is one of the most commonly used port numbers in the Transmission Control Protocol (TCP) suite. Any Web/HTTP client, such as a Web browser, uses port 80 to send and receive requested Web pages from a HTTP server.
 
String request = "";            // http://yourIPadress/request/?  this request can be LEDON or LEDOFF
int LED_Pin = 16;                // Builtin nodemcu LED

 
void setup() 
{
    pinMode(LED_Pin, OUTPUT);     
    
    Serial.begin(9600);        // baudrate of PIC and nodemcu should be same
    Serial.println();
    Serial.println("Serial started at 9600");
    Serial.println("Nodemcu");
    Serial.println();
 
    // Connecting to a WiFi network
    Serial.print(F("Connecting to "));  Serial.println(ssid);
    WiFi.begin(ssid, pass);
 
    while (WiFi.status() != WL_CONNECTED) 
    {
        Serial.print(".");
        delay(500);
    }
      
    Serial.println("");
    Serial.println(F("[CONNECTED]"));
    Serial.print("[IP ");              
    Serial.print(WiFi.localIP()); 
    Serial.println("]");
 
    // start a server
    server.begin();
    Serial.println("Server started");


    // CARLOSXXXXXX
    pinMode(D7, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
    pinMode(D6, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
} 
 
 
 
void loop() 
{
    // Check if a client has connected
    WiFiClient client = server.available();
    if (!client)  {  return;  }
 
    // Read the first line of the request
    request = client.readStringUntil('\r');

    Serial.print("request: "); 
    Serial.println(request); 
 
    if       ( request.indexOf("LEDON") > 0 )  { 
      digitalWrite(LED_Pin, HIGH);
      
      Serial.println(val);




      // carlosxxxxxxxx
      digitalWrite(D7, LOW);   // Turn the LED on (Note that LOW is the voltage level
      // but actually the LED is on; this is because
      // it is active low on the ESP-01)

      digitalWrite(D6, HIGH);
      
      }
    else if  ( request.indexOf("LEDOFF") > 0 ) {
      digitalWrite(LED_Pin, LOW); 
      Serial.println(val);


      digitalWrite(D6, LOW);
      digitalWrite(D7, HIGH);  // Turn the LED off by making the voltage HIGH
      }
 
 
    // Get the LED pin status and create the LED status message
    if (digitalRead(LED_Pin) == HIGH) 
    {
        // the LED is on so the button needs to say turn it off
       html_2 = "  <form id='F1' action='LEDOFF'><input class='button' type='submit' value='ON' ></form><br>\r\n";
    }
    else                              
    {
        // the LED is off so the button needs to say turn it on
        html_2 = "  <form id='F1' action='LEDON'><input class='button' type='submit' value='OFF' ></form><br>\r\n";
    }

    // turns the GPIOs on and off
//    if (header.indexOf("GET /5/on") >= 0) {
//      Serial.println("D1 on");
//      output5State = "on";
//      digitalWrite(output5, HIGH);
//    } else if (header.indexOf("GET /5/off") >= 0) {
//              Serial.println("D1 off");
//              output5State = "off";
//              digitalWrite(output5, LOW);
//    } else if (header.indexOf("GET /4/on") >= 0) {
//              Serial.println("D2 on");
//              output4State = "on";
//              digitalWrite(output4, HIGH);
//    } else if (header.indexOf("GET /4/off") >= 0) {
//      Serial.println("D2 off");
//      output4State = "off";
//      digitalWrite(output4, LOW);
//    }
 
 
    client.flush();
 
    client.print( header );
    client.print( html_1 );    
    client.print( html_2 );
    client.print( html_4);
 
    delay(5);
  // The client will actually be disconnected when the function returns and 'client' object is detroyed
 
} 
