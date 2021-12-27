#ifndef HISTOGRAM_HPP
#define HISTOGRAM_HPP

#include "Sequence.hpp"
#include "QuickSort.hpp"
#include "Person.hpp"
#include "HistogramException.hpp"

#include <sciplot/sciplot.hpp>
#include <type_traits>
//#include "vendor/magic_enum/magic_enum.hpp"

using namespace sciplot;

 enum Criteria
{
    numberOfPartitions_,
    partition_,
};

std::string stringGenerator(int lower, int higher)
{
    std::string res;

    res.push_back('[');

    std::string lowerChar = to_string(lower);
    std::string higherChar = to_string(higher);

    res.append(lowerChar);
    res.push_back('-');
    res.append(higherChar);
    res.push_back(']');

    // cout << res << endl;

    return res;
}

/*
template<typename T>
class SortedSequence
{
    Sequence<T> sortedSeq;

public:
    Sequence<T> get() const
    {
        return sortedSeq;
    }

    SortedSequence<T>()
    {
    }

    explicit SortedSequence<T> (Sequence<T> & seq)
    {
        sortedSeq = QuickSort(seq);
    }

    explicit SortedSequence<T> (SortedSequence<T> & seq)
    {
        sortedSeq = QuickSort(seq);
    }
};
*/

/*
template <typename T>
class Histogram
{
private:
    Sequence<Person> arr_;

    union S
    {
        Sequence<int> seqInt,
        Sequence<float> seqFloat,
        Sequence<double> seqDouble,
        Sequence<char> seqChar
    };

public:

    Histogram(const Sequence<Person> & arr, int range, T criteria)
    // if range equals 5, then we split the data with 5-size chunks
    {
        if (lower >= upper && upper < )
            throw HistogramException("bad borders");
        arr_ = arr;

        if (typeid(T)::name() == "int")
    }

    Sequence<Person> get() const {return arr_;}

};
*/


enum PlotBy
{
    age,
    height,
    weight,
    name
};

class Histogram
{
private:
    vector<Person> people_;

public:
    Histogram(vector<Person> & people)
        : people_(people)
    {
    }

    void plot(int criteria, Criteria crit, PlotBy plotBy)
    {
        size_t amount = people_.size();

        if (criteria <= 0)
            throw HistogramException("criteria should be positive");

        vector<string> arguments; // x - axis
        vector<int> values; // y - axis

        vector<int> toSort;

        size_t min = 500; // magic const
        size_t max = 0;

        switch (plotBy)
        {
            case PlotBy::age:
            {
                for (auto it : people_)
                {
                    if (it.getAge() > max)
                        max = it.getAge();

                    if (it.getAge() < min)
                        min = it.getAge();

                    toSort.push_back(it.getAge());
                }
                break;
            }
            case PlotBy::height:
            {
                for (auto it : people_)
                {
                    if (it.getHeight() > max)
                        max = it.getHeight();

                    if (it.getHeight() < min)
                        min = it.getHeight();

                    toSort.push_back(it.getHeight());
                }
                break;
            }
            case PlotBy::weight:
            {
                for (auto it : people_)
                {
                    if (it.getWeight() > max)
                        max = it.getWeight();

                    if (it.getWeight() < min)
                        min = it.getWeight();

                    toSort.push_back(it.getWeight());
                }
                break;
            }
            case PlotBy::name:
            {
                for (auto it : people_)
                {
                    if (it.getName().size() > max)
                        max = it.getName().size();

                    if (it.getName().size() < min)
                        min = it.getName().size();

                    toSort.push_back(it.getName().size());
                }
                break;
            }
            default:
                throw HistogramException("unsupported type of enum passed");
        }

        int partition;
        int numberOfPartitions;
        int range = max-min;

        vector<int> partitioned;

        if (crit == Criteria::numberOfPartitions_)
        {
            numberOfPartitions = criteria;
            partition = range/criteria+1;
        }
        else if (crit == Criteria::partition_)
        {
            partition = criteria;
            numberOfPartitions = range/criteria+1;
        }

        for (int i=0; i<numberOfPartitions; ++i)
        {
            partitioned.push_back(0);
            //cout << partitioned[i] << endl;
        }

        QuickSort<int> quickSort;
        toSort = quickSort.sort(toSort, 0, int(toSort.size())); // sort the vector


        //cout << "MIN: " << min << endl;
        //cout << "MAAAAX: " << max << endl;

        for (int i=min; i<max; ++i)
        {
            int leftBorder = i;
            int rightBorder = i+partition-1;

            string buff = stringGenerator(leftBorder, rightBorder);
            arguments.push_back(buff);

            for (int j=0; j<amount; ++j)
            {
                int position = floor((i-min)/partition);
                if (toSort[j] >= leftBorder && toSort[j] <= rightBorder)
                    ++partitioned[position];

            }
            i += partition-1;
            //cout << "-------------" << endl;
        }
        values = partitioned;

        Plot plot;
        plot.legend().atTopLeft();
        plot.ylabel("Quantity");

        plot.drawBoxes(arguments, values)
            .fillSolid()
            .fillColor("pink")
            .fillIntensity(0.5)
            .borderShow()
            .labelNone();

        plot.boxWidthRelative(0.75);
        plot.autoclean(false);
        plot.show();
        plot.save("example-boxes-ticklabels.pdf");
    }

