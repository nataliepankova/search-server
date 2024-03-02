//Вставьте сюда своё решение из урока «Очередь запросов».
#pragma once
#include <iostream>
#include <vector>

// ========================================
template <typename Iterator>
class IteratorRange {
public:
    explicit IteratorRange(Iterator begin, Iterator end);
    Iterator begin() const;
    Iterator end() const;
    int size() const;

private:
    Iterator begin_;
    Iterator end_;
};

template <typename Iterator>
IteratorRange<Iterator>::IteratorRange(Iterator begin, Iterator end)
    :begin_(begin), end_(end)
    {}
template <typename Iterator>
Iterator IteratorRange<Iterator>::begin() const {
    return begin_;
}
template <typename Iterator>
Iterator IteratorRange<Iterator>::end() const {
    return end_;
}
template <typename Iterator>
int IteratorRange<Iterator>::size() const {
    return std::distance(begin_, end_);
}
// =========== Iterator range output==============
template <typename Iterator>
std::ostream& operator<<(std::ostream& os, IteratorRange<Iterator> range) {
    for (Iterator i = range.begin(); i != range.end(); advance(i, 1)) {
        os << *i;
    }

    return os;
}
// ============= Paginator ================

template <typename Iterator>
class Paginator {
public:
    explicit Paginator(Iterator begin, Iterator end, int page_size);

    auto begin() const;
    auto end() const;
    int size() const;

private:
    std::vector<IteratorRange<Iterator>> pages_;
};

template <typename Iterator>
Paginator<Iterator>::Paginator(Iterator begin, Iterator end, int page_size) {

        // сохраним последний итератор
        Iterator last_begin;
        for (Iterator i = begin; std::distance(i, end) > page_size; std::advance(i, page_size)) {
            IteratorRange<Iterator> page{i, i+page_size};
            pages_.push_back(page);
            last_begin = i + page_size;

        }
        IteratorRange<Iterator> last_page{last_begin, end};
        pages_.push_back(last_page);
}
template <typename Iterator>
auto Paginator<Iterator>::begin() const {
    return pages_.begin();
}
template <typename Iterator>
auto Paginator<Iterator>::end() const {
    return pages_.end();
}
template <typename Iterator>
int Paginator<Iterator>::size() const {
    return std::distance(pages_.begin(), pages_.end());
}

template <typename Container>
auto Paginate(const Container& c, int page_size) {
    return Paginator<decltype(begin(c))>(begin(c), end(c), page_size);
}
