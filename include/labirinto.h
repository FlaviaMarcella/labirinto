#ifndef PILHA_H
#define PILHA_H

#include <iostream>

void labirinto(void);

class Posicao {
public:
    int x;
    int y;

    // Construtor padrão
    Posicao() : x(0), y(0) {}

    // Construtor com parâmetros
    Posicao(int x, int y) : x(x), y(y) {}

    // Operador de igualdade
    bool operator==(const Posicao& other) const {
        return this->x == other.x && this->y == other.y;
    }
};

class Pilha {
private:
    Posicao elementos[100];
    int topo;

public:
    Pilha();
    
    void push(Posicao p);
    void pop();
    Posicao top();
    bool isEmpty();
    void getElements(Posicao* elementosPilha, int &tamanho);
};

#endif // PILHA_H