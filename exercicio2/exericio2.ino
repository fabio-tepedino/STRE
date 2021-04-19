/*
    DigitalReadSerial
    Este programa recebe o input do arduino na porta de numero 2, e mostra o resultado
    no monitor.
    This example code is in the public domain.
*/
// esta variavel tem o valor do pino que sera utilizado para input.
int pushButton = 2;
// A funcao setup eh executada no inicio, e determina algumas variaveis.
void setup() {
// Serial.begin(9600), determina que a comunicacao serial ocorrera a 9600 bits por segundo.
Serial.begin(9600);
// make the pushbutton's pin an input:
// pinMode determina que o pino, neste caso o 2, sera usado para INPUT
pinMode(pushButton, INPUT);
}
// O loop sera executado enquanto o arduino estiver ligado.
void loop() {
// digitalRead, determina que o arduino deve ler o INPUT no pino 2
// Serial.printIn(), mostra no terminal o resultado do pino.
// delay(1), foi colocado para dar um delay de tempo, e estabilizar o processo.
int buttonState = digitalRead(pushButton);
Serial.println(buttonState);
delay(1);
}
