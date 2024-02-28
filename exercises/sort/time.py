import os
import time

# Lista dos programas de classificação
sort_programs = ['sort1', 'sort2', 'sort3']

# Lista dos arquivos de teste
test_files = ['reversed10000.txt', 'random100000.txt']

# Dicionário para armazenar os resultados
results = {}

# Loop através de cada programa de classificação
for program in sort_programs:
    results[program] = {}

    # Loop através de cada arquivo de teste
    for file in test_files:
        start_time = time.time()

        # Execute o programa de classificação no arquivo de teste
        os.system(f'./{program} {file}')

        end_time = time.time()

        # Calcule o tempo de execução
        execution_time = end_time - start_time

        # Armazene o tempo de execução no dicionário de resultados
        results[program][file] = execution_time

# Imprima os resultados
for program, timings in results.items():
    print(f'Programa: {program}')
    for file, timing in timings.items():
        print(f'  Arquivo: {file}, Tempo de execução: {timing} segundos')
    print('\n')
