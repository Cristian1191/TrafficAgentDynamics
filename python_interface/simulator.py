import nasch_core
import numpy as np
import matplotlib.pyplot as plt
import time # Asegúrate de que 'time' esté importado

# --- Parámetros de la Simulación ---
N_CARS = 50
LENGTH = 500
V_MAX = 5
P_SLOW = 0.3
STEPS = 1000


def run_and_plot_nasch(N, L, V_MAX, P_SLOW, T):
    
    # GENERAR UNA SEMILLA ÚNICA USANDO MICROSEGUNDOS
    # C++ lo recibirá como uint32_t.
    current_seed = int(time.time() * 1000000) % 4294967295 
    
    print(f"--- Inicializando Simulación NASCH (L={L}, V_max={V_MAX}) ---")
    print(f"Coches (N): {N}, Pasos (T): {T}, Semilla: {current_seed}")
    print("-" * 50)
    
    # 1. Ejecutar la simulación con la nueva semilla
    final_cars = nasch_core.run_simulation(N, L, V_MAX, P_SLOW, T, current_seed)
    
    # 2. Extraer posiciones y velocidades
    positions = [car.pos for car in final_cars]
    velocities = [car.vel for car in final_cars]
    
    # 3. Graficación
    plt.figure(figsize=(10, 5))
    plt.scatter(positions, velocities, alpha=0.7, edgecolors='w', s=50)
    
    plt.title(f'Modelo NaSch: Posición vs. Velocidad (T={T} pasos, Semilla: {current_seed})')
    plt.xlabel('Posición (L)')
    plt.ylabel('Velocidad (V)')
    plt.xlim(0, L)
    plt.ylim(0, V_MAX + 1)
    plt.grid(True, linestyle='--', alpha=0.6)
    plt.show()

# Ejecutar la función SIN pasar una semilla fija
run_and_plot_nasch(N_CARS, LENGTH, V_MAX, P_SLOW, STEPS)