    /*
    void plotByHeight()
    {

    }

    void plotByWeight()
    {

    }

    void plotByNameSize()
    {

    }*/


    /*
    plot(PlotBy plotBy, int criteria, Criteria crit)
    {
        vector<string> arguments; // x - axis
        vector<int> values; // y - axis

        int partition;
        int numberOfPartitions;

        bool isPartition = true; // if true, then it means that user passes the partition

        if (rangeOrPartitions.index() == 0)
            partition = get<double>(var);


        switch (plotBy)
        {
            case: PlotBy::age
            {
                break;
            }
            case: PlotBy::height
            {
                break;
            }

            case: PlotBy::weight
            {
                break;
            }

            case: PlotBy::name
            {
                break;
            }
        }

        Sequence<int>* partitioned = new Sequence<int>;

        if (crit == Criteria::numberOfPartitions_)
        {
            numberOfPartitions = criteria;
            partition = floor(data.size()/criteria);
        }
        else if (crit == Criteria::partition_)
        {
            partition = criteria;
            numberOfPartitions = floor(data.size()/criteria);
        }

        for (int i=0; i<numberOfPartitions; ++i)
        {
            partitioned->push_back(0);
            cout << (*partitioned)[i] << endl;
        }

        vector<int> toSort = data.to_vector();
        QuickSort<int> quickSort;
        toSort = quickSort.sort(toSort, 0, int(toSort.size()-1)); // sort the vector

        for (int i=0; i<numberOfPartitions; ++i)
        {
            int leftBorder = i*partition;
            int rightBorder = (i+1)*partition-1;

            string buff = stringGenerator(leftBorder, rightBorder);
            arguments.push_back(buff);

            for (int j=0; j<data.size(); ++j)
            {
                if (data[j] >= leftBorder && data[j] <= rightBorder)
                    ++(*partitioned)[i];

            }
        }
        values = partitioned->to_vector();

        Plot plot;
        plot.legend().atTopLeft();
        plot.ylabel("Quantity");

        plot.drawBoxes(arguments, values)
            .fillSolid()
            .fillColor("pink")
            .fillIntensity(0.5)
            .borderShow()
            .labelNone();

        plot.boxWidthRelative(0.75);
        plot.autoclean(false);
        plot.show();
        plot.save("example-boxes-ticklabels.pdf");
    }
    }*/

};


