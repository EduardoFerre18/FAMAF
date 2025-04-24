use("mflix");

// Ejercicio 1

/* 
Insertar 5 nuevos usuarios en la colección users. Para cada nuevo usuario creado,
insertar al menos un comentario realizado por el usuario en la colección comments.
*/

db.users.insertMany([
  {
    name: "usuario1",
    email: "usuario1@mail.com",
    password: "12345",
  },
  {
    name: "usuario2",
    email: "usuario2@mail.com",
    password: "12345",
  },
  {
    name: "usuario3",
    email: "usuario3@mail.com",
    password: "12345",
  },
  {
    name: "usuario4",
    email: "usuario4@mail.com",
    password: "12345",
  },
  {
    name: "usuario5",
    email: "usuario5@mail.com",
    password: "12345",
  },
]);

db.comments.insertMany([
  {
    name: "usuario1",
    email: "usuario1@mail.com",
    movie_id: ObjectId("573a1390f29313caabcd418c"),
    text: "Comentario del usuario 1",
    date: new Date(),
  },
  {
    name: "usuario2",
    email: "usuario2@mail.com",
    movie_id: ObjectId("573a1390f29313caabcd418c"),
    text: "Comentario del usuario 2",
    date: new Date(),
  },
  {
    name: "usuario3",
    email: "usuario3@mail.com",
    movie_id: ObjectId("573a1390f29313caabcd418c"),
    text: "Comentario del usuario 3",
    date: new Date(),
  },
  {
    name: "usuario4",
    email: "usuario4@mail.com",
    movie_id: ObjectId("573a1390f29313caabcd418c"),
    text: "Comentario del usuario 4",
    date: new Date(),
  },
  {
    name: "usuario5",
    email: "usuario5@mail.com",
    movie_id: ObjectId("573a1390f29313caabcd418c"),
    text: "Comentario del usuario 5",
    date: new Date(),
  },
]);

// Ejercicio 2

/*
Listar el título, año, actores (cast), directores y rating de las 10 películas con mayor
rating (“imdb.rating”) de la década del 90. ¿Cuál es el valor del rating de la película que
tiene mayor rating? (Hint: Chequear que el valor de “imdb.rating” sea de tipo “double”).
*/

db.movies
  .find(
    {
      year: { $gte: 1990, $lt: 2000 },
      "imdb.rating": { $type: "double" },
    },
    {
      title: 1,
      year: 1,
      cast: 1,
      directors: 1,
      "imdb.rating": 1,
    }
  )
  .sort({ "imdb.rating": -1 })
  .limit(10);

/* 
La pelicula con mayor rating es 
    _id: 573a1398f29313caabcebc0b
    title: The Civil War
    rating: 9.4

*/

// Ejercicio 3

/*
Listar el nombre, email, texto y fecha de los comentarios que la película con id
(movie_id) ObjectId("573a1399f29313caabcee886") recibió entre los años 2014 y 2016
inclusive. Listar ordenados por fecha. Escribir una nueva consulta (modificando la
anterior) para responder ¿Cuántos comentarios recibió?
*/

db.comments
  .find(
    {
      movie_id: ObjectId("573a1399f29313caabcee886"),
      date: {
        $gte: ISODate("2014-01-01T00:00:00Z"),
        $lte: ISODate("2016-12-31T23:59:59Z"),
      },
    },
    {
      name: 1,
      email: 1,
      text: 1,
      date: 1,
      _id: 0,
    }
  )
  .sort({ date: -1 });

// Para responder cuantos comentarios recibió hacemos la siguiente consulta:

db.comments.countDocuments({
  movie_id: ObjectId("573a1399f29313caabcee886"),
  date: {
    $gte: ISODate("2014-01-01T00:00:00Z"),
    $lte: ISODate("2016-12-31T23:59:59Z"),
  },
});

// El resultado es 34

// Ejercicio 4

