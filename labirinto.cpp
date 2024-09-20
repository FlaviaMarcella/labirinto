#include <iostream>
#include <fstream>
#include <string>

#include "labirinto.h"

using namespace std;

struct Posicao {
    int x, y;
};

struct Pilha {
    Posicao elementos[100]; // Tamanho máximo da pilha
    int topo;

    Pilha() : topo(-1) {}

    void push(Posicao p) {
        if (topo < 99) {
            elementos[++topo] = p;
        } else {
            cerr << "Pilha cheia!" << endl;
        }
    }

    void pop() {
        if (topo >= 0) {
            --topo;
        } else {
            cerr << "Pilha vazia!" << endl;
        }
    }

    Posicao top() {
        if (topo >= 0) {
            return elementos[topo];
        } else {
            cerr << "Pilha vazia!" << endl;
            return {-1, -1}; // Retorna uma posição inválida
        }
    }

    bool isEmpty() {
        return topo == -1;
    }

    void getElements(Posicao* elementosPilha, int &tamanho) {
        tamanho = topo + 1;
        for (int i = 0; i <= topo; ++i) {
            elementosPilha[i] = elementos[i];
        }
    }
};

bool movimento_valido(int x, int y, char **labirinto, bool **visitado, int n) {
    return (x >= 0 && x < n && y >= 0 && y < n && labirinto[x][y] != 'X' && !visitado[x][y]);
}

void print_labirinto(char **labirinto, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << labirinto[i][j] << ' ';
        }
        cout << endl;
    }
}

int ler_labirinto(ifstream &arquivo, char **labirinto, int n) {
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            arquivo >> labirinto[i][j];
        }
    }

    return 0;
}

void print_caminho(Pilha &pilha) {
    Posicao caminho[100];
    int tamanho;
    pilha.getElements(caminho, tamanho);
    cout << "Caminho completo:" << endl;
    for (int i = 0; i < tamanho; ++i) {
        cout << "(" << caminho[i].x << ", " << caminho[i].y << ")" << endl;
    }
}

bool resolver_labirinto(char **labirinto, int n) {
    Pilha pilha;
    bool **visitado = new bool*[n];
    for (int i = 0; i < n; ++i) {
        visitado[i] = new bool[n]();
    }
    Posicao inicio, fim;

    // Encontrar a posição inicial (S) e final (E)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (labirinto[i][j] == 'S') {
                inicio = {i, j};
            } else if (labirinto[i][j] == 'E') {
                fim = {i, j};
            }
        }
    }

    pilha.push(inicio);
    visitado[inicio.x][inicio.y] = true;

    while (!pilha.isEmpty()) {
        Posicao atual = pilha.top();
        pilha.pop();

        if (atual.x == fim.x && atual.y == fim.y) {
            // Adicionar a posição final à pilha
            pilha.push(fim);

            // Marcar o caminho encontrado
            Posicao caminho[100];
            int tamanho;
            pilha.getElements(caminho, tamanho);
            for (int i = 0; i < tamanho; ++i) {
                labirinto[caminho[i].x][caminho[i].y] = '0'; // Marcar o caminho
            }
            print_caminho(pilha); // Imprimir o caminho completo
            return true; // Encontrou a saída
        }

        // Movimentos possíveis: baixo, direita, esquerda, cima
        Posicao movimentos[] = {{atual.x + 1, atual.y}, {atual.x, atual.y + 1}, {atual.x, atual.y - 1}, {atual.x - 1, atual.y}};

        for (const auto& mov : movimentos) {
            if (movimento_valido(mov.x, mov.y, labirinto, visitado, n)) {
                pilha.push(mov);
                visitado[mov.x][mov.y] = true;
                labirinto[mov.x][mov.y] = '.'; // Marcar o lugar visitado
            }
        }
    }

    return false; // Não encontrou a saída
}

void labirinto(void) {
    int n = 10;
    char **labirinto = new char*[n];
    
    for (int i = 0; i < n; ++i) {
        labirinto[i] = new char[n];
    }

    ifstream arquivo("labirintos/labirinto4.txt");

    if (ler_labirinto(arquivo, labirinto, n) != 0) {
        return;
    }

    if (resolver_labirinto(labirinto, n)) {
        cout << "Caminho encontrado:" << endl;
        print_labirinto(labirinto, n);
    } else {
        cout << "Não há caminho para a saída." << endl;
    }

    // Liberação da memória alocada
    for (int i = 0; i < n; ++i) {
        delete[] labirinto[i];
    }
    delete[] labirinto;
}


