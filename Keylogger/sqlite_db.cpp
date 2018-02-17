#include "sqlite_db.hpp"

sqlite_db::sqlite_db() noexcept : opened(false), db(nullptr) { }

sqlite_db::sqlite_db(std::string_view filename) noexcept : opened(true), db(nullptr)
{
    open(filename);
}

sqlite_db::~sqlite_db() noexcept
{
    if (db)
    {
        close();
    }
}

void sqlite_db::open(std::string_view filename) noexcept
{
    if (sqlite3_open(filename.data(), &db) == SQLITE_OK)
    {
        opened = true;
    }
}

sqlite_db::sqlite_result sqlite_db::execute_query(std::string_view query) noexcept
{
    sqlite_result result;

    sqlite3_exec(db, query.data(), [](void* result_ptr, int count, char** rows_buff, char** columns_buff)
    {
        auto result = static_cast<sqlite_result*>(result_ptr);

        sqlite_row row;

        for (int i = 0; i < count; ++i)
        {
            row.insert({ columns_buff[i], rows_buff[i] ? rows_buff[i] : "NULL" });
        }

        result->push_back(std::move(row));

        return SQLITE_OK;
    }, &result, nullptr);

    return std::move(result);
}


void sqlite_db::run_query(std::string_view query) noexcept
{
    sqlite3_exec(db, query.data(), nullptr, nullptr, nullptr);
}

void sqlite_db::close() noexcept
{
    if (sqlite3_close(db) == SQLITE_OK)
    {
        db = nullptr;
        opened = false;
    }
}

bool sqlite_db::is_opened() const noexcept
{
    return opened;
}
