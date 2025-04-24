// Ejercicio 1

db.grades
  .find(
    {
      $and: [
        {
          $or: [
            { "scores.type": "exam", "scores.score": { $gte: 80 } },
            { "scores.type": "quiz", "scores.score": { $gte: 90 } },
          ],
        },
        {
          "scores.type": "homework",
          "scores.score": { $gte: 60 },
        },
      ],
    },
    {
      _id: 0,
      student_id: 1,
      scores: 1,
      class_id: 1,
    }
  )
  .sort({ class_id: 1, student_id: -1 });

//Ejercicio 2

db.grades.aggregate([
  {
    $match: {
      class_id: { $in: [20, 220, 420] },
    },
  },
  {
    $unwind: "$scores",
  },
  {
    $match: {
      "scores.type": "homework",
    },
  },
  {
    $group: {
      _id: { student_id: "$student_id", class_id: "$class_id" },
      min: { $min: "$scores.score" },
      max: { $max: "$scores.score" },
      avg: { $avg: "$scores.score" },
    },
  },
  {
    $sort: {
      "_id.student_id": -1,
      "_id.class_id": -1,
    },
  },
]);

//Ejercicio 3

db.grades.aggregate([
  {
    $unwind: "$scores",
  },
  {
    $match: {
      "scores.type": { $in: ["exam", "quiz"] },
    },
  },
  {
    $group: {
      _id: { class_id: "$class_id", type: "$scores.type" },
      max: { $max: "$scores.score" },
    },
  },
  {
    $group: {
      _id: "$_id.class_id",
      max_scores: {
        $push: {
          type: "$_id.type",
          max: "$max",
        },
      },
    },
  },
  {
    $sort: { _id: -1 },
  },
]);

//Ejercicio 4

db.createView("top10students", "grades", [
  {
    $unwind: "$scores",
  },
  {
    $match: {
      "scores.type": { $in: ["exam", "quiz", "homework"] },
    },
  },
  {
    $group: {
      _id: "$student_id",
      avg: { $avg: "$scores.score" },
    },
  },
  {
    $sort: { avg: -1 },
  },
  {
    $limit: 10,
  },
]);

//Ejercicio 5

db.grades.aggregate([
  {
    $match: {
      class_id: 339,
    },
  },
  {
    $unwind: "$scores",
  },
  {
    $group: {
      _id: "$_id",
      avg: { $avg: "$scores.score" },
    },
  },
  {
    $addFields: {
      score_avg: "$avg",
      letter: {
        $switch: {
          branches: [
            {
              case: { $gte: ["$avg", 80] },
              then: "P",
            },
            {
              case: { $gte: ["$avg", 60] },
              then: "A",
            },
          ],
          default: "NA",
        },
      },
    },
  },
]);

//Ejercicio 6

// (a)

db.runCommand({
  collMod: "grades",
  validator: {
    $jsonSchema: {
      bsonType: "object",
      required: ["student_id", "class_id", "scores"],
      properties: {
        student_id: {
          bsonType: "int",
          minimum: 0,
        },
        class_id: {
          bsonType: "int",
          minimum: 0,
        },
        scores: {
          bsonType: "array",
          items: {
            bsonType: "object",
            required: ["type", "score"],
            properties: {
              type: {
                enum: ["exam", "quiz", "homework"],
              },
              score: {
                bsonType: "double",
                minimum: 0,
                maximum: 100,
              },
            },
          },
        },
      },
    },
  },
});

// (b)

// Caso de éxito

db.grades.insertOne({
  student_id: 100000,
  class_id: 100000,
  scores: [
    { type: "exam", score: 80.123 },
    { type: "quiz", score: 90.14124 },
    { type: "homework", score: 99.100321 },
  ],
});

// Caso de falla 1

db.grades.insertOne({
  student_id: 100001,
  class_id: 100001,
  scores: [
    { type: "exam", score: 80.456 },
    { type: "quiz", score: 90.7801 },
    { type: "homework", score: 101.132 },
  ],
});

// Este falla porque el score de homework es mayor a 100.

// Caso de falla 2

db.grades.insertOne({
  student_id: 100002,
  class_id: 100002,
  scores: [
    { type: "exam", score: 65.1312 },
    { type: "quiz", score: 32.1245 },
    { type: "homework", score: "100.123" },
  ],
});

// Este falla porque el score de homework es de tipo string.
