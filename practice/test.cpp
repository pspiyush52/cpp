#include "string.h"

int main(int argc, char* argv[])
{
    String paragraph{};
    std::ifstream file("sample.txt");
    file >> paragraph;
    print(paragraph.collapse());
    file.close();
    return 0;
}
