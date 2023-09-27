#include <WiFi.h>
//#include <analogWrite.h>

// Configuracion del Wifi del ESP32
const char* ssid     = "ESP32-Pruebaa";
const char* password = "123456789";

// Asignar el número de puerto del server web
WiFiServer server(80);

// Variable to store the HTTP request (?)
String header;

// Variables que guardan el estado de las salidas

String Adelante = "off";



// Asigna los pines de salida a GPIO
//const int output26 = 26;
//const int output27 = 27;
//const int output28 = 28;
//const int output29 = 29;
//#define STBY 5
//int veloc;
#define MotorA2 16
#define MotorA1 17
#define MotorB1 18
#define MotorB2 19

void setup() {
  Serial.begin(115200);
  // Asigna las variables como salidas
  pinMode(MotorA1, OUTPUT);
  pinMode(MotorA2, OUTPUT);
  pinMode(MotorB1, OUTPUT);
  pinMode(MotorB2, OUTPUT);
  // Asigna las salidas en BAJO
  digitalWrite(MotorA1, LOW);
  digitalWrite(MotorA2, LOW);
  digitalWrite(MotorB1, LOW);
  digitalWrite(MotorB2, LOW);


  // Prende el Wifi
  Serial.print("Iniciando Wifi en AP (Punto de Acceso)");
  Serial.print("\n");
  WiFi.softAP(ssid, password); // Quitar el password para que la señal sea gratuita

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  server.begin();
}

void loop(){
  WiFiClient client = server.available();

  if (client) {
    Serial.println("Nuevo Cliente.");
    String currentLine = "";                // Crea un string para guardar todos los datos recibidos del cliente
    while (client.connected()) {
      if (client.available()) {             
        char c = client.read();             // Lee un byte recibido del cliente
        Serial.write(c);                    
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

//------------------------------------------------------ //C_Code
            
       Adelante_C();

//------------------------------------------------------ //HTML_Code - Default, dont delete.

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}");
            client.println("</style></head>");
            //End HTML HEAD
            
//------------------------------------------------------ //HTML_Code with C

      //Body and Rest Code Start
            client.println("<body><h1>ESP32 Web Server</h1>");
 //<Body>
            
          Adelante_HTML();
             
            
//</Body>
            client.println("</body></html>");

//Below this code dont delete anything
//-------------------------------------
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}