//Вставьте сюда своё решение из урока «Очередь запросов» темы «Стек, очередь, дек».
#pragma once
#include <cstdint>
#include <deque>
#include <vector>

#include "document.h"
#include "search_server.h"

class RequestQueue {
public:
    explicit RequestQueue(SearchServer &search_server);
    // сделаем "обёртки" для всех методов поиска, чтобы сохранять результаты для нашей статистики
    template <typename DocumentPredicate>
    std::vector<Document> AddFindRequest(const std::string &raw_query, DocumentPredicate document_predicate);
    std::vector<Document> AddFindRequest(const std::string &raw_query, DocumentStatus status);
    std::vector<Document> AddFindRequest(const std::string &raw_query);
    int GetNoResultRequests() const;

private:
    struct QueryResult {
        uint64_t timestamp;
        int results_number;
    };
    std::deque<QueryResult> requests_;
    const static int min_in_day_ = 1440;
    uint64_t time_count_ = 0;
    int no_result_requests_count_ = 0;
    // возможно, здесь вам понадобится что-то ещё
    SearchServer& search_server_;

    void UpdateRequests(int results_number);
};

template <typename DocumentPredicate>
    std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate) {
        // напишите реализацию
        std::vector<Document> result = search_server_.FindTopDocuments(raw_query, document_predicate);
        RequestQueue::UpdateRequests(result.size());
        return result;

}
