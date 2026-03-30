#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>
#include "types.hpp"

std::vector<Ponto> lerDados(const std::string& nomeArquivo, int& n, int& m, int& g);

void registrarSaida(const std::string& nomeArquivo, int geracao, const Individuo& melhor);

void gerarPopulacao(std::vector<Individuo>& populacao, int m);

void testarPopulacao(std::vector<Individuo>& populacao, const std::vector<Ponto>& pontos, int n, int m);

void selecionarIndividuos(std::vector<Individuo>& populacao, Individuo& melhorIndividuo1, Individuo& melhorIndividuo2, Individuo& PiorIndividuo, int& indicePior ,int m);

void crossover(Individuo& pai1, Individuo& pai2, Individuo& filho);

void mutacao(Individuo& individuo);

void varrerFilho(Individuo& filho, const std::vector<Ponto>& pontos, int n);


#endif