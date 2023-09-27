
void Adelante_HTML(){
   // Display current state, and ON/OFF buttons for GPIO 26  
            client.println("<p>GPIO 26 - State " + forwardStatus + "</p>");
            // If the forwardStatus is off, it displays the ON button       
            if (forwardStatus=="off") {
              client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 

}

void Adelante_C(){
  
            if (header.indexOf("GET /26/on") >= 0) {
                      Serial.println("GPIO 26 on");
                      forwardStatus = "on";
                      digitalWrite(MotorA1, HIGH);
                      digitalWrite(MotorA2, HIGH);
                } 

                else if (header.indexOf("GET /26/off") >= 0) {
                      Serial.println("GPIO 26 off");
                      forwardStatus = "off";
                      digitalWrite(MotorA1, LOW);
                      digitalWrite(MotorA2, LOW);
                }
}