/*
class Histogram
{
    Sequence<int> dataInt_;
    Sequence<double> dataDouble_;

public:

/*
    Histogram(Sequence<int> & data, int range)
    // range is the number of elements in one partition
    {
        if (range <= 0)
            throw HistogramException("range should be positive");

        vector<int> toSort = data.to_vector();
        QuickSort<int> quickSort;
        toSort = quickSort.sort(toSort, 0, int(toSort.size()-1)); // sort the vector


        Sequence<int> sortedData = Sequence<int>::to_array(toSort); // cast sorted vector to sorted sequence
        Sequence<int> buff;
        Sequence<Sequence<int>> splitted;

        int element = 1; // equals i+1
        for (int i=0; i<sortedData.size(); ++i)
        {
            buff.push_back(sortedData[i]);

            if (element % range == 0)
            {
                splitted.push_back(buff);
                buff.erase();
            }
            ++element;
        }

        Plot arrPlot;

        arrPlot.xlabel("amount of elements");
        arrPlot.ylabel("time (microseconds)");

        // Set the legend to be on the bottom along the horizontal
        arrPlot.legend()
            .atOutsideBottom()
            .displayHorizontal()
            .displayExpandWidthBy(2);

        arrPlot.drawCurve(x, bArrDurations).label("BubbleSort [DynamicArr]");
        arrPlot.drawCurve(x, iArrDurations).label("InsertionSort [DynamicArr]");
        arrPlot.drawCurve(x, mArrDurations).label("MergeSort [DynamicArr]");
        arrPlot.drawCurve(x, qArrDurations).label("QuickSort [DynamicArr]");
        arrPlot.drawCurve(x, sArrDurations).label("SelectionSort [DynamicArr]");
        arrPlot.drawCurve(x, cArrDurations).label("CountingSort [DynamicArr]");
        arrPlot.drawCurve(x, shArrDurations).label("ShellSort [DynamicArr]");
        arrPlot.drawCurve(x, hArrDurations).label("HeapSort [DynamicArr]");
    }
    */
/*
    Histogram(Sequence<int> & data, int criteria, Criteria crit)
    {
        if (criteria <= 0)
            throw HistogramException("criteria should be positive");

        vector<string> arguments; // x - axis
        vector<int> values; // y - axis

        int partition;
        int numberOfPartitions;

        Sequence<int>* partitioned = new Sequence<int>;

        if (crit == Criteria::numberOfPartitions_)
        {
            numberOfPartitions = criteria;
            partition = floor(data.size()/criteria);
        }
        else if (crit == Criteria::partition_)
        {
            partition = criteria;
            numberOfPartitions = floor(data.size()/criteria);
        }

        for (int i=0; i<numberOfPartitions; ++i)
        {
            partitioned->push_back(0);
            cout << (*partitioned)[i] << endl;
        }

        vector<int> toSort = data.to_vector();
        QuickSort<int> quickSort;
        toSort = quickSort.sort(toSort, 0, int(toSort.size()-1)); // sort the vector

        for (int i=0; i<numberOfPartitions; ++i)
        {
            int leftBorder = i*partition;
            int rightBorder = (i+1)*partition-1;

            string buff = stringGenerator(leftBorder, rightBorder);
            arguments.push_back(buff);

            for (int j=0; j<data.size(); ++j)
            {
                if (data[j] >= leftBorder && data[j] <= rightBorder)
                    ++(*partitioned)[i];

            }
        }
        values = partitioned->to_vector();

        Plot plot;
        plot.legend().atTopLeft();
        plot.ylabel("Quantity");

        plot.drawBoxes(arguments, values)
            .fillSolid()
            .fillColor("pink")
            .fillIntensity(0.5)
            .borderShow()
            .labelNone();

        plot.boxWidthRelative(0.75);
        plot.autoclean(false);
        plot.show();
        plot.save("example-boxes-ticklabels.pdf");
    }
};
*/

#endif // HISTOGRAM_HPP
