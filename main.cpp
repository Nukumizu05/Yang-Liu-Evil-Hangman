#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <chrono>

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

class Hangman //Create Kind Hangman Class
{
private:
	unsigned int wordLength; //Word Length entered by the player
	int currentLives; //Current Lives
	bool end; //To determinne whether the game has ended
	std::vector <char> guessedLetters; //Used to determine whether a letter has been guessedor not
	std::string currentWord; //The current word displayed used in PrintState Function
	std::string actualWord; //The right word
	std::vector <std::string> dictionary = load_words("dictionary.txt");

public:
	Hangman() //Constructor
	{
		end = false;

		int a;
		do
		{
			std::cout << "Enter a word length: ";
			std::cin >> a;

			if ((a < 2) || (a > 17))
			{
				std::cout << "No word with such length in the dictionary! Try another length." << std::endl;
			} //Reprompt Message

		} while ((a < 2) || (a > 17));

		wordLength = a; //Enter a word length

		currentWord = "";
		for (size_t i = 0; i < wordLength; i++)
		{
			currentWord += "-";
		}

		currentLives = 5; //Total lives = 5

		int randomNum = 0;
		std::string WORD;
		std::vector <std::string> groupedWords; //Word Grouping

		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::mt19937 number_generator(seed);
		randomNum = number_generator(); //Generate a random number

		for (size_t i = 0; i < dictionary.size(); i++)
		{
			if (dictionary[i].size() == wordLength)
			{
				groupedWords.push_back(dictionary[i]);
			}
		}

		WORD = groupedWords[randomNum % groupedWords.size()]; //Generate a random word

		actualWord = WORD;
	}
	std::vector <std::string> getDictionary() // Get the dictionary
	{
		return dictionary;
	}
	bool HasBeenGuessed(char guess)
	{
		for (size_t i = 0; i < guessedLetters.size(); i++)
		{
			if (guess == guessedLetters[i])
			{
				return false;
				break;
			}
		}

		return true;
	}
	void Guess() //Guess Function
	{
		char guess;
		bool flag1 = false; //Determine whether the guessed letter is in the word
		std::cout << "What is your next guess? "; //Ask the player to enter a guessed letter
		std::cin >> guess;
		while (HasBeenGuessed(guess) == false)
		{
			std::cout << "You have tried this letter! Try another one." << std::endl;
			std::cout << "What is your next guess? "; //Ask the player to enter another letter
			std::cin >> guess;
		}
		guessedLetters.push_back(guess);
		for (size_t i = 0; i < wordLength; i++)
		{
			if (actualWord[i] == guess)
			{
				flag1 = true;
				currentWord[i] = guess;
			}
		}
		if (flag1 == false)
		{
			std::cout << "The letter '" << guess << "' is not in the word." << std::endl;
			currentLives--; //False guess
		}
	}
	void printState() //Print State Function
	{
		std::cout << "--- Current State ---" << std::endl;
		std::cout << "You have " << currentLives << " lives left." << std::endl;
		std::cout << "Word: " << currentWord << std::endl;
	}
	void viewResult() //Get the result
	{
		if (currentLives == 0)
		{
			std::cout << "You used up your last guess and lost!" << std::endl;
			std::cout << "The word was " << actualWord << std::endl;
			end = true;
		}
		else
		{
			bool flag = true;
			for (size_t i = 0; i < wordLength; i++)
			{
				if (std::string(1, currentWord[i]) == "-")
				{
					flag = false;
					break;
				}
			}
			if (flag == true)
			{
				std::cout << "Congratulations! You win!" << std::endl;
				end = true;
			}
			else
			{
				std::cout << std::endl;
			}
		}
	}
	bool getEnd() //Get whether the game has ended
	{
		return end;
	}
};

