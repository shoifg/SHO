/**********
  IFG Campus Goiânia
  Autores: Bruna Michelly O. S. Cordeiro, Fabrycio L. Nakano e Daniel S. Oliveira.
  Objetivo: Envio de leitura do sensor DHT22 para a plataforma ThingSpeak, através do NodeMcu ESP32.
  Observação: Durante a gravação do código, o Esp32 requer que seja pressionado o botão "boot" para a sua gravação
     
*********/

//----------------------- Inclusão de bibliotecas necessárias ----------------------------
#include <DHT.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <SPI.h>

//----------------------------------------------------------------------------------------
#define dhtType DHT22         //--> Definição do tipo de sensor DHT utilizado(DHT11, DHT21, and DHT22).
#define ledGreen 25           //--> Define o pino 25 como o led verde (ledGreen)
#define ledRed 26             //--> Define o pino 26 como o led vermelho (ledRed)

int dhtPin = 4;
float temp = 0;
float umid = 0;

DHT dht(dhtPin, dhtType);     //--> Inicialização do sensor DHT22 (Pino utilizado, Tipo de sensor DHT); 


//------------------- Configurações de rede e cliente WiFi -------------------------------
char ssid[] = "GlobalNet_Daniel";             //--> nome da rede.
char pass[] = "2cc42829";            //--> senha da rede.
char mqttUserName[] = "sho";              //--> nome de usuário do MQTT
char mqttPass[] = "SXVQDA8CTIUT3ES1";     //--> chave de acesso do MQTT.
char writeAPIKey[] = "XJ9DEWT282DXJLX9"; //--> chave de acesso do canal thingspeak.
long channelID = 1471568; //Identificação do canal thingspeak.

//------------------- Definir identificação de cliente randomica -------------------------------

static const char alphanum[] = "0123456789""ABCDEFGHIJKLMNOPQRSTUVWXYZ""abcdefghijklmnopqrstuvwxyz";

//------------------------------------------------------------------------------------------------


WiFiClient client;                               //--> Inicializar a biblioteca do cliente wifi
PubSubClient mqttClient(client);                 //--> Inicializar a biblioteca pubsubclient e definir o broker MQTT thingspeak
const char* server = "mqtt.thingspeak.com";

unsigned long lastConnectionTime = 0;            //--> Variavel para ter controle da ultima conexão e intervalo de publicação dos dados*/
const unsigned long postingInterval = 600000;    //--> Postar a cada 10 minutos.

//=============================== void setup =============================================

void setup(){
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  Serial.begin(115200);
  dht.begin();                                   //--> Inicialização do sensor DHT
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledRed, LOW);
  WiFi.begin(ssid, pass);                        //--> Conexão com o roteador WiFi

  //------------------- Tentativa de conexão a rede WiFi -------------------------------

  while(WiFi.status() != WL_CONNECTED){ 
    delay(500);
    Serial.print(".");
    }
  Serial.println("Conectado ao WiFi: ");
  Serial.println(ssid);
  mqttClient.setServer(server, 1883);           //--> Seta as configurações de acessa ao Broker MQTT.

}

//============================================= void loop ========================================

void loop(){
  if(!mqttClient.connected()){
   reconnect();
  }
  mqttClient.loop();                                     //--> Chama a função loop continuamente para estabelecer a conexão do servidor

  if(millis() - lastConnectionTime > postingInterval){  //--> Caso tenha passado o tempo do intervalo, publicar na thingspeak
    mqttpublish();
  } 
}

 //------------------- Função para conectar com o MQTT Broker -------------------------------
 void reconnect(){                                      
  char clientID[9]; //identificação do cliente.

  /*Gerar clientID*/
  while(!mqttClient.connected()){
    Serial.print("Tentando conexão MQTT...");
    for(int i=0; i<8; i++){
      clientID[i] = alphanum[random(51)];
      }
  clientID[8] = '\0';

//------------------- Conectar ao Broker MQTT -------------------------------------------------

  if(mqttClient.connect(clientID, mqttUserName, mqttPass)){
    Serial.println("Conectado.");
    }else{
      Serial.print("Failed, rc=");
//------------------- Verificar o porque ocorreu a falha. -------------------------------------
  //Ver em: https://pubsubclient.knolleary.net/api.html#state explicação do código da falha.
      Serial.print(mqttClient.state());
      Serial.println("Tentar novamente em 5 segundos.");
      delay(5000);
      }
   }
 }
//------------------- Fim função conexão MQTT -------------------------------------------------

//------------------- Função para publicar os dados no canal da thingspeak --------------------

 void mqttpublish(){
  temp = dht.readTemperature();
  umid = dht.readHumidity();

  if(isnan(umid) || isnan(temp)){
    Serial.println("Erro de leitura DHT22!");
  }
  delay(100);
  Serial.print("Temperatura: ");
  Serial.println(temp);
  Serial.print("Umidade: " );
  Serial.println(umid);
    delay(2000);

  if (temp > 26.0){
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
  }else{
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
  }

//------------------- Criar String de dados para enviar a thingspeak --------------------

  String dados = String("field1=" + String(temp, 2) + "&field2=" + String(umid, 2));
  int tamanho = dados.length();
  char msgBuffer[tamanho];
  dados.toCharArray(msgBuffer,tamanho+1);
  Serial.println(msgBuffer);


//------------ Cria uma String de tópico e publica os dados no canal da thingspeak --------------------

  String topicString = "channels/" + String(channelID) + "/publish/"+String(writeAPIKey);
  tamanho = topicString.length();
  char topicBuffer[tamanho];
  topicString.toCharArray(topicBuffer, tamanho+1);

  mqttClient.publish(topicBuffer, msgBuffer);
  lastConnectionTime = millis();
                                                    
}
