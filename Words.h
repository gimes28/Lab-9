#pragma once
#ifndef WORDS_h
#define WORDS_h
#include<iostream>
using namespace std;

class Words {
private:
	string word;
	int freq;
public:
	Words();
	Words(string str);
	Words(string str, int fre);
	void setWord(string in);
	string getWord();
	void setFreq(int in);
	int getFreq();
	void DisplayWord();
	bool operator > (const Words& obj);
	bool operator < (const Words& obj);
	bool operator == (const Words& obj);
};

Words::Words() {
	word = "";
	freq = 0;
}

Words::Words(string str) {
	word = str;
}

Words::Words(string str, int fre) {
	word = str;
	freq = fre;
}

void Words::setWord(string in) {
	word = in;
}

string Words::getWord() {
	return word;
}

void Words::setFreq(int in) {
	freq = in;
}

int Words::getFreq() {
	return freq;
}

void Words::DisplayWord() {
	cout << word << ": " << freq << " times" << endl;
}

bool Words::operator > (const Words& obj) {
	if (this->word > obj.word) {
		return true;
	}
	return false;
}

bool Words::operator < (const Words& obj) {
	if (this->word < obj.word) {
		return true;
	}
	return false;
}

bool Words::operator == (const Words& obj) {
	if (this->word == obj.word) {
		return true;
	}
	return false;
}


#endif
