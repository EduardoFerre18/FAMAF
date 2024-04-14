import requests

# Obtener todas las películas
response = requests.get('http://localhost:5000/peliculas')
peliculas = response.json()
print("Películas existentes:")
for pelicula in peliculas:
    print(f"ID: {pelicula['id']}, Título: {pelicula['titulo']}, Género: {pelicula['genero']}")
print()

# Agregar una nueva película
nueva_pelicula = {
    'titulo': 'Pelicula de prueba',
    'genero': 'Acción'
}
response = requests.post('http://localhost:5000/peliculas', json=nueva_pelicula)
if response.status_code == 201:
    pelicula_agregada = response.json()
    print("Película agregada:")
    print(f"ID: {pelicula_agregada['id']}, Título: {pelicula_agregada['titulo']}, Género: {pelicula_agregada['genero']}")
else:
    print("Error al agregar la película.")
print()

# Obtener detalles de una película específica
id_pelicula = 1  # ID de la película a obtener
response = requests.get(f'http://localhost:5000/peliculas/{id_pelicula}')
if response.status_code == 200:
    pelicula = response.json()
    print("Detalles de la película:")
    print(f"ID: {pelicula['id']}, Título: {pelicula['titulo']}, Género: {pelicula['genero']}")
else:
    print("Error al obtener los detalles de la película.")
print()

# Actualizar los detalles de una película
id_pelicula = 1  # ID de la película a actualizar
datos_actualizados = {
    'titulo': 'Nuevo título',
    'genero': 'Comedia'
}
response = requests.put(f'http://localhost:5000/peliculas/{id_pelicula}', json=datos_actualizados)
if response.status_code == 200:
    pelicula_actualizada = response.json()
    print("Película actualizada:")
    print(f"ID: {pelicula_actualizada['id']}, Título: {pelicula_actualizada['titulo']}, Género: {pelicula_actualizada['genero']}")
else:
    print("Error al actualizar la película.")
print()

# Eliminar una película
id_pelicula = 1  # ID de la película a eliminar
response = requests.delete(f'http://localhost:5000/peliculas/{id_pelicula}')
if response.status_code == 200:
    print("Película eliminada correctamente.")
else:
    print("Error al eliminar la película.")
print()

# tests para funcionalidades nuevas
# Devolver peliculas de un genero especifico
genero_pelicula = 'Acción'
response = requests.get(f'http://localhost:5000/peliculas/{genero_pelicula}')
peliculas = response.json()
if response.status_code == 200:
    print("Peliculas del genero Acción:")
    for pelicula in peliculas:
        print(f"ID: {pelicula['id']}, Título: {pelicula['titulo']}, Género: {pelicula['genero']}")
else:
    print("Error al solicitar peliculas por genero")
print()

# Buscar peliculas por titulo
titulo_pelicula = 'The'
response = requests.get(f'http://localhost:5000/peliculas/buscar/{titulo_pelicula}')
peliculas = response.json()
if response.status_code == 200:
    print("Peliculas con The en el titulo:")
    for pelicula in peliculas:
        print(f"ID: {pelicula['id']}, Título: {pelicula['titulo']}, Género: {pelicula['genero']}")
else:
    print("Error al buscar peliculas por titulo")
print()

# Obtener una pelicula aleatoria
response = requests.get(f'http://localhost:5000/peliculas/aleatoria')
if response.status_code == 200:
    pelicula = response.json()
    print("Sugerencia aleatoria:")
    print(f"ID: {pelicula['id']}, Título: {pelicula['titulo']}, Género: {pelicula['genero']}")
else:
    print("Error al obtener una sugerencia aleatoria")
print()

# Obtener una pelicula aleatoria segun genero
genero_pelicula = 'Acción'
response = requests.get(f'http://localhost:5000/peliculas/aleatoria/{genero_pelicula}')
if response.status_code == 200:
    pelicula = response.json()
    print("Sugerencia aleatoria de genero Acción")
    print(f"ID: {pelicula['id']}, Título: {pelicula['titulo']}, Género: {pelicula['genero']}")
else:
    print("Error al obtener una pelicula aleatoria de un genero especifico")
print()

# Obtener una pelicula aleatoria para el siguiente feriado
genero_pelicula = 'Acción'
response = requests.get(f'http://127.0.0.1:5000/peliculas/feriado/{genero_pelicula}')
if response.status_code == 200:
    feriado = response.json()[0]
    pelicula = response.json()[1]
    print(f"El proximo feriado es el {feriado['dia']} con motivo {feriado['motivo']}")
    print(f"Pelicula de Acción sugerida:")
    print(f"ID: {pelicula['id']}, Título: {pelicula['titulo']}, Género: {pelicula['genero']}")
else:
    print("Error al obtener una sugerir una pelicula para el siguiente feriado")
print()