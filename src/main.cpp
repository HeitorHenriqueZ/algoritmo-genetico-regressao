#include <iostream>
#include <ctime>
#include <fstream>
#include "utils.hpp"
#include "types.hpp"

using namespace std;

int main() 
{
    int n, m, g, indicePior = 0;
    Individuo melhorIndividuo1,melhorIndividuo2, PiorIndividuo, Filho;
    srand(time(NULL));
    

    vector<Ponto> pontos = lerDados("data/input.dat", n, m, g);

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

    std::ofstream limpar("data/output.dat", std::ios::out | std::ios::trunc);
    limpar.close();
    
    for(int i = 0; i < g; i++)
    {
        crossover(melhorIndividuo1, melhorIndividuo2, Filho);

        mutacao(Filho);

        varrerFilho(Filho, pontos, n);

        populacao[indicePior] = Filho;

        selecionarIndividuos(populacao, melhorIndividuo1, melhorIndividuo2, PiorIndividuo, indicePior ,m);

        registrarSaida("data/output.dat", i + 1, melhorIndividuo1);
    }
    cout << "\n======================================" << endl;
    cout << "          RESULTADO FINAL             " << endl;
    cout << "======================================" << endl;
    cout << "Melhor reta: y = " << melhorIndividuo1.a << "x + " << melhorIndividuo1.b << endl;
    cout << "Parametro a: " << melhorIndividuo1.a << endl;
    cout << "Parametro b: " << melhorIndividuo1.b << endl;
    cout << "Erro medio:  " << melhorIndividuo1.erro << endl;
    cout << "Fitness:     " << melhorIndividuo1.fitness << endl;
    cout << "======================================" << endl;
    return 0;
}