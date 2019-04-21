 #include <ESP8266WiFi.h>

unsigned char ToggleCnt = 0;
unsigned char F_ToggleLed=0; 

const char* ssid = "SSID";
const char* password = "Password; // GPIO13
WiFiServer server(80);



void ToggleLed();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
  // Connect to WiFi network
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
 
while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}

 
 

void loop() {

  if(F_ToggleLed==1)
  {
    ToggleLed(); 
  }
  
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
  Serial.println("**********");
  Serial.print("Main funct =>");
  Serial.print(" F_ToggleLed=");
  Serial.println(F_ToggleLed);
   
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, LOW);
    value = HIGH;
    Serial.print("LED HIGH");
    F_ToggleLed=2;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin, HIGH);
     F_ToggleLed=0;
    value = LOW;
    Serial.print("LED LOW");
  }
  if (request.indexOf("/LED=TOGGLE")!=-1){
     F_ToggleLed=1;  
     Serial.print("LED TOGGLE");
  }

  /*if(F_ToggleLed==1)
  {
    ToggleLed(); 
  }*/
     
  
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Led pin is now: ");
 
  if(value == HIGH) {
    client.print("On");
  }
  else if(value == LOW) {
    client.print("Off");  
  }
  else {
    client.print("Toggle");
  }
  
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a><br />");
  client.println("<br><br>");
  client.println("<a href=\"/LED=TOGGLE\"\"><button>Toggle On</button></a><br />");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");

}



void ToggleLed()
{ 
  Serial.print("ToggleLed funct =>");
  Serial.print(" F_ToggleLed=");
  Serial.println(F_ToggleLed);
  Serial.println();
  Serial.print(" ToggleCnt=");
  Serial.println(ToggleCnt);
  
    ToggleCnt++;
    if(ToggleCnt > 20)
    {
      ToggleCnt = 0;
      digitalWrite(ledPin, LOW);
    }
    else
    {
      digitalWrite(ledPin, HIGH);
    }
} 
 



