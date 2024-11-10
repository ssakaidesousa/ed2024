// PROGRAMA DE ESTATÍSTICA BÁSICA
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Função de comparação para ordenação
int compare(const void *a, const void *b) {
    return (*(float*)a - *(float*)b);
}

int main() {
    int n;
    float *vetor;
    float max, min, x = 0, x2 = 0, media, mediana, s = 0, s2 = 0;

    printf("Quantos números na sua série (N): ");
    scanf("%d", &n);
    
    // Alocação de memória para o vetor
    vetor = malloc(n * sizeof(float));
    if (!vetor) {  // Verifica falha na alocação
        printf("Erro de alocação de memória\n");
        exit(-1);
    }
    
    printf("Entre com os números:\n");
    for (int i = 0; i < n; i++) {
        printf("> ");
        scanf("%f", &vetor[i]);
    }
    
    // Inicializa min e max
    min = max = vetor[0];

    // Cálculos de min, max, soma (para a média) e soma dos quadrados (para o desvio padrão)
    for (int i = 0; i < n; i++) {
        if (vetor[i] < min) min = vetor[i];
        if (vetor[i] > max) max = vetor[i];
        x += vetor[i];
        x2 += vetor[i] * vetor[i];
    }

    // Cálculo da média
    media = x / n;

    // Ordena o vetor para calcular a mediana
    qsort(vetor, n, sizeof(float), compare);
    
    // Cálculo da mediana
    if (n % 2 == 0) {
        mediana = (vetor[n/2 - 1] + vetor[n/2]) / 2;
    } else {
        mediana = vetor[n/2];
    }

    // Cálculo do desvio padrão (e variância)
    s2 = (x2 - (x * x) / n) / (n - 1); // Variância
    s = sqrt(s2);  // Desvio padrão

    // Exibe os resultados
    printf("Valor mínimo: %.2f\n", min);
    printf("Valor máximo: %.2f\n", max);
    printf("Média: %.2f\n", media);
    printf("Mediana: %.2f\n", mediana);
    printf("Desvio-padrão: %f\n", s);
	//printf("Somatório de n: %.2f\n", x);
	//printf("Somatório de n²: %.2f\n", x2);
	//printf("Variância: %f\n", s2);

    // Libera a memória alocada
    free(vetor);
    
    return 0;
}
