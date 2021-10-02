-- Keep a log of any SQL queries you execute as you solve the mystery.

sqlite3 fiftyville.db
.schema
.schema crime_scene_reports
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = "Chamberlin Street";
.schema interviews
SELECT name FROM interviews WHERE month = 7 AND day = 28;
SELECT transcript FROM interviews WHERE name = "Jose" AND month = 7 AND day = 28;
SELECT transcript FROM interviews WHERE name = "Eugene" AND month = 7 AND day = 28;      !!!
SELECT transcript FROM interviews WHERE name = "Barbara" AND month = 7 AND day = 28;
SELECT transcript FROM interviews WHERE name = "Ruth" AND month = 7 AND day = 28;        !!!
SELECT transcript FROM interviews WHERE name = "Raymond" AND month = 7 AND day = 28;     !!!
.schema atm_transactions
SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location = "Fifer Street";