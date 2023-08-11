#include <vector>
#include <string>
#include <cstdio>
#include <fstream>

void criarFitas(int quantidadeFitas) {
    std::ofstream saida;
    for(int i = 0; i < quantidadeFitas; i++) {
        saida.open("./fita"+ std::to_string(i) + ".txt");
        saida.close();
    }
}

// lol
void deletarFitas(int quantidadeFitas) {
    remove("fita0.txt");
    remove("fita1.txt");
    remove("fita2.txt");
    remove("fita3.txt");
    remove("fita4.txt");
    remove("fita5.txt");
}

void lerEntranda(int& tamanhoMemoria, int& quantidadeFitas) {
    std::ifstream entrada("./Entrada.txt");

    entrada >> tamanhoMemoria;
    entrada >> quantidadeFitas;

    char memoria[tamanhoMemoria];
    entrada.readsome(memoria, tamanhoMemoria);

    int metadeFitas = quantidadeFitas/2;
    std::ifstream fitas;

    for(int i = 0; i < quantidadeFitas/2; i++) {
        
    }

    entrada.close();
}