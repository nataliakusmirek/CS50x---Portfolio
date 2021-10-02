SELECT title FROM movies JOIN stars ON stars.movie_id = movies.id JOIN people ON stars.person_id=people.id
WHERE name FROM people ="Johnny Depp"
AND title in (SELECT title FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON stars.person_id = people.id
WHERE name FROM people ="Helena Bonham Carter"
);