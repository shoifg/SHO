% Script para o cálculo da média por hora.

% Identificação do canal - ID do canal
readChannelID = XXXXXXX; 
% Número de identificação do campos a serem lidos os dados. 
tempFieldID = 1; % ID do campo da Temperatura.
umidFieldID = 2; % ID do campo da Umidade.


% INÍCIO - LEITURA DOS DADOS DO CANAL. 
% Chave de leitura dos dados do canal privado.
readAPIKey = 'XXXXXXXXXXXXXXXX'; 

% Paramentros da função(Identificação do canal, Identificação do campo, Faixa de tempo de dados, Chave de leitura)

% Dados de Temperatura.
temp = thingSpeakRead(readChannelID,'Fields',tempFieldID, 'NumMinutes', 50,'ReadKey',readAPIKey);
% Dados de Umidade.
umid = thingSpeakRead(readChannelID,'Fields', umidFieldID,'NumMinutes', 50,'ReadKey',readAPIKey);

% INÍCIO - CÁLCULO DAS MÉDIAS.
% Média da Temperatura.
mediaTemp = mean(temp);
% Média da Umidade.
mediaUmid = mean(umid);
% FIM - CÁLCULO DAS MÉDIAS.

% INÍCIO - OUTPUT
% Para verificar os dados a serem enviados - teste do código.
display(mediaTemp,'media temperatura');
display(mediaUmid,'media umidade'); 
% FIM - OUTPUT

% INÍCIO - ESCRITA DOS DADOS NO CANAL.
% Identificaçao da canal para escrita dos dados.
writeChannelID = XXXXXXX; 
% Chave de escrita no canal. 
writeAPIKey = 'XXXXXXXXXXXXXXXX'; 
% Função de escrita dos dados.
% Parametros(Identificação do canal, [Dados], [Campos para escrita], Chave de escrita).
thingSpeakWrite(writeChannelID , 'Fields', [3, 4], 'Values',[mediaTemp, mediaUmid], 'writekey',writeAPIKey);
