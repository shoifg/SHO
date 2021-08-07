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

 O [código desenvolvido](https://github.com/shoifg/SHO/blob/main/sho_mqtt/sho_mqtt.ino) pode ser consultado e baixado em nosso repositório.


## ENVIO DE DADOS PARA O GOOGLE SHEETS
<p align="justify"> A conexão com a planilha Google Sheets, foi realizada de acordo com o fluxograma mostrado na figuras 5. Para melhorar o entendimento, a implementação do script na planilha será mostrado passo-a-passo a seguira.</p>


## IMPLEMENTAÇÃO DO SCRIPT NA PLANILHA ON-LINE

1. Criar uma nova planilha no Google Sheet, com usuário e senha válidos. Recomenda-se renomear a planilha com um nome que seja relacionado com o objeto de trabalho. exemplo: *Banco de dados DHT22*;
1. Nomear os cabeçalhos das colunas A, B, C e D com os nomes Date, Time, Temperature (ºC) e Humidity (%) respectivamente;
2. Clicar em **_Ferramentas_** e a seguir em **_script editor_**. Recomenda-se usar o editor de *script legado* e renomear a planilha com um nome que seja relacionado com o objeto de trabalho;
3. Copiar todo o código fonte do arquivo ["Código do Script Google sheet.txt"](https://github.com/shoifg/SHO/blob/main/Script/C%C3%B3digo%20do%20Script%20Google%20sheet.txt) para o *script editor*. O código pode ser consultado e copiado de nosso repositório;
4. No código dentro do *script editor*, copiar o **_Spreadsheet ID_** da planilha que servirá como banco de dados, para o interior das aspas em frente à variável "**_var sheet_id_**". O **_Spreadsheet ID_** e o local para onde deve copiado, são mostrados nas figuras 6 e 7 a seguir.

![Spreadsheet ID numero](https://user-images.githubusercontent.com/88517401/128616174-716170c1-3f6e-4877-8d1b-7025bfc507a0.PNG)

<p align="center">
 Figura 6: Spreadsheet ID
</p>

![Spreadsheet ID](https://user-images.githubusercontent.com/88517401/128616109-d8a318cd-2d50-4c96-914b-d5433124a413.PNG)


<p align="center">
Figura 7: Local para inserção do Spreadsheet ID
</p>

5. Para que o horário seja expresso corretamente, substituir a expressão **_Asia/Jakarta_** por **_America/Sao_Paulo_**.
6. Clicar em **_Publicar_** e em **_Implantar como aplicativo da web_**. Na próxima janela, no menu suspenso da opção **_Who has access to the app:_** escolha a opção **_Anyone, even anonymous_**, conforme mostra a figura 8.
7. Neste momento o usuários estará autorizando que qualquer um poderá ter acesso ao aplicativo, mesmo que anônimo.

![deploy as web](https://user-images.githubusercontent.com/88517401/128615963-eb27574f-d987-4dc1-8bb9-84b637267fa2.PNG)

<p align="center">
Figura 8: Autorização para acesso
</p>

8. Nas janelas a seguir, autorizar que o aplicativo tenha acesso à planilha criada. Quando a janela apresentada na figura 9 aparecer, copie o link do aplicativo na web (**_Current web app URL_**). Este link servirá para testar e para ser inserido no código do microcontrolador para o envio dos dados do sensor para a planilha.

![current app url](https://user-images.githubusercontent.com/88517401/128616033-9df22921-b6fe-43d5-9e2c-103f64bff629.PNG)

 
<p align="center">
Figura 9: Link do aplicativo na web
</p>

9. Para testar o envio de dados para a planilha, cole o link copiado na janela do navegador, seguido pela expressão **_?temperature=100&humidity=20_**. Conferir se a planilha recebeu os dados com sucesso. Caso afirmativo, a planilha terá aspecto similar com aquele mostrado na figura 10.
 
 ![planilha tutorial](https://user-images.githubusercontent.com/88517401/128615994-8856f331-8e17-46b5-bf20-edbb3de7141d.PNG)

 
 <p align="center">
 Figura 10: Envio de dados para a planilha no Google Sheet
</p>

10. 



COLOCAR FLUXOGRAMA AQUI

<p align="center">
 Figura 5: Fluxograma de conexão
</p>

 O [código desenvolvido](https://github.com/shoifg/SHO/blob/main/sho_gs/sho_gs.ino) pode ser consultado e baixado em nosso repositório.
