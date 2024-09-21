#include "labirinto.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

#include "labirinto.h"

// Implementação da classe Pilha

Pilha::Pilha() : topo(-1) {}

void Pilha::push(Posicao p) {
    if (topo < 99) {
        elementos[++topo] = p;
    } else {
        std::cerr << "Pilha cheia!" << std::endl;
    }
}

void Pilha::pop() {
    if (topo >= 0) {
        --topo;
    } else {
        std::cerr << "Pilha vazia!" << std::endl;
    }
}

Posicao Pilha::top() {
    if (topo >= 0) {
        return elementos[topo];
    } else {
        std::cerr << "Pilha vazia!" << std::endl;
        return {-1, -1}; // Retorna uma posição inválida
    }
}

bool Pilha::isEmpty() {
    return topo == -1;
}

void Pilha::getElements(Posicao* elementosPilha, int &tamanho) {
    tamanho = topo + 1;
    for (int i = 0; i <= topo; ++i) {
        elementosPilha[i] = elementos[i];
    }
}
// Classe Pilha para armazenar as posições no labirinto

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

void print_caminhoPilha(Pilha &pilha) {
    Posicao caminho[100];
    int tamanho;
    pilha.getElements(caminho, tamanho);
    cout << "Caminho: " << endl;
    for (int i = 0; i < tamanho; ++i) {
        cout << "(" << caminho[i].x << ", " << caminho[i].y << ")" << endl;
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

bool resolver_labirinto(char **labirinto, int n) {
    Pilha pilha;
    bool **visitado = new bool*[n];
    for (int i = 0; i < n; ++i) {
        visitado[i] = new bool[n]();
    }
    Posicao inicio, fim;

    // Encontrar a posição inicial (E) e final (S)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (labirinto[i][j] == 'E') {
                inicio = {i, j};
            } else if (labirinto[i][j] == 'S') {
                fim = {i, j};
            }
        }
    }

    pilha.push(inicio);
    visitado[inicio.x][inicio.y] = true;

    while (!pilha.isEmpty()) {
        Posicao atual = pilha.top();

        // Se chegou à saída, imprimir o caminho
        if (atual.x == fim.x && atual.y == fim.y) {
            print_caminhoPilha(pilha);
            return true;
        }

        // Possíveis movimentos: baixo, direita, esquerda, cima
        Posicao movimentos[] = {
            {atual.x + 1, atual.y}, // Baixo
            {atual.x, atual.y + 1}, // Direita
            {atual.x - 1, atual.y}, // Cima
            {atual.x, atual.y - 1}  // Esquerda
        };

        bool movimento_feito = false;

        // Tenta fazer um movimento válido
        for (const auto& mov : movimentos) {
            if (movimento_valido(mov.x, mov.y, labirinto, visitado, n)) {
                pilha.push(mov);
                visitado[mov.x][mov.y] = true;
                labirinto[mov.x][mov.y] = '.'; // Marcar o lugar visitado
                movimento_feito = true;
                break; // Fazer apenas um movimento por iteração
            }
        }

        // Se não foi possível fazer nenhum movimento válido, retrocede (desempilha)
        if (!movimento_feito) {
            pilha.pop();
        }
    }

    return false; // Não encontrou a saída
}

int listar_arquivos(string folder[], int max_files) {
    int count = 0;
    for (const auto& entry : fs::directory_iterator("labirintos/")) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            if (count < max_files) {
                folder[count++] = entry.path().filename().string();
            } else {
                break;
            }
        }
    }
    return count;
}

void escolhe_arquivo(int num_files, string folder[], char **labirinto, int n, bool &retFlag)
{
    retFlag = true;
    if (num_files == 0)
    {
        cout << "Nenhum arquivo encontrado!" << endl;
        return;
    }

    cout << "Arquivos disponiveis:" << endl;
    for (int i = 0; i < num_files; ++i)
    {
        cout << i + 1 << ": " << folder[i] << endl;
    }
    // menu para escolher o arquivo de entrada

    string opcao;
    cout << "Escolha o arquivo de entrada: ";
    cin >> opcao;

    opcao = "labirintos/" + folder[opcao[0] - '1'];

    cout << opcao << endl;

    ifstream arquivo(opcao);
    ler_labirinto(arquivo, labirinto, n);
    arquivo.close();
    retFlag = false;
}

void labirinto(void) {
    int n = 10;
    char **labirinto = new char*[n];
    string folder[5];
    
    for (int i = 0; i < n; ++i) {
        labirinto[i] = new char[n];
    }

    int num_files = listar_arquivos(folder, 5);

    bool retFlag;
    escolhe_arquivo(num_files, folder, labirinto, n, retFlag);
    if (retFlag)
        return;

    if (resolver_labirinto(labirinto, n)) {
        cout << "Caminho encontrado!" << endl;
        //print_labirinto(labirinto, n);
    } else {
        cout << "Não há caminho para a saída." << endl;
    }

    // Liberação da memória alocada
    for (int i = 0; i < n; ++i) {
        delete[] labirinto[i];
    }
    delete[] labirinto;
}
