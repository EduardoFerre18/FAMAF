/*
Agregar las siguientes reglas de validación usando JSON Schema. Luego de cada
especificación testear que efectivamente las reglas de validación funcionen, intentando insertar
5 documentos válidos y 5 inválidos (por distintos motivos).
*/

// Ejercicio 1

/*
Especificar en la colección users las siguientes reglas de validación: El campo name
(requerido) debe ser un string con un máximo de 30 caracteres, email (requerido) debe
ser un string que matchee con la expresión regular: "^(.*)@(.*)\\.(.{2,4})$" ,
password (requerido) debe ser un string con al menos 50 caracteres.

*/

db.runCommand({
  collMod: "users",
  validator: {
    $jsonSchema: {
      bsonType: "object",
      required: ["name", "email", "password"],
      properties: {
        name: {
          bsonType: "string",
          maxLength: 30,
          description: "debe ser un string con un máximo de 30 caracteres",
        },
        email: {
          bsonType: "string",
          pattern: "^(.*)@(.*)\\.(.{2,4})$",
          description:
            "debe ser un string tal tiene un nombre de usuario seguido de @, un dominio con una extensión de 2 a 4 caracteres y es requerido",
        },
        password: {
          bsonType: "string",
          minLength: 50,
        },
      },
    },
  },
});

// 5 casos validos
db.users.insertMany([
  {
    name: "Juan",
    email: "prueba1@mail.com",
    password: "12345678901234567890123456789012345678901234567890",
  },
  {
    name: "Manuel",
    email: "prueba2@mail.com",
    password: "12345678901234567890123456789012345678901234567890",
  },
  {
    name: "Gregorio",
    email: "prueba3@mail.com",
    password: "01234567890123456789012345678901234567890123456789",
  },
  {
    name: "Matias",
    email: "prueba4@mail.com",
    password: "12345678901234567890123456789012345678901234567890",
  },
  {
    name: "Lucas",
    email: "prueba5@mail.com",
    password: "12345678901234567890123456789012345678901234567890",
  },
]);

// 5 casos invalidos
db.users.insertMany([
  {
    name: "1",
    email: "1@mail.com",
    password: "123456789012345678901234567890123",
  },
  {
    name: "2",
    email: "a",
    password: "1234567",
  },
  {
    name: "3",
    email: "2@mail.com",
    password: "01234567890123450123456789",
  },
  {
    name: "12345678901234567890123456789012345678901234567890",
    email: "4@mail.com",
    password: "12345678901234567890123456789012345678901234567890",
  },
  {
    name: "5",
    email: "5@test.com ",
    password: "123456789012345678901234567890127890",
  },
]);

// Ejercicio 2

/*
Obtener metadata de la colección users que garantice que las reglas de validación
fueron correctamente aplicadas. 
*/
db.getCollectionInfos({ name: "users" });

// Ejercicio 3
/*
Especificar en la colección theaters las siguientes reglas de validación: El campo
theaterId (requerido) debe ser un int y location (requerido) debe ser un object con:
a. un campo address (requerido) que sea un object con campos street1, city, state
y zipcode todos de tipo string y requeridos
b. un campo geo (no requerido) que sea un object con un campo type, con valores
posibles “Point” o null y coordinates que debe ser una lista de 2 doubles
*/

db.runCommand({
  collMod: "theaters",
  validator: {
    $jsonSchema: {
      bsonType: "object",
      required: ["theaterId", "location"],
      properties: {
        theaterId: {
          bsonType: "int",
          description: "debe ser un int",
        },
        location: {
          bsonType: "object",
          required: ["address"],
          properties: {
            address: {
              bsonType: "object",
              required: ["street1", "city", "state", "zipcode"],
              properties: {
                street1: {
                  bsonType: "string",
                  description: "debe ser un string y es requerido",
                },
                city: {
                  bsonType: "string",
                  description: "debe ser un string y es requerido",
                },
                state: {
                  bsonType: "string",
                  description: "debe ser un string y es requerido",
                },
                zipcode: {
                  bsonType: "string",
                  description: "debe ser un string y es requerido",
                },
              },
            },
            geo: {
              bsonType: "object",
              properties: {
                type: {
                  enum: ["Point", null],
                  description:
                    "debe ser un string con valores posibles “Point” o null",
                },
                coordinates: {
                  bsonType: "array",
                  minItems: 2,
                  maxItems: 2,
                  items: {
                    bsonType: "double",
                  },
                  description: "debe ser una lista de 2 doubles",
                },
              },
            },
          },
        },
      },
    },
  },
  validationAction: "warn",
});

// 5 casos validos

db.theaters.insertMany([
  {
    theaterId: 9999,
    location: {
      address: {
        street1: "Calle 1",
        city: "CORDOBA",
        state: "CORDOBA",
        zipcode: "1234",
      },
      geo: {
        type: "Point",
        coordinates: [77.777, 66.666],
      },
    },
  },
  {
    theaterId: 2222222,
    location: {
      address: {
        street1: "Calle 2",
        city: "CABA",
        state: "CABA",
        zipcode: "1234",
      },
      geo: {
        type: "Point",
        coordinates: [52.5641, 81.1421],
      },
    },
  },
  {
    theaterId: 33333,
    location: {
      address: {
        street1: "Calle 3",
        city: "CABA",
        state: "CABA",
        zipcode: "1234",
      },
      geo: {
        type: "Point",
        coordinates: [-81.321, 42.411],
      },
    },
  },
  {
    theaterId: 44444,
    location: {
      address: {
        street1: "Calle 4",
        city: "ROSARIO",
        state: "ROSARIO",
        zipcode: "1234",
      },
      geo: {
        type: "Point",
        coordinates: [11.1214, 21.1456],
      },
    },
  },
  {
    theaterId: 555555,
    location: {
      address: {
        street1: "Calle 5",
        city: "CABA",
        state: "CABA",
        zipcode: "1234",
      },
      geo: {
        type: "Point",
        coordinates: [34.12, 41.12],
      },
    },
  },
]);

