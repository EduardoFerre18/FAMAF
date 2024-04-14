import requests
import pytest
import requests_mock

@pytest.fixture
def mock_response():
    with requests_mock.Mocker() as m:
        # Simulamos la respuesta para obtener todas las películas
        m.get('http://localhost:5000/peliculas', json=[
            {'id': 1, 'titulo': 'Indiana Jones', 'genero': 'Acción'},
            {'id': 2, 'titulo': 'Star Wars', 'genero': 'Acción'}
        ])

        # Simulamos la respuesta para agregar una nueva película
        m.post('http://localhost:5000/peliculas', status_code=201, json={'id': 3, 'titulo': 'Pelicula de prueba', 'genero': 'Acción'})

        # Simulamos la respuesta para obtener detalles de una película específica
        m.get('http://localhost:5000/peliculas/1', json={'id': 1, 'titulo': 'Indiana Jones', 'genero': 'Acción'})

        # Simulamos la respuesta para actualizar los detalles de una película
        m.put('http://localhost:5000/peliculas/1', status_code=200, json={'id': 1, 'titulo': 'Nuevo título', 'genero': 'Comedia'})

        # Simulamos la respuesta para eliminar una película
        m.delete('http://localhost:5000/peliculas/1', status_code=200)

        # nuevas simulaciones para nuevas funciones
        # Simulamos la respuesta para obtener peliculas por genero
        m.get('http://localhost:5000/peliculas/Ciencia ficción', status_code=200, json=[
            {'id': 3, 'titulo': 'Interstellar', 'genero': 'Ciencia ficción'},
            {'id': 6, 'titulo': 'Back to the Future', 'genero': 'Ciencia ficción'},
            {'id': 9, 'titulo': 'Inception', 'genero': 'Ciencia ficción'}
        ])

        # Simulamos la respuesta de buscar peliculas a partir de un string
        m.get('http://localhost:5000/peliculas/buscar/ark', status_code=200, json=[
            {"genero":"Aventura","id":4,"titulo":"Jurassic Park"},
            {"genero":"Acci\u00f3n","id":8,"titulo":"The Dark Knight"}
        ])

        yield m

def test_obtener_peliculas(mock_response):
    response = requests.get('http://localhost:5000/peliculas')
    assert response.status_code == 200
    assert len(response.json()) == 2

def test_agregar_pelicula(mock_response):
    nueva_pelicula = {'titulo': 'Pelicula de prueba', 'genero': 'Acción'}
    response = requests.post('http://localhost:5000/peliculas', json=nueva_pelicula)
    assert response.status_code == 201
    assert response.json()['id'] == 3

def test_obtener_detalle_pelicula(mock_response):
    response = requests.get('http://localhost:5000/peliculas/1')
    assert response.status_code == 200
    assert response.json()['titulo'] == 'Indiana Jones'

def test_actualizar_detalle_pelicula(mock_response):
    datos_actualizados = {'titulo': 'Nuevo título', 'genero': 'Comedia'}
    response = requests.put('http://localhost:5000/peliculas/1', json=datos_actualizados)
    assert response.status_code == 200
    assert response.json()['titulo'] == 'Nuevo título'

def test_eliminar_pelicula(mock_response):
    response = requests.delete('http://localhost:5000/peliculas/1')
    assert response.status_code == 200

def test_peliculas_por_genero(mock_response):
    response = requests.get('http://localhost:5000/peliculas/Ciencia ficción')
    assert response.status_code == 200
    assert len(response.json()) == 3

def test_peliculas_por_string(mock_response):
    response = requests.get('http://localhost:5000/peliculas/buscar/ark')
    assert response.status_code == 200
    assert len(response.json()) == 2