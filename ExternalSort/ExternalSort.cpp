#include <vector>
#include <string>
#include <fstream>

std::ifstream entrada;

std::fstream* fitasLeitura;
std::fstream* fitasGravacao;

bool lendoMetadeCima = false;

char separador = '*';

int quantidadeFitas;
int tamanhoMemoria;

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

void abrirFitasLeitura() {
    int comeco, fim;

    if(lendoMetadeCima) {
        comeco = 0;
        fim = quantidadeFitas/2;
    } else {
        comeco = quantidadeFitas/2;
        fim = quantidadeFitas;
    }

    fitasLeitura = new std::fstream[quantidadeFitas/2];
    for(int i = comeco; i < fim; i++) {
        fitasLeitura[i].open("fita"+to_string(i)+".txt", std::fstream::in);
    }
}

void abrirFitas(int quantidadeFitas) {
    int comecoGravacao, fimGravacao;
    int comecoLeitura, fimLeitura;

    if(lendoMetadeCima) {
        comecoLeitura = 0;
        fimLeitura = quantidadeFitas/2;
        comecoGravacao = quantidadeFitas/2;
        fimGravacao = quantidadeFitas;
    } else {
        comecoGravacao = 0;
        comecoGravacao = quantidadeFitas/2;
        comecoLeitura = quantidadeFitas/2;
        fimLeitura = quantidadeFitas;
    }

    fitasGravacao = new std::fstream[quantidadeFitas/2];
    fitasLeitura = new std::fstream[quantidadeFitas/2];

    for(int i = comecoGravacao; i < fimGravacao; i++) {
        fitasLeitura[i].open("fita"+to_string(i)+".txt", std::fstream::out);
    }

    
    for(int i = comecoLeitura; i < fimLeitura; i++) {
        fitasLeitura[i].open("fita"+to_string(i)+".txt", std::fstream::in);
    }
}

void lerDadosIniciais(std::string endereco) {
    entrada.open(endereco);
    entrada >> tamanhoMemoria;
    entrada >> quantidadeFitas;
}

void montarBlocosIniciais() {
    char memoria[tamanhoMemoria];

    while(!entrada.eof()) {
        // fazer
    }
}

void intercalacao() {
    char memoria[tamanhoMemoria];
    bool fitaAberta[quantidadeFitas/2];
    bool fitasDisponiveis = true;

    for(int i = 0; i < quantidadeFitas/2; i++) {
        fitaAberta[i] = true;
    }

    while(fitasDisponiveis) {
        for(int i = 0; i < quantidadeFitas/2; i++) {
            fitasLeitura[i].get() >> memoria[i];            
        }
    }

}

void fecharFitas() {
    for(int i = 0; i < quantidadeFitas/2; i++) {
        fitasGravacao[i].close();
        fitasLeitura[i].close();
    }
    delete[] fitasGravacao;
    delete[] fitasLeitura;
}