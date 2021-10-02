SELECT title FROM movies JOIN stars ON stars.movie_id = movies.id
JOIN people ON stars.person_id = people.id
JOIN ratings ON ratings.movie_id = movies.id
WHERE name FROM people ="Chadwick Boseman"
ORDER BY rating FROM ratings DESC
limit 5;