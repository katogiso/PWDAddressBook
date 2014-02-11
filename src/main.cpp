#include <QApplication>
#include <QHeaderView>
#include <QSqlTableModel>
#include <QTableView>

#include <QMessageBox>

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QtWidgets>

#define DBNAME    "/home/so/prog/qt/PWDAddressBook/db/TSA.iprettygetter.sqlite3"
#define TABLENAME "tweet_table"

int main(int argc, char *argv[]){
  
  QApplication app(argc, argv);

  //createConnection
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  
  db.setDatabaseName( DBNAME );
  if (!db.open()) {
    QMessageBox::critical(0, "Cannot open database",
			  "Unable to establish a database connection.\n"
			  "This example needs SQLite support. Please read "
			  "the Qt SQL driver documentation for information how "
			  "to build it.\n\n"
			  "Click Cancel to exit.",
			QMessageBox::Cancel);
    return false;
  } 
  
  
  //Model
  QSqlTableModel sqlModel( &app );
  sqlModel.setTable( TABLENAME );
  //sqlModel.setFilter("name=まゆみ");
  QString filter = "name='まゆみ'";
  sqlModel.setFilter(filter);
  sqlModel.select();
  sqlModel.setHeaderData( 0, Qt::Horizontal, "date"   );
  sqlModel.setHeaderData( 1, Qt::Horizontal, "name"   );
  sqlModel.setHeaderData( 2, Qt::Horizontal, "tweet");
  sqlModel.setHeaderData( 3, Qt::Horizontal, "tweetid");
  
  //View
  QTableView tableView;
  tableView.setModel( &sqlModel );
  tableView.resizeColumnsToContents();

  tableView.show();
  //QHBoxLayout *mainLayout = new QHBoxLayout;
  //mainLayout->addWidget( &tableView );
  //mainLayout->setWindowTitle("Cached Table");
  //mainLayout->show();
    
  return app.exec();
}
