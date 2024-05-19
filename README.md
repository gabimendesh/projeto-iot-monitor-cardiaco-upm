[[# Projeto de Monitoramento Cardíaco com protocolo MQTT

## Descrição

Este projeto de monitoramento cardíaco integra-se ao contexto do curso de Objetos Inteligentes Conectados, realizado na Universidade Presbiteriana Mackenzie. A sua finalidade é monitorar em tempo real os batimentos cardíacos, transmitindo esses dados para uma plataforma remota por meio do protocolo MQTT e visualização em uma página web. Essencialmente, trata-se de um projeto de IoT, onde dispositivos conectados e inteligentes são empregados para coleta e transmissão de informações relevantes.

## Funcionalidades

- Monitoramento contínuo dos batimentos cardíacos.
- Transmissão dos dados para uma plataforma remota via MQTT.
- Alerta sonoro quando o batimento cardíaco ultrapassa 150 BPM.

## Componentes Utilizados

### Módulo NodeMCU ESP8266

| Característica        | Descrição                                    |
|-----------------------|----------------------------------------------|
| Wireless Padrão       | 802.11 b/g/n                                  |
| Contém                | Antena embutida                               |
| Contém                | Conector micro-USB CH340                      |
| Modos de Operação     | STA/AP/STA+AP                                 |
| Suporta               | 5 conexões TCP/IP                             |
| Portas GPIO           | 11                                           |
| GPIO                  | PWM, I2C, SPI, etc                           |
| Tensão de Operação    | 3,3VDC                                       |
| Taxa de Transferência | 110-460 mbps                                 |
| Suporta               | Upgrade remoto de firmware                   |
| Contém                | Conversor analógico digital (ADC)            |

### Motor de Vibração

| Característica          | Descrição            |
|-------------------------|----------------------|
| Tensão de Operação      | 3.7 e 5.3V          |
| Corrente de Operação    | 60mA (90mA, no máximo) |
| Velocidade de Rotação   | 9000RPM              |

### Sensor de Pulso

| Característica          | Descrição            |
|-------------------------|----------------------|
| Tensão de Operação      | 3.3V - 5V            |
| Consumo de Energia      | Cerca de 4mA         |
| Compatibilidade         | ESP8266 ESP-01       |

### Demais componentes:

- Protoboard
- Jumpers Macho-Fêmea
- Micro cabo USB 2.0 modelo CMC-USB-30

# Documentação do Código

## Descrição

O código `monitoramento_cardiaco_mqtt.ino` implementa um sistema de monitoramento cardíaco utilizando o microcontrolador ESP8266 (NodeMCU) e o protocolo MQTT para transmitir os dados para uma plataforma remota. O sistema monitora os batimentos cardíacos em tempo real e envia os dados do BPM (batimentos por minuto) para um servidor MQTT.

## Configurações Iniciais

- **SSID e Senha da Rede Wi-Fi**: As variáveis `ssid` e `password` devem ser configuradas com o nome e senha da sua rede Wi-Fi, respectivamente.
- **Servidor MQTT**: A variável `mqtt_server` deve ser configurada com o endereço do servidor MQTT a ser utilizado.

## Configuração do Hardware

- **Sensor de Pulso (Sensor de Batimentos Cardíacos)**: Conecte o sensor de pulso ao NodeMCU da seguinte maneira:
  - Conecte o pino VCC do sensor ao pino 3V do NodeMCU.
  - Conecte o pino GND do sensor ao pino GND do NodeMCU.
  - Conecte o pino S ao pino analógico A0 do NodeMCU.

- **Buzzer (motor de vibração)**: Conecte o buzzer ao NodeMCU da seguinte maneira:
  - Conecte o pino positivo (VCC) do buzzer ao pino 3V do NodeMCU.
  - Conecte o pino negativo (GND) do buzzer ao pino GND do NodeMCU.
  - Conecte o pino de sinal do buzzer ao pino digital D5 (GPIO14) do NodeMCU.

## Funcionamento do Código

1. **Setup**: Inicializa a comunicação serial, conecta-se à rede Wi-Fi e configura o servidor MQTT.
2. **Reconexão MQTT**: Função para reconectar ao servidor MQTT em caso de desconexão.
3. **Publicação MQTT**: Função para publicar os dados do BPM no tópico MQTT.
4. **Loop**: Loop principal do programa, onde ocorre a leitura do sensor de pulso, cálculo do BPM, publicação dos dados MQTT e controle do buzzer.

## Detalhes de Implementação

- O código faz uso da biblioteca PubSubClient para comunicação MQTT.
- A leitura do sensor de pulso é realizada utilizando a função `analogRead()` e comparada com um limiar para detectar batimentos cardíacos.
- O tempo entre batimentos é calculado utilizando a função `millis()`.

## Considerações

- Certifique-se de que as bibliotecas necessárias (`ESP8266WiFi.h` e `PubSubClient.h`) estejam instaladas no seu ambiente de desenvolvimento.
- Ao configurar o servidor MQTT, verifique se o endereço e a porta estão corretos e se o servidor está disponível.

## Software Utilizado

- Arduino IDE: Para programação do NodeMCU ESP8266.
- HTML: Para a interface web de visualização dos dados.
- CSS: Para estilização da interface web.
- JavaScript: Para interatividade na interface web.
- Biblioteca MQTT.

## Como rodar a página web localmente

Para reproduzir este projeto, siga as etapas abaixo:

1. Clone este repositório para sua máquina local.
2. Monte o hardware de acordo com o protótipo.
3. Carregue o código-fonte no Arduino IDE.
4. Configure as credenciais do Wi-Fi.
5. Conecte a placa em uma fonte de energia utilizando um cabo micro USB 2.0 
6. Compile e envie o programa para a placa e observe os dados sendo transmitidos.
7. Para rodar a página web, entre na pasta com os arquivos ```html```, ```css```, ```javascript```, abra o terminal e rode ```npm install```, e depois execute o script ```npx http-server``` para instalar o servidor local, e para executar ```http-server```.
Após esses passos ao acessar a rota exibida no terminal a página web estará disponível:

<img src="https://ik.imagekit.io/q8vyo7feaitz/web_n3UnR4KBU.png?updatedAt=1716160106107" alt="Página web do monitoramento cardíado">

## Protótipo
<img src="https://ik.imagekit.io/q8vyo7feaitz/Captura%20de%20tela%202024-05-19%20193956_nelYW5Igv.png?updatedAt=1716158448195" alt="Sensor de Pulso">
](https://ik.imagekit.io/q8vyo7feaitz/web_n3UnR4KBU.png?updatedAt=1716160106107)https://ik.imagekit.io/q8vyo7feaitz/web_n3UnR4KBU.png?updatedAt=1716160106107](https://ik.imagekit.io/q8vyo7feaitz/web_n3UnR4KBU.png?updatedAt=1716160106107)
