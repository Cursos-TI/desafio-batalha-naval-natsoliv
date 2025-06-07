#include <stdio.h>

#define TAM 10
#define TAM_HAB 5
#define NAVIO 3
#define AGUA 0
#define HABILIDADE 5

// Função para inicializar o tabuleiro com 0 (água)
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para imprimir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Verifica se é possível posicionar um navio de tamanho 3
int podePosicionar(int tabuleiro[TAM][TAM], int x, int y, int dx, int dy) {
    for (int i = 0; i < 3; i++) {
        int nx = x + dx * i;
        int ny = y + dy * i;
        if (nx < 0 || nx >= TAM || ny < 0 || ny >= TAM || tabuleiro[nx][ny] != AGUA)
            return 0;
    }
    return 1;
}

// Posiciona navio no tabuleiro com direção (dx, dy)
void posicionarNavio(int tabuleiro[TAM][TAM], int x, int y, int dx, int dy) {
    for (int i = 0; i < 3; i++) {
        int nx = x + dx * i;
        int ny = y + dy * i;
        tabuleiro[nx][ny] = NAVIO;
    }
}

// Função para sobrepor uma habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[TAM_HAB][TAM_HAB], int origemX, int origemY) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (habilidade[i][j] == 1) {
                int tx = origemX + i - centro;
                int ty = origemY + j - centro;
                if (tx >= 0 && tx < TAM && ty >= 0 && ty < TAM && tabuleiro[tx][ty] == AGUA) {
                    tabuleiro[tx][ty] = HABILIDADE;
                }
            }
        }
    }
}

// Constrói habilidade em forma de cone (aponta para baixo)
void construirCone(int cone[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (j >= (TAM_HAB / 2 - i) && j <= (TAM_HAB / 2 + i))
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

// Constrói habilidade em forma de cruz
void construirCruz(int cruz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == TAM_HAB / 2 || j == TAM_HAB / 2)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }
}

// Constrói habilidade em forma de octaedro (losango)
void construirOctaedro(int octaedro[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - TAM_HAB / 2) + abs(j - TAM_HAB / 2) <= TAM_HAB / 2)
                octaedro[i][j] = 1;
            else
                octaedro[i][j] = 0;
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    // Posicionamento dos navios
    // Horizontal (linha 1, coluna 1)
    if (podePosicionar(tabuleiro, 1, 1, 0, 1))
        posicionarNavio(tabuleiro, 1, 1, 0, 1);

    // Vertical (linha 4, coluna 7)
    if (podePosicionar(tabuleiro, 4, 7, 1, 0))
        posicionarNavio(tabuleiro, 4, 7, 1, 0);

    // Diagonal principal (linha 7, coluna 0)
    if (podePosicionar(tabuleiro, 7, 0, -1, 1))
        posicionarNavio(tabuleiro, 7, 0, -1, 1);

    // Diagonal secundária (linha 2, coluna 7)
    if (podePosicionar(tabuleiro, 2, 7, 1, 1))
        posicionarNavio(tabuleiro, 2, 7, 1, 1);

    // Matrizes de habilidades
    int cone[TAM_HAB][TAM_HAB], cruz[TAM_HAB][TAM_HAB], octaedro[TAM_HAB][TAM_HAB];

    construirCone(cone);
    construirCruz(cruz);
    construirOctaedro(octaedro);

    // Aplicar habilidades ao tabuleiro (com origem no centro do tabuleiro)
    aplicarHabilidade(tabuleiro, cone, 2, 2);       // Cone
    aplicarHabilidade(tabuleiro, cruz, 5, 5);       // Cruz
    aplicarHabilidade(tabuleiro, octaedro, 7, 7);   // Octaedro

    // Exibir tabuleiro final
    printf("Tabuleiro com navios (3), água (0) e áreas de habilidade (5):\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}