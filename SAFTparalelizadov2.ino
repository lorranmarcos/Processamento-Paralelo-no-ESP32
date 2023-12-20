#include "header_saft3.h"
#include <Arduino.h>
//#include <FreeRTOS.h>

float V[Nz][Nx] = {0};

// Semáforo para controlar o acesso à matriz V
SemaphoreHandle_t vSemaphore;

// Função da tarefa para o núcleo 0
void processamentoCore0(void* parameTe0r) {
    int z1 = (int)parameTe0r;
    float SIG0, Te0, Kr0, Tr0;
    int  t0, x1, Nr0 = 0, indice_sample0;

    for (int x1 = 0; x1 < Nx; x1++) {
      SIG0 = 0;
      for (Nr0 = 0; Nr0 < R; Nr0++) {
        Tr0 = sqrt(pow(x[x1] - xn[Nr0 + Ne - 1], 2) + z[z1]);
        Te0 = Tr0 + sqrt(pow(x[x1] - xn[Ne], 2) + z[z1]);
        t0 = round(Te0 / resolucao);
        Kr0 = Te0 / resolucao - t0;
        indice_sample0 = t0 - indice_ref - indice_min;
        if (indice_sample0 < lgth_sample) {
          SIG0 = SIG0 + (matriz[indice_sample0][Nr0] + Kr0 * (matriz[indice_sample0 + 1][Nr0] - matriz[indice_sample0][Nr0]));;
        }
      }

      // Adquire o semáforo anTe0s de acessar a matriz V
      xSemaphoreTake(vSemaphore, portMAX_DELAY);
      V[z1][x1] = SIG0;
      // Libera o semáforo após acessar a matriz V
      xSemaphoreGive(vSemaphore);
    }
  
  vTaskDelete(NULL);
}

// Função da tarefa para o núcleo 1 do ESP32
void processamentoCore1(void* parameter) {
    int z1 = (int)parameter;
    float SIG, Te, Kr, Tr;
    int t, x1, Nr = 0, indice_sample;

    for (int x1 = 0; x1 < Nx; x1++) {
      SIG = 0;
      for (Nr = 0; Nr < R; Nr++) {
        Tr = sqrt(pow(x[x1] - xn[Nr + Ne - 1], 2) + z[z1]);
        Te = Tr + sqrt(pow(x[x1] - xn[Ne], 2) + z[z1]);
        t = round(Te / resolucao);
        Kr = Te / resolucao - t;
        indice_sample = t - indice_ref - indice_min;
        if (indice_sample < lgth_sample) {
          SIG = SIG + (matriz[indice_sample][Nr] + Kr * (matriz[indice_sample + 1][Nr] - matriz[indice_sample][Nr]));;
        }
      }

      // Adquire o semáforo antes de acessar a matriz V
      xSemaphoreTake(vSemaphore, portMAX_DELAY);
      V[z1][x1] = SIG;
      // Libera o semáforo após acessar a matriz V
      xSemaphoreGive(vSemaphore);
    }
  

  vTaskDelete(NULL);
}

void printMatrix() {//função de impressao de matriz pela serial
  for (int zz1 = 0; zz1 < Nz; zz1++) {
    for (int xx1 = 0; xx1 < Nx; xx1++) {
      Serial.print(V[zz1][xx1], 5);
      Serial.print(" ");
    }
    Serial.println();
  }
}

void setup() {
  Serial.begin(115200);

  // Criação do semáforo
  vSemaphore = xSemaphoreCreateMutex();
  unsigned long tempoInicio = millis();
  // Criação das tarefas
  int k=0,i=0;
  while (i < nz) {
    xTaskCreatePinnedToCore(processamentoCore0, "processamentoCore0", 1024, (void*)i, 1, NULL, 0);
    i++;
    xTaskCreatePinnedToCore(processamentoCore1, "processamentoCore1", 1024, (void*)i, 1, NULL, 1);
    i++;
  }
  unsigned long tempoFinal = millis();

  unsigned long tempoExecucao = tempoFinal - tempoInicio;

    Serial.print("Tempo de execucao: ");
    Serial.print(tempoExecucao);
    Serial.println(" ms");
}
void loop() {

}
