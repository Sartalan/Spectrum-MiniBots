
// Import required libraries
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char* ssid = "Vllamada";
const char* password = "Vllamada_2021";

 int Numero;

#define Motor1a 16
#define Motor1b 17
#define Motor2a 18
#define Motor2b 19

bool Arriba_BOOL, Derecha_BOOL, Abajo_BOOL, MenosIzquierda , ledState, Izquierda_BOOL = 0;

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
        :root {
    --pads-color:#000000;
}

:root {
    --left-radius:1em 0 0 1em;
    --right-radius:0 1em 1em 0;
    --bottom-radius:0 0 1em 1em;
    --top-radius:1em 1em 0 0;
}
/*GRID POSITION*/
/*! ------------------------------------- */
.top {
    grid-column: 2;
    grid-row:1;
    border-radius: var(--top-radius);
}
.bottom {
    grid-column: 2;
    grid-row: 3;
    border-radius: var(--bottom-radius);
}
.right {
    grid-column: 3;
    grid-row: 2;
    border-radius: var(--right-radius);
}
.left {
    grid-column: 1;
    grid-row: 2;
    border-radius: var(--left-radius);
}

/*Styles Customization*/
/*! ------------------------------------- */

* {
    padding: 0;
    margin: 0;
    box-sizing: border-box;
}

body {
    background-color: #181717;
    display: flex;
    justify-content: center;
    align-items: center;
    height: 100vh;
}

.controller-box {
    width: 20em;
    height: 20em;
    background-color:transparent;
    display: grid;
    position: relative;
    grid-template-columns: 1fr 1fr 1fr;
    grid-template-rows: 1fr 1fr 1fr;
}

/*! Center controller btn*/
/*! ------------- */
.center {
    background-color: var(--pads-color);
    grid-column: 2;
    grid-row: 2;
    display: flex;
    align-items: center;
    justify-content: center;
}

.center-icon {
    width: 3em;
    height: 3em;
    
}

/*!Buttons*/
/*! ------------- */

.controller-btn {
    background-color: var(--pads-color);
    display: flex;
    justify-content: center;
    align-items: center;
    cursor: pointer;
}

.controller-btn > .arrow-in {
    width: 6em;
    height: 6em;
    filter: invert(1);
}

/*? Button Functionality*/
/*! ------------------------------------- */

.controller-btn.active {
    background-color: rgba(46, 138, 126, 0.733);
}

</style>


<title>ESP Web Server</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="icon" href="data:,">
</head>
<body>
  <div class="controller-box">

        <div class="center"></div>

        <div class="left controller-btn">
          <img class="arrow-in" src="#" alt="">
        </div>

        <div class="right controller-btn">
          <img class="arrow-in" src="#" alt="">
        </div>

        <div class="bottom controller-btn">
          <img class="arrow-in" src="#" alt="">
        </div>

        <div class="top controller-btn">
          <img class="arrow-in" src="#" alt="">
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
  
  //Controller Functionality Start
// ------------------------------------- 

  function initButton() {

  let izquierda = document.querySelector('.left')
  let derecha = document.querySelector('.right')
  let abajo = document.querySelector('.bottom')
  let arriba = document.querySelector('.top')
  let Estado = 0
  let senalEnviada = 0 
      window.addEventListener("keydown", function (event) {
            
            let letra = (event.code)
  
      switch (letra) {
        default:

          izquierda.classList.remove('active')
          derecha.classList.remove('active')
          abajo.classList.remove('active')
          arriba.classList.remove('active')

        break;
                
            //!--------------IZQUIERDA---------------

          case 'KeyA':
          Estado=1;
          
          if(Estado && !senalEnviada){
          console.log('Presionaste A y soy el boton de la izquierda =D')
          izquierda.classList.add('active')
          websocket.send('IZQUIERDA');
          senalEnviada=1;
          }

        break;

            //!--------------DERECHA---------------

          case 'KeyD':
          Estado=1;
          if(Estado && !senalEnviada){
          console.log('Presionaste D y soy el boton de la derecha =D')     
          derecha.classList.add('active')    
          websocket.send('DERECHA');
          senalEnviada=1;
          }

        break;

            //!--------------ABAJO---------------
           
          case 'KeyS':
          Estado=1;
          if(Estado && !senalEnviada){
          console.log('Presionaste S y soy el boton de abajo =D') 
          websocket.send('ABAJO');         
          abajo.classList.add('active')
          senalEnviada=1;
          }

        break;           

            //!--------------ARRIBA---------------

          case 'KeyW':
          Estado=1;
          if(Estado && !senalEnviada){
          console.log('Presionaste W y soy el boton de arriba =D')    
          arriba.classList.add('active')
          websocket.send('ARRIBA');
          senalEnviada=1;
          }
        break;    
}})

//SÍ TOCA LA TECLA        ↑ <=
  //-------------------------------
//SÍ SUELTA LA TECLA      => ↓


      window.addEventListener("keyup", function (event) {

          let letra = (event.code)

      switch (letra) {


            //!--------------MENOS_IZQUIERDA---------------

          case 'KeyA':

            console.log('Dejó de presionarse A y soy el boton de la izquierda =D')
            izquierda.classList.remove('active')
            websocket.send('MENOSIZQUIERDA');
            Estado=0
            senalEnviada=0

        break;
                
            //!--------------MENOSDERECHA---------------

          case 'KeyD':

            console.log('Dejo de presionarse D y soy el boton de la derecha =D')
            derecha.classList.remove('active')
            senalEnviada=0

        break;
                
            //!--------------MENOSABAJO---------------
        
            case 'KeyS':

              console.log('Dejo de presionarse S y soy el boton de abajo =D')
              abajo.classList.remove('active')
              senalEnviada=0

          break;
                
            //!--------------MENOSARRIBA---------------

            case 'KeyW':

              console.log('Dejo de presionarse W y soy el boton de arriba =D')
              arriba.classList.remove('active')
              senalEnviada=0

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

//----------------

       if (strcmp((char*)data, "IZQUIERDA") == 0) {
      Izquierda_BOOL  = true ;
      MenosIzquierda = false ;
      Serial.println("Soy true IZQUIERDA");
      Serial.println(Izquierda_BOOL);
      Serial.println(MenosIzquierda);
      Serial.println("---------------------");
      notifyClients();
    }

       if (strcmp((char*)data, "MENOSIZQUIERDA") == 0) {
      MenosIzquierda = true ;
      Izquierda_BOOL = false ;
      Serial.println(MenosIzquierda);
      Serial.println(Izquierda_BOOL);
      Serial.println("---------------------");
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

  pinMode(Motor1a, OUTPUT);
  pinMode(Motor1b, OUTPUT);
  pinMode(Motor2a, OUTPUT);
  pinMode(Motor2b, OUTPUT);

  digitalWrite(Motor1a, LOW);
  digitalWrite(Motor1b, LOW);
  digitalWrite(Motor2a, LOW);
  digitalWrite(Motor2b, LOW);
  
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

  if(MenosIzquierda == true){
    Izquierda_BOOL = false;
  }

  switch (Izquierda_BOOL)
{

    case true:
        digitalWrite(Motor1a, LOW);
        digitalWrite(Motor1b, HIGH);
        digitalWrite(Motor2a, HIGH);
        digitalWrite(Motor2b, LOW);
        Serial.println("Voy hacia Izquierda");
        break;

    default:
        digitalWrite(Motor1a, LOW);
        digitalWrite(Motor1b, LOW);
        digitalWrite(Motor2a, LOW);
        digitalWrite(Motor2b, LOW);
        Serial.println("Morí");
        break;
}
}