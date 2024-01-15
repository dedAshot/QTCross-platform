#include "database.h"

DataBase::DataBase(QObject *parent){

}

DataBase::~DataBase()
{

}

void DataBase::connectToDataBase()
{
    /* Перед подключением к базе данных производим проверку на ее
существование.
* В зависимости от результата производим открытие базы данных или ее
восстановление
* */
    if(!QFile(DATABASE_NAME).exists()){
        this->restoreDataBase();
    } else {
        this->openDataBase();
    }
}

bool DataBase::restoreDataBase()
{
    // Если база данных открылась ...
    if(this->openDataBase()){
        // Производим восстановление базы данных
        return (this->createTable()) ? true : false;
    } else {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
    return false;
}

bool DataBase::openDataBase()
{
    /* База данных открывается по заданному пути
* и имени базы данных, если она существует
* */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName(DATABASE_NAME);
    if(db.open()){
        return true;
    } else {
        return false;
    }
}

void DataBase::closeDataBase()
{
    db.close();
}

bool DataBase::createTable()
{
    /* В данном случае используется формирование сырого SQL-запроса
* с последующим его выполнением
* */
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " TABLE " ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    TABLE_FNAME " VARCHAR(255) NOT NULL,"
                    TABLE_SNAME " VARCHAR(255) NOT NULL,"
                    TABLE_PHONE " VARCHAR(255) NOT NULL"
                    " )"
                    )){
        qDebug() << "DataBase: error of create " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

bool DataBase::inserIntoTable(const QVariantList &data)
{
    /* Запрос SQL формируется из QVariantList,
* в который передаются данные для вставки в таблицу.
* */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
* которые потом связываются методом bindValue
* для подстановки данных из QVariantList
* */
    query.prepare("INSERT INTO " TABLE " ( " TABLE_FNAME ", "
                  TABLE_SNAME ", "
                  TABLE_PHONE " ) "
                  "VALUES (:FirstName, :SurName, :Phone)");
    query.bindValue(":FirstName", data[0].toString());
    query.bindValue(":SurName", data[1].toString());
    query.bindValue(":Phone", data[2].toString());
    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

bool DataBase::inserIntoTable(const QString &fname, const QString &sname,
                              const QString &phone)
{
    QVariantList data;
    data.append(fname);
    data.append(sname);
    data.append(phone);
    if(inserIntoTable(data))
        return true;
    else
        return false;
}

bool DataBase::removeRecord(const int id)
{
    // Удаление строки из базы данных будет производитсья с помощью SQL- запроса
    QSqlQuery query;
    // Удаление производим по id записи, который передается в качестве аргумента функции
    query.prepare("DELETE FROM " TABLE " WHERE id= :ID ;");
    query.bindValue(":ID", id);
    // Выполняем удаление
    qDebug() << "try delete id " << id;
    if(!query.exec()){
        qDebug() << "error delete row " << TABLE ;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}
