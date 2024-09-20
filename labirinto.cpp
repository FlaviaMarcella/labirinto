#include "labirinto.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

typedef struct {
    int x;
    int y;
    bool visitado;
} Posicao;

//Os movimentos possíveis são: baixo, esquerda e direita; Deve-se seguir uma ordem de checagem dos movimentos: baixo, direita e esquerda.
//A função labirinto deve ser implementada de forma recursiva, e deve receber como parâmetro a posição atual do robô, a matriz que representa o labirinto, e o tamanho do labirinto.


//devemos ler o arquivo de entrada e armazenar o labirinto em uma matriz de inteiros.
//cada linha do arquivo de entrada representa uma linha da matriz, e os valores de cada linha são separados por caracteres unicos, ou seja lê-se um, lê-se outro,
//lê-se outro, e assim por diante. O arquivo de entrada é composto por um inteiro n, que representa o tamanho do labirinto, seguido de n linhas, cada uma com n inteiros.
int ler_labirinto(ifstream &arquivo, char **labirinto, int n){

        if (!arquivo.is_open()) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            arquivo >> labirinto[i][j];
        }
    }

    return 0;

}

void print_labirinto(char **labirinto, int n){

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << labirinto[i][j] << " ";
        }
        cout << endl;
    }
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


void labirinto(void){

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

    print_labirinto(labirinto, n);
}

