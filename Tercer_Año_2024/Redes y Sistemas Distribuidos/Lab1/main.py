import random
from flask import Flask, jsonify, request
import requests
from datetime import date
from unidecode import unidecode
from proximo_feriado import NextHoliday
from proximo_feriado import months

app = Flask(__name__)
peliculas = [
    {'id': 1, 'titulo': 'Indiana Jones', 'genero': 'Acción'},
    {'id': 2, 'titulo': 'Star Wars', 'genero': 'Acción'},
    {'id': 3, 'titulo': 'Interstellar', 'genero': 'Ciencia ficción'},
    {'id': 4, 'titulo': 'Jurassic Park', 'genero': 'Aventura'},
    {'id': 5, 'titulo': 'The Avengers', 'genero': 'Acción'},
    {'id': 6, 'titulo': 'Back to the Future', 'genero': 'Ciencia ficción'},
    {'id': 7, 'titulo': 'The Lord of the Rings', 'genero': 'Fantasía'},
    {'id': 8, 'titulo': 'The Dark Knight', 'genero': 'Acción'},
    {'id': 9, 'titulo': 'Inception', 'genero': 'Ciencia ficción'},
    {'id': 10, 'titulo': 'The Shawshank Redemption', 'genero': 'Drama'},
    {'id': 11, 'titulo': 'Pulp Fiction', 'genero': 'Crimen'},
    {'id': 12, 'titulo': 'Fight Club', 'genero': 'Drama'}
]


def obtener_peliculas():
    return jsonify(peliculas)


def obtener_pelicula(id):
    # Lógica para buscar la película por su ID y devolver sus detalles
    pelicula_encontrada = None
    for pelicula in peliculas:
        if pelicula['id'] == id:
            pelicula_encontrada = pelicula
            return jsonify(pelicula_encontrada)
    return jsonify({'mensaje': 'Película no encontrada'}), 404


def agregar_pelicula():
    nueva_pelicula = {
        'id': obtener_nuevo_id(),
        'titulo': request.json['titulo'],
        'genero': request.json['genero']
    }
    peliculas.append(nueva_pelicula)
    print(peliculas)
    return jsonify(nueva_pelicula), 201


def actualizar_pelicula(id):
    # Lógica para buscar la película por su ID y actualizar sus detalles
    pelicula_actualizada = None
    for pelicula in peliculas:
        if pelicula['id'] == id:
            pelicula['titulo'] = request.json['titulo']
            pelicula['genero'] = request.json['genero']
            pelicula_actualizada = pelicula
            return jsonify(pelicula_actualizada)
    return jsonify({'mensaje': 'Pelicula no encontrada'}), 404


def eliminar_pelicula(id):
    # Lógica para buscar la película por su ID y eliminarla
    peliculas.pop(id-1)
    # Reasignamos los ID
    if (len(peliculas) > id):
        for i in range(id, len(peliculas)):
            peliculas[i-1]['id'] = i
    return jsonify({'mensaje': 'Pelicula eliminada correctamente'})


def obtener_nuevo_id():
    if len(peliculas) > 0:
        ultimo_id = peliculas[-1]['id']
        return ultimo_id + 1
    else:
        return 1


def obtener_peliculas_por_genero(genero):
    genero_norm = unidecode(genero)
    lista_genero = []
    for pelicula in peliculas:
        if unidecode(pelicula['genero']).lower() == genero_norm.lower():
            lista_genero.append(pelicula)
    if (lista_genero != []):
        return jsonify(lista_genero)
    return jsonify({'mensaje': 'Pelicula no encontrada'}), 404


def buscar_peliculas_por_titulo(subcadena):
    peliculas_encontradas = []
    for pelicula in peliculas:
        if subcadena.lower() in pelicula['titulo'].lower():
            peliculas_encontradas.append(pelicula)
    if (peliculas_encontradas != []):
        return jsonify(peliculas_encontradas)
    return jsonify({'mensaje': 'Pelicula no encontrada'}), 404


def pelicula_aleatoria():
    pelicula_aleatoria = random.choice(peliculas)
    return jsonify(pelicula_aleatoria)


def pelicula_aleatoria_genero(genero):
    genero_norm = unidecode(genero)
    try:
        lista_genero = obtener_peliculas_por_genero(genero_norm).json
    except:
        return jsonify({'mensaje': 'No hay peliculas en el genero especificado'}), 404
    if lista_genero:
        pelicula_aleatoria = random.choice(lista_genero)
        return jsonify(pelicula_aleatoria)
    else:
        return jsonify({'mensaje': 'No hay peliculas en el genero especificado'}), 404


# Funcion auxiliar. El enunciado solo pide fecha y motivo del feriado
def limpiar_feriado(feriado):
    feriado_limpio = {
        'dia': feriado['dia'], 'mes': months[feriado['mes'] - 1], 'motivo': feriado['motivo']}
    return feriado_limpio


def obtener_feriado_pelicula(genero):
    genero_norm = unidecode(genero)
    feriado_pelicula = []
    feriado = NextHoliday()
    feriado.fetch_holidays()
    feriado_limpio = limpiar_feriado(feriado.holiday)
    feriado_pelicula.append(feriado_limpio)
    try:
        pelicula = pelicula_aleatoria_genero(genero_norm).json
        feriado_pelicula.append(pelicula)
        return jsonify(feriado_pelicula)
    except:
        return jsonify({'mensaje': 'No hay peliculas en el genero especificado'}), 404


app.add_url_rule('/peliculas', 'obtener_peliculas',
                 obtener_peliculas, methods=['GET'])
app.add_url_rule('/peliculas/<int:id>', 'obtener_pelicula',
                 obtener_pelicula, methods=['GET'])
app.add_url_rule('/peliculas', 'agregar_pelicula',
                 agregar_pelicula, methods=['POST'])
app.add_url_rule('/peliculas/<int:id>', 'actualizar_pelicula',
                 actualizar_pelicula, methods=['PUT'])
app.add_url_rule('/peliculas/<int:id>', 'eliminar_pelicula',
                 eliminar_pelicula, methods=['DELETE'])
app.add_url_rule('/peliculas/<string:genero>', 'obtener_peliculas_por_genero',
                 obtener_peliculas_por_genero, methods=['GET'])
app.add_url_rule('/peliculas/buscar/<string:subcadena>',
                 'buscar_peliculas_por_titulo', buscar_peliculas_por_titulo, methods=['GET'])
app.add_url_rule('/peliculas/aleatoria', 'pelicula_aleatoria',
                 pelicula_aleatoria, methods=['GET'])
app.add_url_rule('/peliculas/aleatoria/<string:genero>',
                 'pelicula_aleatoria_genero', pelicula_aleatoria_genero, methods=['GET'])
app.add_url_rule('/peliculas/feriado/<string:genero>',
                 'obtener_feriado_pelicula', obtener_feriado_pelicula, methods=['GET'])

if __name__ == '__main__':
    app.run()
