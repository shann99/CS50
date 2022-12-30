-- Keep a log of any SQL queries you execute as you solve the mystery.
-- starting with crime_scene_reports to get started
SELECT * FROM crime_scene_reports;
--in the crime scene reports, it states that the CS50 duck theft crime took place at the Humphrey street bakery at 10:15am and that 3 witnesses present at the time had an interview
SELECT  name, transcript, day, month, year FROM interviews WHERE month = 7 AND day = 28 AND year = 2021;
--Eugene said it was someone he recognized, and saw them at the ATM on Leggett Street withdrawing money (this was before the theft)
SELECT * FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";
--Ruth mentioned to check the bakery security footage within the first 10 min of the crime
SELECT * FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25;
--Raymond said that the thief called someone for less than a minute and asked them to book the earliest flight for them
SELECT * FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;
--connect bank accounts and atm information (results: bruce, diana, iman)
SELECT DISTINCT(bank_accounts.person_id), people.name FROM bank_accounts JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number 
JOIN people ON bank_accounts.person_id = people.id
WHERE atm_transactions.account_number IN (SELECT atm_transactions.account_number FROM atm_transactions 
WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw");
--connect licenses to people
SELECT DISTINCT(people.id), people.name FROM people JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate 
WHERE people.license_plate IN 
(SELECT bakery_security_logs.license_plate  FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25);
--comparing the previous query to the connect bank and atm info query there are 4 suspects (Iman. Luca, Diana, Barry)
--connect phone numbers and names - Bruce and Diana appear
SELECT distinct(people.id), people.name, phone_calls.caller FROM people JOIN phone_calls ON phone_calls.caller = people.phone_number WHERE phone_calls.caller IN
(SELECT phone_calls.caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60);
--getting passenger passport info for those on the plane out of fiftyville on July 29 (Bruce and Luca pop up) -> flight is to NYC
SELECT DISTINCT(passengers.passport_number), flights.id, flights.day, flights.hour, flights.origin_airport_id, flights.destination_airport_id, airports.full_name, airports.city FROM passengers 
JOIN flights ON flights.id = passengers.flight_id JOIN airports ON airports.id = flights.destination_airport_id WHERE flights.id =
(SELECT flights.id FROM flights JOIN airports ON flights.origin_airport_id = airports.id 
 WHERE flights.year = 2021 and month = 7 AND day = 29 ORDER BY flights.hour);
--connect bruce's phone call to person (the receiver) -> tthe receiver is Robin
SELECT distinct(people.id), people.name, phone_calls.caller, phone_calls.receiver FROM people JOIN phone_calls ON phone_calls.receiver = people.phone_number WHERE phone_calls.receiver IN
(SELECT phone_calls.receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60);













