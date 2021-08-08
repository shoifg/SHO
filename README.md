# MONITORAMENTO INTELIGENTE DA QUALIDADE DO AR PARA AMBIENTES DE TRABALHO REMOTO
<p align="justify">
Em uma empresa, vários fatores são verificados e monitorados para manter a saúde ocupacional dos funcionários. Quando o ambiente de trabalho é alterado para o trabalho remoto, ou seja, feito na casa do funcionário, torna-se complexo para a empresa ter conhecimento se as condições ambientes previstas em legislação estão sendo seguidas.  Em virtude disso, é necessário que haja um sistema que possa realizar o monitoramento adequado nesses ambientes. Desse modo, este trabalho apresenta o sistema SHO (Smart Home Office) que consiste em uma solução IoT para o monitoramento da qualidade do ar em ambientes de trabalho remoto.</p>    

<p align="justify">
Neste projeto, o monitoramente dos dados coletados pelo sensor de temperatura e umidade foram enviados para a plataforma ThingSpeak<sup>TM</sup> para a visualização em tempo real e para uma planilha no Google Sheets, que servirá como um banco de dados dos parâmetros lidos pelo sensor.</p> 


## ÍNDICE
- [Hardware](https://github.com/shoifg/SHO#hardware).
- [Conexão via protocolo MQTT](https://github.com/shoifg/SHO/blob/main/README.md#conex%C3%A3o-via-protocolo-mqtt).
- [Envio para a planilha Google Sheets](https://github.com/shoifg/SHO#envio-de-dados-para-o-google-sheets).
  - [Implementação do script na planilha on-line](https://github.com/shoifg/SHO#implementa%C3%A7%C3%A3o-do-script-na-planilha-on-line).
  - [Adaptação do código do NodeMcu ESP32](https://github.com/shoifg/SHO#adapta%C3%A7%C3%A3o-do-c%C3%B3digo-do-nodemcu-esp32).


## HARDWARE
<p align="justify">
Para a montagem do protótipo foram utilizados o NodeMcu ESP32, o sensor de temperatura e umidade DHT22, LEDs, resistores de 68 Ohm e uma fonte de alimentação 5 VDC, mostrados na figura 1.
</p>

![figura componentes](https://user-images.githubusercontent.com/88517401/128616376-e6f6b14f-4ca7-4f86-a2b5-91b3ea90c40c.PNG)

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

![esp32_bb](https://user-images.githubusercontent.com/88517401/128616361-a142b168-5318-4c53-a0eb-b0384aa3abe8.png)

<p align="center">
 Figura 2: Esquemático
</p>

<p>     
<p/>

![prototipo](https://user-images.githubusercontent.com/88517401/128616401-980f2ef7-e0a2-4461-b00a-0912ce7ba574.jpeg)

<p align="center">
 Figura 3: Protótipo montado
</p>

<p align="justify">
Nos tópicos a seguir são mostradas as etapas para a comunicação e envio de dados via protocolo MQTT para a plataforma ThingSpeak<sup>TM</sup> e para a planilha no Google Sheets.
</p>

## CONEXÃO VIA PROTOCOLO MQTT
<p align="justify"> A conexão com a plataforma ThingSpeak<sup>TM</sup> via protocolo MQTT, foi realizada de acordo com o fluxograma mostrado na figura 4.</p>

![Fluxograma MQTT (1)](https://user-images.githubusercontent.com/88517401/128641297-568a4e6f-4ae4-4ead-9153-9196aa8345c4.png)

<p align="center">
 Figura 4: Fluxograma de conexão com a plataforma ThingSpeak<sup>TM</sup>
</p>

 O [código desenvolvido](https://github.com/shoifg/SHO/blob/main/sho_mqtt/sho_mqtt.ino) pode ser consultado e baixado em nosso repositório.


## ENVIO DE DADOS PARA O GOOGLE SHEETS
<p align="justify"> A conexão com a planilha Google Sheets, foi realizada de acordo com o fluxograma mostrado na figuras 5. Para melhorar o entendimento, a implementação do script na planilha será mostrado passo-a-passo a seguir.</p>

![Fluxograma GS (1)](https://user-images.githubusercontent.com/88517401/128641336-a7b0d9b9-3f0d-4f6d-83ee-870ad4c31ab4.png)

<p align="center">
 Figura 5: Fluxograma de conexão com a planilha Google Sheets
</p>


### IMPLEMENTAÇÃO DO SCRIPT NA PLANILHA ON-LINE

1. Criar uma nova planilha no Google Sheet, com usuário e senha válidos. Recomenda-se renomear a planilha com um nome que seja relacionado com o objeto de trabalho. exemplo: *Banco de dados DHT22*;
1. Nomear os cabeçalhos das colunas A, B, C e D com os nomes Data, Hora, Temperatura (ºC) e Umidade (%) respectivamente;
2. Clicar em **_Ferramentas_** e a seguir em **_script editor_**. Recomenda-se usar o editor de *script legado* e renomear o script com um nome que seja relacionado com o objeto de trabalho;
3. Copiar todo o código fonte do arquivo ["Código do Script Google sheet.txt"](https://github.com/shoifg/SHO/blob/main/Script/C%C3%B3digo%20do%20Script%20Google%20sheet.txt) para o *script editor*. O código pode ser consultado e copiado de nosso repositório;
4. No código dentro do *script editor*, copiar o **_Spreadsheet ID_** da planilha que servirá como banco de dados, para o interior das aspas em frente à variável "**_var sheet_id_**". O **_Spreadsheet ID_** e o local para onde deve ser copiado, são mostrados nas figuras 6 e 7 a seguir.

![image](https://user-images.githubusercontent.com/88517401/128641691-e3fbb3ae-f0d3-4de4-8c5c-4a16c077de32.png)

<p align="center">
 Figura 6: Spreadsheet ID
</p>

![image](https://user-images.githubusercontent.com/88517401/128641619-2e89fc8a-6c74-44ac-a313-284f827f7ceb.png)


<p align="center">
Figura 7: Local para inserção do Spreadsheet ID
</p>

5. Para que o horário seja expresso corretamente, substituir a expressão **_Asia/Jakarta_** por **_America/Sao_Paulo_**.
6. Clicar em **_Publicar_** e em **_Implantar como aplicativo da web_**. Na próxima janela, no menu suspenso da opção **_Who has access to the app:_** escolha a opção **_Anyone, even anonymous_**, conforme mostra a figura 8. Neste momento o usuários estará autorizando que qualquer um poderá ter acesso ao aplicativo, mesmo que anônimo.

![deploy as web](https://user-images.githubusercontent.com/88517401/128615963-eb27574f-d987-4dc1-8bb9-84b637267fa2.PNG)

<p align="center">
Figura 8: Autorização para acesso
</p>

9. Nas janelas a seguir, autorizar que o aplicativo tenha acesso à planilha criada. Quando a janela apresentada na figura 9 aparecer, copie o link do aplicativo na web (**_Current web app URL_**). Este link servirá para testar e para ser inserido no código do microcontrolador para o envio dos dados do sensor para a planilha.

![current app url](https://user-images.githubusercontent.com/88517401/128616033-9df22921-b6fe-43d5-9e2c-103f64bff629.PNG)

 
<p align="center">
Figura 9: Link do aplicativo na web
</p>

10. Para testar o envio de dados para a planilha, cole o link copiado na janela do navegador, seguido pela expressão **_?temperature=100&humidity=20_**. Conferir se a planilha recebeu os dados com sucesso. Caso afirmativo, a planilha terá aspecto similar com aquele mostrado na figura 10.
 
 ![planilha tutorial](https://user-images.githubusercontent.com/88517401/128615994-8856f331-8e17-46b5-bf20-edbb3de7141d.PNG)

 
 <p align="center">
 Figura 10: Envio de dados para a planilha no Google Sheet
</p>

11. Para que qualquer usuário tenha acesso à visualização dos dados da planilha, é necessário alterar as opções de compartilhamento da planilha, no canto superior direito da tela, clicando em "**_compartilhar_**" e concedendo as permissões necessárias.

### ADAPTAÇÃO DO CÓDIGO DO NODEMCU ESP32

1. Inserir o nome da rede na qual se deseja ter conexão e a respectiva senha. Inserir entre as aspas da variável **_String GAS_ID_** o **_spreadsheet script ID_**. O trecho de código a seguir mostra o local de inserção do **_spreadsheet script ID_**.
```
const char* host = "script.google.com";
const int httpsPort = 443;
//-------------------------------------------------------------------------------------------------------------------------
WiFiClientSecure client;                                                    //--> Criação do objeto WiFiClientSecure.                                                       
String GAS_ID = "AKfycbyQgTKDPBFyKlVmm2LO16C-bFvL4H26OPiW1x4QUYSK8DXvyls";  //--> spreadsheet script ID
```
***
IMPORTANTE:

O **_spreadsheet script ID_** pode ser extraído do **_Current web app URL_** obtido no item 9. Se, por exemplo, o **_Current web app URL_** for:

https://script.google.com/macros/s/AKfycbyQgTKDPBFyKlVmm2LO16C-bFvL4H26OPiW1x4QUYSK8DXvyls/exec

O **_spreadsheet script ID_** será o código entre **/s/** e **/exec**, ou seja: **AKfycbyQgTKDPBFyKlVmm2LO16C-bFvL4H26OPiW1x4QUYSK8DXvyls**.
***
Um [video explicativo](https://github.com/shoifg/SHO/blob/main/NodeMCU%20ESP8266%20%2B%20Google%20Spreadsheet%20_%20NodeMCU%20Sends%20Data%20to%20Google%20Sheets%20Directly%20(No%20Third%20Party).mp4) de apoio pode ser consultado no link: https://www.youtube.com/watch?v=okNECYf2xlY, creditado ao canal [Uteh Str](https://www.youtube.com/channel/UCk8rZ8lhAH4H-75tQ7Ljc1A).


 O [código desenvolvido](https://github.com/shoifg/SHO/blob/main/sho_gs/sho_gs.ino) pode ser consultado e baixado em nosso repositório.
 
## RESULTADOS
Neste projeto, os dados provenientes das leituras do sensor DHT22 foram disponibilizados em um site construído através do serviço *__Google Sites__*. Os dados podem ser visualizados graficamente e em tempo real. A figura 11 mostra uma captura de tela do site construído até o momento.

![image](https://user-images.githubusercontent.com/88517401/128644666-0d58e9b4-94be-40f8-88cd-00c843685945.png)

 <p align="center">
 Figura 11: Visualização da leitura do sensor no Site
 </p>

Além do site, os dados também podem ser visualizados através de canais na plataforma ThingSpeak<sup>TM</sup>, conforme mostra a figura 12.
<p>
</p>

![image](https://user-images.githubusercontent.com/88517401/128644882-84900c31-79dd-460b-a359-3a4887f0159f.png)


 <p align="center">
 Figura 12: Visualização da leitura na plataforma ThingSpeak<sup>TM</sup>
</p>

<p align="justify">
A construção do Site não será detalhada neste tutorial, pois pode ser facilmente realizada através da plataforma Google Sites. O principal detalhe é o código a ser incorporado no site para a leitura dos sensores, podendo ser feita através do seguinte código:
</p>
***
Gráfico:
```
<iframe width="450" height="260" style="border: 0px solid #cccccc;" src="https://thingspeak.com/channels/CHANNEL_ID/charts/2?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&type=line&update=15"></iframe>
```
**IMPORTANTE:** Substituir "**Channel_ID** pelo número do canal, obtido na platadorma ThingSpeak. 
***

Última leitura do sensor (tempo real):
```
	<!DOCTYPE html>
	<html lang="en">
	<head>
	<title>JavaScript - read JSON from URL</title>
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.1/jquery.min.js"></script>
	 <script>
		   
	 $(function() {
	   setTime();
	   function setTime() {
			var date = new Date().getTime();
			  //var string = "Timestamp: "+date;
			
			//Adicionar cdg para atualizar
			fetch('https://api.thingspeak.com/channels/CHANNEL_ID/feeds/last.json?api_key=AT194Y84NJE00KCP')
			.then(response => response.json())
			.then(data => {
					
			//umidade		
			if (data.field2 <= 65) {
			document.getElementById("umidade").style.color = '#08298A';
			document.getElementById("umidade").innerHTML = Math.trunc(data.field2)+"%";
			}
			if (data.field2 >= 66) {
			document.getElementById("umidade").style.color = 'red';
			document.getElementById("umidade").innerHTML = Math.trunc(data.field2)+"%";
			}

			})
			.catch(error => console.error(error))
			
				
			//fim cdg atualizar

			setTimeout(setTime, 3000);
			  $('#setTime').html(string);
			}
		});
		
	</script>

	<body>

	<div class="div-float">
		<h1 id="umidade" style="text-align:center"></h1>
		<p  class="div-texto" style="text-align:center">Umidade Relativa</p>		
		<p style="text-align:center">Faixa Recomendável: 40% à 65%</p>

	</div>
	</body>

	<style rel="stylesheet" type="text/css">


	.div-texto{
	  font-size:20px;
	  color: #08298A;
}

	.div-clear {
		clear: center;
	}

	</style>
	</html>
```
 **IMPORTANTE:** Substituir **Chanel_ID** pelo número do canal, obtido na platadorma ThingSpeak. O campo **api_key** (Read) também deve ser atualizado, obtido na mesma plataforma. 
***
