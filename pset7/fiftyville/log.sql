-- Keep a log of any SQL queries you execute as you solve the mystery.

--check day format in C_S_R
SELECT day FROM crime_scene_reports;
--numbers

--check month format in C_S_R
SELECT month FROM crime_scene_reports;
--numbers

--search crime_scene_reports for match to date and location:July 28, 2020, Chamberlin Street.
SELECT description FROM crime_scene_reports WHERE year = "2020" AND month = "7" AND day = "28" AND street = "Chamberlin Street";
--Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

--search transcripts mentioning the courthouse to pull up witness interviews.
SELECT name, transcript FROM interviews WHERE year = "2020" AND month = "7" AND day = "28";
--Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
--NOTE cars that left car park within 10 mins of theft
--Eugene | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
--NOTE ATM on Fifer Street earlier same morning
--Raymond | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
--NOTE phone call as leaving courhouse, earliest flight next morning, person on call books ticket.

--hour minute format
SELECT activity, hour, minute FROM courthouse_security_logs WHERE year = "2020" AND month = "7" AND day = "28";
-- within 10 mins of 10.15... 10.16/18/18/19/20/21/23/23- 8 matches


--Checking car park footage
SELECT activity, license_plate FROM courthouse_security_logs WHERE year = "2020" AND month = "7" AND day = "28" AND hour = 10 AND minute > 15 AND minute < 25;
--exit | 5P2BI95
--exit | 94KL13X
--exit | 6P58WS2
--exit | 4328GD8
--exit | G412CB7
--exit | L93JTIZ
--exit | 322W7JE
--exit | 0NTHK55

--atm logs for morning of crime
SELECT id, account_number, transaction_type, amount FROM atm_transactions WHERE atm_location = "Fifer Street" AND year = "2020" AND month = "7" AND day = "28";
--id | account_number | transaction_type | amount
--246 | 28500762 | withdraw | 48
--264 | 28296815 | withdraw | 20
--266 | 76054385 | withdraw | 60
--267 | 49610011 | withdraw | 50
--269 | 16153065 | withdraw | 80
--275 | 86363979 | deposit | 10
--288 | 25506511 | withdraw | 20
--313 | 81061156 | withdraw | 30
--336 | 26013199 | withdraw | 35

--phone records, around 10.15, less than a minute length
SELECT caller, receiver, duration FROM phone_calls WHERE year = "2020" AND month = "7" AND day = "28" AND duration < 60;
--caller | receiver | duration
--(130) 555-0289 | (996) 555-8899 | 51
--(499) 555-9472 | (892) 555-8872 | 36
--(367) 555-5533 | (375) 555-8161 | 45
--(499) 555-9472 | (717) 555-1342 | 50
--(286) 555-6063 | (676) 555-6554 | 43
--(770) 555-1861 | (725) 555-3243 | 49
--(031) 555-6622 | (910) 555-3251 | 38
--(826) 555-1652 | (066) 555-9701 | 55
--(338) 555-6650 | (704) 555-2131 | 54

--NOW to cross reference licence plates, atm acc and phone call.

--cross reference licence-plate and phone number.
SELECT name, phone_number FROM people WHERE license_plate = "5P2BI95" OR license_plate = "94KL13X" OR license_plate = "6P58WS2" OR license_plate = "4328GD8" OR license_plate = "G412CB7" OR license_plate = "L93JTIZ" OR license_plate = "322W7JE" OR license_plate = "0NTHK55";
--Patrick | (725) 555-4692, n
--Amber | (301) 555-4174, n
--Elizabeth | (829) 555-5269, n
--Roger | (130) 555-0289, MATCH,
--Danielle | (389) 555-5198,n
--Russell | (770) 555-1861, MATCH
--Evelyn | (499) 555-9472, MATCH
--Ernest | (367) 555-5533, MATCH

--cross reference atm transactions with names.

--get person id
SELECT name, id FROM people WHERE license_plate = "5P2BI95" OR license_plate = "94KL13X" OR license_plate = "6P58WS2" OR license_plate = "4328GD8" OR license_plate = "G412CB7" OR license_plate = "L93JTIZ" OR license_plate = "322W7JE" OR license_plate = "0NTHK55";
--Roger | 398010
--Russell | 514354
--Evelyn | 560886
--Ernest | 686048

SELECT account_number, person_id FROM bank_accounts WHERE person_id = "398010" OR person_id = "514354" OR person_id = "560886" OR person_id = "686048";
--49610011 | 686048 Ernst
--26013199 | 514354 Russell

--now who Ernst and russell spoke two and which of them bought a plane ticket.
--(770) 555-1861 | (725) 555-3243 | 49 russell and reciever
--(367) 555-5533 | (375) 555-8161 | 45 Ernest and reciever

SELECT name, phone_number FROM people WHERE phone_number == "(725) 555-3243" OR phone_number = "(375) 555-8161";
--name | phone_number
--Berthold | (375) 555-8161 by Ernest
--Philip | (725) 555-3243- called by Russell

--cross check passports and passenegers
SELECT passport_number, name FROM people WHERE name = "Ernest" OR name = "Russell";
--passport_number | name
--3592750733 | Russell
--5773159633 | Ernest


--flights under suspect names
SELECT flight_id, passport_number FROM passengers WHERE passport_number = "3592750733" OR passport_number = "5773159633";
--flight_id | passport_number
--18 | 3592750733 - Rus
--24 | 3592750733 - Rus
--36 | 5773159633 - Ernest
--54 | 3592750733- rus

--search for all info on flight numbers suspects
SELECT * FROM flights WHERE id = "18" OR id = "24" OR id = "36" OR id = "54";
--id | origin_airport_id | destination_airport_id | year | month | day | hour | minute
--18 | 8 | 6 | 2020 | 7 | 29 | 16 | 0
--24 | 7 | 8 | 2020 | 7 | 30 | 16 | 27
--36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20-- this is ernest, rest is rus
--54 | 8 | 5 | 2020 | 7 | 30 | 10 | 19


--raymond witness said earliest flight out of fiftyville 'tomorrow' meaning 29th

--now check the flight info.
SELECT * FROM airports WHERE id ="8" OR id ="6" OR id ="4" OR id ="7" OR id = "5";
--id | abbreviation | full_name | city
--4 | LHR | Heathrow Airport | London
--5 | DFS | Dallas/Fort Worth International Airport | Dallas
--6 | BOS | Logan International Airport | Boston
--7 | DXB | Dubai International Airport | Dubai
--8 | CSF | Fiftyville Regional Airport | Fiftyville


--ernest flight from fifty to heathrow,
--rus is from fifty to logan, then fifty to dallas, then dubai back to fifty.- seems suspicious, but eve is the first flight out.

--was heathrow flight id 36 the first flight out of fifty?
SELECT * FROM flights WHERE origin_airport_id = 8 AND year = "2020" AND month = "7" AND day = "29";
--id | origin_airport_id | destination_airport_id | year | month | day | hour | minute
--18 | 8 | 6 | 2020 | 7 | 29 | 16 | 0
--23 | 8 | 11 | 2020 | 7 | 29 | 12 | 15
--36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20 - YES, THIS IS THE FIRST FLIGHT.
--43 | 8 | 1 | 2020 | 7 | 29 | 9 | 30
--53 | 8 | 9 | 2020 | 7 | 29 | 15 | 20

--IN CONCLUSION Its Ernest helped by Berthold now in heathrow/london.

--Opportunities here to join tables to make fewer enquiries, the manual cross-referencing led to having to recheck some things...