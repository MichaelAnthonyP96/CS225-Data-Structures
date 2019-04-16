/**
 * @file logfile_parser.cpp
 * Implementation of the LogfileParser class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */

#include "logfile_parser.h"
#include <iostream>
#include <iomanip>

using std::string;
using std::vector;
using std::ifstream;
using std::istringstream;

/**
 * Constructs a LogLine from a string (actual physical line in the
 * logfile).
 *
 * @param line The line in the file to extract info from.
 */
LogfileParser::LogLine::LogLine(const string& line)
{
    istringstream iss(line);
    iss >> customer;
    customer = customer.substr(1, customer.length() - 3);
    iss >> url;
    string dte = "";
    string dline;
    do {
        iss >> dline;
        dte += dline;
        dte += " ";
    } while (iss);
		
    dte = dte.substr(0, dte.length() - 6); 
    std::tm tm = {};
    std::stringstream ss(dte);
    ss >> std::get_time(&tm, "%a %b %d %H:%M:%S %Y");
    date = time(NULL);
    // force correct DST
    tm.tm_isdst = 1;
    date = mktime(&tm);
}

/**
 * Constructs a new LogfileParser from the name of a log file.
 *
 * @param fname The name of the log file to open.
 */
LogfileParser::LogfileParser(const string& fname) : whenVisitedTable(256)
{
    SCHashTable<string, bool> pageVisitedTable(256);
    ifstream infile(fname.c_str());
    string line;
    while (infile.good()) {
        getline(infile, line);

        // if the line length is 0, move on to the next loop iteration
        if (line.length() == 0)
            continue;

        // otherwise parse the line and update the hash tables and vector
        LogLine ll(line);
        /**
         * @todo Finish implementing this function.
         *
         * Given the LogLine above, you should be able to update the member
         * variable hash table and any other hash tables necessary to solve
         * this problem. This should also build the uniqueURLs member
         * vector as well.
         */
        //extract the new Key from logline, not sure why you ignore the last two characters
        //but the given code does it so I followed what they did
        string newKey = ll.customer.substr(1,ll.customer.size() - 3);
        string uniqueURL = ll.url;
        newKey.append(uniqueURL); 
        //if the key exists and was visisted in the past then update its last visited date
        if(whenVisitedTable.keyExists(newKey)){
            if(whenVisitedTable[newKey] < ll.date) whenVisitedTable[newKey] = ll.date;
        }
        //if it hasn't been visited then insert it into the visisted Table
        else{
            whenVisitedTable.insert(newKey, ll.date);
        }
        //if the URL does not exist in the page Visisted table then insert it into vector
        //and marke it as true in the page Visited table
        if(!pageVisitedTable.keyExists(uniqueURL)) uniqueURLs.push_back(uniqueURL);
        pageVisitedTable[uniqueURL] = true;

    }
    infile.close();
}

/**
 * Determines if a given customer has ever visited the given url.
 *
 * @param customer The customer name.
 * @param url The url.
 * @return A boolean value indicating whether the customer visited the url.
 */
bool LogfileParser::hasVisited(const string& customer, const string& url) const
{

    /**
     * @todo Implement this function.
     */
    //extracts the key minus the last two characters, given code does it but Im not sure why
    string newKey = customer.substr(1,customer.size() - 3);
    //copies the const URL to a non const form so that we can use it
    string uniqueURL = url;
    //appends to the key the URL
    newKey.append(uniqueURL);
    //returns whether or not the key exists in the visisted table
    return whenVisitedTable.keyExists(newKey);
}

/**
 * Determines *when* a customer last visited a given url. If the customer
 * has not visited the given url, the output of this function should be the
 * default time_t.
 *
 * @param customer The customer name.
 * @param url The url.
 * @return A time_t representing when the customer last visited the given
 *  url.
 */
time_t LogfileParser::dateVisited(const string& customer,
                                  const string& url) const
{

    /**
     * @todo Implement this function.
     */
    //extracts the key 
    string newKey = customer.substr(1,customer.size() - 3);
    //copies the const URL to a non const form so that we can use it
    string uniqueURL = url;
    //appends to the key the URL
    newKey.append(uniqueURL);
    //returns when the has been visited, which returns the default time if 
    //it hasnt been visited before
    return whenVisitedTable.find(newKey);
}

/**
 * Gets all of the unique urls that have been visited.
 *
 * @return A vector of urls that were visited in the logfile. Note
 *  that **there should be no duplicates in this vector**.
 */
vector<string> LogfileParser::uniquePages() const
{
    return uniqueURLs;
}
