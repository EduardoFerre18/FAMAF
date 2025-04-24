// Ejercicio 12

/*
Listar el id y nombre de los restaurantes junto con su puntuación máxima, mínima y la
suma total. Se puede asumir que el restaurant_id es único.

a. Resolver con $group y accumulators.
b. Resolver con expresiones sobre arreglos (por ejemplo, $sum) pero sin $group.
c. Resolver como en el punto b) pero usar $reduce para calcular la puntuación
total.
d. Resolver con find.
 */

//a Resolver con $group y accumulators.

db.restaurants.aggregate([
  {
    $unwind: "$grades",
  },
  {
    $group: {
      _id: { restaurant_id: "$restaurant_id", name: "$name" },
      grade_sum: {
        $sum: "$grades.score",
      },
      grade_max: {
        $max: "$grades.score",
      },
      grade_min: {
        $min: "$grades.score",
      },
    },
  },
  {
    $project: {
      restaurant_id: "$_id.restaurant_id",
      name: "$_id.name",
      grade_sum: 1,
      grade_max: 1,
      grade_min: 1,
      _id: 0,
    },
  },
]);

//b Resolver con expresiones sobre arreglos (por ejemplo, $sum) pero sin $group$.

db.restaurants.aggregate([
  {
    $match: {
      "grades.score": { $exists: true, $type: "number" },
    },
  },
  {
    $project: {
      restaurant_id: 1,
      name: 1,
      grade_sum: {
        $sum: "$grades.score",
      },
      grade_max: {
        $max: "$grades.score",
      },
      grade_min: {
        $min: "$grades.score",
      },
      _id: 0,
    },
  },
]);

//c Resolver como en el punto b) pero usar $reduce para calcular la puntuación total.

db.restaurants.aggregate([
  {
    $match: {
      "grades.score": { $exists: true, $type: "number" },
    },
  },
  {
    $project: {
      restaurant_id: 1,
      name: 1,
      grade_sum: {
        $reduce: {
          input: "$grades",
          initialValue: 0,
          in: { $add: ["$$value", "$$this.score"] },
        },
      },
      grade_max: {
        $max: "$grades.score",
      },
      grade_min: {
        $min: "$grades.score",
      },
      _id: 0,
    },
  },
]);

//d Resolver con find.

db.restaurants.find(
  {},
  {
    restaurant_id: 1,
    name: 1,
    grade_stats: {
      $reduce: {
        input: "$grades",
        initialValue: {
          sum: 0,
          max: -Infinity,
          min: Infinity,
        },
        in: {
          sum: { $add: ["$$value.sum", "$$this.score"] },
          max: { $max: ["$$value.max", "$$this.score"] },
          min: { $min: ["$$value.min", "$$this.score"] },
        },
      },
    },
    _id: 0,
  }
);
// Ejercicio 13

/* 
13. Actualizar los datos de los restaurantes añadiendo dos campos nuevos.
a. "average_score": con la puntuación promedio
b. "grade": con "A" si "average_score" está entre 0 y 13,
con "B" si "average_score" está entre 14 y 27
con "C" si "average_score" es mayor o igual a 28
Se debe actualizar con una sola query.
a. HINT1. Se puede usar pipeline de agregación con la operación update
b. HINT2. El operador $switch o $cond pueden ser de ayuda.
*/

db.restaurants.updateMany({}, [
  {
    $set: {
      average_score: {
        $avg: "$grades.score",
      },
    },
  },
  {
    $set: {
      grade: {
        $switch: {
          branches: [
            { case: { $gte: ["$average_score", 28] }, then: "C" },
            { case: { $gte: ["$average_score", 14] }, then: "B" },
            { case: { $gte: ["$average_score", 0] }, then: "A" },
          ],
          default: null, // Valor por defecto si no se cumple ninguna condición
        },
      },
    },
  },
]);
