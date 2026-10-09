#include <EEPROM.h>
const int LED_PIN = 8;
const int TOTAL_ROUNDS = 5;
int difficulty = 2;
unsigned long bestScore = 0;
const int EEPROM_ADDRESS = 0;
void setup()
{
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    Serial.begin(9600);
    randomSeed(analogRead(A0));
    EEPROM.get(EEPROM_ADDRESS, bestScore);
    if (bestScore == 0xFFFFFFFF)
    {
        bestScore = 0;
    }

    showMenu();
}
void loop()
{
    if (Serial.available() > 0)
    {
        char choice = getInput();

        if (choice == '1')
        {
            startTest();
        }
        else if (choice == '2')
        {
            selectDifficulty();
        }
        else if (choice == '3')
        {
            showInstructions();
        }
        else if (choice == '4')
        {
            showBestScore();
        }
        else if (choice == '5')
        {
            Serial.println();
            Serial.println("Program stopped.");
            Serial.println("Press the Arduino RESET button to restart.");
        }
        else
        {
            Serial.println();
            Serial.println("Invalid choice.");
            showMenu();
        }
    }
}

char getInput()
{
    char input;
    while (Serial.available() == 0)
    {
    }

    input = Serial.read();
    while (input == '\n' || input == '\r')
    {
        while (Serial.available() == 0)
        {
        }

        input = Serial.read();
    }
    clearSerial();

    return input;
}
//game start
void startTest()
{
    unsigned long totalTime = 0;
    unsigned long fastest = 999999;
    unsigned long slowest = 0;
    int completedRounds = 0;
    Serial.println();
    Serial.println("        REACTION TIME ANALYZER");
    Serial.println();

    if (difficulty == 1)
    {
        Serial.println("Difficulty: EASY");
    }
    else if (difficulty == 2)
    {
        Serial.println("Difficulty: NORMAL");
    }
    else
    {
        Serial.println("Difficulty: HARD");
    }

    Serial.println();
    Serial.println("You will complete 5 rounds.");
    Serial.println("Wait for the LED to turn ON.");
    Serial.println("Then press ENTER as quickly as possible.");
    Serial.println();
    Serial.println("Press any key to begin.");
    getInput();
    delay(1000);
    //rounds
    int round = 1;
    while (round <= TOTAL_ROUNDS)
    {
        Serial.println();
        Serial.println("----------------------------------------");

        Serial.print("ROUND ");
        Serial.print(round);
        Serial.println(" / 5");

        Serial.println("----------------------------------------");

        Serial.println("Get ready...");
        digitalWrite(LED_PIN, LOW);
        clearSerial();

        delay(1000);

        int minimumDelay;
        int maximumDelay;

        if (difficulty == 1)
        {
            // Easy
            minimumDelay = 2500;
            maximumDelay = 5000;
        }
        else if (difficulty == 2)
        {
            // Normal
            minimumDelay = 1500;
            maximumDelay = 4000;
        }
        else
        {
            // Hard
            minimumDelay = 1000;
            maximumDelay = 3000;
        }

        int waitTime = random(minimumDelay, maximumDelay);
        unsigned long waitStart = millis();
        bool falseStart = false;
//false start check
        while (millis() - waitStart < waitTime)
        {
            if (Serial.available() > 0)
            {
                clearSerial();
                falseStart = true;
                Serial.println();
                Serial.println("!!! FALSE START !!!");
                Serial.println("You pressed ENTER too early.");
                Serial.println("This round will be repeated.");
                delay(1500);
                break;
            }
        }
        if (falseStart)
        {
            continue;
        }
        digitalWrite(LED_PIN, HIGH);
        Serial.println();
        Serial.println("********************");
        Serial.println("        GO!");
        Serial.println("********************");
        unsigned long startTime = millis();
//response
        while (Serial.available() == 0)
        {
        }
        unsigned long endTime = millis();
        clearSerial();
        digitalWrite(LED_PIN, LOW);
//reaction time calculation
        unsigned long reactionTime = endTime - startTime;
        Serial.println();
        Serial.print("Your reaction time: ");
        Serial.print(reactionTime);
        Serial.println(" ms");
        totalTime = totalTime + reactionTime;
        completedRounds++;
        if (reactionTime < fastest)
        {
            fastest = reactionTime;
        }

        if (reactionTime > slowest)
        {
            slowest = reactionTime;
        }
        round++;
        if (round <= TOTAL_ROUNDS)
        {
            Serial.println();
            Serial.println("Next round...");
            delay(1500);
        }
    }
//final result
    unsigned long average = totalTime / completedRounds;
    Serial.println();
    Serial.println();
    Serial.println("             FINAL RESULTS");
    Serial.print("Rounds Completed : ");
    Serial.println(completedRounds);
    Serial.print("Fastest          : ");
    Serial.print(fastest);
    Serial.println(" ms");
    Serial.print("Slowest          : ");
    Serial.print(slowest);
    Serial.println(" ms");
    Serial.print("Average          : ");
    Serial.print(average);
    Serial.println(" ms");

//performance stats
    Serial.println();
    Serial.print("Performance      : ");
    if (average < 250)
    {
        Serial.println("EXCELLENT!");
    }
    else if (average < 350)
    {
        Serial.println("VERY GOOD!");
    }
    else if (average < 500)
    {
        Serial.println("GOOD!");
    }
    else if (average < 700)
    {
        Serial.println("AVERAGE");
    }
    else
    {
        Serial.println("KEEP PRACTICING!");
    }
//best score
    if (bestScore == 0 || fastest < bestScore)
    {
        bestScore = fastest;
        EEPROM.put(EEPROM_ADDRESS, bestScore);

        Serial.println();
        Serial.println("*** NEW BEST SCORE! ***");
    }
    Serial.println();
    Serial.println("Test completed.");
    delay(2000);
    showMenu();
}
//difficulty selector
void selectDifficulty()
{
    Serial.println();
    Serial.println("             DIFFICULTY");
    Serial.println();
    Serial.println("1. Easy");
    Serial.println("2. Normal");
    Serial.println("3. Hard");
    Serial.println();
    Serial.print("Choose difficulty: ");
    char choice = getInput();
    if (choice == '1')
    {
        difficulty = 1;
        Serial.println();
        Serial.println("Easy mode selected.");
        Serial.println("Waiting time: 2.5 - 5 seconds");
    }
    else if (choice == '2')
    {
        difficulty = 2;

        Serial.println();
        Serial.println("Normal mode selected.");
        Serial.println("Waiting time: 1.5 - 4 seconds");
    }

    else if (choice == '3')
    {
        difficulty = 3;
        Serial.println();
        Serial.println("Hard mode selected.");
        Serial.println("Waiting time: 1 - 3 seconds");
    }

    else
    {
        Serial.println();
        Serial.println("Invalid choice.");
    }
    delay(1500);
    showMenu();
}
//instructions
void showInstructions()
{
    Serial.println();
    Serial.println("             INSTRUCTIONS");
    Serial.println();
    Serial.println("1. Select Start Reaction Test.");
    Serial.println("2. Press ENTER to begin.");
    Serial.println("3. Wait for the LED to turn ON.");
    Serial.println("4. Press ENTER immediately.");
    Serial.println("5. Your reaction time will be displayed.");
    Serial.println("6. Complete all 5 rounds.");
    Serial.println("7. Final statistics will be displayed.");
    Serial.println();
    Serial.println("IMPORTANT:");
    Serial.println("Do NOT press ENTER before the LED turns ON.");
    Serial.println();
    Serial.println("Press any key to return to menu.");
    getInput();
    showMenu();
}
//best score
void showBestScore()
{
    Serial.println();
    Serial.println("              BEST SCORE");
    Serial.println();
    if (bestScore == 0)
    {
        Serial.println("No score recorded yet.");
        Serial.println("Complete a reaction test first.");
    }

    else
    {
        Serial.print("Best Reaction Time: ");
        Serial.print(bestScore);
        Serial.println(" ms");
    }
    Serial.println();
    Serial.println("Press any key to return to menu.");
    getInput();
    showMenu();
}
//menu
void showMenu()
{
    Serial.println();
    Serial.println("       ARDUINO REACTION ANALYZER");
    Serial.println();
    Serial.println("1. Start Reaction Test");
    Serial.println("2. Select Difficulty");
    Serial.println("3. Instructions");
    Serial.println("4. View Best Score");
    Serial.println("5. Exit");
    Serial.println();
    Serial.print("Enter your choice: ");
}
void clearSerial()
{
    while (Serial.available() > 0)
    {
        Serial.read();
    }
}