# Arduino Reaction Time Analyzer

An Arduino UNO-based project that measures human reaction time using an LED as a visual stimulus. The system runs five rounds, records response times, and tracks the best reaction time achieved during the session.

## Features

* Measures reaction time in response to an LED signal.
* Runs five rounds per session.
* Tracks the best reaction time.
* Uses Arduino timing functions to calculate response speed.
* Provides a hands-on introduction to embedded systems and electronics.

## Components Used

* Arduino UNO
* LED
* Resistor
* Breadboard and jumper wires

## Technologies Used

* Arduino C/C++
* Arduino IDE
* Digital output control and timing functions

## How It Works

1. The Arduino initiates the reaction test.
2. The LED turns on to provide a visual signal.
3. The user responds as quickly as possible.
4. The Arduino calculates the reaction time.
5. The test repeats for five rounds, and the best result is tracked.

## Learning Outcomes

This project helped develop practical skills in Arduino programming, digital output control, time measurement, and hardware-software integration.

## Future Improvements

* Add an LCD or OLED display to show results.
* Introduce randomized delays to reduce anticipation.
* Include a buzzer for audio feedback.
* Display the average reaction time alongside the best result.
