#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>
#include <vector>


struct Ponto 
{
    double x = 0.0;
    double y = 0.0;
};

struct Individuo 
{
    double a = 0.0;
    double b = 0.0;
    double fitness = 0.0;
    double erro = 0.0; // Padronizado para 'erro' (em português)
};

struct Config 
{
    int n = 0; // número de pontos
    int m = 0; // tamanho da população
    int g = 0; // número de gerações
};


#endif