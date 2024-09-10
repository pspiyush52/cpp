#include "string.h"
#include "ordered_map.h"

int main(int argc, char* argv[])
{
    void printDefinition(String& word, const OrderedSMap<String, deque<String>>& dict);
    if (argc == 2) {
        String query{argv[1]};
        OrderedSMap<String, deque<String>> dictionary;
        
        std::ifstream file("words.txt");
        String defLine{4096};
        
        if (query.similar("-u")) {
            std::ofstream out("word.txt");
            
            while (defLine.getline(file)) {
                auto pos = defLine.search(' ');
                String word = defLine.slice(pos).to_lower();
                for (char ch : word)
                    out.put(ch);
                out.put('\n');
            }
            
            out.close();
            print("word.txt succesfully updated");
        }
        else {
            std::cout << "Loading the words into the dictionary... ";
            
            while (defLine.getline(file)) {
                auto pos = defLine.search(' ');
                String word = defLine.slice(pos).to_lower();
                deque<String> definitions = defLine.split(pos + 1, '|');
                dictionary.insert(static_cast<String&&>(word), static_cast<deque<String>&&>(definitions));
            }
            
            print("Success!");
            std::cout << "Dictionary with " << dictionary.size()
                << " words succesfully loaded into an AVL tree of height "
                << dictionary.getHeight()
                << '\n';
            
            print("Now searching for your word...\n");
            printDefinition(query.strip().to_lower(), dictionary);
        }
        
        file.close();
        return EXIT_SUCCESS;
    }
    else {
        print("Usage:\n   ", argv[0], "word");
        return EXIT_FAILURE;
    }
}

void printDefinition(String& word, const OrderedSMap<String, deque<String>>& dict) {
    deque<String>* defs = dict.search(word);
    if (defs == nullptr) {
        std::cout << "Sorry :(\n\t" << "The word \"" << word << "\" does not exist in the dictionary\n";
    }
    else {
        std::cout << word.capitalize() << ":\n";
        for (auto& definition : *defs)
            print("    ", definition);
    }
}
