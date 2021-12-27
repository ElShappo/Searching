#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main()
#include "catch.hpp"

#include <string>
#include <vector>

#include "AlphabetPtr.hpp"
#include "Dictionary.hpp"
#include "Sequence.hpp"
#include "MySet.hpp"
#include "SequenceGenerator.hpp"
#include "MySetGenerator.hpp"

/*
TEST_CASE( "Parse function test") {

    string test = " This is the 1st  test  ";
    vector<string> parsed;

    parsed = parse(test);

    CHECK_NOTHROW([&](){
        parsed = parse(test);
    }());

    CHECK(parsed[0] == "This");
    CHECK(parsed[1] == "is");
    CHECK(parsed[2] == "the");
    CHECK(parsed[3] == "1st");
    CHECK(parsed[4] == "test");
}
*/

TEST_CASE("Testing removeAllOccurrences") {

    int arr[6] = {5, 5, 4, 0, 1, 2};

    Sequence<int> seq(arr, 6);
    seq.removeAllOccurrences(5);
    seq.print();
}

TEST_CASE("Testing removeRepetitions") {

    int arr[6] = {5, 5, 4, 0, 1, 2};

    Sequence<int> seq(arr, 6);
    seq.removeRepetitions(5);
    seq.print();
}

// TESTING SEQUENCE CTORS

TEST_CASE("Testing normal ctor")
{
    double test[7] = {1.0, 5.67, 0.35, 0.45, 0.45, 0.45, 25.789};
    Sequence<double> seq(test, 7);
    CHECK(seq.size() == 7);

    seq.remove(5);

    CHECK(seq.size() == 6);
    seq.print();
}

TEST_CASE("Testing copy ctor")
{
    double test[7] = {1.0, 5.67, 0.35, 0.45, 0.45, 0.45, 25.789};
    Sequence<double> seq(test, 7);
    Sequence<double> newSeq(seq);
}

TEST_CASE("Testing assign ctor")
{
    double test[7] = {1.0, 5.67, 0.35, 0.45, 0.45, 0.45, 25.789};
    Sequence<double> seq(test, 7);
    Sequence<double> newSeq = seq;
}

TEST_CASE("Testing the comparing")
{
    double test[7] = {1.0, 5.67, 0.35, 0.45, 0.45, 0.45, 25.789};

    Sequence<double> seq1(test, 7);
    Sequence<double> seq2(test, 7);

    CHECK(seq1 == seq2);
}

TEST_CASE("Testing remove [1]")
{
    double test[7] = {1.0, 5.67, 0.35, 0.45, 0.45, 0.45, 25.789};
    Sequence<double> seq(test, 7);

    cout << "Testing remove [1]" << endl;

    seq.remove(4);
    CHECK(seq.size() == 6);
    seq.print();

    cout << endl;

    seq.remove(0);
    CHECK(seq.size() == 5);
    seq.print();

    cout << endl;

    seq.insert(1.0, 0);
    CHECK(seq.size() == 6);
    seq.print();

    seq.remove(1);
    seq.remove(1);
    seq.remove(1);
}

TEST_CASE("Complex test for Sequence")
{
    SequenceGenerator<int> seqIntGen;
    SequenceGenerator<float> seqFloatGen;

    Sequence<int> randomInt = seqIntGen(-100, 100, 20);
    Sequence<float> randomFloat = seqFloatGen(-100, 100, 20);

    CHECK(randomInt.size() == 20);
    CHECK(randomFloat.size() == 20);

    randomInt.print();
    cout << endl;
    randomFloat.print();
}


TEST_CASE("Complex test for Set")
{
    MySetGenerator<int> setIntGen;
    MySetGenerator<float> setFloatGen;

    MySet<int> randomInt(setIntGen(-100, 100, 50));
    MySet<float> randomFloat(setFloatGen(-100, 100, 50));

    cout << "Set: randomInt.print():" << endl;
    randomInt.print();
    cout << "Set: randomFloat.print():" << endl;
    randomFloat.print();

    int *arr = new int[5];

    arr[0] = 4298;
    arr[1] = 2891;
    arr[2] = 190;
    arr[3] = 189;
    arr[4] = 62798;

    MySet<int> setIntManual(arr, 5);
    setIntManual.print();

    CHECK(setIntManual.find(2891));
    setIntManual.remove(189);

    CHECK_THROWS(setIntManual.remove(687));

    setIntManual.add(6);
    setIntManual.add(6);

    setIntManual.print();

}



/*

TEST_CASE("Testing MySet [1]")
{
    Sequence<float> seq = generateSequence<float>(15, -100, 50);
    seq.print();

    Set<float> set(seq);
    set.print();
}

TEST_CASE("Testing MySet [2]")
{
    Sequence<float> seq = generateSequence<float>(15, 5, 50);
    seq.print();

    cout << endl << endl;

    Set<float> set(seq);
    set.print();
}

TEST_CASE("Testing Dictionary [1]")
{
    Dictionary<string, float> & dict = Dictionary<string, float>::gene;
}

*/
