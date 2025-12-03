#include "nasch_core.h"
#include <random>
#include <algorithm>
Auto::Auto(int position, int velocity) noexcept
    : pos(position), vel(velocity) {}

// Agregamos la lógica que mientras no se llegue a la velocidad máxima el auto acelerará
void Auto::accelerate(int v_max) noexcept {
    if (vel<v_max) vel++;
}
// Aquí tambien empezamos a agregar el frenado gap (distancia)
void Auto::brake_to_gap(int gap) noexcept {
    if (vel>gap) vel=gap;
}
void Auto::random_slow(double p, uint32_t rnd) noexcept {
    if(vel>0) {
        // Convertimos un entero de 32-bit a un double en [0,1]
        double r= (double)rnd/ 4294967295.0;
        if(r<p) vel--;
    }
}
std::vector<Auto> int_random_position(int N, int L, uint32_t seed) {
    std::vector<int> all_positions(L);
    for (int i=0; i<L; i++) all_positions[i]=i;
    std::mt19937 rng(seed);
    std::shuffle(all_positions.begin(),all_positions.end(), rng); // Reordenamos aleatoriamente

    std::vector<Auto> cars;
    cars.reserve(N);
    for (int i=0; i< N; i++) cars.emplace_back(all_positions[i],0); // Aqui recien agregamos posiciones en nuestra lista de autos(cars) mediante un push.
    // Ordenamos por la posicion en la que se cuentra el auto
    std::sort(cars.begin(), cars.end(),
        [](const Auto& a, const Auto& b){return a.pos < b.pos;});
    return cars;
}
// Modelo NASCH -> Acelera, aleatoriza, mueve y reordena
void step_nasch(std::vector<Auto>& cars, int L, int v_max, double p, uint32_t seed) {
    int N= cars.size();
    // 1. Aceleramos
    for (int i=0; i<N; ++i) cars[i].accelerate(v_max);
    // 2. Frenado por distancia
    for (int i=0; i<N; ++i){
        int next= (i+1)%N; // Será una carretara circular ya que las posiciones se van a repetir (%N)
        int gap = (cars[next].pos - cars[i].pos -1 + L) %L;
        cars[i].brake_to_gap(gap);
    }
    // 3. Disminución de velocidad por aleatoriedad
    std::mt19937  rng(seed);
    for(int i=0; i<N; ++i) cars[i].random_slow(p,rng());
    // 4. Movimiento a los autos en cars
    for(int i=0; i<N; ++i) cars[i].pos = (cars[i].pos +cars[i].vel) %L;
    // 5. Reordenar por posición para la siguiente iteración
    std::sort(cars.begin(), cars.end(),
        [](const Auto& a, const Auto& b){return a.pos < b.pos;});
}
// Ahora creamos los bucles completos "T" para el wrapper
std::vector<Auto> run_simulation(int N, int L, int v_max, double p, int T, uint32_t seed){
    auto cars = int_random_position(N,L,seed);
    for (int t=0;t<T;++t) step_nasch(cars, L,v_max,p, seed+t);
    return cars; // ¡Devuelve el resultado final!
}
