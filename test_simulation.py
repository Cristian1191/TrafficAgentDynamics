import nasch_core
import time

# --- Parámetros de la Simulación ---
N_CARS = 10         # Número de autos
LENGTH = 100        # Longitud de la carretera (L)
V_MAX = 5           # Velocidad máxima
P_SLOW = 0.3        # Probabilidad de frenado aleatorio (p)
STEPS = 50          # Número de pasos de simulación (T)
SEED = int(time.time()) # Semilla aleatoria

print(f"--- Inicializando Simulación NASCH (L={LENGTH}, V_max={V_MAX}) ---")
print(f"Coches (N): {N_CARS}, Pasos (T): {STEPS}, Semilla: {SEED}")
print("-" * 50)
# 1. Prueba de la Clase Auto y sus métodos
try:
    print("1. Probando clase Auto...")
    coche = nasch_core.Auto(position=5, velocity=2)
    print(f"   Auto inicial: Pos={coche.pos}, Vel={coche.vel}")

    coche.accelerate(V_MAX)
    print(f"   Después de accelerate: Vel={coche.vel}") # Debería ser 3

    coche.brake_to_gap(1)
    print(f"   Después de brake_to_gap(1): Vel={coche.vel}") # Debería ser 1
except Exception as e:
    print(f"   ERROR al probar la clase Auto: {e}")
    
print("-" * 50)

# 2. Prueba de la función de inicialización (int_random_position)
try:
    print("2. Probando función init_random_position...")
    
    # Llama a la función de C++ para obtener el vector<Auto>
    cars = nasch_core.init_random_position(N_CARS, LENGTH, SEED)
    
    print(f"   Se crearon {len(cars)} autos.")
    print("   Primeros 3 autos:")
    
    # Itera sobre los objetos Auto devueltos por C++
    for i in range(min(3, len(cars))):
        print(f"     Auto {i}: Pos={cars[i].pos}, Vel={cars[i].vel}")
        
except Exception as e:
    print(f"   ERROR al probar la inicialización: {e}")

print("-" * 50)

# 3. Prueba de la simulación completa (run_simulation)
try:
    print("3. Probando función run_simulation...")
    
    # La función run_simulation ejecuta T pasos, pero no devuelve nada (void)
    # Por ahora, solo probamos que se ejecute sin errores.
    start_time = time.time()
    nasch_core.run_simulation(N_CARS, LENGTH, V_MAX, P_SLOW, STEPS, SEED)
    end_time = time.time()
    
    print(f"   Simulación de {STEPS} pasos completada.")
    print(f"   Tiempo de ejecución (C++): {end_time - start_time:.6f} segundos.")
    print("   ¡La vinculación funciona correctamente!")
    
except Exception as e:
    print(f"   ERROR al probar run_simulation: {e}")

print("-" * 50)