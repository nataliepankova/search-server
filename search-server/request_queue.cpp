//Вставьте сюда своё решение из урока «Очередь запросов» темы «Стек, очередь, дек».
#include "request_queue.h"

RequestQueue::RequestQueue(SearchServer& search_server) :
    search_server_(search_server)
    {
        // напишите реализацию
    }
    // сделаем "обёртки" для всех методов поиска, чтобы сохранять результаты для нашей статистики
std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query, DocumentStatus status) {
    // напишите реализацию
    return AddFindRequest(raw_query, [status](int, DocumentStatus doc_status, int) {
        return doc_status == status;
    });
}
std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query) {
    // напишите реализацию
    return AddFindRequest(raw_query, DocumentStatus::ACTUAL);
}
int RequestQueue::GetNoResultRequests() const {
    // напишите реализацию
    return no_result_requests_count_;
}


void RequestQueue::UpdateRequests(int results_number) {
    ++time_count_;
    while (!requests_.empty() && min_in_day_ <= time_count_ - requests_.front().timestamp) {
            if (0 == requests_.front().results_number) {
                --no_result_requests_count_;
            }
            requests_.pop_front();
        }
    requests_.push_back({time_count_, results_number});
    if (results_number == 0) {
        ++no_result_requests_count_;
    }
}
