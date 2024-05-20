import multiprocessing
from math import sqrt

def fibonacci(n):
    sqrt5 = sqrt(5)
    phi = (1 + sqrt5) / 2
    psi = (1 - sqrt5) / 2
    return int((1 / sqrt5) * (phi ** n - psi ** n))

def trabajador(inicio, fin, cola_resultados):
    resultados = []
    for i in range(inicio, fin):
        resultados.append(fibonacci(i))
    cola_resultados.put(resultados)

def principal():
    n = 1000
    num_procesadores = multiprocessing.cpu_count()
    tamaño_chunk = n // num_procesadores

    cola_resultados = multiprocessing.Queue()

    procesos = []
    for i in range(num_procesadores):
        inicio = i * tamaño_chunk + 1
        fin = (i + 1) * tamaño_chunk + 1 if i < num_procesadores - 1 else n + 1
        proceso = multiprocessing.Process(target=trabajador, args=(inicio, fin, cola_resultados))
        procesos.append(proceso)
        proceso.start()

    for proceso in procesos:
        proceso.join()

    # Recolectar resultados de la cola
    resultados = []
    while not cola_resultados.empty():
        resultados.extend(cola_resultados.get())

    print("Secuencia de Fibonacci hasta el término", n, ":", resultados)

if __name__ == "__main__":
    principal()
