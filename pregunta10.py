#Pregunta 10
import multiprocessing as mp

def generate_series(start, end):
    return [2 * i for i in range(start, end)]

def main(M, N):
    # Calcular la cantidad de términos por procesador
    terms_per_proc = N // M
    processes = []
    results = []

    # Crear una cola para recibir los resultados
    result_queue = mp.Queue()

    for i in range(M):
        start = i * terms_per_proc + 1  # Comenzar desde 1 para la multiplicación por 2
        end = start + terms_per_proc if i != M - 1 else N + 1  # +1 para incluir el último término

        # Crear y arrancar el proceso
        p = mp.Process(target=lambda q, s, e: q.put(generate_series(s, e)), args=(result_queue, start, end))
        processes.append(p)
        p.start()

    # Recoger los resultados de los procesos
    for _ in processes:
        results.extend(result_queue.get())

    # Asegurarse de que todos los procesos han terminado
    for p in processes:
        p.join()

    # Ordenar los resultados para mantener el orden correcto
    results.sort()

    return results

if __name__ == "__main__":
    M = 4  # Número de procesadores

    # Solicitar al usuario el número de términos
    N = int(input("Introduce el número de términos en la serie: "))

    series = main(M, N)
    print(*series)