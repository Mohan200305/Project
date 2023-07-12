#include<Arduino.h>
#include<WiFi.h>
#include<AsyncTCP.h>
#include<ESPAsyncWebServer.h>
#include<math.h>
#include"lib.h"

AsyncWebServer server(80);

const char* ssid = "M12";
const char* password = "mohan2003";

const char* input_parameter30 = "input30";
const char* input_parameter31 = "input31";
const char* input_parameter32 = "input32";
const char* input_parameter00 = "input00";
const char* input_parameter01 = "input01";
const char* input_parameter02 = "input02";
const char* input_parameter10 = "input10";
const char* input_parameter11 = "input11";
const char* input_parameter12 = "input12";
const char* input_parameter20 = "input20";
const char* input_parameter21 = "input21";
const char* input_parameter22 = "input22";

const char* matrix1[3]={input_parameter30,input_parameter31,input_parameter32};
const char* matrix2[9]={input_parameter00,input_parameter01,input_parameter02,input_parameter10,input_parameter11,input_parameter12,input_parameter20,input_parameter21,input_parameter22};

const char index_html[] PROGMEM = R"rawliteral(


  

<!DOCTYPE HTML><html><head>
  <title>COORDINATES OF X,Y ND Z</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {font-family: Times New Roman; display: inline-block; text-align: center;}
    h2 {font-size: 2.0rem; color: blue;}
  </style> 
  </head><body>
  <h2>TO FIND COORDINATES OF X,Y and z</h2> 
  <p>Enter the values of points e1,q1
  <form action="/get">
    Enter the values of e1: <input type="number" name="input30"><br><input type="number" name="input31"><br><input type="number" name="input32"><br>
    Enter the values of q1: <input type="number" name="input00"><br><input type="number" name="input01"><br><input type="number" name="input02"><br><input type="number" name="input10"><br><input type="number" name="input11"><br><input type="number step=0.866025" name="input12"><br><input type="number" name="input20"><br><input type="number" name="input21"><br><input type="number step=-0.5" name="input22"><br>
    <input type="submit" value="Submit">
    
  </form><br>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connecting...");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
        double k=11;
	double **e1,**e2,**q1,**q2,**q;
        e1 = load_ser(request,matrix1);
	q1 = load_serv(request,matrix2);
        e2=scalarProduct(k,e1);
	q2 = linalg_inv(q1,3,3);
        q=matmul(q2,e2,3,1,1);
        request->send(200, "text/html", "The values of q are <br>[" + String(q[0][0]) + "]<br>[" + String(q[1][0]) + "]<br>[" + String(q[2][0]) + "]<br><a href=\"/\">Return to Home Page</a>");}
	
);   
  server.onNotFound(notFound);
  server.begin();
}
void loop() {
}
