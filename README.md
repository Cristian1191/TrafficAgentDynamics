# Simulador de Tráfico (NaSch) — Explicación conceptual

Resumen
- Este proyecto implementa una versión del modelo de tráfico de Nagel–Schreckenberg (NaSch). Es una simulación discreta en tiempo y espacio que reproduce comportamientos básicos del tráfico: aceleración, frenado por falta de espacio, y ralentizaciones aleatorias.
- El objetivo es modelar tráfico realístico a nivel macroscópico y usar simulaciones tipo Monte Carlo para estimar cantidades observables (velocidad media, flujo, tiempos de viaje) y analizar decisiones de agentes en marcos de teoría de juegos.

Idea física y comportamientos modelados (intuitivo)
- Vehículos discretos ocupan posiciones en una vía circular o en una rejilla. Cada paso temporal todos los coches actualizan su velocidad y posición según reglas sencillas.
- Aceleración: si hay espacio libre, el coche intenta aumentar su velocidad hasta una velocidad máxima.
- Frenado por distancia (gap): si el coche delantero está cercano, el vehículo reduce la velocidad para evitar colisiones. Esta regla incorpora la distancia de frenado mínima.
- Ralentización aleatoria: representa pequeñas variaciones humanas o condiciones (errores de conducción, reacción, pavimento), modelada como probabilidad de reducir la velocidad un paso.
- Estas tres reglas juntas producen fenómenos reales como formación de ondas de choque (atascos espontáneos) y dependencia del flujo con la densidad.

Cómo se refleja esto en el código (mapa conceptual)
- Auto (estructura/clase): contiene posición y velocidad del vehículo; métodos principales:
  - accelerate — incrementa velocidad hacia v_max.
  - brake_to_gap — reduce velocidad para respetar la distancia al vehículo de delante.
  - random_slow — aplica la ralentización aleatoria.
- step_nasch: ejecuta las reglas anteriores en el orden clásico (acelerar, frenar por gap, random slow, mover).
- int_random_position / init_random_position: colocan los vehículos aleatoriamente en la vía para crear una configuración inicial.
- run_simulation: corre T pasos y devuelve estados (posiciones/velocidades) para análisis posterior.
- Interface Python (pybind11): expone estas funciones/clases al entorno Python para ejecutar experimentos, procesar resultados y graficar.

Qué puede medir y cómo interpretarlo
- Velocidad media: promedio sobre vehículos y repeticiones — indicador de eficiencia del sistema.
- Flujo (flow): número de coches que pasan por un punto por unidad de tiempo; depende no linealmente de la densidad.
- Tiempos de viaje y retardos: útiles para evaluar utilidad en teoría de juegos.
- Eventos de frenado: frecuencia y magnitud de frenadas abruptas (indicador de inseguridad y riesgo).
- Para cada observable, use R réplicas independientes (Monte Carlo) y calcule media y desviación estándar para cuantificar incertidumbre.

Uso como experimento Monte Carlo y vínculo con teoría de juegos (intuitivo)
- Monte Carlo: repetir la simulación con distintas semillas y promediar observables permite estimar valores esperados y distribuciones de salida bajo las mismas reglas.
- Vehículos como agentes: cada agente puede tener parámetros (por ejemplo, v_max, probabilidad de frenado, agresividad al adelantar). Esas elecciones son sus “estrategias”.
- Pago / utilidad: puede definirse según velocidad media, tiempo de viaje, consumo estimado o riesgo (número de frenadas bruscas). La utilidad esperada se obtiene promediando resultados de R réplicas.
- Análisis de equilibrio: comparando utilidades esperadas para distintas combinaciones de parámetros, puede investigarse si existe alguna estrategia dominante, equilibrio de Nash aproximado, o incentivos para cooperar (ej. mantener distancia).

Cómo ejecutar (rápido)
- Instalar dependencias de build (si usa bindings):
  - pip install -U pybind11 wheel setuptools
- Compilar la extensión (directorio raíz):
  - python setup.py build_ext --inplace
- Ejecutar ejemplo:
  - python python_interface/simulator.py
- Ejecutar pruebas:
  - python test_simulation.py

Limitaciones y supuestos importantes
- Modelo discreto y simplificado: no modela dinámica continua (frenado físico exacto), reacciones humanas detalladas ni condiciones microclimáticas complejas.
- Reglas locales: no hay planificación a largo plazo ni comunicación explícita entre agentes salvo por la observación del gap.
- Parámetros y representación de seguridad/frenado deben calibrarse con datos reales para usos predictivos.

Sugerencias prácticas para análisis
- Use barridos de parámetros (densidad, probabilidad de frenado, v_max) y montecarlo por parámetro para obtener curvas de flujo vs. densidad con bandas de incertidumbre.
- Defina utilidades claras para agentes y calcule ganancias esperadas por réplica; compare estrategias con pruebas estadísticas simples.
- Registrar histogramas de velocidades y tiempos de viaje para capturar heterogeneidad.
