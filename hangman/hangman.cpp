#include <iostream>
#include <map>
#include <time.h>
#include <stdlib.h>

using namespace std;

class GuessWord;

class Action {
public:
    virtual void run(GuessWord* guess_word) = 0;
};

class GuessWord {
    std::string word;
    std::string hidden_word;

public:
    GuessWord(const std::string& word);
    int get_word_length();
    void guess_char(char chr);
    bool have_won();
    void reveal_letter(int index);
    void set_word(const std::string& word);
    void show_hidden_word();
};

GuessWord::GuessWord(const std::string& word) {
    set_word(word);
}

int GuessWord::get_word_length() {
    return word.size();
}

void GuessWord::guess_char(char chr) {
    for (int i = 0; i < word.size(); i++) {
        if (word[i] == chr && hidden_word[i] == '*') {
            reveal_letter(i);
        }
    }
}

bool GuessWord::have_won() {
    return word == hidden_word;
}

void GuessWord::reveal_letter(int index) {
    if (index >= 0 && index < word.size()) {
        hidden_word[index] = word[index];
    }
}

void GuessWord::set_word(const string& word) {
    this->word = word;
    this->hidden_word.clear();

    for (int i = 0; i < word.size(); i++)
        hidden_word.push_back('*');
}

void GuessWord::show_hidden_word() {
    cout << "WORD: " << hidden_word << endl;
}


int main(int argc, char** argv) {
  
    class GuessLetter : public Action
    {
    private:
        char letter;
    public:
        GuessLetter(char letter) : letter(letter) {}
        virtual void run(GuessWord* guess_word) { guess_word->guess_char(letter); }
    };

    class RevealLetter : public Action
    {
    private:
        int place;
    public:
        RevealLetter(int place) : place(place) {}
        virtual void run(GuessWord* guess_word) { guess_word->reveal_letter(place); }
    };

    class RevealRandom : public Action
    {
    public:
        //static vector<int> availablePlaces; ?????
        RevealRandom() { srand(time(NULL)); }
        virtual void run(GuessWord* guess_word) { guess_word->reveal_letter(rand() % guess_word->get_word_length()); }

    };
    GuessWord* word = new GuessWord("Hello");
    string action;
    char letter;
    int place;
    map<string, GuessLetter*> lettersGuessed;
    map<string, GuessLetter*>::iterator ptr1 = lettersGuessed.begin();

    map<string, RevealLetter*> lettersRevealed;
    map<string, RevealLetter*>::iterator ptr2;

    map<string, RevealRandom*> randomLettersRevealed;
    map<string, RevealRandom*>::iterator ptr3;
    cout << "ACTIONS: guess reveal reveal_random" << endl;
    while (!word->have_won())
    {

        word->show_hidden_word(); cout << "> ";
        cin >> action;
        if (action == "guess")
        {
            cin >> letter;
            lettersGuessed[action] = new GuessLetter(letter);
            lettersGuessed[action]->run(word);
        }
        else if (action == "reveal")
        {
            cin >> place;
            lettersRevealed[action] = new RevealLetter(place);
            lettersRevealed[action]->run(word);
        }
        else if (action == "reveal_random")
        {
            randomLettersRevealed[action] = new RevealRandom;
            randomLettersRevealed[action]->run(word);
        }
        else
        {
            cout << "No such command" << endl;
        }
                    
       

    }

    word->show_hidden_word(); cout << "> ";
    cout << "Victory!" << endl;


}
