#include <vector>

struct Item{
    int id;
};

void heap_constroi(std::vector<Item>& vetor);
void refaz_cima_baixo(std::vector<Item>& vetor, int pai);
void refaz_baixo_cima(std::vector<Item>& vetor, int filho);
void troca(Item& pai, Item& filho);
void heap_insere(std::vector<Item>& vetor, Item novo);
void heap_remove(std::vector<Item>& vetor);

void heap_constroi(std::vector<Item>& vetor) {
    int tamanho = vetor.size()/2;
    while(tamanho >= 1) {
        refaz_cima_baixo(vetor, tamanho);
        tamanho--;
    }
}

void refaz_cima_baixo(std::vector<Item>& vetor, int pai) {
    int filho = pai*2;
    int tamanho = vetor.size();
    while(filho < tamanho) {
        if(filho < tamanho && vetor[filho].id < vetor[filho+1].id) {
            filho++;
        }
        if(vetor[pai].id >= vetor[filho].id) {
            break;
        }
        troca(vetor[pai], vetor[filho]);

        pai = filho;
        filho = pai*2;
    }
}

void refaz_baixo_cima(std::vector<Item>& vetor, int filho) {
    int pai = filho/2;
    while(pai > 1) {
        if(vetor[filho].id > vetor[pai].id) {
            troca(vetor[filho], vetor[pai]);
        }
        pai = filho;
        filho /= 2;
    }
}

void troca(Item& pai, Item& filho) {
    Item aux = pai;
    pai = filho;
    filho = aux;
}

void heap_insere(std::vector<Item>& vetor, Item novo) {
    vetor.push_back(novo);
    refaz_baixo_cima(vetor, vetor.size()-1);
}

void heap_remove(std::vector<Item>& vetor) {
    troca(vetor[1], vetor[vetor.size()-1]);
    vetor.pop_back();
    refaz_cima_baixo(vetor, vetor.size()-1);
}

void heapsort(std::vector<Item>& vetor) {
    heap_constroi(vetor);
    int tamanho = vetor.size()-1;
    while(tamanho >= 1) {
        troca(vetor[tamanho], vetor[1]);
        tamanho--;
        refaz_cima_baixo(vetor, 1);
    }
}
