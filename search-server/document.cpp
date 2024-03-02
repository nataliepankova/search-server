//Вставьте сюда своё решение из урока «Очередь запросов» темы «Стек, очередь, дек».
#include "document.h"
#include <iostream>
#include <string>

using namespace std;

Document::Document() = default;

Document::Document(int id, double relevance, int rating)
    : id(id)
    , relevance(relevance)
    , rating(rating) {
}

void PrintDocument(const Document& document) {
    cout << "{ "s
         << "document_id = "s << document.id << ", "s
         << "relevance = "s << document.relevance << ", "s
         << "rating = "s << document.rating << " }"s << std::endl;
}

std::ostream& operator<<(std::ostream& os, Document doc) {
    os << "{ "s << "document_id = "s << doc.id << ", relevance = "s << doc.relevance << ", rating = "s << doc.rating << " }"s;
    return os;
}
