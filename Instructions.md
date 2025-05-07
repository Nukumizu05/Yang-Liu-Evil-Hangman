## Intro to the Project

In 2025, it is hard to find a college student that has not played a single game on the computer.  If you remember from the first week of class, we discussed C++'s prevalence in the video game industry, so it may come as no surprise to you that your first project will be to develop a simple computer game of your own.  While you won't be using Unreal Engine or any of the big tools the developers use (yet), this project will give you a chance to work on your core C++ competencies including control structures, logical decision making, and modular programming.  While the premise of this game is rather simple, your focus should be on writing _clean, maintainable_ code that can be easily read by not only the course staff, but also other developers who may look at your code down the line.

## Let's Talk Hangman

In order to understand how our game works, we must first understand how its predecessor works. In a _traditional_ game of Hangman, a player (your program in our case) selects a secret word whose length is noted by a number of dashes.  A second player (in our case the user of your program and/or the test suite) attempts to guess this word by guessing letters that may be contained in said word.  If the letter selected by the second player is in the word, the first player reveals the places in the word where the letter is used.  Should the letter not be in the word, the player gets a "strike" up to some limit of wrong guesses.  This pattern continues until the second player either guesses the word correctly (by selecting all of the letters in the chosen word) or runs out of wrong guesses based on the predetermined threshold.

Though it may not seem apparent on first glance, a fundamental component of this game is the fact that the word chosen by the first player remains static throughout the duration of the game.

Let's consider for a moment what would happen if the word did _not_ remain constant?  Suppose that we are nearing the end of a game of Hangman with the following letters on the board for a player's final guess:

D O \_\_ B L E

After iterating through the entire alphabet, one would quickly realize that there are two English words that are valid choices for this word: "doable" and "double".  In our dystopian version of the game, whatever way the player chooses to solve it can be considered incorrect simply by selecting the other option!  Enter: Evil Hangman! 😈

For this project, you will implement **both** a regular version of the Hangman game as well as its evil twin.  We will describe the expectations of your game and what we will provide you below, though the exact implementation of your project is entirely up to you (so long as it works and passes our tests when we play it!)

## Milestone One: "Regular Hangman"

In part one, you will implement the regular version of the game. How you do so is primarily up to your own design.  Perhaps the most difficult piece of this project is deciding _which_ data types / data structures make the most sense to use while implementing the game. I'll note that there is a solution to this problem that can be done entirely using `std::vector` and similar containers, though you are welcome to use any data structures you choose.

Here are the expectations for the game:

1. Welcome the player via a welcome message: `Welcome to COP 3504 C's Hangman!`
2. Ask the player to enter the length of their desired word, reprompting as necessary until the player enters a number such that there is at least one word in the dictionary that is exactly that long.  Once a valid length has been selected, select a random word of that given length to use for that game.
3. You'll begin the game by printing the current state of the game, which includes the number of lives left and the current state of the "dashed" version of the word.  For the purposes of this game, you may assume that the player always starts with **five lives** that decrements each time the player guesses a letter not in the word.
4. Prompt the player for a single letter guess, reprompting until the player enters a letter that has not been guessed yet.  Make sure that you validate this input!
5. Notify the player whether their guessed letter is in the word and utilize the guess to update the "dashed" version of the word, revealing correctly guessed letters.
6. If the player has correctly guessed the word, congratulate the player and exit the game gracefully.  Otherwise, if the player has run out of lives, inform the player that they have run out of lives and reveal the word that was originally selected.

A sample winning and losing game has been provided below for your reference:

### Winning Game

```plaintext
Welcome to COP 3504 C's Hangman!

Enter a word length: 2

--- Current State --- 
You have 5 lives left.
Word: - - 

What is your next guess? k
The letter 'k' is not in the word.

--- Current State --- 
You have 4 lives left.
Word: - - 

What is your next guess? l
The letter 'l' is not in the word.

--- Current State --- 
You have 3 lives left.
Word: - - 

What is your next guess? i
The letter 'i' is in the word!

--- Current State --- 
You have 3 lives left.
Word: i - 

What is your next guess? d
The letter 'd' is in the word!

--- Current State --- 
You have 3 lives left.
Word: i d 

Congratulations! You win!
```

### Losing Game

