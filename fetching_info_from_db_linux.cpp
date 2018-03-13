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
   sqlite3 *db;
   rc = sqlite3_open("stux_base.db", &db);
   sqlite3_stmt * stmt = nullptr;
   string sqlSelect = "SELECT cash, strikes FROM mainGamePlayer where name = 'Nick';";
   sqlite3_prepare(db, sqlSelect.c_str(), sqlSelect.size(), &stmt, nullptr);
   sqlite3_step(stmt);
   int cash =  sqlite3_column_int(stmt, 0);
   int strikes =  sqlite3_column_int(stmt, 1); 
   cout<<cash<<' '<<strikes<<endl;
   sqlite3_finalize(stmt);
   sqlite3_close(db);
   return 0;
}
