// Durante a gravação do código, o Esp32 requer que seja pressionado o botão "boot" para a sua gravação


#include <DHT.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <SPI.h>

#define dhtType DHT22
  #define ledGreen 25
#define ledRed 26

int dhtPin = 4;
float temp = 0;
float umid = 0;

DHT dht(dhtPin, dhtType);

/*Configurações de rede e cliente WiFi*/
char ssid[] = "GlobalNet_Daniel"; //nome da rede.
char pass[] = "2cc42829"; //senha da rede.
char mqttUserName[] = "sho"; //nome de usuário do MQTT
char mqttPass[] = "SXVQDA8CTIUT3ES1"; //chave de acesso do MQTT.
char writeAPIKey[] = "DN6SJJDTOJUJIUVP"; //chave de acesso do canal thingspeak.
long channelID = 1447649; //Identificação do canal thingspeak.
/*Definir identificação de cliente randomica.*/
static const char alphanum[] = "0123456789""ABCDEFGHIJKLMNOPQRSTUVWXYZ""abcdefghijklmnopqrstuvwxyz";

/*Inicializar a biblioteca do cliente wifi*/
WiFiClient client;
/*Inicializar a biblioteca pubsubclient e definir o broker MQTT thingspeak*/
PubSubClient mqttClient(client);
const char* server = "mqtt.thingspeak.com";
/*Variavel para ter controle da ultima conexão e intervalo de publicação dos dados*/
unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 20000L; //Postar a cada 20 segundos.

void setup(){
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  Serial.begin(115200);
  dht.begin();
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledRed, LOW);
  WiFi.begin(ssid, pass); //Conectar a rede WiFi WPA/WPA2.
  //int status = WL_IDLE_STATUS; //Setar uma conexão wifi temporaria.
/*Tentativa de conexão a rede WiFi*/
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    }
  Serial.println("Conectado ao WiFi: ");
  Serial.println(ssid);
  mqttClient.setServer(server, 1883); //Seta as configurações de acessa ao Broker MQTT.

}

void loop(){
  if(!mqttClient.connected()){
   reconnect();
  }
  mqttClient.loop(); //Chama a função loop continuamente para estabelecer a conexão do servidor

/*Caso tenha passado o tempo do intervalo, publicar na thingspeak.*/
  if(millis() - lastConnectionTime > postingInterval){
    mqttpublish();
  } 
} // fim loop()

/*Função para conectar com o MQTT Broker.*/
 void reconnect(){
  char clientID[9]; //identificação do cliente.

  /*Gerar clientID*/
  while(!mqttClient.connected()){
    Serial.print("Tentando conexão MQTT...");
    for(int i=0; i<8; i++){
      clientID[i] = alphanum[random(51)];
      }
  clientID[8] = '\0';

  /*Conectar ao Broker MQTT*/
  if(mqttClient.connect(clientID, mqttUserName, mqttPass)){
    Serial.println("Conectado.");
    }else{
      Serial.print("Failed, rc=");
      /*Verificar o porque ocorreu a falha.*/
      //Ver em: https://pubsubclient.knolleary.net/api.html#state explicação do código da falha.
      Serial.print(mqttClient.state());
      Serial.println("Tentar novamente em 5 segundos.");
      delay(5000);
      }
   }
 } //fim função conexão MQTT


/*Função para publicar os dados no canal da thingspeak.*/
 void mqttpublish(){
  /*Leitura dos valores dos sensores.*/
  //DHT11
  temp = dht.readTemperature();
  umid = dht.readHumidity();

  if(isnan(umid) || isnan(temp)){
    Serial.println("Erro de leitura DHT11!");
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
  
  /*Criar String de dados para enviar a thingspeak.*/
  String dados = String("field1=" + String(temp, 2) + "&field2=" + String(umid, 2));
  int tamanho = dados.length();
  char msgBuffer[tamanho];
  dados.toCharArray(msgBuffer,tamanho+1);
  Serial.println(msgBuffer);

  /*Cria uma String de tópico e publica os dados no canal da thingspeak.*/
  String topicString = "channels/" + String(channelID) + "/publish/"+String(writeAPIKey);
  tamanho = topicString.length();
  char topicBuffer[tamanho];
  topicString.toCharArray(topicBuffer, tamanho+1);

  mqttClient.publish(topicBuffer, msgBuffer);
  lastConnectionTime = millis();
}
