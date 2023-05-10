#include <iostream>
#include <vector>
#include <map>
#include "lexicon.h"

#define MIN_WORD_SIZE 3

class Boggle {
private:
    Lexicon lexicon;

    struct letter {
        int row;
        int col;
        char ch;
        bool checked;
    };

    struct Map {
        int row, col;
        letter *map;

        Map(int row, int col): row(row), col(col) {
            map = new letter[row * col];
        }
        ~Map() {
            delete[] map;
        }
        letter *operator[](const int &r) const {
            return &map[r * col];
        }
    } map;
    
public:
    enum status {OK, NOT_FOUND, NOT_WORD, UNDER_SIZE};

    explicit Boggle(int N): lexicon("../EnglishWords.txt"), map(N, N) {
        char ch;
        for (int i = 0; i < map.row; i++)
            for (int j = 0; j < map.col; j++) {
                std::cin >> ch;
                ch = (char)toupper(ch);
                map[i][j] = {i, j, ch, false};
            }
    }
    ~Boggle() = default;

    void print() {
        for (int i = 0; i < map.row; i++) {
            for (int j = 0; j < map.col; j++)
                std::cout << map[i][j].ch;
            std::cout << std::endl;
        }
    }

    status find_word(const std::string &word) {
        if (word.size() <= MIN_WORD_SIZE)
            return UNDER_SIZE;
        if (!lexicon.contains(word))
            return NOT_WORD;

        return find_rest(word, nullptr, 0);
    }

    size_t auto_find(std::map<std::string, int> &already, std::map<std::string, int> &list) {
        size_t size = 0;

        auto_rest(already, list, size, nullptr, "");

        return size;
    }
    
private:
    status find_rest(const std::string &word, letter *p, int pre) {
        if (pre == word.size())
            return OK;

        status ret = NOT_FOUND;

        std::vector<letter *> children;
        if (p == nullptr)
            find_letter(word[pre], children);
        else
            find_neighbor(p, word[pre], children);

        p != nullptr && (p->checked = true);
        for (auto next : children) {
            if (find_rest(word, next, pre + 1) == OK) {
                ret = OK;
                break;
            }
        }
        p != nullptr && (p->checked = false);

        return ret;
    }

    void auto_rest(std::map<std::string, int> &already, std::map<std::string, int> &list, size_t &size, letter *p, const std::string& prefix) {
        if (!lexicon.containsPrefix(prefix))
            return;

        if (prefix.size() > MIN_WORD_SIZE && lexicon.contains(prefix) &&
            already.count(prefix) == 0 && list.count(prefix) == 0) {
            list.emplace(prefix, 0);
            size += prefix.size();
        }

        std::vector<letter *> children;
        if (p == nullptr)
            find_letter(0, children);
        else
            find_neighbor(p, 0, children);
        if (children.empty())
            return;

        for (auto &next : children) {
            next->checked = true;
            auto_rest(already, list, size, next, prefix + next->ch);
            next->checked = false;
        }
    }

    void find_letter(char ch, std::vector<letter *> &list) {
        for (int i = 0; i < map.row; i++)
            for (int j = 0; j < map.col; j++)
                if ((ch == 0 || map[i][j].ch == toupper(ch)) &&
                    !map[i][j].checked)
                    list.push_back(&map[i][j]);
    }

    void find_neighbor(letter *p, char ch, std::vector<letter *> &list) {
        int n_r = p->row + 1 < map.row ? p->row + 1 : map.row - 1;
        int n_c = p->col + 1 < map.col ? p->col + 1 : map.col - 1;
        for (int i = p->row - 1 > 0 ? p->row - 1 : 0; i <= n_r; i++)
            for (int j = p->col - 1 > 0 ? p->col - 1 : 0; j <= n_c; j++)
                if ((ch == 0 || map[i][j].ch == toupper(ch))
                    && !map[i][j].checked
                    && (i != p->row || j != p->col))
                    list.push_back(&map[i][j]);
    }
};

/*
4
eeca
alep
hnbo
qtty

5
eeird
agmrs
ciiln
dlote
frwot

10
aklodrgiew
lopuijoklo
ooleravbae
jkqosovjre
ooalebnmsj
oaeihjnkeo
jkonjoeiji
jiokkwechi
jsiokooaee
aojeilksqa
 */

int main() {
    int N;
    do std::cin >> N; while (N < 0);
    Boggle boggle(N);

    size_t player_score = 0;
    size_t auto_score = 0;
    std::vector<std::string> player_words;
    std::map<std::string, int> player_hash_lower;
    std::map<std::string, int> player_hash_upper;
    std::map<std::string, int> auto_words;

    std::string input;
    while (true) {
        boggle.print();
        std::cout << "Your Score: " << player_score << std::endl;
        std::cout << "Your Words: ";
        for (auto &word: player_words)
            std::cout << word << " ";
        std::cout << std::endl;

        std::cin >> input;
        if (input == "???") {
            auto_score = boggle.auto_find(player_hash_upper, auto_words) - 3 * auto_words.size();
            std::cout << "Computer Score: " << auto_score << std::endl;
            std::cout << "Computer Words: ";
            for (auto &word: auto_words)
                std::cout << word.first << " ";
            std::cout << std::endl;
            break;
        }

        switch (boggle.find_word(input)) {
            case Boggle::OK:
                for (auto &c : input)
                    c = (char)tolower(c);
                if (player_hash_lower.count(input) != 0)
                    std::cout << input << " is already found." << std::endl;
                else {
                    player_words.emplace_back(input);
                    player_hash_lower.emplace(input, 0);
                    for (auto &c : input)
                        c = (char)toupper(c);
                    player_hash_upper.emplace(input, 0);
                    player_score += (input.size() - 3);
                }
                break;
            case Boggle::NOT_FOUND:
                std::cout << input << " is not on board." << std::endl;
                break;
            case Boggle::NOT_WORD:
                std::cout << input << " is not a word." << std::endl;
                break;
            case Boggle::UNDER_SIZE:
                std::cout << input << " is too short." << std::endl;
                break;
        }
    }

    return 0;
}
