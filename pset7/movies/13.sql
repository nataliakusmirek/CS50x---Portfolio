SELECT name FROM people
JOIN stars ON stars.person_id=people.id
JOIN movies ON stars.movie_id=movies.id
WHERE movies.id in
(SELECT movies.id FROM movies JOIN people ON stars.person_id = people.id JOIN stars ON stars.movie_id = movies.id WHERE name FROM people = "Kevin Bacon"
AND birth FROM people = 1958)
AND name FROM people != "Kevin Bacon";