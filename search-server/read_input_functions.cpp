//Вставьте сюда своё решение из урока «Очередь запросов» темы «Стек, очередь, дек».
#include "read_input_functions.h"
#include <iostream>

using namespace std;

string ReadLine() {
    string s;
    getline(cin, s);
    return s;
}

int ReadLineWithNumber() {
    int result;
    cin >> result;
    ReadLine();
    return result;
}
