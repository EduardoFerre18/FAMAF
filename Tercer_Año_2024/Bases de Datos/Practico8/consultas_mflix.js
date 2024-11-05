use("mflix");

// Realizar las consultas usando el pipeline de agregación

// Ejercicio 1

/*
1. Cantidad de cines (theaters) por estado.
*/

db.theaters.aggregate([
  {
    $group: {
      _id: "$location.address.state",
      total: {
        $sum: 1,
      },
    },
  },
]);

// Ejercicio 2

/*
Cantidad de estados con al menos dos cines (theaters) registrados.
 */

db.theaters.aggregate([
  {
    $group: {
      _id: "$location.address.state",
      total: {
        $sum: 1,
      },
    },
  },
  {
    $match: {
      total: {
        $gte: 2,
      },
    },
  },
  {
    $count: "total",
  },
]);

// Ejercicio 3

/*
Cantidad de películas dirigidas por "Louis Lumière". Se puede responder sin pipeline de
agregación, realizar ambas queries.
*/

db.movies
  .find({
    directors: "Louis Lumière",
  })
  .count();

db.movies.aggregate([
  {
    $match: {
      directors: "Louis Lumière",
    },
  },
  {
    $count: "total",
  },
]);

// Ejercicio 4

/*
Cantidad de películas estrenadas en los años 50 (desde 1950 hasta 1959). Se puede
responder sin pipeline de agregación, realizar ambas queries.

*/

db.movies
  .find({
    year: {
      $gte: 1950,
      $lte: 1959,
    },
  })
  .count();

db.movies.aggregate([
  {
    $match: {
      year: {
        $gte: 1950,
        $lte: 1959,
      },
    },
  },
  {
    $count: "peliculas_en_los_50s",
  },
]);

// Ejercicio 5

/*
Listar los 10 géneros con mayor cantidad de películas (tener en cuenta que las películas
pueden tener más de un género). Devolver el género y la cantidad de películas. Hint:
unwind puede ser de utilidad

*/

db.movies.aggregate([
  {
    $unwind: "$genres",
  },
  {
    $group: {
      _id: "$genres",
      total: {
        $sum: 1,
      },
    },
  },
  {
    $sort: {
      total: -1,
    },
  },
  {
    $limit: 10,
  },
]);

// Ejercicio 6

/*
 Top 10 de usuarios con mayor cantidad de comentarios, mostrando Nombre, Email y
Cantidad de Comentarios.
 */

db.comments.aggregate([
  {
    $group: {
      _id: { name: "$name", email: "$email" },
      total: {
        $sum: 1,
      },
    },
  },
  {
    $sort: {
      total: -1,
    },
  },
  {
    $limit: 10,
  },
]);

// Ejercicio 7

/* 
7. Ratings de IMDB promedio, mínimo y máximo por año de las películas estrenadas en
los años 80 (desde 1980 hasta 1989), ordenados de mayor a menor por promedio del
año.


*/

db.movies.aggregate([
  {
    $match: {
      year: {
        $gte: 1980,
        $lte: 1989,
      },
      "imdb.rating": { $type: "number" },
    },
  },
  {
    $group: {
      _id: "$year",
      promedio: {
        $avg: "$imdb.rating",
      },
      minimo: {
        $min: "$imdb.rating",
      },
      maximo: {
        $max: "$imdb.rating",
      },
    },
  },
  {
    $sort: {
      promedio: -1,
    },
  },
]);

// Ejercicio 8

/* 

Título, año y cantidad de comentarios de las 10 películas con más comentarios.
*/

db.comments.aggregate([
  {
    $group: {
      _id: "$movie_id",
      comments: {
        $sum: 1,
      },
    },
  },
  {
    $sort: {
      comments: -1,
    },
  },
  {
    $limit: 10,
  },
  {
    $lookup: {
      from: "movies",
      localField: "_id",
      foreignField: "_id",
      as: "movie",
    },
  },
  {
    $unwind: "$movie",
  },
  {
    $project: {
      title: "$movie.title",
      year: "$movie.year",
      comments: 1,
    },
  },
]);

// Ejercicio 9

/*
Crear una vista con los 5 géneros con mayor cantidad de comentarios, junto con la
cantidad de comentarios.
*/

db.createView("top5_genres_comments", "comments", [
  {
    $group: {
      _id: "$movie_id",
      cant_comments: { $sum: 1 },
    },
  },
  {
    $lookup: {
      from: "movies",
      localField: "_id",
      foreignField: "_id",
      as: "movie",
    },
  },
  {
    $unwind: "$movie",
  },
  {
    $project: {
      genres: "$movie.genres",
      cant_comments: 1,
    },
  },
  {
    $unwind: "$genres",
  },
  {
    $group: {
      _id: "$genres",
      cant_comments: { $sum: "$cant_comments" },
    },
  },
  {
    $sort: {
      cant_comments: -1,
    },
  },
  {
    $limit: 5,
  },
]);

db.top5_genres_comments.find();

// Ejercicio 10

/* 
Listar los actores (cast) que trabajaron en 2 o más películas dirigidas por "Jules Bass".
Devolver el nombre de estos actores junto con la lista de películas (solo título y año)
dirigidas por “Jules Bass” en las que trabajaron.
a. Hint1: addToSet
b. Hint2: {'name.2': {$exists: true}} permite filtrar arrays con al menos 2
elementos, entender por qué.
*/

db.movies.aggregate([
  {
    $match: {
      directors: { $elemMatch: { $regex: /Jules Bass/i } },
    },
  },
  {
    $unwind: "$cast",
  },
  {
    $group: {
      _id: "$cast",
      movies: {
        $addToSet: {
          _id: "$_id",
          title: "$title",
          year: "$year",
        },
      },
    },
  },
  {
    $match: {
      "movies.1": { $exists: true },
    },
  },
  {
    $project: {
      actor_name: "$_id",
      movies: 1,
      _id: 0,
    },
  },
]);

// Ejercicio 11

/* 
Listar los usuarios que realizaron comentarios durante el mismo mes de lanzamiento de
la película comentada, mostrando Nombre, Email, fecha del comentario, título de la
película, fecha de lanzamiento. HINT: usar $lookup con multiple condiciones

*/

db.comments.aggregate([
  {
    $lookup: {
      from: "movies",
      localField: "movie_id",
      foreignField: "_id",
      as: "movie",
    },
  },
  {
    $unwind: "$movie",
  },
  {
    $match: {
      $expr: {
        $and: [
          { $eq: [{ $month: "$date" }, { $month: "$movie.released" }] },
          { $eq: [{ $year: "$date" }, { $year: "$movie.released" }] },
        ],
      },
    },
  },
  {
    $project: {
      user_name: "$name",
      user_email: "$email",
      comment_date: "$date",
      movie_released_date: "$movie.released",
      movie_title: "$movie.title",
      _id: 0,
    },
  },
]);
