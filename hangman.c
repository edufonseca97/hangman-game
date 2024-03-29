#include "hangman.h"

int main()
{
    char playAgain;

    printEntrance();

    do
    {
        char guess;
        char guessedLetters[MAX_WORD_LENGTH] = {0};
        int triesLeft = MAX_TRIES;
        int numGuessedLetters = 0;

#ifdef RANDOM_WORD
        char *secretWord = getRandomWord();
#else
        char *secretWord = chooseWord();
#endif // RANDOM_WORD

        char *guessedWord = initializeGuessedWord(strlen(secretWord));

        while (triesLeft)
        {
            do
            {
                drawHangman(triesLeft);

                printf("You have %d tries left.\n", triesLeft);
                printf("Guessed word: %s\n", guessedWord);
                printf("Tried letters: ");

                for (int i = 0; i < numGuessedLetters; i++)
                    printf("%c ", guessedLetters[i]);

                printf("\nEnter your guess: ");
                scanf(" %c", &guess);
                guess = tolower(guess);

                clearScreen();
            } while (!isValidGuess(guess, guessedLetters, numGuessedLetters));

            guessedLetters[numGuessedLetters] = guess;
            numGuessedLetters++;

            if (isCorrectGuess(guess, secretWord, guessedWord))
                printf("Correct guess!\n");
            else
            {
                triesLeft--;
                printf("Incorrect guess!\n");
            }

            if (strcmp(secretWord, guessedWord) == NULL)
            {
                printf("Congratulations! You won!\nThe word was %s\n", secretWord);
                break;
            }
        }

        if (triesLeft == 0)
        {
            drawHangman(triesLeft);

            printf("You have %d tries left.\n", triesLeft);
            printf("Guessed word: %s\n", guessedWord);
            printf("Tried letters: ");

            for (int i = 0; i < numGuessedLetters; i++)
                printf("%c ", guessedLetters[i]);

            printf("\nYou lost! The word was %s\n", secretWord);
        }

        printf("\nDo you want to play again? (y/n): ");
        scanf(" %c", &playAgain);

        clearScreen();

        free(secretWord);
        free(guessedWord);

    } while (playAgain == 'y' || playAgain == 'Y');

    printf("\nThank you for playing! =)");

    return 0;
}