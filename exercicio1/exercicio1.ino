/*
Blink

Este programa faz um LED piscar a cada 1 segundo, intermitentemente.
O Arduino Uno possui um LED em sua placa, ligado ao pino 13.
A variavel LED_BUILTIN eh usada para tal pino.

This example code is in the public domain.
modified 8 May 2014
by Scott Fitzgerald
modified 2 Sep 2016
by Arturo Guadalupi
modified 8 Sep 2016
by Colby Newman
*/
// A funcao de setup determina para o arduino o que deve ser executado antes do programa
void setup() {
// pinMode determina que tipo de modo determinado pino tera, sendo Outup ou Input
pinMode(LED_BUILTIN, OUTPUT);
}
// Este loop eh o programa em si, que fara o LED piscar
void loop() {
    /* 
        digitalWrite, determina que o pino possui forma digital de transferir informacoes
        HIGH e LOW, sao as voltagens colocadas no pino quando a linha for executada.
        delay(1000), determina que o arduino espere 1000 mili segundos
    */
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}
