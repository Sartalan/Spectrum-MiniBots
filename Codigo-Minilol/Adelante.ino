void Adelante_HTML (){
  //#define MotorA2 16  //outputInt
  //#define MotorA1 17  //outputInt
  String Estado_Adelante = "off";

  //--------------------------------------------------------------
  //Creación HTML con href = on && off


            client.println("<p>Estado Motor Hacia Delante" + Estado_Adelante + "</p>");

            if (Adelante=="on") {
              client.println("<p><a href=\"/16/on\"><button class=\"button\">ON</button></a></p>");
            }

             else {
              client.println("<p><a href=\"/16/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
}

  //--------------------------------------------------------------
  //Creación código C recibiendo el on || off

            void Adelante_C(){

              if (header.indexOf("GET /16/on") >= 0) {        //Sí recibe on == Prendido
                      Serial.println("Adelante");
                      Estado_Adelante = "on";
                      digitalWrite(MotorA2, HIGH);
                      digitalWrite(MotorA1, HIGH);
              } 

              else if (header.indexOf("GET /16/off") >= 0) {
                      Serial.println("Parado");               //Sí recibe off == Apagado
                      Estado_Adelante = "off";
                      digitalWrite(MotorA2, LOW);
                      digitalWrite(MotorA1, LOW);
                }
}


 