```plaintext
Welcome to COP 3504 C's Hangman!

Enter a word length: 5

--- Current State --- 
You have 5 lives left.
Word: - - - - - 

What is your next guess? 
a
The letter 'a' is not in the word.

--- Current State --- 
You have 4 lives left.
Word: - - - - - 

What is your next guess? 
b
The letter 'b' is not in the word.

--- Current State --- 
You have 3 lives left.
Word: - - - - - 

What is your next guess? 
c
The letter 'c' is not in the word.

--- Current State --- 
You have 2 lives left.
Word: - - - - - 

What is your next guess? 
d
The letter 'd' is not in the word.

--- Current State --- 
You have 1 lives left.
Word: - - - - - 

What is your next guess? 
e
The letter 'e' is in the word!

--- Current State --- 
You have 1 lives left.
Word: - e - - e 

What is your next guess? 
f
The letter 'f' is not in the word.

--- Current State --- 
You have 0 lives left.
Word: - e - - e 

You used up your last guess and lost!
The word was verse.
```

## Loading Words From the Dictionary

Inside the project template repository in a file called `dictionary.txt` you'll find a large file of potential words that one could use as a hangman word.  As we won't have gone over File I/O until after this project has been released, we have provided a prewritten function `std::vector<std::string> load_words(const std::string& path)` that will handle taking words from a file entitled `words.txt` and adding them to a `std::vector<std::string>` aptly named `words`.

You can use this provided function by initializing a vector of strings with it:

```clike
std::vector<string> words = load_words("RELATIVE PATH TO YOUR CHOSEN DICTIONARY FILE GOES HERE");
```

## Selecting and Seeding Your Random Number For Your Words

Youu may have noticed in the Prisoners Dilemma lab that we provided a random number generator using the `std::mt19937` class from the `random` header, which provides a 32-bit pseudo-random number based on the Mersenne twister algorithm.   In order to utilize this random number generator, you must provide it a **seed**.  For the purposes of your game play, you may choose whatever seed you would like. (Feel free to search the internet for _extensive_ discussion on the "best" seeds to use with this random generator.)  However, for debugging and testing purposes you may wish to use a constant value for the seed so that the random numbers selected remain the same each time you run the program.

Consider the following **minimal working example** (MWE) utilizing `std::m19337`:

```c++
#include <iostream>
#include <random> // for the generator
  
int main(){
	std::mt19937 number_generator(3504);

	std::cout << number_generator() << std::endl; // prints out a pseudorandom number -  3223002299
	
	std::cout << number_generator() << std::endl; // prints out a pseudorandom number - 2610710537

	return 0;
}
```

## Milestone 2: "Evil Hangman"

In the second (and more challenging) milestone of this project, you'll implement the Evil Hangman algorithm described in the introduction. Let's illustrate this technique with an example. Suppose that you are playing Hangman and it's your turn to choose a word, which we'll assume is of length four. Rather than committing to a secret word, you instead compile a list of every four-letter word in the English language. For simplicity, let's assume that English only has a few four-letter words, all of which are reprinted here:

ALLY BETA COOL DEAL ELSE FLEW GOOD HOPE IBEX

Now, suppose that your opponent guesses the letter 'E.' You now need to tell your opponent which letters in the word you've “picked” are E's. Of course, you haven't picked a word, and so you have multiple options about where you reveal the E's.

Here's the above word list, with E's highlighted in each word:

ALLY &emsp; B<ins>**E**</ins>TA &emsp; COOL &emsp; D<ins>**E**</ins>AL &emsp; <ins>**E**</ins>LS<ins>**E**</ins>	 &emsp; FL<ins>**E**</ins>W &emsp; GOOD &emsp; HOP<ins>**E**</ins> &emsp; IB<ins>**E**</ins>X

If you'll notice, every word in your word list falls into one of five “word families:”

- \- - - - (ALLY, COOL, and GOOD)

- \-E-- (BETA and DEAL)

- \--E- (FLEW and IBEX)

- \---E (HOPE)

- E--E (ELSE)

Since the letters you reveal have to correspond to some word in your word list, you can choose to reveal any one of the above five families.

There are many ways to pick which family to reveal – perhaps you want to steer your opponent toward a smaller family with more obscure words, or toward a larger family in the hopes of keeping your options open. For this project, in the interests of simplicity, we'll adopt the latter approach and always choose the largest of the remaining word families. In this case, it means that you should pick the family ----.

This reduces your word list down to ALLY COOL GOOD and, since you didn't reveal any letters, you would tell your opponent that his guess was wrong. Let's see a few more examples of this strategy.

Given this three-word word list, if your opponent guesses the letter O, then you would break your word list down into two families:

- \-OO-, containing COOL and GOOD.
- \----, containing ALLY.

