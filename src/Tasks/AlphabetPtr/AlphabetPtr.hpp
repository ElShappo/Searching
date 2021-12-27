#ifndef ALPHABET_PTR_HPP
#define ALPHABET_PTR_HPP

#include <string>
#include <vector>
#include <exception>
#include <fstream>
//#include "tabulate.hpp"

#include "AlphabetPtrException.hpp"
std::vector<string> & parse(std::string str)
// split the string into words (whitespace is the delimeter)
{
    std::vector<string> * parsed = new vector<string>();
    std::string buff = "";

    for (const auto & it : str)
    {
        if (iswalnum(it))
            buff.push_back(it);
        else
        {
            if (!buff.empty())
            {
                parsed->push_back(buff);
                buff = ""; // erase the string
            }
        }
    }
    if (!buff.empty())
        parsed->push_back(buff);
    return *parsed;
}

class AlphabetPtr
{
public:

    typedef std::vector<string> Line;

    // -------------START OF LINES DEFINITION-------------

    class Lines {
    private:
        std::vector<vector<string>> lines_; // list of lines
        size_t lineSize_ = 0; // max number of symbols in the line

    public:
        Lines()
        {

        }
        Lines(const Line & words, const size_t lineSize)
        // merge words into lines
        // there is a maximum amount of words on each string
        {
            this->lineSize_ = lineSize;

            Line buff;
            size_t buffSize; // total length of the buffer + the whitespaces

            for (const auto & it : words)
            {
                buffSize = 0;
                for (auto const & word : buff)
                    buffSize += word.size();
                buffSize += buff.size()-1; // add the whitespaces

                if (it.size() + 1 + buffSize <= lineSize_)
                // if we want to add new word to the string, we have to check whether whitespace plus the word length fit in
                {
                    buff.push_back(it);
                }
                else
                // if buffer is full
                // push the constructed string to the 'lines_'
                // clear the buffer and add the word which didn't fit in
                // Note: buffer is not guaranteed to have the length <= lineSize_
                //       but it's contents get passed to lines_ nonetheless (if the word is too long for one string,
                //       this string gets wider to fit this word
                {
                    lines_.push_back(buff);
                    buff.erase(buff.begin(), buff.end());
                    buff.push_back(it);
                }
            }
            lines_.push_back(buff);
        }
        void operator= (Line & str)
        // normally we would need to pass vector<vector<string>>, but there is only one case of this method usage
        {
            lines_.erase(lines_.begin(), lines_.end());
            lines_.push_back(str);
        }
        Line & operator[] (size_t index)
        // access the line with the passed index
        {
            return lines_[index];
        }
        void push_back(Line & str)
        // push line to the list of lines
        {
            lines_.push_back(str);
        }
        std::vector<vector<string>> get() const
        // get the list of lines
        {
            return lines_;
        }
        Line get(unsigned int index) const
        // get the line with the needed index
        {
            return lines_[index];
        }
        size_t size() const
        // get number of lines
        {
            return lines_.size();
        }
        bool empty() const
        {
            if (this->size() == 0)
                return true;
            return false;
        }
        /*
        void print(unsigned int index)
        // print line
        {
            printLine(lines_[index]);
        }
        void print()
        // print Lines
        {
            for (const auto & line : lines_)
            {
                printLine(line);
                cout << endl;
            }
        }
        */

        /*
        size_t totalLength() const
        // returns the total length of all the words in the lines (without whitespaces)
        {
            size_t length = 0;

            for (const auto & it : lines_)
            {
                for (const auto & word : it)
                {
                    length += word.size();
                }
            }
            return length;
        }

        size_t totalLengthWithSpaces() const
        {
            size_t spaces = size()-1;
            return totalLength() + spaces;
        }*/
    };

    // -------------END OF LINES DEFINITION-------------

    // -------------START OF PAGES DEFINITION-------------