// 5 casos invalidos  (Completar)

db.theaters.insertOne({
  theaterId: "666666",
  location: {
    address: {
      street1: "Calle 6",
      city: "CABA",
      state: "CABA",
      zipcode: "1234",
    },
    geo: {
      type: "Point",
      coordinates: [34.12],
    },
  },
});

// Ejercicio 4

/*
Especificar en la colección movies las siguientes reglas de validación: El campo title
(requerido) es de tipo string, year (requerido) int con mínimo en 1900 y máximo en 3000,
y que tanto cast, directors, countries, como genres sean arrays de strings sin
duplicados.
a. Hint: Usar el constructor NumberInt() para especificar valores enteros a la hora
de insertar documentos. Recordar que mongo shell es un intérprete javascript y
en javascript los literales numéricos son de tipo Number (double).
*/

db.runCommand({
  collMod: "movies",
  validator: {
    $jsonSchema: {
      bsonType: "object",
      required: ["title", "year"],
      properties: {
        title: {
          bsonType: "string",
          description: "debe ser un string",
        },
        year: {
          bsonType: "int",
          minimum: 1900,
          maximum: 3000,
          description: "debe ser un int con mínimo en 1900 y máximo en 3000",
        },
        cast: {
          bsonType: "array",
          uniqueItems: true,
          items: {
            bsonType: "string",
          },
        },
        directors: {
          bsonType: "array",
          uniqueItems: true,
          items: {
            bsonType: "string",
          },
        },
        countries: {
          bsonType: "array",
          uniqueItems: true,
          items: {
            bsonType: "string",
          },
        },
        genres: {
          bsonType: "array",
          uniqueItems: true,
          items: {
            bsonType: "string",
          },
        },
      },
    },
  },
});

// 5 casos validos

db.movies.insertOne({
  title: "Titulo",
  year: NumberInt(2024),
  cast: ["actor1", "actor2"],
  directors: ["director1", "director2"],
  countries: ["country1", "country2"],
  genres: ["genre1", "genre2"],
});

//5 casos invalidos

db.movies.insertOne({
  title: "Titulo",
  year: NumberInt(2024),
  cast: ["actor1", 412142],
  directors: ["director1", "director1"],
  countries: ["country1", "country1"],
  genres: ["genre1", "genre1"],
});

// Ejercicio 5

/*
 Crear una colección userProfiles con las siguientes reglas de validación: Tenga un
campo user_id (requerido) de tipo “objectId”, un campo language (requerido) con alguno
de los siguientes valores [ “English”, “Spanish”, “Portuguese” ] y un campo
favorite_genres (no requerido) que sea un array de strings sin duplicados.
*/

db.createCollection("userProfiles", {
  validator: {
    $jsonSchema: {
      bsonType: "object",
      required: ["user_id", "language"],
      properties: {
        user_id: {
          bsonType: "objectId",
        },
        language: {
          enum: ["English", "Spanish", "Portuguese"],
        },
        favorite_genres: {
          bsonType: "array",
          uniqueItems: true,
          items: {
            bsonType: "string",
          },
        },
      },
    },
  },
});

// Ejercicio 6

/* 
Identificar los distintos tipos de relaciones (One-To-One, One-To-Many) en las
colecciones movies y comments. Determinar si se usó documentos anidados o
referencias en cada relación y justificar la razón.

//Respuesta
En la colección movies se puede identificar una relación One-To-Many con la colección comments por referencias.
Esto se debe a que un comentario puede estar relacionado con una sola película, pero una película puede tener muchos comentarios.
*/

// Ejercicio 7

/*Dado el diagrama de la base de datos shop junto con las queries más importantes (Ver imagen del enunciado)

Queries
I.
Listar el id, titulo, y precio de los libros y sus categorías de un autor en particular
II.
Cantidad de libros por categorías
III.
Listar el nombre y dirección entrega y el monto total (quantity * price) de sus
pedidos para un order_id dado.
Debe crear el modelo de datos en mongodb aplicando las estrategias “Modelo de datos
anidados” y Referencias. El modelo de datos debe permitir responder las queries de
manera eficiente.

Inserte algunos documentos para las colecciones del modelo de datos. Opcionalmente
puede especificar una regla de validación de esquemas para las colecciones.
Se provee el archivo shop.tar.gz que contiene algunos datos que puede usar como
ejemplo para los inserts en mongodb.

*/

db.createCollection("books", {
  validator: {
    $jsonSchema: {
      bsonType: "object",
      required: ["title", "author", "price", "category_id"],
      properties: {
        title: {
          bsonType: "string",
        },
        author: {
          bsonType: "string",
        },
        price: {
          bsonType: "double",
        },
        category_id: {
          bsonType: "string",
        },
      },
    },
  },
});

db.createCollection("orders", {
  validator: {
    $jsonSchema: {
      bsonType: "object",
      properties: {
        delivery_name: {
          bsonType: "string",
        },
        delivery_address: {
          bsonType: "string",
        },
        cc_name: {
          bsonType: "string",
        },
        cc_number: {
          bsonType: "string",
        },
        cc_expiry: {
          bsonType: "string",
        },
        books_details: {
          bsonType: "array",
          items: {
            bsonType: "object",
            required: ["title", "author", "quantity", "price"],
            properties: {
              title: {
                bsonType: "string",
              },
              author: {
                bsonType: "string",
              },
              quantity: {
                bsonType: "int",
              },
              price: {
                bsonType: "double",
              },
            },
          },
        },
      },
    },
  },
});
