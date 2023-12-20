#include "header_saft1.h" //carregamento da matriz de dados para as resoluções de baixa, media, alta resolução.
#include <Arduino.h>



void setup() {
  Serial.begin(115200);
  // Criação da matriz V e processamento de sinais
  float V[Nz][Nx] = {0}; // imagem final
  float SIG, Te, Kr, Tr;
  int t,z1,x1,Nr=0, indice_sample;
    
 unsigned long tempoInicio = millis();
  // realiza o processamento de sinais para a formação da imagem
  for (z1 = 0; z1 < Nz; z1++) {
    for (x1 = 0; x1 < Nx; x1++) {
      SIG = 0;
      for (Nr = 0; Nr < R; Nr++) {
        Tr = sqrt(pow(x[x1]-xn[Nr+Ne-1], 2) + z[z1]);
        Te = Tr + sqrt(pow(x[x1]-xn[Ne], 2) + z[z1]);
        t = round(Te/resolucao);
        Kr = Te/resolucao - t;
        indice_sample = t-indice_ref-indice_min;
        if (indice_sample < lgth_sample) {
                     
          SIG = SIG + (matriz[indice_sample][Nr]+Kr*(matriz[indice_sample+1][Nr]-matriz[indice_sample][Nr]));; 
 
        }
      }

      V[z1][x1] = SIG;
          
//      Serial.print(V[z1][x1], 5); //impressão da matriz pela porta serial
//      Serial.print(" ");
    }
//    Serial.println(" ");
  }
  unsigned long tempoFinal = millis(); 

  unsigned long tempoExecucao = tempoFinal - tempoInicio; //calculo de tempo de processamento.

  Serial.print("Tempo de execucao: ");
  Serial.print(tempoExecucao);
  Serial.println(" ms");


}

void loop() {
  
}
