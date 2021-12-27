#include <iostream>
#include <fstream>
#include <string>
#include <regex>

#include "Histogram.hpp"
#include "AlphabetPtr.hpp"
#include "SparseVector.hpp"
#include "MySet.hpp"
#include "SequenceGenerator.hpp"
#include "DictionaryGenerator.hpp"
#include "PersonGenerator.hpp"
#include "SparseVectorGenerator.hpp"

string readFileIntoString(const string& path)
{
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    return string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}


struct Input
{
    virtual string operator()() = 0;

    protected:
        regex reg;
};

struct WordInput : public Input
{
    WordInput()
    {
        reg = "^[a-zA-Z1-9]*$";
    }

    string operator()() override
    {
        string buff;
        char ch;

        while (true)
        {
            cout << "Please, enter some word: " << endl;

            while ((ch = getchar() ) != '\n')
                buff.push_back(ch);

            cin.clear();

            if (!regex_match(buff, reg) )
            {
                cout << "Invalid input. Please, retype" << endl << endl;
                buff.erase(buff.begin(), buff.end());
                continue;
            }
            break;
        }
        return buff;
    }
};

struct UI
{
    AlphabetPtr wordSearch(string text, size_t lineSize, size_t pageSize)
    // alphabetPtr
    {
        while (true)
        {
            cout << "Testing alphabetPtr" << endl;
            cout << "Type ! to exit interrupt" << endl;

            WordInput word;
            string buff = word();

            AlphabetPtr aPtr(text, lineSize, pageSize);

            if (buff == "!")
            {
                cout << "End of test" << endl;;
                break;
            }
            return aPtr;
        }
    }
    void histogram()
    {

    }

};

int main()
{
    UI ui;

    string path("src/Tasks/AlphabetPtr/samples/sample1.txt");
    string fillerText = readFileIntoString(path);

    AlphabetPtr aPtr = ui.wordSearch(fillerText, 24, 50);
    aPtr.print();

    AlphabetPtr::Occurrences occurrences(aPtr.find("vitae"));

    cout << "Found occurrences: " << endl << endl;
    occurrences.print();

    // Histogram Section

    std::pair<double, double> ageRange(10, 70);
    std::pair<double, double> heightRange(150, 200);
    std::pair<double, double> weightRange(50, 130);
    size_t shortestName(1);
    size_t longestName(30);

    vector<Person> people = personGenerator(30, ageRange, heightRange, weightRange, shortestName, longestName);

    for (auto it : people)
    {
        it.print();
        cout << endl;
    }

    Histogram histogram(people);
    histogram.plot(5, Criteria::partition_, PlotBy::weight);

    SparseVector sparseVector(sparseVectorGenerator(100, 75, 10, 1000));
    sparseVector.print();

    /*
    cout << "Hello world!" << endl;

    string test = "   This     is   the 1st     test      ";
    vector<string> parsed;

    parsed = parse(test);
    int iteration = 0;

    for (auto it : parsed)
        cout << iteration++ << ": " << it << endl;


    string filename("src/Tasks/AlphabetPtr/samples/sample1.txt");
    string file_contents;

    file_contents = readFileIntoString(filename);

    AlphabetPtr ptr(file_contents, 20, 5);
    AlphabetPtr::Pages pages = ptr.get();
    ptr.exportToFile();


    AlphabetPtr::Occurrences occurrences(ptr.find("amet"));

    vector<unsigned int> occurrence(occurrences[0]);

    cout << "Size: " << occurrence.size() << endl;

    cout << "Page: " << occurrence[0] << endl;
    cout << "Line: " << occurrence[1] << endl;
    cout << "Word: " << occurrence[2] << endl;

    /*

    //Person::Gender gender = Person::Gender::male;

    //Person person(40, 170, 75, "Michael", "John", gender);

    //cout << person.getName() << endl;

    cout << endl << endl << endl;

    int* indexes = new int[5];

    for (int i=0; i<5; ++i)
    {
        indexes[i] = i+10;
    }

    float* values = new float[5];

    for (int i=0; i<5; ++i)
        values[i] = i + 0.5;

    MySet<int> Indexes(indexes, 5);
    Sequence<float> Values(values, 5);

    cout << "Printing Indexes" << endl;
    Indexes.print();

    cout << "Printing Values" << endl;
    Values.print();

    Dictionary<int, float> dict(Indexes, Values);

    SparseVector<float> sparseVector(dict);
    sparseVector.print();

    //SparseVector<float> testingGeneration = SparseVector<float>::generate(30, 80);

    // generatedSequence.print();

    Sequence<int> testSet;

    for (int i=0; i<10; ++i)
        testSet.push_back(i);

    Criteria crit = Criteria::partition_;
    //Histogram histogram1(testSet, 4, crit);


    SequenceGenerator<int> seqGen;
    Sequence<int> testHistogram = seqGen(10, 100, 500);

    cout << "testHistogram" << endl;
    //testHistogram.print();
    cout << "testHistogram" << endl;
    Histogram histogram2(testHistogram, 4, crit);
    */


    /*

    int *arr = new int[5];

    arr[0] = 4298;
    arr[1] = 2891;
    arr[2] = 190;
    arr[3] = 189;
    arr[4] = 62798;

    MySet<int> setIntManual(arr, 5);
    cout << "Initial size: " << setIntManual.size() << endl;
    setIntManual.print();

    if (setIntManual.find(2891))
        cout << "2891 has been found" << endl;

    setIntManual.remove(189);
    cout << "189 is likely to be deleted" << endl;

    cout << setIntManual.size() << endl;

    //setIntManual.remove(687);

    setIntManual.add(6);
    setIntManual.add(6);

    cout << endl;

    setIntManual.print();

    //DictionaryGenerator<int, int> dictGen;
    //Dictionary<int, int> dict(move(dictGen(-10000, 10000, -100, 100, 50)));

    //dict.print();

    Dictionary<double, double> dict = dictionaryGenerator<double, double>(-1000, 1000, -10, 10, 7);

    dict.printKeys();
    dict.printValues();

    dict.add(50.6888, 6789);

    dict.printKeys();
    dict.printValues();

    dict.remove(50.6888);

    dict.printKeys();
    dict.printValues();
    */



    //SparseVector<double> sparseVector(sparseVectorGenerator<double>(20, 75, 10, 100));
    //sparseVector.print();


    return 0;
}
