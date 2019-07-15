
// Alberto Carlos Perez
// Jorge Villareal
// Jason Godwin
// FINAL PROJECT
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
  #main {
            display: table; 
            margin: auto;  
        } 
  h2 {text-align:center; } 
  h3 {text-align:center; } 
  h4 {text-align:center; } 
  .button1 { padding:10px 10px 10px 10px; width:100%; background-color: #44aff2; font-size: 120%;}
  .button2 { padding:10px 10px 10px 10px; width:100%; background-color: #ff1414; font-size: 120%;}
  .solidGold {
            border-style: solid;
            background-color: #CFC493;
            text-align: center;
            color: #f6f6f6;
            width: 100%;
      }
  .solidGreen {
            border-style: solid;
            background-color: #006747;
            text-align: center;
            color: #f6f6f6;
            width: 100%;
      }
  .sansserif {
            font-family: Arial, Helvetica, sans-serif;
      }
 </style>

 <title>Embedded Sys Course</title>
</head>
<body bgcolor="#cfcfcf">
 <div id='main'>
  
    <div class="solidGreen">
      <h2><u>Embedded Systems Course</u></h2>
      <h3>Final Project</h3>
      <h3>Summer 2019</h3>
    </div>

   
  
    <div class="solidGold">
       <table style="width:100%">
        <tr>
          <th class="sansserif"></th>
          <th class="sansserif"><u>TEAM</u></th>
          <th class="sansserif"></th>
        </tr>
        <tr>
          <th class="sansserif"></th>
        </tr>
        <tr>
          <th class="sansserif"></th>
        </tr>
        <tr>
          <th class="sansserif">Jason Godwin</th>
          <th class="sansserif">Alberto Carlos Perez</th>
          <th class="sansserif">Jorge Villareal</th>
        </tr>
        <tr>
          <td class="sansserif">Computer Engineer</td>
          <td class="sansserif">Computer Engineer</td>
          <td class="sansserif">Computer Engineer</td>
        </tr>
      </table>
    </div>

    <div>
      <h1></h1>
    </div>
    <div>
      <h1></h1>
    </div>
    <div>
      <h1></h1>
    </div>
)=====";

String html_2 = "";

String html_4 = R"=====(
  </div>
 </body>
</html>
)=====";


#include <ESP8266WiFi.h>



//xxxxxxxxxxxxxxx
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "KG1xVYG83acfMt8KAF2rqedAfkoLbBna";


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



    // BLYNK
    Blynk.begin(auth, ssid, pass);
 
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

    pinMode(D7, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
    pinMode(D6, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
} 
 
 
 
void loop() 
{
    //xxxxxxxxxxxxx
    Blynk.run();
  
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
       html_2 = "  <form id='F1' action='LEDOFF'><input class='button1' type='submit' value='Turn ON' ></form><br>\r\n";
    }
    else                              
    {
        // the LED is off so the button needs to say turn it on
        html_2 = "  <form id='F1' action='LEDON'><input class='button2' type='submit' value='Turn OFF' ></form><br>\r\n";
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
