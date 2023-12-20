# Processamento-Paralelo-no-ESP32
Programação paralela no ESP32 utilizando Arduino-IDE.
Este repositório contém códigos desenvolvidos como parte do Trabalho de Conclusão de Curso (TCC), abordando técnicas de Focalização por Abertura Sintética (SAFT). Esses códigos são implementações práticas das técnicas e algoritmos discutidos e explorados no meu trabalho.

Conteúdo do Repositório
Estrutura dos Arquivos
[SAFT01.ino]: código de processamento sequencial de imagens ultrassonicas, utilizando apenas um núcleo da plataforma ESP32 desenvolvido em C++.
[SAFTparalelizado.ino]: código de processamento paralelizado com préfixação de tarefas em cada um dos dois núcleos do ESP32.
[SAFTRTOS.ino]: código de processamento paralelizado com alocação dinamica das tarefas pelo FreeRTOS da plataforma ESP32.
[header_saft1.h]: matriz de dados para processamento da imagens ultrassonica pelo algoritmo saft com baixa resolução.
[header_saft2.h]: matriz de dados para processamento da imagens ultrassonica pelo algoritmo saft com média resolução.
[header_saft3.h]: matriz de dados para processamento da imagens ultrassonica pelo algoritmo saft com alta(limite do ESP32) resolução.

Instruções de Uso.

Os arquivos do tipo "header_saft.h" deverão estar na pasta do projeto juntamente com a sua extenção ".ino". 
Após o carregamento do algoritmo no ESP a matriz resultante para a formação da imagem ultrassonica poderá ser coletada diretamente na serial do ESP, utilizando o software PUTTY
para aquisição e arquivamento dos dados da serial em arquivo ".txt".
Para formação da imagem ultrassonica necessário a utilização do software MATLAB ou similares para representação da imagem processada no ESP32.
