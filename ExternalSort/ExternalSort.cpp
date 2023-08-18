#include <vector>
#include <string>
#include <fstream>

#include <iostream>
using namespace std;

void fecharFitas();
void montarBlocosIniciais();
void intercalacao();

std::ifstream entrada;

std::fstream* fitasLeitura;
std::fstream* fitasGravacao;

bool lendoMetadeCima;

char separador = '*';

int quantidadeFitas = 6;
int tamanhoMemoria = 3;

void criarFitas() {
    std::ofstream saida;
    for(int i = 0; i < quantidadeFitas; i++) {
        saida.open("./fita"+ std::to_string(i) + ".txt");
        saida.close();
    }
}

// lol
void deletarFitas() {
    remove("fita0.txt");
    remove("fita1.txt");
    remove("fita2.txt");
    remove("fita3.txt");
    remove("fita4.txt");
    remove("fita5.txt");
}

void abrirFitas() {
    int comecoGravacao, fimGravacao;
    int comecoLeitura, fimLeitura;

    if(lendoMetadeCima) {
        comecoLeitura = 0;
        fimLeitura = quantidadeFitas/2;

        comecoGravacao = quantidadeFitas/2;
        fimGravacao = quantidadeFitas;
    } else {
        comecoGravacao = 0;
        fimGravacao = quantidadeFitas/2;

        comecoLeitura = quantidadeFitas/2;
        fimLeitura = quantidadeFitas;
    }
    
    fitasGravacao = new std::fstream[quantidadeFitas/2];
    fitasLeitura = new std::fstream[quantidadeFitas/2];
    
    int auxCont = 0;
    for(int i = comecoGravacao; i < fimGravacao; i++) {
        fitasGravacao[auxCont].open("fita"+std::to_string(i)+".txt", std::fstream::out);
        auxCont++;
    }

    auxCont = 0;
    for(int i = comecoLeitura; i < fimLeitura; i++) {
        fitasLeitura[auxCont].open("fita"+std::to_string(i)+".txt", std::fstream::in);
        auxCont++;
    }
}

void externalSort(std::string endereco) {
    lendoMetadeCima = false;
    entrada.open(endereco);
    criarFitas();
    montarBlocosIniciais();
    intercalacao();
    fecharFitas();
}

void teste() {
    string teste;
    fitasGravacao = new std::fstream[3];
    fitasGravacao[0].open("fita0.txt", std::fstream::out);
    fitasGravacao[0] << "teste";
}

int compare(const void* a, const void* b) {
    const char* x = (char*) a;
    const char* y = (char*) b;

    if(*x > *y) {
        return 1;
    } else if(*x < *y) {
        return -1;
    }
    return 0;
}

int comparePair(const void* a, const void* b) {
    const pair<char, int>* x = (pair<char, int>*) a;
    const pair<char, int>* y = (pair<char, int>*) b;

    if((*x).first > (*y).first) {
        return 1;
    } else if((*x).first < (*y).first) {
        return -1;
    }
    return 0;
}

void montarBlocosIniciais() {
    char memoria[tamanhoMemoria];
    int tamanhoVetor;
    int auxCont = 0;
    abrirFitas();
    while(!entrada.eof()) {   
        entrada.get(memoria, tamanhoMemoria+1);

        tamanhoVetor = tamanhoMemoria;
        for(int i = 1; i < tamanhoMemoria; i++) {
            if(memoria[i] == '\0') {
                tamanhoVetor = i;
                break;
            }
        }

        qsort(memoria, tamanhoVetor, sizeof(char), compare);

        if(auxCont >= quantidadeFitas/2) {
            auxCont = 0;
        }

        fitasGravacao[auxCont] << memoria << separador;
        auxCont++;
    }
    lendoMetadeCima = true;
    entrada.close();
    fecharFitas();
}

void intercalacao() {
    pair<char, int> memoria[tamanhoMemoria];

    bool fitaAberta[quantidadeFitas/2];
    bool intercalando = true;
    bool passosRestando = true;

    int contMemoria = 0;
    int contGravacao = 0;
    int contFitas = 0;
    int fitasDisponiveis = quantidadeFitas/2;
    

    char charAux;

    abrirFitas();

    while(intercalando) {

        for(int i = 0; i < quantidadeFitas/2; i++) {
            fitaAberta[i] = true;
        }

        fitasDisponiveis = quantidadeFitas/2;

        while(passosRestando) {            
            if(fitaAberta[contFitas]) {

                fitasLeitura[contFitas].get(charAux);

                if(charAux == separador) {
                    fitaAberta[contFitas] = false;
                    fitasDisponiveis--;
                } else {
                    memoria[contMemoria].first = charAux;
                    memoria[contMemoria].second = contFitas;
                    contMemoria++;
                }
            }
            
            contFitas++;
            if(contFitas == quantidadeFitas/2) {
                contFitas = 0;
            }

            if(contMemoria == tamanhoMemoria || fitasDisponiveis == 0) {
                qsort(memoria, contMemoria, sizeof(pair<char, int>), comparePair);
                cout << memoria[0].first;
                cout << memoria[1].first;
                cout << memoria[2].first;
                // TODO guardar no arquivo o resultado
                // fitasGravacao[contGravacao] << memoria[0].first;
                break;
            }

            if(fitasDisponiveis == 0) {
                passosRestando = false;
            }
        }
        intercalando = false;
    }
    // TODO verificar o erro
    // fecharFitas();
}

void fecharFitas() {
    for(int i = 0; i < quantidadeFitas/2; i++) {
        fitasGravacao[i].close();
        fitasLeitura[i].close();
    }
    delete[] fitasGravacao;
    delete[] fitasLeitura;
}