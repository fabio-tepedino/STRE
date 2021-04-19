/*
  Este exemplo mostra como definir threads, semaforos, 
  e como para threads
  Este exercicio eh igual ao exercicio3, modificado para ter mais uma thread
*/
#include <NilRTOS.h>

// O LED vermelho foi sera colocado no pino de numero 13
const uint8_t LED_PIN = 13;

// Adicionei um LED no pino 9, para verificar que a outra thread esta executando
int A9 = 9;
const uint8_t LED_PIN_BLUE = A9;

// Adicionei mais um LED, desta vez no pino 10, para verificar a execucao da thread 3
int A10 = 10;
const uint8_t LED_PIN_GREEN = A10;

// Este contador determina quando a thread 3 sera executada.
int counter = 0;


// Declaracao de dois semaforos com um contador inicial de valor zero.
SEMAPHORE_DECL(sem, 0);
SEMAPHORE_DECL(sem2, 0);
//-----------------------------------------------------------------------------
/*
  Aqui eh a Thread 1.
  Quando a thread 2 envia o sinal, ela desliga o LED Vermelho
  e liga o LED Azul
*/
// Declara um stack de 128 bytes de forma global.
NIL_WORKING_AREA(waThread1, 128);
// Funcao da thread 1
NIL_THREAD(Thread1, arg) {
  while (TRUE) {
    /* Executa a funcao e espera pelo sinal da Thread2
      Quando recebido,
      digitalWrite(), determina qual led deve apagar (LOW), e qual acender (HIGH).
    */
    nilSemWait(&sem);
    digitalWrite(LED_PIN, LOW);
    digitalWrite(LED_PIN_BLUE, HIGH);
    
  }
}
//-----------------------------------------------------------------------------
/*
  Thread 2, liga o LED Vermelho e sinaliza para a thread 1 que deve executar sua funcao.
  depois desliga o LED Azul
*/
// Declara um stack de 128 bytes de forma global.
NIL_WORKING_AREA(waThread2, 128);
// Funcao da thread 2
NIL_THREAD(Thread2, arg) {
  // Determina que o modo do pino 13 deve ser OUTPUT
  pinMode(LED_PIN, OUTPUT);
    while (TRUE) {
      /* 
        liga o LED vermelho
        espera 1000 milisegundos
        Manda um sinal a thread 1 para que seja executada.
        espera 1000 milisegundos
        desliga o led Azul
      */
      digitalWrite(LED_PIN, HIGH);
      nilThdSleepMilliseconds(1000);
      nilSemSignal(&sem);
      nilThdSleepMilliseconds(1000);
      digitalWrite(LED_PIN_BLUE, LOW);

      /*
        Adiciona-se uma unidade ao contador
        Caso seja igual a tres:
          sinaliza a thread3 para execucao
          zera o contador
          espera 1 segundo
      */
      counter = counter + 1;
      if(counter == 3)
      {
        nilSemSignal(&sem2);
        counter = 0;
        nilThdSleepMilliseconds(1000);
      }
    }
}
//-----------------------------------------------------------------------------
/*
* Thread 3, turn the GREEN LED on every 3 cicles of RED LED
*/
// Declare a stack with 128 bytes beyond context switch and interrupt needs.
NIL_WORKING_AREA(waThread3, 128);
// Declare the thread function for thread 2.
NIL_THREAD(Thread3, arg) {
while (TRUE) {
  // Wait for signal from thread 2.
  nilSemWait(&sem2); 
  // Turn LED on.
  digitalWrite(LED_PIN_GREEN, HIGH);
  // Sleep for 200 milliseconds.
  nilThdSleepMilliseconds(500);
  // Turn LED off.
  digitalWrite(LED_PIN_GREEN, LOW);
}
}
//-----------------------------------------------------------------------------
/*
  Aqui sao declaras as threads que serao usadas no programa.
  Suas prioridades sao determinadas por sua posicao na tabela.
  As de maior prioridade sao declaradas antes.

  Sao declaradas com argumento NULL. 
  Podem ter nome nulo, tambem, a fim de poupar memoria
*/
NIL_THREADS_TABLE_BEGIN()
NIL_THREADS_TABLE_ENTRY("thread1", Thread1, NULL, waThread1, sizeof(waThread1))
NIL_THREADS_TABLE_ENTRY("thread2", Thread2, NULL, waThread2, sizeof(waThread2))
NIL_THREADS_TABLE_ENTRY("thread3", Thread3, NULL, waThread3, sizeof(waThread3))
NIL_THREADS_TABLE_END()
//-----------------------------------------------------------------------------
void setup() {
  // nilSysBegin inicia a biblioteca NilRTOS
  // pinMode(), determina que os pinos sejam OUTPUT
  // Serial.begin(9600), determina que a comunicacao serial ocorrera a 9600 bits por segundo.
  nilSysBegin();
  pinMode(A9, OUTPUT);
  pinMode(A10, OUTPUT);
  Serial.begin(9600);
}
//-----------------------------------------------------------------------------
// Loop eh uma thread que nao realiza nada.
// Ela nao pode invocar nada do Kernel que possa mudar seu estado para "nao executavel"
void loop() {

}