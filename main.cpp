#include <iostream>
#include <ctime>
#include "utils.h"
#include "types.h"

using namespace std;

int main() 
{
    int n, m, g, indicePior = 0;
    Individuo melhorIndividuo1,melhorIndividuo2, PiorIndividuo, Filho;
    srand(time(NULL));
    

    vector<Ponto> pontos = lerDados("input.dat", n, m, g);

    if (pontos.empty()) 
    {
        cerr << "Nenhum ponto foi lido. Verifique o arquivo input.dat." << endl;
        return 1;
    }

    cout << "Dados lidos com sucesso!" << endl;
    cout << "Numero de pontos (n): " << n << endl;
    cout << "Tamanho da populacao (m): " << m << endl;
    cout << "Numero de geracoes (G): " << g << endl;

    vector<Individuo> populacao(m);

    gerarPopulacao(populacao, m);
   
    testarPopulacao(populacao, pontos, n, m);

    selecionarIndividuos(populacao, melhorIndividuo1, melhorIndividuo2, PiorIndividuo, indicePior ,m);

    for(int i = 0; i < g; i++)
    {
        crossover(melhorIndividuo1, melhorIndividuo2, Filho);

        varrerFilho(Filho, pontos, n);

        populacao[indicePior] = Filho;

        selecionarIndividuos(populacao, melhorIndividuo1, melhorIndividuo2, PiorIndividuo, indicePior ,m);

        registrarSaida("output.dat", i + 1, melhorIndividuo1);
    }
    return 0;
}