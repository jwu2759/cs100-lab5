#ifndef __SELECT_TEST_HPP__
#define __SELECT_TEST_HPP__

#include "gtest/gtest.h"
#include "spreadsheet.hpp"
#include "select.hpp"

TEST(SelectContains, SelectContainsStandard){
    Spreadsheet sheet;
    std::stringstream sstr;
    sheet.set_column_names({"First","Last","Age","Major"});
    sheet.add_row({"Amanda","Andrews","22","business"});
    sheet.add_row({"Brian","Becker","21","computer science"});
    sheet.add_row({"Carol","Conners","21","computer science"});
    sheet.add_row({"Joe","Jackson","21","mathematics"});
    sheet.add_row({"Sarah","Summers","21","computer science"});
    sheet.add_row({"Diane","Dole","20","computer engineering"});
    sheet.add_row({"David","Dole","22","electrical engineering"});
    sheet.add_row({"Dominick","Dole","22","communications"});
    sheet.add_row({"George","Genius","9","astrophysics"});
    sheet.set_selection(new Select_Contains(&sheet, "First", "Joe"));
    
    sheet.print_selection(sstr);
    ASSERT_EQ("Joe Jackson 21 mathematics \n",sstr.str());
}

TEST(SelectContains, SelectContainsNull){
    Spreadsheet sheet;
    std::stringstream sstr;
    sheet.set_column_names({"First","Last","Age","Major"});
    sheet.add_row({"Amanda","Andrews","22","business"});
    sheet.add_row({"Brian","Becker","21","computer science"});
    sheet.add_row({"Carol","Conners","21","computer science"});
    sheet.add_row({"Joe","Jackson","21","mathematics"});
    sheet.add_row({"Sarah","Summers","21","computer science"});
    sheet.add_row({"Diane","Dole","20","computer engineering"});
    sheet.add_row({"David","Dole","22","electrical engineering"});
    sheet.add_row({"Dominick","Dole","22","communications"});
    sheet.add_row({"George","Genius","9","astrophysics"});

    sheet.set_selection(new Select_Contains(&sheet, "First", "Jack"));
    sheet.print_selection(sstr);
    ASSERT_EQ("Amanda Andrews 22 business \nBrian Becker 21 computer science \nCarol Conners 21 computer science \nJoe Jackson 21 mathematics \nSarah Summers 21 computer science \nDiane Dole 22 electrical engineering \nDavid Dole 22 electrical engineering \nDominick Dole 22 communications \nGeorge Genius 9 astrophysics \n", sstr.str());
}

TEST(SelectContains, SelectContainsMultiple){
    Spreadsheet sheet;
    std::stringstream sstr;
    sheet.set_column_names({"First","Last","Age","Major"});
    sheet.add_row({"Amanda","Andrews","22","business"});
    sheet.add_row({"Brian","Becker","21","computer science"});
    sheet.add_row({"Carol","Conners","21","computer science"});
    sheet.add_row({"Joe","Jackson","21","mathematics"});
    sheet.add_row({"Sarah","Summers","21","computer science"});
    sheet.add_row({"Diane","Dole","20","computer engineering"});
    sheet.add_row({"David","Dole","22","electrical engineering"});
    sheet.add_row({"Dominick","Dole","22","communications"});
    sheet.add_row({"George","Genius","9","astrophysics"});

    sheet.set_selection(new Select_And(
		new Select_And(
			new Select_Contains(&sheet, "Age", "22"),
			new Select_Contains(&sheet, "Last", "Becker")),
		new Select_Contains(&sheet, "First", "George")));

    sheet.print_selection(sstr);
    ASSERT_EQ("Amanda Andrews 22 business \nBrian Becker 21 computer science \nDavid Dole 22 electrical engineering \nDominick Dole 22 communications \nGeorge Genius 9 astrophysics \n", sstr.str());
}

TEST(SelectAnd, SelectAndStandard){	
    Spreadsheet sheet;
    std::stringstream sstr;
    sheet.set_column_names({"First","Last","Age","Major"});
    sheet.add_row({"Amanda","Andrews","22","business"});
    sheet.add_row({"Brian","Becker","21","computer science"});
    sheet.add_row({"Carol","Conners","21","computer science"});
    sheet.add_row({"Joe","Jackson","21","mathematics"});
    sheet.add_row({"Sarah","Summers","21","computer science"});
    sheet.add_row({"Diane","Dole","20","computer engineering"});
    sheet.add_row({"David","Dole","22","electrical engineering"});
    sheet.add_row({"Dominick","Dole","22","communications"});
    sheet.add_row({"George","Genius","9","astrophysics"});
    sheet.set_selection(new Select_And(
		new Select_Contains(&sheet, "Major", "engineering"),
		new Select_Contains(&sheet, "Last", "Dole")));
	sheet.print_selection(sstr);
	ASSERT_EQ("Diane Dole 20 computer engineering \nDavid Dole 22 electrical engineering \n", sstr.str());
}

TEST(SelectNot, SelectNotStandard){
    Spreadsheet sheet;
    std::stringstream sstr;
    sheet.set_column_names({"First","Last","Age","Major"});
    sheet.add_row({"Amanda","Andrews","22","business"});
    sheet.add_row({"Brian","Becker","21","computer science"});
    sheet.add_row({"Carol","Conners","21","computer science"});
    sheet.add_row({"Joe","Jackson","21","mathematics"});
    sheet.add_row({"Sarah","Summers","21","computer science"});
    sheet.add_row({"Diane","Dole","20","computer engineering"});
    sheet.add_row({"David","Dole","22","electrical engineering"});
    sheet.add_row({"Dominick","Dole","22","communications"});
    sheet.add_row({"George","Genius","9","astrophysics"});
    
    sheet.set_selection(
	new Select_And(
		new Select_Not(
			new Select_Contains(&sheet, "Major", "computer science")), 
			new Select_Contains(&sheet, "Age", "21")));
    sheet.print_selection(sstr);
    ASSERT_EQ("Joe Jackson 21 mathematics \n", sstr.str());
}

TEST(SelectOr, SelectOrStandard){
    Spreadsheet sheet;
    std::stringstream sstr;
    sheet.set_column_names({"First","Last","Age","Major"});
    sheet.add_row({"Amanda","Andrews","22","business"});
    sheet.add_row({"Brian","Becker","21","computer science"});
    sheet.add_row({"Carol","Conners","21","computer science"});
    sheet.add_row({"Joe","Jackson","21","mathematics"});
    sheet.add_row({"Sarah","Summers","21","computer science"});
    sheet.add_row({"Diane","Dole","20","computer engineering"});
    sheet.add_row({"David","Dole","22","electrical engineering"});
    sheet.add_row({"Dominick","Dole","22","communications"});
    sheet.add_row({"George","Genius","9","astrophysics"});

    sheet.set_selection(new Select_Or(	
	new Select_Contains(&sheet, "Major", "engineering"),
        new Select_Contains(&sheet, "Last", "Dole")));
    sheet.print_selection(sstr);

    ASSERT_EQ("Diane Dole 20 computer engineering \nDavid Dole 22 electrical engineering \nDominick Dole 22 communications \n", sstr.str());
}

#endif
