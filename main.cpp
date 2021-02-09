#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <fstream>
#include <map>
#include <sstream>
#include <locale>
#include <codecvt>

using namespace std;

map<int, string> first_consonants = {{0, "r"},{1, "R"},{2, "s"},{3, "e"},{4, "E"},{5, "F"},{6, "a"},{7, "q"},{8, "Q"},{9, "t"},{10, "T"},{11, "d"},{12, "w"},{13, "W"},{14, "c"},{15, "z"},{16, "x"},{17, "v"},{18, "g"},};
map<int, string> vowels = {{0, "k"},{1, "o"},{2, "i"},{3, "O"},{4, "j"},{5, "p"},{6, "u"},{7, "P"},{8, "h"},{9, "hk"},{10, "ho"},{11, "hl"},{12, "y"},{13, "n"},{14, "nl"},{15, "np"},{16, "nl"},{17, "b"},{18, "m"},{19, "ml"},{20, "l"},};
map<int, string> final_consonants = {{0, ""}, {1, "r"},{2, "R"},{3, "rt"},{4, "s"},{5, "sw"},{6, "sg"},{7, "e"},{8, "f"},{9, "fr"},{10, "fa"},{11, "fq"},{12, "ft"},{13, "fx"},{14, "fv"},{15, "fg"},{16, "a"},{17, "q"},{18, "qt"},{19, "t"},{20, "T"},{21, "d"},{22, "w"},{23, "c"},{24, "z"},{25, "x"},{26, "v"},{27, "g"},};

int main() {
    /*string file_name = "additional_consonants";
    ifstream in_file(file_name);
    ofstream out_file(file_name + "_edit");

    string p1;
    string p2;
    string line;
    while (in_file >> p1 >> p2) {
        line.append("{");
        line.append(p1);
        line.append(", \"");
        line.append(p2);
        line.append("\"},");
    }
    out_file << line << endl;*/

    _setmode(_fileno(stdout), _O_WTEXT);
    _setmode(_fileno(stdin), _O_WTEXT);

    ifstream param_file("first_consonants");

    int key;
    string value;

    while (param_file >> key >> value) {
        first_consonants[key] = value;
    }

    param_file.close();
    param_file = ifstream("vowels");

    while (param_file >> key >> value) {
        vowels[key] = value;
    }

    param_file.close();
    param_file = ifstream("additional_consonants");

    while (param_file >> key >> value) {
        final_consonants[key] = value;
    }

    wstring input_string;
    string output;

    // TODO: More useful output-input.
    // TODO: Handle standalone hanja.

    while (true) {
        getline(std::wcin, input_string);

        for (wchar_t& c : input_string) {
            int val = c;

            wcout << val << endl;
            val = val - 44032;
            wcout << val << endl;
            if (val < 0) {
                break;
            }

            int first = val / 588;
            val = val - first * 588;
            int vowel = val / 28;
            val = val - vowel * 28;

            wcout << first << endl;
            wcout << vowel << endl;
            wcout << val << endl;
            output.append(first_consonants[first] + vowels[vowel] + final_consonants[val]);

            wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            wstring output_string = converter.from_bytes(output);

            wcout << output_string << endl;
        }
    }
}
