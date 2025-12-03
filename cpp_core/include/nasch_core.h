// Este archivo permitirá conectar python con c++. Solo es escribirán las declaraciones y nos el código "real".
#pragma once
#include <cstdint>
#include <vector>
struct Auto{
    int pos;   // poss desde la recta en (0,0)
    int vel;   // velocidad actual
    Auto(int position=0, int velocity=0) noexcept;
    // Agregamos los métodos para nuestro nuevo datatype
    void accelerate(int v_max) noexcept;  
    void brake_to_gap(int gap) noexcept;
    void random_slow(double p, uint32_t rnd) noexcept; // Una función muy importante que permitirá simular el tráfico.
};

// Ahora agregaremos las funciones para nuestro "Auto"
// Inicializamos N autos en posiciones aleatorios sin colisiones 
std::vector<Auto> int_random_position(
    int N,
    int L,
    uint32_t seed
);

// Aplicamos el modelo NASCH al vector de autos
// p: probabilidad de frenado
void step_nasch(
    std::vector<Auto>& cars,
    int L,
    int v_max,
    double p,
    uint32_t seed
);

// Ejecutamos T iteraciones del modelo
std::vector<Auto> run_simulation(
    int N,
    int L,
    int v_max,
    double p,
    int T,
    uint32_t seed
);