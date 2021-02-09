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
map<int, string> unassembled = {{1, "r"},{2, "R"},{3, "rt"},{4, "s"},{5, "sw"},{6, "sg"},{7, "e"},{8, "E"},{9, "f"},{10, "fr"},{11, "fa"},{12, "fq"},{13, "ft"},{14, "fx"},{15, "fv"},{16, "fg"},{17, "a"},{18, "q"},{19, "Q"},{20, "qt"},{21, "t"},{22, "T"},{23, "d"},{24, "w"},{25, "W"},{26, "c"},{27, "z"},{28, "x"},{29, "v"},{30, "g"},{31, "k"},{32, "o"},{33, "i"},{34, "O"},{35, "j"},{36, "p"},{37, "u"},{38, "P"},{39, "h"},{40, "hk"},{41, "ho"},{42, "hl"},{43, "y"},{44, "n"},{45, "nj"},{46, "np"},{47, "nl"},{48, "b"},{49, "m"},{50, "ml"},{51, "l"},};

string assembled_hanja(wchar_t hanja) {
    int val = hanja - 44032;

    int first = val / 588;
    val = val - first * 588;
    int vowel = val / 28;
    int final = val - vowel * 28;

    string assembled;

    assembled.append(first_consonants[first]);
    assembled.append(vowels[vowel]);
    assembled.append(final_consonants[final]);

    return assembled;
}

string unassembled_hanja(wchar_t hanja) {
    return unassembled[(int) hanja - 0x3130];
}

int main() {
    string file_name = "unassembled";
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
    out_file << line << endl;

    _setmode(_fileno(stdout), _O_WTEXT);
    _setmode(_fileno(stdin), _O_WTEXT);

    wstring input_string;

    wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    while (true) {
        wstring output;

        getline(std::wcin, input_string);

        for (wchar_t c : input_string) {
            int val = c;

            if (0x3131 < val && val < 0x318E) {
                wcout << converter.from_bytes(unassembled_hanja(c));
            } else if (0xAC00 < val && val < 0xD7A3) {
                wcout << converter.from_bytes(assembled_hanja(c));
            } else {
                wcout << c;
            }
        }

        wcout << endl;

    }



}
