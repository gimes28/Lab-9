#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Words.h"
#include "BinaryTree.h"
#include "Exception.h"
using namespace std;

struct bookInfo {
    string Title;
    string authorName;
    int wordCount = 0;
    int lineCount = 0;
    double letFreq = 0;
};

int main() {
    ifstream inputFile; //File of book to be read
    ofstream outputFile; //File for output of book information

    //BinaryTree<Words> freqTree; //Binary Tree to hold the words and their frequencies

    string fileName; // Name of file given by user
    char answer;
    bool freq = true;
    bool continuing = true;
    int counter = 0;
    string word;
    string lines;

    bookInfo book;


    while (continuing) {    // True until the user wants to quit inputting books

        BinaryTree<Words> freqTree; //Binary Tree to hold the words and their frequencies

        cout << "Enter the name of the file: ";
        cin >> fileName;
        cout << endl;

        inputFile.open(fileName, ios::in);

        while (inputFile.fail()) {  // Tests if file could be opened
            cout << "File could not be open" << endl;
            cout << "Enter the name of the file: ";
            cin >> fileName;
            inputFile.open(fileName, ios::in);
        }

        cout << "Would you like to see the letter frequency?" << endl;
        cout << "Type 'Y' for Yes or 'N' for No: ";
        cin >> answer;
        cout << endl;

        if (answer == 'Y') {    // Outputs frequency
            freq = true;
        }
        else if (answer == 'N') {   // Doesn't output frequency
            freq = false;
        }

        if (outputFile.fail() || counter > 0) { // If the file is found or is adding another book
            outputFile.open("CardCatalog.txt", ios::out | ios::app);
        }
        else {  // If the file is not found or needs created
            outputFile.open("CardCatalog.txt", ios::out);
        }

        getline(inputFile, book.Title);
        outputFile << "Title: " << book.Title << endl;
        getline(inputFile, book.authorName);
        int pos = book.authorName.find(' ');
        outputFile << "Author: " << book.authorName << endl;
        outputFile << "Author First Name: " << book.authorName.substr(0, pos) << endl;
        outputFile << "Author Last Name: " << book.authorName.substr(pos + 1, string::npos) << endl;

        char alphaList[] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' }; // Array of alphabet letters
        double statsList[26] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };    // Array of count for each letter
        int arrSize = sizeof(alphaList) / sizeof(alphaList[0]); // size of array
        int totalCharacters = 0;



        ifstream file(fileName);
        bool foundContents = false;
        while (inputFile >> word) {     // Finds number of words
            //--------------------- Adds words to the tree or increases the count if they already exist
            if (foundContents == false) {
                if (word == "Contents:") {  // Doesn't starting count till 'contents:' is found
                    foundContents = true;
                }
            }
            else {		// Finds word count, total number of characters, and each letter count
                string temp;
                for (int i = 0; i < word.length(); i++) {
                    for (int j = 0; j < arrSize; ++j) {
                        if (tolower(word.at(i)) == alphaList[j]) {
                            temp += tolower(word.at(i));
                        }
                    }
                }
                Words* thisWord = new Words(temp); // creates a word object with the read word as the string for comparison, default constructor initializes the count to 0
                if (freqTree.head == nullptr) {
                    freqTree.Insert(thisWord);
                    thisWord->setFreq(1);
                }
                if (freqTree.Find(thisWord, freqTree.head) == nullptr) {// if null call insert
                    thisWord->setFreq(1); //set freq count to 1 since the word has appeared for the 1st time
                    freqTree.Insert(thisWord); //insert the Words object into the tree
                }
                else {
                    freqTree.Find(thisWord, freqTree.head)->setFreq(freqTree.Find(thisWord, freqTree.head)->getFreq() + 1); // finds word in the tree and increments the count
                }
                thisWord = nullptr;
                //---------------------

                if (foundContents == false) {
                    if (word == "Contents:") {  // Doesn't starting count till 'contents:' is found
                        foundContents = true;
                    }
                }
                else {		// Finds word count, total number of characters, and each letter count
                    book.wordCount++;
                    book.lineCount++;
                    for (int i = 0; i < word.length(); i++) {
                        for (int j = 0; j < arrSize; ++j) {
                            if (tolower(word.at(i)) == alphaList[j]) {
                                totalCharacters++;
                                statsList[j]++;
                            }
                        }
                    }
                }
            }
        }
        outputFile << "Number of words: " << book.wordCount << endl;
        outputFile << "Number of lines: " << book.lineCount << endl;
        if (freq) { // If user wants to see the frequency of words
            for (int i = 0; i < arrSize; i++) {
                outputFile << alphaList[i] << ": " << setprecision(4) << static_cast<double>(statsList[i] / totalCharacters) << endl;
            }
        }
        cout << "Check CardCatalog.txt File!" << endl;

        outputFile << endl;
        //--------------------------- Searching for words
        char checkWords = 'Y';
        while (checkWords) {
            cout << "\n -- Search for a Word in the Text -- " << endl;
            string wordSearch;

            cout << "Enter a word to search the text for: ";
            cin >> wordSearch;
            Words* compWord = new Words(wordSearch);
            //node* thisNode = freqTree.Find(compWord, freqTree.head)

            if (freqTree.Find(compWord, freqTree.head) != nullptr) {
                cout << "Word appears in the text " << freqTree.Find(compWord, freqTree.head)->getFreq() << " times. " << endl;
            }
            else {
                cout << "This word does not appear in the text." << endl;
            }
            cout << "\nDo you want to check another word?" << endl;
            cout << "Type 'Y' for Yes or 'N' for No: ";
            cin >> checkWords;

            if (checkWords == 'Y') { // If user wants to keep checking words
                checkWords = true;
            }
            else if (checkWords == 'N') {    // If user wants to not stop checking words
                checkWords = false;
            }
        }
        //--------------------------- Searching for words

        char displayList;
        cout << "\nDo you want to display the list in ascending or descending order?" << endl;
        cout << "Type 'A' for Ascending or 'D' for Descending: ";
        cin >> displayList;
        cout << endl;

        if (displayList == 'A') { // If user wants to output the list in ascending order 
            freqTree.GetAllAscending(freqTree.head);
        }
        else if (displayList == 'D') {    // If user wants to output the list in ascending order
            freqTree.GetAllDescending(freqTree.head);
        }

        char keepGoing;

        cout << "\nDo you want to enter a new file?" << endl;
        cout << "Type 'Y' for Yes or 'N' for No: ";
        cin >> keepGoing;

        if (keepGoing == 'Y') { // If user wants to continue inputting books
            counter++;
            continuing = true;
        }
        else if (keepGoing == 'N') {    // If user wants to continue inputting books
            continuing = false;
        }
        freqTree.EmptyTree(freqTree.head);  // clkear tree for next book
        outputFile.close();
        inputFile.close();
    }
}