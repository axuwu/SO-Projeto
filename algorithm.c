// Bibliotecas
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Valor real do pi
#define M_PI 3.14159265358979323846

int main() {
	// Iniciar variaveis
	clock_t inicio, fim;
	double duracao, npontos, coordenadax, coordenaday, PI, erro;
	int nthreads;

	printf("Trabalho de SO!\n");
  
  // Obtencao dos valores
	printf(
		"\nConsidera os seguintes números de pontos: 500, 20000, 100000, "
		"1000000 e 10000000 pontos.\n");
	printf("\nQuantos números de pontos: ");
	scanf("%lf", &npontos);

	printf("\nConsidera os seguintes números de threads: 2, 4, 6 e 8.\n");
	printf("\nQuantos números de thread: ");
	scanf("%d", &nthreads);

	printf("\nPontos: %lf\n", npontos);
	printf("\nThreads: %d\n\n", nthreads);

	printf("\n-----Monte Carlo-----\n\n");

	inicio = clock();

	// Função que calcula o pi
	void *CalcularPI() {
		int circle_count = 0;

		// Geracao de numeros
		for (int j = 0; j < npontos; j++) {
			coordenadax = rand() % 101;
			coordenadax = coordenadax / 100;

			coordenaday = rand() % 101;
			coordenaday = coordenaday / 100;

			// Contagem dos numeros dentro do circulo
			if ((sqrt(pow((coordenadax), 2) + pow((coordenaday), 2))) <= 1.0) {
				circle_count++;
			}
		}

		// Calcular estimativa do valor de pi
		PI = 4.0 * circle_count / npontos;

		fim = clock();

		printf("\nValor aproximado de PI: %lf \n", PI);

		printf("\nNúmero de pontos dentro do círculo: %d \n", circle_count);

		// Contabilizar o tempo que demora cada estimacao do valor de pi
		duracao = (double)(fim - inicio) / CLOCKS_PER_SEC;

		printf("\nTempo gasto pelo CPU = %f s\n", duracao);

		// Medir a qualidade de cada estimativa (erro relativo percentual)
		erro = (fabs)(M_PI - PI) / M_PI * 100;

		printf("\nErro Relativo Percentual: %f %\n", erro);
	}

	// ID da thread
	pthread_t tID[nthreads];

	// Criar thread que vai correr a função CalcularPI
	for (int i = 0; i < nthreads; i++) {
		pthread_create(&tID[i], NULL, &CalcularPI, NULL);
	}

	// Ciclo que executa a função join
	for (int i = 0; i < nthreads; ++i) {
		pthread_join(tID[i], NULL);
	}

	return 0;
}
