// table-submit.h

#ifndef TABLE_SUBMIT_H_
#define TABLE_SUBMIT_H_

#include "column.h"

#include <string>
#include <iostream>

/// TODO: Add the missing function definitions below

template <>
inline const Column<int>* Table::get_column_view(std::string name) const {
    const Column<int>* result = get_column<int>(num_int_columns_, int_columns_, name);
    return result;
}

template <>
inline const Column<std::string>* Table::get_column_view(std::string name) const {
    const Column<std::string>* result = get_column<std::string>(num_string_columns_, string_columns_, name);
    return result;
}

template <>
inline const Column<bool>* Table::get_column_view(std::string name) const {
    const Column<bool>* result = get_column<bool>(num_bool_columns_, bool_columns_, name);
    return result;
}

template <>
inline void Table::update_at(std::string name, int index, int value) {
    this->update_at<int> (index, value, num_int_columns_, int_columns_, name);
}

template <>
inline void Table::update_at(std::string name, int index, std::string value) {
    this->update_at<std::string> (index, value, num_string_columns_, string_columns_, name);
}

template <>
inline void Table::update_at(std::string name, int index, bool value) {
    update_at<bool> (index, value, num_bool_columns_, bool_columns_, name); 
}

template <typename T>
void Table::append_records(const Table& other, int& num_columns, Column<T>* columns) 
{
    for (int i=0; i<num_columns; i++)
    {
        for (int j=0; j<other.num_int_columns_; j++)
        {
            if (columns->get_name() == other.int_columns_[j].get_name())
            columns->append(*other.get_column_view<T>(other.int_columns_[j].get_name()));
        }
        for (int j=0; j<other.num_string_columns_; j++)
        {
            if (columns->get_name() == other.string_columns_[j].get_name())
            columns->append(*other.get_column_view<T>(other.string_columns_[j].get_name()));
        }
        for (int j=0; j<other.num_bool_columns_; j++)
        {
            if (columns->get_name() == other.bool_columns_[j].get_name())
            columns->append(*other.get_column_view<T>(other.bool_columns_[j].get_name()));
        }
        columns++;
    }
}
#endif  // TABLE_SUBMIT_H_
