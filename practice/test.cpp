#include "string.h"
#include "plist.h"
#include "tuples.h"

int main(int argc, char* argv[])
{
    if (argc == 2) {
        PList<Pair<String, deque<String>>> words;
        String defLine{};
        std::ifstream file("words.txt");

        for (int i{}; defLine.getline(file); ++i) {
            auto pos = defLine.search(' ');
            String word = defLine.slice(pos).to_lower();
            deque<String> definitions = defLine.split(pos + 1, '|');
            words.emplace();
            words[i].emplaceFirst(static_cast<String&&>(word));
            words[i].emplaceSecond(static_cast<deque<String>&&>(definitions));
        }
        String word{argv[1]};
        word.strip().to_lower();
        for (auto& def : words) {
            if (def.getFirst().similar(word)) {
                for (auto& definition : def.getSecond())
                    print("   ", definition);
            }
        }

        file.close();
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
