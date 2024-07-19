#include <iostream>
#include <fstream>
#include "arr_string.h"
#include "utils.h"

int main(void)
{
	std::ifstream file("words.txt");
	arr::Array<string> words(1000);
	string word;
	int i{};
	while (!file.eof()){
		getline(file, word);
		words[i++] = std::move(word);
	}
	sort::mergesort(words);

	std::ofstream of("words_s.txt");
	for (string& s : words){
		of << s;
		of.put('\n');
	}

	file.close();
	of.close();
	return 0;
}