class EvilHangman //Create Evil Hangman Class
{
private:
	unsigned int wordLength;
	int currentLives;
	bool end;
	std::vector <char> guessedLetters; //Used to determine whether a letter has been guessedor not
	std::string currentWord; //Same Parameters as Kind Hangman
	std::vector <std::string> evilActualWords; //Generate a =n updated list of words according the guessed letter
	std::vector <std::string> dictionary = load_words("dictionary.txt");

public:
	EvilHangman() //Constructor
	{
		end = false;

		unsigned int a;
		do
		{
			std::cout << "Enter a word length: ";
			std::cin >> a;

			if ((a < 2) || (a > 17))
			{
				std::cout << "No word with such length in the dictionary! Try another length." << std::endl;
			} //Reprompt Message

		} while ((a < 2) || (a > 17));

		wordLength = a; //Enter a word length

		currentWord = "";
		for (size_t i = 0; i < wordLength; i++)
		{
			currentWord += "-";
		}

		currentLives = 5; //Total lives = 5

		for (size_t i = 0; i < dictionary.size(); i++) //Get every word in the dictionary that has the word length
		{
			if (dictionary[i].size() == wordLength)
			{
				evilActualWords.push_back(dictionary[i]);
			}
		}
	}
	std::vector <std::string> EvilgetDictionary() // Get the dictionary
	{
		return dictionary;
	}
	bool EvilHasBeenGuessed(char guess)
	{
		for (size_t i = 0; i < guessedLetters.size(); i++)
		{
			if (guess == guessedLetters[i])
			{
				return false;
				break;
			}
		}

		return true;
	}
	void EvilGuess()
	{
		std::vector <int> loc;
		char guess;
		std::cout << "What is your next guess? ";
		std::cin >> guess;
		while (EvilHasBeenGuessed(guess) == false)
		{
			std::cout << "You have tried this letter! Try another one." << std::endl;
			std::cout << "What is your next guess? "; //Ask the player to enter a guessed letter
			std::cin >> guess;
		}
		guessedLetters.push_back(guess);
		std::vector <std::pair<std::string, std::string>> wordInfo;
		for (size_t i = 0; i < evilActualWords.size(); i++) //Get word info for every word
		{
			std::string loc = "";
			for (size_t j = 0; j < wordLength; j++) //Identify each word's type
			{
				if (evilActualWords[i][j] == guess)
				{
					loc += (std::to_string(j));
				}
			}
			wordInfo.push_back({ loc, evilActualWords[i] });
		}
		
		std::string maxLoc = ""; //The word type with largest number of members
		int max = 0; //The largest number
		for (size_t i = 0; i < wordInfo.size(); i++) //Get number of words with the word's same type of every word
		{
			int count = 0;
			for (size_t j = 0; j < wordInfo.size(); j++)
			{
				if (wordInfo[i].first == wordInfo[j].first)
				{
					count++;
				}
			}
			if (count > max) //Get the largest number
			{
				max = count;
				maxLoc = wordInfo[i].first;
			}
		}

		std::vector <std::string> largestFamily; //Get Largest Family
		for (size_t i = 0; i < wordInfo.size(); i++)
		{
			if (wordInfo[i].first == maxLoc)
			{
				largestFamily.push_back(wordInfo[i].second);
			}
		}

		std::vector <std::pair<std::string, std::string>> n_wordInfo;
		for (size_t i = 0; i < largestFamily.size(); i++) //Get rid of groups with same num of types but with different types from the first element in the vector
		{
			std::string n_loc = "";
			for (size_t j = 0; j < wordLength; j++)
			{
				if (largestFamily[i][j] == guess)
				{
					n_loc += (std::to_string(j));
				}
			}
			n_wordInfo.push_back({ n_loc, largestFamily[i] });
		}

		for (size_t i = 0; i < largestFamily.size();)
		{
			if (n_wordInfo[i].first != n_wordInfo[0].first)
			{
				largestFamily.erase(largestFamily.begin() + i);
				n_wordInfo.erase(n_wordInfo.begin() + i);
			}
			else
			{
				i++;
			}
		}

		evilActualWords.clear(); //Update evilActualWords
		for (size_t i = 0; i < largestFamily.size(); i++)
		{
			evilActualWords.push_back(largestFamily[i]);
		}

		if (n_wordInfo[0].first == "")
		{
			std::cout << "The letter '" << guess << "' is not in the word." << std::endl;
			currentLives--;
		}
		else
		{
			for (size_t i = 0; i < wordLength; i++)
			{
				if (largestFamily[0][i] == guess)
				{
					currentWord[i] = guess;
				}
			}
		}
	}
	void EvilPrintState()
	{
		std::cout << "--- Current State ---" << std::endl;
		std::cout << "You have " << currentLives << " lives left." << std::endl;
		std::cout << "Word: " << currentWord << std::endl;
	}
	void EvilViewResult()
	{
		if (currentLives == 0)
		{
			std::cout << "You used up your last guess and lost!" << std::endl;
			std::cout << "The word was " << evilActualWords[0] << std::endl;
			end = true;
		}
		else
		{
			bool flag = true;
			for (size_t i = 0; i < wordLength; i++)
			{
				if (std::string(1, currentWord[i]) == "-")
				{
					flag = false;
					break;
				}
			}
			if (flag == true)
			{
				std::cout << "Congratulations! You win!" << std::endl;
				end = true;
			}
			else
			{
				std::cout << std::endl;
			}
		}
	}
	bool EvilGetEnd()
	{
		return end;
	}

};

int main()
{
	std::cout << "Welcome to COP 3504 C's Hangman! " << std::endl << std::endl; //Welcome Message

	int mode = 0;
	std::cout << "Select Mode: 1. Kind Hangman; 2. Evil Hangman "; //Select Mode
	std::cin >> mode;

	if (mode == 1)
	{
		Hangman h1;
		h1.printState();

		do
		{
			h1.Guess();
			h1.printState();
			h1.viewResult();
			if (h1.getEnd() == true)
			{
				break;
			}

		} while (h1.getEnd() == false);
	}

	else
	{
		EvilHangman h2;
		h2.EvilPrintState();

		do
		{
			h2.EvilGuess();
			h2.EvilPrintState();
			h2.EvilViewResult();
			if (h2.EvilGetEnd() == true)
			{
				break;
			}

		} while (h2.EvilGetEnd() == false);
	}

	return 0;
}