import multiprocessing as mp

def generar_serie(inicio, fin):
    return [2 * i for i in range(inicio, fin)]

def principal(M, N):
    terminos_por_proc = N // M
    procesos = []
    resultados = []

    # Crear una cola para recibir los resultados
    cola_resultados = mp.Queue()

    for i in range(M):
        inicio = i * terminos_por_proc + 1  
        fin = inicio + terminos_por_proc if i != M - 1 else N + 1  # +1 para incluir el último término

        p = mp.Process(target=lambda q, s, e: q.put(generar_serie(s, e)), args=(cola_resultados, inicio, fin))
        procesos.append(p)
        p.start()

    for _ in procesos:
        resultados.extend(cola_resultados.get())

    for p in procesos:
        p.join()

    resultados.sort()

    return resultados

if __name__ == "__main__":
    M = 4  
    N = int(input("Introduce el número de términos en la serie: "))

    serie = principal(M, N)
    print(*serie)