    class Pages
    {
    private:
        std::vector<Lines> pages_; // list of pages
        size_t pageSize_ = 0; // max number of lines on the page
    public:
        Pages() {}
        void operator= (const Lines & lines)
        {
            Lines page;

            pages_.erase(pages_.begin(), pages_.end());

            for (size_t i=0; i<lines.size(); ++i)
            {
                /*
                cout << "PAGE INITIAL STATE: "; page.print(); cout << endl << endl;
                if (page.empty())
                    cout << "Empty!" << endl;
                */

                size_t modifiedPageSize = pageSize_;

                if (pages_.size() == 0) // if the main page
                {
                    modifiedPageSize = (int)pageSize_ /2;
                }
                else if ((pages_.size()+1) % 10 == 0) // if the 10th, 20th, ... page
                    modifiedPageSize = (int)pageSize_*3/4;

                auto line = lines.get(i); // current element

                if (page.size() + 1 <= modifiedPageSize) // amount of already added lines + one more
                    page.push_back(line);
                else
                {
                    /*
                    page.print();
                    cout << endl << endl << endl;
                    */
                    pages_.push_back(page);
                    page = line;
                }
            }
            pages_.push_back(page);

        }
        Pages(Lines lines, size_t pageSize)
        {
            this->pageSize_ = pageSize;
            *this = lines;
        }
        Lines & operator[] (int index)
        // get single page
        {
            return pages_[index];
        }
        std::vector<Lines> get() const
        // get list of all pages
        {
            return pages_;
        }
        size_t size() const
        {
            return pages_.size();
        }
    };

    // -------------END OF PAGES DEFINITION-------------

    Pages pages_;

    AlphabetPtr(std::string text, size_t lineSize = 30, size_t pageSize = 100)
    {
        Line words = parse(text); // split into words

        if (words.empty())
            cout << "Empty" << endl;

        Lines lines(words, lineSize); // merge the words into Strings
        Pages pages(lines, pageSize); // merge the lines into Pages

        pages_ = pages;

        // Note: each index [] of Pages is the page
        //       each index [] of Lines is the line
        //       each index [] of Words is the word
    }

    Pages get()
    {
        return pages_;
    }

    ofstream exportToFile()
    {
        ofstream outFile("src/Tasks/AlphabetPtr/ouputs/output1.txt");

        int page = 1;

        for (auto & it : this->get().get())
        // get page
        {
            outFile << "PAGE " << page++ << endl;
            for (int i=0; i<it.size(); ++i)
            // get string (vector<string>)
            {
                Line buff = it[i];

                int iteration = 0;
                for (const auto &str : buff)
                {
                    if (iteration != buff.size()-1)
                        outFile << str << " ";
                    else
                        outFile << str; // if last symbol in the string no whitespace on the end is needed
                }
                outFile << "\n";
            }
        }
        outFile << endl << endl << endl;
        return outFile;
    }

    void print() const
    {
        //Tabulate::Table table;

        //table.add_row({"This paragraph contains a veryveryveryveryveryverylong word. The long word will "
                        //"break and word wrap to the next line.",
                        //"This paragraph \nhas embedded '\\n' \ncharacters and\n will break\n exactly "
                        //"where\n you want it\n to\n break."});

        //table[0][0].format().width(20);
        //table[0][1].format().width(50);


        for (int i=0; i<pages_.size(); ++i)
        // iterate over pages
        {
            int numberOfLinesOnThePage = pages_[i].size();

            cout << i << " PAGE" << endl << endl;

            for (int j=0; j<numberOfLinesOnThePage; ++j)
            // iterate over lines on the page
            {
                int numberOfWordsOnTheLineOnThePage = pages_[i][j].size();
                cout << "[" << j << "]: ";

                Line line = pages_[i][j];
                size_t lineTotalLength = 0;

                for (auto word : line)
                    lineTotalLength += word.size();

                lineTotalLength += line.size()-1; // add N-1 whitespaces

                for (int k=0; k<numberOfWordsOnTheLineOnThePage; ++k)
                // iterate over words on the line on the page
                {
                    cout << pages_[i][j][k] << " ";
                }
                cout << "(" << lineTotalLength << ")" << endl; // end of string
            }
            cout << endl << endl; // end of page
        }
    }

    class Occurrences
    {
    private:
        // holding the indexes (from 0)
        std::vector<int> pages_;
        std::vector<int> lines_;
        std::vector<int> words_;

        std::string key_;

    public:
        explicit Occurrences(const vector<int> & pages, const vector<int> & lines, const vector<int> & words, const string & key)
        {
            pages_ = pages;
            lines_ = lines;
            words_ = words;

            key_ = key;
        }
        std::vector<int> getPages() const {return pages_;}
        std::vector<int> getLines() const {return lines_;}
        std::vector<int> getWords() const {return words_;}

        void print()
        {
            bool enter = false;

            for (int i=0; i<pages_.size(); ++i)
            {
                cout << "[" << pages_[i] << "]" << "[" << lines_[i] << "]" << "[" << words_[i] << "]" << endl;
                enter = true;
            }
            if (!enter)
                cout << "No occurrences of the word " << key_ << endl;
        }
    };