/*
Listar el nombre, id de la película, texto y fecha de los 3 comentarios más recientes
realizados por el usuario con email patricia_good@fakegmail.com.

*/

db.comments
  .find(
    {
      email: "patricia_good@fakegmail.com",
    },
    {
      name: 1,
      movie_id: 1,
      text: 1,
      date: 1,
    }
  )
  .sort({ date: -1 })
  .limit(3);

// Ejercicio 5

/*
 Listar el título, idiomas (languages), géneros, fecha de lanzamiento (released) y número
de votos (“imdb.votes”) de las películas de géneros Drama y Action (la película puede
tener otros géneros adicionales), que solo están disponibles en un único idioma y por
último tengan un rating (“imdb.rating”) mayor a 9 o bien tengan una duración (runtime)
de al menos 180 minutos. Listar ordenados por fecha de lanzamiento y número de
votos.
 */

db.movies
  .find(
    {
      genres: { $in: ["Drama", "Action"] },
      countries: { $size: 1 },
      $or: [{ "imdb.rating": { $gt: 9 } }, { runtime: { $gte: 180 } }],
      released: { $type: "date" },
      "imdb.votes": { $type: "number" },
    },
    {
      title: 1,
      languages: 1,
      genres: 1,
      released: 1,
      "imdb.votes": 1,
    }
  )
  .sort({ released: -1, "imdb.votes": -1 });

// Ejercicio 6

/*
Listar el id del teatro (theaterId), estado (“location.address.state”), ciudad
(“location.address.city”), y coordenadas (“location.geo.coordinates”) de los teatros que
se encuentran en algunos de los estados "CA", "NY", "TX" y el nombre de la ciudades
comienza con una ‘F’. Listar ordenados por estado y ciudad.
*/

db.theaters
  .find(
    {
      "location.address.state": { $in: ["CA", "NY", "TX"] },
      "location.address.city": { $regex: /^F/ },
    },
    {
      _id: 0,
      theaterId: 1,
      "location.address.state": 1,
      "location.address.city": 1,
      "location.geo.coordinates": 1,
    }
  )
  .sort({ "location.address.state": 1, "location.address.city": 1 });

// Ejercicio 7

/*
Actualizar los valores de los campos texto (text) y fecha (date) del comentario cuyo id es
ObjectId("5b72236520a3277c015b3b73") a "mi mejor comentario" y fecha actual
respectivamente.

*/
db.comments.updateOne(
  {
    _id: ObjectId("5b72236520a3277c015b3b73"),
  },
  {
    $set: {
      text: "mi mejor comentario",
      date: new Date(),
    },
  }
);

// Verificacion
db.comments.findOne({
  _id: ObjectId("5b72236520a3277c015b3b73"),
});

// Ejercicio 8

/*
Actualizar el valor de la contraseña del usuariocuyo email es joel.macdonel@fakegmail.com a "some password". 
La misma consulta debe poderinsertar un nuevo usuario en caso que el usuario no exista. Ejecute la consulta dos
veces. ¿Qué operación se realiza en cada caso? (Hint: usar upserts).

*/

db.users.updateOne(
  {
    email: "joel.macdonel@fakegmail.com",
  },
  {
    $set: {
      password: "some password",
    },
  },
  {
    upsert: true, // Si no existe en el documento, lo inserta.
  }
);

// Verificacion
db.users.findOne({
  email: "joel.macdonel@fakegmail.com",
});

// La primera vez se realiza un insert, pues no exisitia el usuario. La segunda vez se realiza un update, pues ya existe el usuario.

// Ejercicio 9
/**
Remover todos los comentarios realizados por el usuario cuyo email es
victor_patel@fakegmail.com durante el año 1980.
 */

db.comments.deleteMany({
  email: "victor_patel@fakegmail.com",
  date: {
    $gte: ISODate("1980-01-01T00:00:00Z"),
    $lte: ISODate("1980-12-31T23:59:59Z"),
  },
});
