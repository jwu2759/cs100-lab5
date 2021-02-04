#ifndef __SPREADSHEET_HPP__
#define __SPREADSHEET_HPP__

#include <string>
#include <initializer_list>
#include <vector>
#include <iosfwd>

class Select;

class Spreadsheet
{
    std::vector<std::string> column_names;
    std::vector<std::vector<std::string> > data;
    std::vector<bool> bools;
    Select* select = nullptr;

public:
    ~Spreadsheet();

    const std::string& cell_data(int row, int column) const
    {
        return data.at(row).at(column);
    }

    std::string& cell_data(int row, int column)
    {
        return data.at(row).at(column);
    }

    const bool bool_data(int row) const
    {
	return bools.at(row);
    }

    void set_bool(int row, bool new_bool)
    {
	bools.at(row) == new_bool;
    }

    void set_selection(Select* new_select);

    // TODO: Implement print_selection.
    void print_selection(std::ostream& out) const;

    void clear();
    void set_column_names(const std::vector<std::string>& names);
    void add_row(const std::vector<std::string>& row_data);
    int get_column_by_name(const std::string& name) const;
};

#endif //__SPREADSHEET_HPP__