    Occurrences find(string key)
    {
        std::vector<int> pages;
        std::vector<int> lines;
        std::vector<int> words;

        int page, line, word; // their positions in the text i.e pages_[i][j][k]

        for (int i=0; i<pages_.size(); ++i)
        // iterate over pages
        {
            int numberOfLinesOnThePage = pages_[i].size();

            for (int j=0; j<numberOfLinesOnThePage; ++j)
            // iterate over lines on the page
            {
                int numberOfWordsOnTheLineOnThePage = pages_[i][j].size();

                for (int k=0; k<numberOfWordsOnTheLineOnThePage; ++k)
                // iterate over words on the line on the page
                {
                    if (pages_[i][j][k] == key)
                    {
                        pages.push_back(i);
                        lines.push_back(j);
                        words.push_back(k);
                    }
                }
            }
        }
        return Occurrences (pages, lines, words, key);
    }
/*
    // -------------START OF OCCURRENCES DEFINITION-------------

    class Occurrences
    // auxiliary class to store the occurrences of the word (used in 'find' method)
    {
    public:
        Occurrences(string keyword)
        {
            keyword_ = keyword;
        }

        void operator=(const Occurrences & occurrences)
        {
            keyword_ = occurrences.getKeyword();
            matches_ = occurrences.getMatches();
            pagesNumbers_ = occurrences.getPages();
            linesNumbers_ = occurrences.getLines();
            wordsNumbers_ = occurrences.getWords();
        }

        Occurrences(const Occurrences & occurrences)
        // copy constructor
        {
            keyword_ = occurrences.getKeyword();
            matches_ = occurrences.getMatches();
            pagesNumbers_ = occurrences.getPages();
            linesNumbers_ = occurrences.getLines();
            wordsNumbers_ = occurrences.getWords();
        }

        void add(unsigned int pageNumber, unsigned int lineNumber, unsigned int wordNumber)
        // add occurrence
        {
            cout << "Add has been called!" << endl;

            cout << "Page: " << pageNumber << endl;
            cout << "Line: " << lineNumber << endl;
            cout << "Word: " << wordNumber << endl;

            pagesNumbers_.push_back(pageNumber);
            linesNumbers_.push_back(lineNumber);
            wordsNumbers_.push_back(wordNumber);
        }

        vector<unsigned int> & get(unsigned int index)
        {
            vector<unsigned int>* occurrence = new vector<unsigned int>
                {pagesNumbers_[index],
                linesNumbers_[index],
                wordsNumbers_[index]};
            return *occurrence;
        }
        vector<unsigned int> & operator[](unsigned int index)
        {
            return get(index);
        }
        size_t size() const
        {
            return pagesNumbers_.size();
        }

        vector<unsigned int> getPages() const {return pagesNumbers_;}
        vector<unsigned int> getLines() const {return linesNumbers_;}
        vector<unsigned int> getWords() const {return wordsNumbers_;}

        string getKeyword() const {return keyword_;}
        // return the word the occurrence of which is to find

        size_t getMatches() const {return matches_;}

    private:
        string keyword_; // word the occurrence of which is to find

        size_t matches_ = 0; // number of matches of the specific word

        vector<unsigned int> pagesNumbers_; // list of pages where specific word is met
        vector<unsigned int> linesNumbers_; // list of lines where specific word is met
        vector<unsigned int> wordsNumbers_; // list of words where specific word is met
    };

    // -------------END OF OCCURRENCES DEFINITION-------------

    Occurrences & find(string cmp)
    {
        unsigned int pageNumber = 0;
        unsigned int lineNumber = 0;
        unsigned int wordNumber = 0;

        Occurrences* occurrences = new Occurrences(cmp);

        for (unsigned int i = 0; i < pages_.size(); ++i)
        {
            Lines page = pages_[i];

            for (int j=0; j<page.size(); ++j)
            {
                Line line = page[j];

                for (const auto & word : line)
                {
                    if (word == cmp)
                    {
                        cout << "Match!" << endl;

                        occurrences->add(pageNumber, lineNumber, wordNumber);
                    }

                    ++wordNumber;
                }
                ++lineNumber;
            }
            ++pageNumber;
        }

        cout << "Amount of occurrences: " << occurrences->size() << endl;

        return *occurrences;
    }
    */
};

#endif // ALPHABET_PTR_HPP
/*
void printStrings(Line lines)
{
    int iteration = 0;

    for (const auto & it : vec)
    {
        if (iteration == vec.size()-1)
            cout << it;
        else
            cout << it << " ";
        ++iteration;
    }
}

void printPages()
{
    vector<Pages> buff = get();

    for (const auto & it : buff)

}
*/
