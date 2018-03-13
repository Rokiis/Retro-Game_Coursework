#include <iostream>
#include <ios>
#include <string>
using namespace std;
#include "sqlite3.h"
int main()
{
   int rc;
   char *error;
 
   // Open Database
   cout << "Opening MyDb.db ..." << endl;
   sqlite3 *db;
   rc = sqlite3_open("stux_base.db", &db);
   if (rc)
   {
      cerr << "Error opening SQLite3 database: " << sqlite3_errmsg(db) << endl << endl;
      sqlite3_close(db);
      return 1;
   }
   else
   {
      cout << "Opened MyDb.db." << endl << endl;
   }
    cout << "Retrieving values in MyTable ..." << endl;
   const char *sqlSelect = "SELECT * FROM mainGamePlayer;";
   char **results = NULL;
   int rows, columns;
   sqlite3_get_table(db, sqlSelect, &results, &rows, &columns, &error);
   if (rc)
   {
      cerr << "Error executing SQLite3 query: " << sqlite3_errmsg(db) << endl << endl;
      sqlite3_free(error);
   }
   else
   {
      // Display Table
      for (int rowCtr = 0; rowCtr <= rows; ++rowCtr)
      {
         for (int colCtr = 0; colCtr < columns; ++colCtr)
         {
            // Determine Cell Position
            int cellPosition = (rowCtr * columns) + colCtr;
 
            // Display Cell Value
            cout.width(12);
            cout.setf(ios::left);
            cout << results[cellPosition] << " ";
         }
 
         // End Line
         cout << endl;
 
         // Display Separator For Header
         if (0 == rowCtr)
         {
            for (int colCtr = 0; colCtr < columns; ++colCtr)
            {
               cout.width(12);
               cout.setf(ios::left);
               cout << "~~~~~~~~~~~~ ";
            }
            cout << endl;
         }
      }
   }
   sqlite3_free_table(results);
}
