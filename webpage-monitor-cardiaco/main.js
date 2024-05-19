 // Configurações do broker MQTT
 var broker = "wss://mqtt.eclipseprojects.io:443/mqtt";
 var port = 443;
 var clientId = "web-client-" + parseInt(Math.random() * 100000, 10);

 // Cria um cliente MQTT
 var client = new Paho.MQTT.Client(broker, clientId);

 // Função de callback para quando a conexão é estabelecida
 client.onConnectionLost = function (responseObject) {
   if (responseObject.errorCode !== 0) {
     console.log("Conexão perdida: " + responseObject.errorMessage);
   }
 };

 // Função de callback para quando uma mensagem é recebida
 client.onMessageArrived = function (message) {
   updateDisplay(message.payloadString);
   console.log("Mensagem recebida: " + message.payloadString);
   document.getElementById("bpm").innerText =
     "BPM: " + message.payloadString;
     
 };

 // Conecta-se ao broker MQTT
 client.connect({
   onSuccess: function () {
     console.log("Conexão estabelecida com sucesso");
     // Subscreve ao tópico onde o BPM está sendo publicado
     client.subscribe("esp.mackenzie/sensorcardiaco");
   },
   onFailure: function (errorMessage) {
     console.log("Falha na conexão: " + errorMessage.errorMessage);
   },
   useSSL: true,
 });

 function updateDisplay(bpm) {
  const pulseStatusElement = document.getElementById('monitor-cardiaco-pulso-status');
  const recommendationElement = document.getElementById('monitor-cardiaco-sugestao');

  let pulseStatus = '';
  let recommendation = '';
  let recommendationClass = '';

    if (bpm > 240) {
      pulseStatus = 'Muito Alto ⚠️';
      recommendation = 'Por favor, procure atendimento médico imediatamente.';
      recommendationClass = 'high';
    } else if (bpm > 90) {
        pulseStatus = 'Alto (em repouso) ⚠️';
        recommendation = 'Por favor, se esse é seu batimento em descanso monitore seu pulso, respire fundo e descanse.';
        recommendationClass = 'high';
    } else if (bpm >= 50) {
        pulseStatus = 'Normal';
        recommendation = 'Seu pulso está normal. Continue monitorando regularmente.';
        recommendationClass = 'normal';
    } else if (bpm >= 30) {
        pulseStatus = 'Baixo ⚠️';
        recommendation = 'Seu pulso está baixo, por favor, procure atendimento médico imediatamente.';
        recommendationClass = 'low';
    } else {
        pulseStatus = 'Muito Baixo ⚠️';
        recommendation = 'Por favor, procure atendimento médico imediatamente.';
        recommendationClass = 'low';
    }

  pulseStatusElement.textContent = `Status: ${pulseStatus}`;
  recommendationElement.textContent = `Recomendação: ${recommendation}`;
  recommendationElement.className = `recommendation ${recommendationClass}`;
}