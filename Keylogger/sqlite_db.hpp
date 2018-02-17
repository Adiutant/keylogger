#pragma once

#include <sqlite3.h>
#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>

class sqlite_db
{
public:
    using sqlite_row = std::unordered_map<std::string, std::string>;
    using sqlite_result = std::vector<sqlite_row>;

    sqlite_db() noexcept;

    sqlite_db(std::string_view filename) noexcept;

    sqlite_db(const sqlite_db&) = delete;

    sqlite_db(sqlite_db&&) = default;

    sqlite_db& operator=(const sqlite_db&) = delete;

    sqlite_db& operator=(sqlite_db&&) = default;

    ~sqlite_db() noexcept;

    void open(std::string_view filename) noexcept;

    sqlite_result execute_query(std::string_view query) noexcept;

    void run_query(std::string_view query) noexcept;

    void close() noexcept;

    bool is_opened() const noexcept;
private:
    sqlite3* db;

    bool opened;
};
