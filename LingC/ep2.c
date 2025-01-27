#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar os dados do registro
typedef struct {
    char nome[100];
    char cargo[100];
    char uorg_lotacao[100];
} Registro;

// Nó da árvore binária de busca
typedef struct No {
    Registro registro;
    struct No *esq, *dir;
} No;

// Função para criar um novo nó
No* criarNo(Registro reg) {
    No* novo = (No*)malloc(sizeof(No));
    novo->registro = reg;
    novo->esq = novo->dir = NULL;
    return novo;
}

// Função para inserir um registro na ABB
No* inserir(No* raiz, Registro reg) {
    if (raiz == NULL)
        return criarNo(reg);

    if (strcmp(reg.nome, raiz->registro.nome) < 0)
        raiz->esq = inserir(raiz->esq, reg);
    else if (strcmp(reg.nome, raiz->registro.nome) > 0)
        raiz->dir = inserir(raiz->dir, reg);

    return raiz;
}

// Função para buscar um registro pelo nome na ABB
No* buscar(No* raiz, const char* nome) {
    if (raiz == NULL || strcmp(nome, raiz->registro.nome) == 0)
        return raiz;

    if (strcmp(nome, raiz->registro.nome) < 0)
        return buscar(raiz->esq, nome);
    else
        return buscar(raiz->dir, nome);
}

// Função para remover espaços extras
void trim(char* str) {
    char* end;
    while (*str == ' ') str++; // Remove espaços do início
    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\n' || *end == '\r')) end--;
    *(end + 1) = '\0'; // Adiciona o terminador nulo
}

// Função para converter uma string para maiúsculas
void to_uppercase(char* str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= ('a' - 'A');
        }
    }
}

// Função para ler o arquivo CSV e carregar os dados na ABB
No* lerCSV(const char* nomeArquivo, No* raiz) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    char linha[300];
    while (fgets(linha, sizeof(linha), arquivo)) {
        Registro reg;
        char* token = strtok(linha, ",");
        if (token) { 
            trim(token); 
            to_uppercase(token); // Converte o nome para maiúsculas
            strcpy(reg.nome, token); 
        }

        token = strtok(NULL, ",");
        if (token) { trim(token); strcpy(reg.cargo, token); }

        token = strtok(NULL, ",");
        if (token) { trim(token); strcpy(reg.uorg_lotacao, token); }

        raiz = inserir(raiz, reg);

        // Depuração: imprime os registros carregados
        printf("Carregado: Nome='%s', Cargo='%s', UORG_LOTACAO='%s'\n", 
                reg.nome, reg.cargo, reg.uorg_lotacao);
    }

    fclose(arquivo);
    return raiz;
}

// Função principal
int main() {
    No* raiz = NULL;
    char nomeArquivo[100] = "Unifesp-24r.csv";

    printf("Carregando dados do arquivo '%s'...\n", nomeArquivo);
    raiz = lerCSV(nomeArquivo, raiz);
    if (!raiz) {
        printf("Erro ao carregar os dados do arquivo.\n");
        return 1;
    }

    char nomeBusca[100];
    printf("Digite o nome completo para buscar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    trim(nomeBusca); // Remove espaços e quebras de linha
    to_uppercase(nomeBusca); // Converte para maiúsculas

    No* resultado = buscar(raiz, nomeBusca);
    if (resultado) {
        printf("\nRegistro encontrado:\n");
        printf("Cargo: %s\n", resultado->registro.cargo);
        printf("UORG_LOTACAO: %s\n", resultado->registro.uorg_lotacao);
    } else {
        printf("\nRegistro não encontrado.\n");
    }

    return 0;
}
