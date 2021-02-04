#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include <cstring>

class Select
{
public:
    virtual ~Select() = default;

    // Return true if the specified row should be selected.
    virtual bool select(const Spreadsheet* sheet, int row) const = 0;
};

// A common type of criterion for selection is to perform a comparison based on
// the contents of one column.  This class contains contains the logic needed
// for dealing with columns. Note that this class is also an abstract base
// class, derived from Select.  It introduces a new select function (taking just
// a string) and implements the original interface in terms of this.  Derived
// classes need only implement the new select function.  You may choose to
// derive from Select or Select_Column at your convenience.
class Select_Column: public Select
{
 protected:
    int column;
 public:
    Select_Column(const Spreadsheet* sheet, const std::string& name)
    {
        column = sheet->get_column_by_name(name);
    }

    virtual bool select(const Spreadsheet* sheet, int row) const
    {
        return select(sheet->cell_data(row, column));
    }
 
    // Derived classes can instead implement this simpler interface.
     virtual bool select(const std::string& s) const = 0;
};


class Select_Contains: public Select{
	private:
		int column;
		std::string query;
	public:
		Select_Contains(const Spreadsheet* sheet, const std::string& name, const std::string& query){
			column = sheet->get_column_by_name(name);		
			this->query = query;
		}
		virtual bool select(const Spreadsheet* sheet, int row) const{
			return (sheet->cell_data(row, column).find(query) != std::string::npos)? true : false;
		}
};


class Select_And : public Select{
	private:
		Select* s1 = nullptr; 
		Select* s2 = nullptr;
	public:
	Select_And(Select* select1, Select* select2){
		s1 = select1;
		s2 = select2;
	}
	~Select_And(){
		delete s1;
		delete s2;
	}
	virtual bool select(const Spreadsheet* sheet, int row) const
	{
		return s1->select(sheet,row) && s2->select(sheet,row);
	}
};

class Select_Or : public Select{
	private:
		Select* s1 = nullptr;
		Select* s2 = nullptr;
	public:
	Select_Or(Select* select1, Select* select2){
		s1 = select1;
		s2 = select2;
	}
	virtual bool select(const Spreadsheet* sheet, int row)const{
		return s1->select(sheet, row) || s2->select(sheet, row);
	}
};


class Select_Not : public Select{
	private:
		Select* s1 = nullptr;
	public:
	Select_Not(Select* s){
		s1 = s;
	}
	~Select_Not(){
		delete s1;
	}
	virtual bool select(const Spreadsheet* sheet, int row) const
	{
		return !(s1->select(sheet,row));
	}
};

#endif //__SELECT_HPP__
