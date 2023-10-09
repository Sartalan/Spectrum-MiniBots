/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-websocket-server-arduino/
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

// Import required libraries
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char* ssid = "TP-LINK_3C90";
const char* password = "yBxwCV3AryoFqJ8RHfYU";

const int ledPin = 23;
const int ledPinDos = 22;
const int ledPinTres = 18;
const int ledPinCuatro = 19;

bool ledState,ledStateDos,ledStateTres,ledStateCuatro = 0;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
<style>
  html {
    font-family: Arial, Helvetica, sans-serif;
    text-align: center;
  }
  h2{
    font-size: 1.5rem;
    font-weight: bold;
    color: #143642;
  }
  body {
    margin: 0;
  }
  .content {
    padding: 30px;
    max-width: 600px;
    margin: 0 auto;
  }
  .card {
    background-color: #F8F7F9;;
    box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5);
    padding-top:10px;
    padding-bottom:20px;
  }
  .button {
    padding: 15px 50px;
    font-size: 24px;
    text-align: center;
    outline: none;
    color: #fff;
    background-color: #0f8b8d;
    border: none;
    border-radius: 5px;
    -webkit-touch-callout: none;
    -webkit-user-select: none;
    -khtml-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    user-select: none;
    -webkit-tap-highlight-color: rgba(0,0,0,0);
   }
   /*.button:hover {background-color: #0f8b8d}*/
   .button:active {
     background-color: #0f8b8d;
     box-shadow: 2 2px #CDCDCD;
     transform: translateY(2px);
   }
   .state {
     font-size: 1.5rem;
     color:#8c8c8c;
     font-weight: bold;
   }
  </style>
<title>ESP Web Server</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="icon" href="data:,">
</head>
<body>
  <div class="content">
    <div class="card">
      <h2>Prueba GPIO 2</h2>

      <p class="state">state: <span id="state">%STATE%</span></p>
      <p><button id="button" class="button">Toggle</button></p>
      
    </div>
  </div>
<script>
  var gateway = `ws://${window.location.hostname}/ws`;
  var websocket;
  window.addEventListener('load', onLoad);
  function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen    = onOpen;
    websocket.onclose   = onClose;
    websocket.onmessage = onMessage; // <-- add this line
  }
  function onOpen(event) {
    console.log('Connection opened');
  }
  function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
  }

  function onMessage(event) {
    var state;
    if (event.data == "1"){
      state = "ON";
    }
    else{
      state = "OFF";
    }
    document.getElementById('state').innerHTML = state;
  }
  function onLoad(event) {
    initWebSocket();
    initButton();
  }
  function initButton() {
         window.addEventListener("keydown", function (event) {
            
            let letra = (event.code)

             
            
            switch (letra) {
                default:

                break;
                
            //!--------------IZQUIERDA---------------
                case 'KeyA':
                console.log('Presionaste A y soy el boton de la izquierda =D')
                websocket.send('IZQUIERDA');
                break;

            //!--------------DERECHA---------------

                case 'KeyD':
                console.log('Presionaste D y soy el boton de la derecha =D')         
                websocket.send('DERECHA'); 
                break;

            //!--------------ABAJO---------------
           
                case 'KeyS':
                console.log('Presionaste S y soy el boton de abajo =D') 
                websocket.send('ABAJO');         
                break;           

            //!--------------ARRIBA---------------

                case 'KeyW':
                console.log('Presionaste W y soy el boton de arriba =D')    
                websocket.send('ARRIBA');   
                break;    

            }
        
        })
        window.addEventListener("keyup", function (event) {
            let letra = (event.code)
            switch (letra) {
            //!--------------MENOSIZQUIERDA---------------
                case 'KeyA':
                console.log('Dejó de presionarse A y soy el boton de la izquierda =D')
     
                break;
                
            

            //!--------------MENOSDERECHA---------------

                case 'KeyD':
                console.log('Dejo de presionarse D y soy el boton de la derecha =D')
           
                break;
                
            

            //!--------------MENOSABAJO---------------

            
                case 'KeyS':
                console.log('Dejo de presionarse S y soy el boton de abajo =D')

                break;
                
            

            //!--------------MENOSARRIBA---------------

                case 'KeyW':
                console.log('Dejo de presionarse W y soy el boton de arriba =D')
       
                break;

                
            }

        })

  }






  function toggle(){


    websocket.send('alan');

  }
</script>
</body>
</html>
)rawliteral";

void notifyClients() {
  ws.textAll(String(ledState));
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    if (strcmp((char*)data, "IZQUIERDA") == 0) {
      ledState = !ledState;
      notifyClients();
    }
    if (strcmp((char*)data, "DERECHA") == 0) {
      ledStateDos = !ledStateDos;
      notifyClients();
    }
       if (strcmp((char*)data, "ARRIBA") == 0) {
      ledStateTres = !ledStateTres;
      notifyClients();
    }
       if (strcmp((char*)data, "ABAJO") == 0) {
      ledStateCuatro = !ledStateCuatro;
      notifyClients();
    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

String processor(const String& var){
  Serial.println(var);
  if(var == "STATE"){
    if (ledState){
      return "ON";
    }
    else{
      return "OFF";
    }
  }
  return String();
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  pinMode(ledPinDos, OUTPUT);
  pinMode(ledPinTres, OUTPUT);
  pinMode(ledPinCuatro, OUTPUT);

  digitalWrite(ledPin, LOW);
  digitalWrite(ledPinDos, LOW);
  digitalWrite(ledPinTres, LOW);
  digitalWrite(ledPinCuatro, LOW);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  initWebSocket();

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Start server
  server.begin();
}

void loop() {
  ws.cleanupClients();
  digitalWrite(ledPin, ledState);
  digitalWrite(ledPinDos, ledStateDos);
  digitalWrite(ledPinTres, ledStateTres);
  digitalWrite(ledPinCuatro, ledStateCuatro);
}