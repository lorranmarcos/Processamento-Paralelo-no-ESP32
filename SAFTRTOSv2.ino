#include "header_saft3.h"
#include "esp_task_wdt.h"
#include <Arduino.h>

float V[Nz][Nx] = {0};
SemaphoreHandle_t semaforoV;
int tasksCompleted = 0;

void processamentoTask(void* parameter) {
  int z1 = (int)parameter;
  float SIG, Te, Kr, Tr;
  int indice_sample, t, x1, Nr = 0;

  for (x1 = 0; x1 < Nx; x1++) {
    SIG = 0;
    for (Nr = 0; Nr < R; Nr++) {
      Tr = sqrt(pow(x[x1] - xn[Nr + Ne - 1], 2) + z[z1]);
      Te = Tr + sqrt(pow(x[x1] - xn[Ne], 2) + z[z1]);
      t = floor(Te / resolucao);
      Kr = Te / resolucao - t;
      indice_sample = t - indice_ref - indice_min;
      if (indice_sample < lgth_sample) {
        SIG += matriz[indice_sample][Nr] + Kr * (matriz[indice_sample + 1][Nr] - matriz[indice_sample][Nr]);
      }
    }
    // Protege o acesso à matriz V usando o semáforo
    xSemaphoreTake(semaforoV, portMAX_DELAY);
    V[z1][x1] = SIG;
    xSemaphoreGive(semaforoV);
  }

  // Aumenta o contador de tarefas concluídas
  tasksCompleted++;

  vTaskDelete(NULL);
}

void printMatrix() {
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

  // Cria o semáforo
  semaforoV = xSemaphoreCreateMutex();

  unsigned long tempoInicio = millis();
  // Criação das tarefas
  for (int i = 0; i < Nz; i++) {
    xTaskCreate(processamentoTask, "processamentoTask", 1024, (void*)i, 1, NULL);
  }
  unsigned long tempoFinal = millis();
  unsigned long tempoExecucao = tempoFinal - tempoInicio;
    Serial.print("Tempo de execucao: ");
    Serial.print(tempoExecucao);
    Serial.println(" ms");
 
}

void loop() {}