The first of these families is larger than the second, and so you choose it, revealing two O's in the word and reducing your list down to:

C**OO**L and G**OO**D

What happens if your opponent guesses a letter that doesn't appear anywhere in your word list? For example, what happens if your opponent now guesses 'T'? This isn't a problem. If you try splitting these words apart into word families, you'll find that there's only one family: the family ---- containing both COOL and GOOD. Since there is only one word family, it's trivially the largest, and by picking it you'd maintain the word list you already had. There are two possible outcomes of this game. First, your opponent might be smart enough to pare the word list down to one word and then guess what that word is. In this case, you should congratulate the player– that's an impressive feat considering the scheming you were up to! Second, and by far the most common case, your opponent will be completely stumped and will run out of guesses. When this happens, you can pick any word you'd like from your list and say it's the word that you had chosen all along. The beauty of this setup is that your opponent will have no way of knowing that you were dodging guesses the whole time – it looks like you simply picked an unusual word and stuck with it the whole way.

For Milestone Two, your Hangman should function and play exactly like your Hangman in Milestone One (and **feel free to reuse any and all parts of it!)** with the exception that it utilizes the Evil Hangman algorithm described above.

## Project Structure and Submission

In comparison to your labs thus far, how you choose to style and structure your project is entirely of your choosing.  With that in mind, be sure that you think carefully about where would be best to store the various functions in your program.  (Hint: It's probably not to have a `main()` function with 1000+ lines of code!)  Use various `.h(pp)` and `.cpp` files as you feel it is appropriate.  If you're struggling to decide on a program structure, **please** come talk to the course staff so we can help you decide on a direction!

As a starting point, a few of the following functions may be useful to consider:
* A function that prints the current state of the game.
* A function that determines if a word is "complete" (i.e. there are no dashes left in the word).
* A function to determine if a guess is a "valid guess," namely if the guess is a single character (a-z) that has not been guessed before in that game.  [How could you store a collection of previous guesses?]

In order for us to grade your project, you must provide a `README.md` in your GitHub repository that tells us **exactly** how to compile your program for both Milestones 1 and 2. You are welcome to also provide the staff with a `Makefile` or `CMakeLists.txt`, though these are not required for Project 0 (though you'll use them in the later projects in the course!).

Once your project is complete and ready for grading, create a **pull request** stating that your project is complete and submit the files to Gradescope.

## Testing Your Project

Given that everyone's project structure will (and should!) be different, there will not be an automated test suite provided for the project.  That being said, we encourage you to heavilly test your project!

A few recommendations:

- Once you create your Hangman game, test it on a **single** word to ensure that your game is working as intended! (Hint: You can create a `words` vector with only one element!)

- Create a few small variants of words.txt and pick a consistent random seed (so that you can determine what words you should be getting) to ensure that you know your "random" logic is working!

- Test as you go!  There are always ways to create small test cases for each function you create.  Waiting until the end to test your entire program will inevitably lead to errors... don't make this mistake!

The course staff will utilize the same set of tests on every project (including the same seeds and lists of words) to ensure a consistency in functionality.

## Extra Credit
The algorithm described above is by no means the most optimal way to solve this problem -- in fact, in many cases, it makes terrible choices!  Particularly, if the goal of evil hangman is to ensure that the player loses, it is often the case that it is better to pick a smaller word family rather than the largest word family.  (Alert for the math nerds: yes, you can prove this -- cardinality and such...).   

For up to 10% extra credit on the project, you are welcome to consider (and implement) improvements to the above algorithm.  Note in your `README.md` how you improved the algorithm and what needs to be done to play the game via your improved algorithm vs. the algorithm written above.

## Appendix: File Reading Function

```c++
std::vector<std::string> load_words(const std::string& path) {
    std::ifstream dict_file(path);

    // Check if the file was opened successfully
    if (!dict_file.is_open()) {
        std::cerr << "Error: could not open file " << path << std::endl;
        return {};
    }

    // Read the file line by line
    std::vector<std::string> words;
    std::string word_line;
    while (std::getline(dict_file, word_line)) {
        // Add words - MAJOR HINT - you may wish to add some additional conditions here to get the "right" words into your vector!)
        words.push_back(word_line);
    }

    return words;
}
```

## Acknowledgements and Contributions

This project was adapted by Michael Link for COP 3504 C  based on prior work by (and with the generous consent of) Jule Schatz, Ph.D. (University of Illinois Urbana Champaign) and the SIGCSE Nifty Assignment by Keith Schwartz, Ph.D. (Stanford University).
