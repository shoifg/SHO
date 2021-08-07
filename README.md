# MONITORAMENTO INTELIGENTE DA QUALIDADE DO AR PARA AMBIENTES DE TRABALHO REMOTO
<p align="justify">
Em uma empresa, vários fatores são verificados e monitorados para manter a saúde ocupacional dos funcionários. Quando o ambiente de trabalho é alterado para o trabalho remoto, ou seja, feito na casa do funcionário, torna-se complexo para a empresa ter conhecimento se as condições ambientes previstas em legislação estão sendo seguidas.  Em virtude disso, é necessário que haja um sistema que possa realizar o monitoramento adequado nesses ambientes. Desse modo, este trabalho apresenta o sistema SHO (Smart Home Office) que consiste em uma solução IoT para o monitoramento da qualidade do ar em ambientes de trabalho remoto.<p/>    

<p align="justify">
Neste projeto, o monitoramente dos dados coletados pelo sensor de temperatura e umidade foram enviados para a plataforma ThingSpeak<sup>TM</sup> para a visualização em tempo real e para uma planilha no Google Sheets, que servirá como um banco de dados dos parâmetros lidos pelo sensor.</p> 


## HARDWARE
<p align="justify">
Para a montagem do protótipo foram utilizados o NodeMcu ESP32, o sensor de temperatura e umidade DHT22, LEDs, resistores de 68 Ohm e uma fonte de alimentação 5 VDC, mostrados na figura 1.
</p>

![Componentes utilizados](https://user-images.githubusercontent.com/88517401/128585415-306f60da-9e10-45a5-a162-0ea447117c0d.PNG)
<p align="center">
 Figura 1: Materiais utilizados
</p>
<p align="justify">Na tabela 1 são mostrados os componentes e as quantidades dos materiais utilizados.<p/>

|Item  |Componente                |  Quantidade|
|:---: |                       ---|       :---:|
|1     |NodeMcu Esp32             |           1|
|2     |DHT22                     |           1|
|3     |Led 3mm (verde e vermelho)|           2|
|4     |Resistores 68 Ohm         |           2|
|5     |Resistor 1k Ohm           |           1|

<p align="justify">
Os componentes foram conectados por meio de jumpers tipo macho em duas protoboards, pois o tamanho da placa NodeMCU ESP32 não permite que seja utilizada somente uma protoboard (mesmo que com muitos furos). O diagrama esquemático e protótipo montado são mostrados nas figuras 2 e 3.
<p/>

![esquemático](https://user-images.githubusercontent.com/88517401/128602926-fa6e880e-bf4c-407d-a5bf-7d18de1bc702.png)

<p align="center">
 Figura 2: Esquemático
</p>

<p>     
<p/>

![prototipo](https://user-images.githubusercontent.com/88517401/128603050-fe82b4a6-b5f8-4276-b5d7-8124fb128bee.jpeg)

<p align="center">
 Figura 3: Protótipo montado
</p>

<p align="justify">
Nos tópicos a seguir são mostradas as etapas para a comunicação e envio de dados via protocolo MQTT para a plataforma ThingSpeak<sup>TM</sup> e para a planilha no Google Sheets.
</p>

## CONEXÃO VIA PROTOCOLO MQTT
<p align="justify"> A conexão com a plataforma ThingSpeak<sup>TM</sup> via protocolo MQTT, foi realizada de acordo com o fluxograma mostrado na figura 4.</p>

![Fluxograma MQTT](https://user-images.githubusercontent.com/88517401/128608905-441cc8c4-8981-4cb5-a769-819e83ef926d.png)


<p align="center">
 Figura 4: Fluxograma de conexão
</p>

<p align="justify"> O código desenvolvido está...... (REFERENCIAR o Código).</p>



## ENVIO DE DADOS PARA O GOOGLE SHEETS
---
