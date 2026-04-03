#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "utils.hpp"

using namespace std;

vector<Ponto> lerDados(const string& nomeArquivo, int& n, int& m, int& g) 
{
    ifstream arquivo(nomeArquivo);
    vector<Ponto> pontos;

    if (!arquivo.is_open()) 
    {
        cerr << "Erro ao abrir o arquivo: " << nomeArquivo << endl;
        return pontos;
    }

    // Lê n, m e g do cabeçalho do arquivo [cite: 108]
    if (!(arquivo >> n >> m >> g)) 
    {
        cerr << "Erro ao ler o cabecalho do arquivo." << endl;
        return pontos;
    }

    // Lê os n pares de coordenadas x y [cite: 109-111]
    for (int i = 0; i < n; ++i) 
    {
        Ponto p;
        if (arquivo >> p.x >> p.y) 
        {
            pontos.push_back(p);
        }
    }

    arquivo.close();
    return pontos;
}

void registrarSaida(const string& nomeArquivo, int geracao, const Individuo& melhor) 
{
    
    ofstream arquivo(nomeArquivo, ios::app);

    if (arquivo.is_open()) 
    {
        arquivo << "Geracao: " << geracao << " | " 
                << "Fitness: " << melhor.fitness << " | " 
                << "Erro: " << melhor.erro << " | " 
                << "a: " << melhor.a << " | " 
                << "b: " << melhor.b << endl;
        arquivo.close();
    }
}
void gerarPopulacao(vector<Individuo>& populacao, int m) 
{
    for (int i = 0; i < m; ++i) 
    {
        populacao[i].a = (rand() % 2000 - 1000) / 10.0; // Gera entre -100.0 e 99.9
        populacao[i].b = (rand() % 2000 - 1000) / 10.0;
        populacao[i].fitness = 0;
        populacao[i].erro = 0;
    }
}

void testarPopulacao(vector<Individuo>& populacao,const vector<Ponto>& pontos, int n, int m) 
{
    double y, somaerro = 0;

   for(int i = 0; i<m;i++)
    {
        for(int j = 0; j<n;j++)
        {
            y = populacao[i].a * pontos[j].x + populacao[i].b;
            somaerro += (pontos[j].y - y) * (pontos[j].y - y);
        }
        populacao[i].erro =somaerro / n;
        somaerro = 0;
        populacao[i].fitness = 1.0 / (populacao[i].erro + 1e-6);//Para nao ter perigo a divisao por 0 adiciona-se uma constante pequena.
    }
}

void selecionarIndividuos(vector<Individuo>& populacao, Individuo& melhorIndividuo1, Individuo& melhorIndividuo2, Individuo& PiorIndividuo, int& indicePior ,int m) 
{   
    melhorIndividuo1.fitness = -1.0; 
    melhorIndividuo2.fitness = -1.0;
    PiorIndividuo.fitness = 9999999.0; 

    for(int i=0 ; i<m;i++)
    {
        if(populacao[i].fitness > melhorIndividuo1.fitness)
        {
            melhorIndividuo2 = melhorIndividuo1;
            melhorIndividuo1 = populacao[i];
        }
        else if(populacao[i].fitness > melhorIndividuo2.fitness)
        {
            melhorIndividuo2 = populacao[i];
        }
        if(populacao[i].fitness < PiorIndividuo.fitness)
        {
            PiorIndividuo = populacao[i];
            indicePior = i;
        }
    }
}

void mutacao(Individuo& individuo) 
{
    // Gera o delta (pequena variação controlada), por exemplo, entre -1.0 e 1.0
    double delta = (rand() % 21 - 10) / 10.0;

    // Sorteia 0 ou 1 para decidir qual gene sofrerá a mutação
    if (rand() % 2 == 0) 
    {
        individuo.a += delta;
    } 
    else 
    {
        individuo.b += delta;
    }
}

void crossover(Individuo& pai1, Individuo& pai2, Individuo& filho) 
{
   // Sorteia para o gene 'a'
    if (rand() % 2 == 0) 
    {
        filho.a = pai1.a; 
    }
     else 
    {
        filho.a = pai2.a;
    }

    // Sorteia para o gene 'b'
    if (rand() % 2 == 0) 
    {
        filho.b = pai1.b;
    } 
    else 
    {
        filho.b = pai2.b;
    }

}

void varrerFilho(Individuo& filho, const vector<Ponto>& pontos, int n) 
{
    double y;
    double somaerro = 0;
    for (int i = 0; i < n; ++i) 
    {
        y = filho.a * pontos[i].x + filho.b;
        somaerro += (pontos[i].y - y) * (pontos[i].y - y);
    }
    filho.erro = somaerro / n;
    filho.fitness = 1.0 / (filho.erro + 1e-6); //Para nao ter perigo a divisao por 0 adiciona-se uma constante pequena.
}

