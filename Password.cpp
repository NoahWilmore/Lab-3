#include "ListArrayIterator.h"
#include "Password.h"
#include <iostream>
using namespace std;
using namespace CSC2110;

Password::Password()
{
	all_words = new ListArray<String>();
	viable_words = new ListArray<String>();
	len = 0;
}

Password::~Password()
{
	delete all_words;
	delete viable_words;
}

int Password::getNumMatches(String* curr_word, String* word_guess)
{
	int counter = 0;
	
	for (int i = 0; i < curr_word->sz; i++)
	{
		if (curr_word->charAt(i) == word_guess->charAt(i))
		{
			counter++;
		}
	}
	return counter;
}

void Password::addWord(String* word)
{
	all_words->addWord();
}

void Password::guess(int try_password, int num_matches)
{
	/*look up the guessed word
	get and try password (note it must be written as try_password - 1)
	for each word in viable_words, count the number of characters in common with guessed word
	if the number of matches that we just counted equals the number of passes that was just passed to us, we're done
	*/
	ListArrayIterator<String>* iter= vialble_words->iterator;
	
	iter->next();
	
	while(iter->hasNext())
	{
		if(getNumMatches(viable_words->get (try_password), curr_word != num_matches))
		{
			
		}
	}
}

int Password::getNumberOfPasswordsLeft()
{
	//iterate through the list and count the number of remaining passwords
	ListArrayIterator<String>* iter = [ListArray]->iterator();
	while(iter->hasNext())
	{
		iter->Next()->[displayString];
		iter->Next()->[viable_words];
	}
	
	return iter;
}

void Password::displayViableWords()
{
	//iterate through the list and display the remaining viable words
	viable_words->displayString();
}

String* Password::getOriginalWord(int index)
{
	//take the one-based index and turn it into a zero-based index
	String* original = index->get(viable_words);
	
	return original;
}

int Password::bestGuess()
{
   int best_guess_index = -1;
   int best_num_eliminated = -1;
   int num_viable_passwords = getNumberOfPasswordsLeft();

   //loop over ALL words, even if they have been eliminated as the password
   int count = 1;
   ListArrayIterator<String>* all_iter = all_words->iterator();
   while(all_iter->hasNext())
   {
      String* original_word = all_iter->next();

      //loop over only those words that could still be the password
      //count up the number of matches between a possible password and a word in the original list
      int* count_num_matches = new int[len + 1];

      for (int i = 0; i < len; i++) 
      {
         count_num_matches[i] = 0;
      }

      ListArrayIterator<String>* viable_iter = viable_words->iterator();
      while(viable_iter->hasNext())
      {
         String* viable_word = viable_iter->next();
         int num_matches = getNumMatches(viable_word, original_word);
         count_num_matches[num_matches]++;
      }
      delete viable_iter;

      //find the largest number in the count_num_matches array
      //the largest number indicates the guess that will generate the most eliminations
      int most_num_matches = 0;
      for (int j = 0; j < len; j++) 
      {
         int curr_num_matches = count_num_matches[j];
         if (curr_num_matches > most_num_matches)
         {
            most_num_matches = curr_num_matches;
         }
      }

      //compute the fewest that can possibly be eliminated by guessing the current word (original list)
      int num_eliminated = num_viable_passwords - most_num_matches;

      //select the word to guess that maximizes the minimum number of eliminations (minimax)
      if (num_eliminated > best_num_eliminated)
      {
         best_num_eliminated = num_eliminated;
         best_guess_index = count;
      }
      
      count++;
      delete[] count_num_matches;
   }

   delete all_iter;
   return best_guess_index;  //return a 1-based index into the all_words list of words (careful)
}
