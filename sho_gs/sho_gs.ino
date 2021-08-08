/**********
  IFG Campus Goiânia
  Autores: Bruna Michelly O. S. Cordeiro, Fabrycio L. Nakano e Daniel S. Oliveira.
  Objetivo: Envio de leitura do sensor DHT22 para o Google sheets a cada cinco minutos, através do NodeMcu ESP8266.
  Origem: https://www.youtube.com/watch?v=okNECYf2xlY 
     
*********/

//----------------------- Inclusão de bibliotecas necessárias ----------------------------
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "DHT.h"
//----------------------------------------------------------------------------------------

#define DHTTYPE DHT22           //--> Definição do tipo de sensor DHT utilizado(DHT11, DHT21, and DHT22).
#define ON_Board_LED 2          //--> Defining do pino 2 como "ON_Board_LED", indicação de conexão com o roteador WiFi

const int DHTPin = 5;           //--> The pin used for the DHT11 sensor is Pin D1 = GPIO5
DHT dht(DHTPin, DHTTYPE);       //--> Initialize DHT sensor, DHT dht(Pin_used, Type_of_DHT_Sensor);


//----------------------- SSID and Senha do roteador WiFi --------------------------------
const char* ssid = "GlobalNet_Daniel";                //--> Nome da rede WiFi name or SSID.
const char* password = "2cc42829";                    //--> Senha da WiFi.

//---------------------------------------- Host & httpsPort ------------------------------
const char* host = "script.google.com";
const int httpsPort = 443;
//----------------------------------------------------------------------------------------
WiFiClientSecure client;                              //--> Criação do objeto WiFiClientSecure. https://script.google.com/macros/s/AKfycbyQgTKDPBFyKlVmm2LO16C-bFvL4H26OPiW1x4QUYSK8DXvyls/exec
                                                      
String GAS_ID = "AKfycbxbSLo2WBFgwg_rk9PclcdW4dZPM4FVIOEKJV--O-6fwbZ8yyw"; //--> spreadsheet script ID

//=============================== void setup =============================================

 void setup() {
  
  Serial.begin(115200);
  delay(500);

  dht.begin();                                        //--> Inicialização do sensor DHT
  delay(500);
  
  WiFi.begin(ssid, password);                         //--> Conexão com o roteador WiFi 
  Serial.println("");
    
  pinMode(ON_Board_LED,OUTPUT);                       //--> Configuração de LED on board como saída (output)
  digitalWrite(ON_Board_LED, HIGH);                   //--> Turn off Led On Board

  //------------------------------------ Espera pela conexão ------------------------------------
  Serial.print("Conectando");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    
  //---------------------------------- LED pisca durante a conexão com o roteador WiFi ----------
  digitalWrite(ON_Board_LED, LOW);
  delay(250);
  digitalWrite(ON_Board_LED, HIGH);
  delay(250);
  //---------------------------------------------------------------------------------------------
  }
  
  digitalWrite(ON_Board_LED, HIGH);                   //--> Desliga o LED on board quando o ESP8266 estiver conectado ao roteador.
  
  //------- Se ocorrer a conexão com sucesso, o endereço IP é mostrado no monitor serial ----------
  Serial.println("");
  Serial.print("Conectado com sucesso à rede : ");
  Serial.println(ssid);
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  
  client.setInsecure();
 }

 //============================================= void loop ========================================
void loop() {
 
 //--------------- Rotina de leitura do sensor DHT22 ---------------------------------------------- 
  int h = dht.readHumidity();                             //--> Leitura da umidade (%)
  int t = dht.readTemperature();                          //--> Leitura da temperatura (ºC)
    
  if (!(isnan(h) || isnan(t))) {                         //--> Checagem de falhas. Caso ocorram, tenta realizar a leitura novamente.
    String Temp = "Temperature : " + String(t) + " °C";
    String Humi = "Humidity : " + String(h) + " %";

    Serial.println();
    Serial.println(Temp);
    Serial.println(Humi);
    sendData(t, h);                                         //--> Chama a subrotina "sendData"
    delay(300000);                                          //--> Aguarda cinco minutos para repetira o envio de dados
  }  
  else{
    Serial.println("Falha na leitura de leitura do sensor DHT!");
    delay(500);
    return;
  }

}

//========================================= void sendData =====================================

//--------------------------- Subrotina para envio de dados para a Google Sheets --------------

void sendData(int tem, int hum) {
  Serial.println("==========");
  Serial.print("conectando a ");
  Serial.println(host);                                   //--> Host definido como "script.google.com"
  
  //------------------------------- Connect to Google host -----------------------------------
  if (!client.connect(host, httpsPort)) {                 //--> Host "script.google.com" e porta 443
    Serial.println("Conexão falhou");
    return;
  }
  
  //-------------------------- Processando e enviando dados ----------------------------------
  String string_temperature =  String(tem);
  String string_humidity =  String(hum, DEC); 
  String url = "/macros/s/" + GAS_ID + "/exec?temperature=" + string_temperature + "&humidity=" + string_humidity;
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "User-Agent: BuildFailureDetectorESP8266\r\n" +
         "Connection: close\r\n\r\n");

  Serial.println("pedido enviado");

  //------------------------- Verificação se os dados foram enviados com sucesso ou não --------------------------
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("cabeçalhos recebidos");
      break;
    }
  }
 
} 
//==============================================================================
