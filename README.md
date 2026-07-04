# Project Eletronics - Use an LDR sensor to turn on an LED
Projeto de eletrônica para demonstrar o uso de um sensor para acender um LED.
É importante salientar, antes de tudo, que algumas partes básicas de montagem do circuito serão ocultadas aqui, como funcionamento das trilhas de energia na protoboard, entre outras coisas.
Caso você não saiba ou não entenda o que foi feito, recomendo consultar o Projeto do [Semáforo](https://github.com/andreigomess/Basic-Project-Eletronics-Traffic-Light) que é mais básico e possui explicações básicas mais detalhadas.

# Ideia Central
A ideia central é utilizar um fotorresistor, de sigla LDR (do inglês Light Dependent Resistor) para acender um LED. Utilizando um Arduino Uno, ele receberá informações do sensor e com base nelas enviará um sinal para o LED ligar ou desligar.
As imagens serão novamente do [Thinkercad](https://www.tinkercad.com/dashboard), um simulador de projetos eletrônicos. É bastante útil também para ajudar a montar o projeto fisicamente, mitigando qualquer erro de conexão ou na montagem no circuito que possa ocorrer e consequentemente danificar algum componente.

## Componenetes de Software necessários:
- [IDE Arduino](https://www.arduino.cc/en/software/)

## Componentes de Hardware necessários:
- 1 Microcontrolador - Nesse caso, será usado o Arduino Uno
- 1 LED de qualquer cor - Nesse caso, usarei um branco
- 2 Resistores - sendo 1 de 10K Ohms e outro de 1,5K Ohms
- 1 Protoboard
- Jumpers Macho-Macho

# Hardware: alimentação do LDR e do LED
No [Thinkercad](https://www.tinkercad.com/dashboard), será demonstrado cada etapa da construção do circuito.

## 1. Energizando o LDR
- Primeiramente, pegue o Arduino e a Protoboard. Ligue o GND na trilha negativa e o 5V na trilha positiva. Dessa forma, teremos corrente elétrica, pois o GND é a referência 0V.
- Ligue uma das pernas do LDR ao GND e a outra ao 5V através de um Resistor de 10K Ohms. Para alterar o valor do Resistor no [Thinkercad](https://www.tinkercad.com/dashboard), basta clicar sobre ele e alterar o valor para 10 (verifique se está em K Ohms).
- O LDR não possui polaridade, ou seja, não é preciso tomar o cuidado de conectar o GND e o 5V cada um em uma perna específica.

![ligarLDR](Imagens/ligar_LDR.png)

Pronto, agora nosso LDR está energizado corretamente. Há um motivo específico para o uso de um Resistor de 10K Ohms, que será explicado no próximo tópico.

## 2. Captando os dados do LDR
- O LDR lerá a tensão com base na quantidade de luz (fótons) do ambiente. Quando maior a quantidade de luz, maior a resistência, quanto menor, menor será a resistência do LDR. Portanto, quanto menos luz, maior o valor da tensão e isso é o que ativará o LED.
- A leitura ta tensão não é digital, ou seja 0 ou 1. Ela é analógica, e para isso será usado uma das portas analógicas do Arduino.
- É aqui que entra também o uso do Resistor de 10K Ohms. O Resistor de 10K é o ideal aqui pois ...