# philosophers-42MalagaProyect

## 📌 Descripción

Este proyecto implementa el clásico problema de los **filósofos comensales** ("Dining Philosophers"), una conocida metáfora utilizada en ciencias de la computación para ilustrar problemas de concurrencia y sincronización en sistemas multitarea.

El objetivo es aplicar conceptos de programación concurrente utilizando **hilos (threads)** y **mutexes** para evitar condiciones de carrera, bloqueos y hambrunas, respetando las normas del sistema operativo y del estándar POSIX.

## 🎯 Objetivos del proyecto

* Comprender y aplicar conceptos de **concurrencia**, **sincronización** y **exclusión mutua**.
* Implementar un sistema donde múltiples hilos (filósofos) comparten recursos limitados (tenedores) sin entrar en **deadlock** ni **starvation**.
* Profundizar en el uso de **pthread**, incluyendo `pthread_create`, `pthread_join`, y `pthread_mutex_*`.

## 🛠️ Tecnologías utilizadas

* Lenguaje: **C (C99)**
* Librerías: `pthread.h` (POSIX Threads)
* Sistema operativo: Basado en Unix (evaluado en Linux)
* Normas: Normas de codificación de la Escuela 42

## 🧪 Cómo compilar y ejecutar

### 🔧 Compilación

```bash
make
```

Esto generará el ejecutable `philo`.

### 🚀 Ejecución

```bash
./philo <n_filosofos> <tiempo_para_morir> <tiempo_para_comer> <tiempo_para_dormir> [n_comidas]
```

#### Parámetros

1. `n_filosofos`: Número de filósofos (y tenedores).
2. `tiempo_para_morir`: Tiempo (en milisegundos) que un filósofo puede estar sin comer antes de morir.
3. `tiempo_para_comer`: Tiempo (en milisegundos) que tarda un filósofo en comer.
4. `tiempo_para_dormir`: Tiempo (en milisegundos) que tarda un filósofo en dormir.
5. `n_comidas` *(opcional)*: Número de veces que cada filósofo debe comer antes de que el programa termine.

#### Ejemplo

```bash
./philo 5 800 200 200
```

Este comando ejecuta una simulación con 5 filósofos, cada uno muriendo si no come en 800 ms, tardando 200 ms en comer y 200 ms en dormir.

## 🧠 Conceptos clave

* **Mutexes**: Se utilizan para representar tenedores y evitar condiciones de carrera.
* **Hilos**: Cada filósofo es un hilo independiente que ejecuta su rutina.
* **Monitoreo**: Un hilo monitor vigila si algún filósofo muere (por falta de comida).

## ✅ Reglas implementadas

* Un filósofo solo puede tomar los tenedores adyacentes.
* Si un filósofo no come a tiempo, se imprime que ha muerto y la simulación termina.
* No se permite el deadlock ni la hambruna.
* Si se proporciona el número de comidas, el programa finaliza cuando todos los filósofos han comido al menos ese número de veces.
