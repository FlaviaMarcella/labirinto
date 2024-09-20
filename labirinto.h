#ifndef _H_LABIRINTO
#define _H_LABIRINTO

void push(Posicao);
void pop();
Posicao top();
bool isEmpty();
void GetElements(Posicao*, int);
bool movimento_valido(int, int, char**, bool**, int);
void print_labirinto(char**, int);
int ler_labirinto(ifstream &, char**, int);
void print_caminho(Pilha &);
bool resolver_labirinto(char**, int);
void labirinto(void);

#endif // LABIRINTO_H