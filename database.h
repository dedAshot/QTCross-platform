#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QQmlEngine>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

#define DATABASE_HOSTNAME "NameDataBase"
#define DATABASE_NAME "Name.db"
#define TABLE "NameTable" // Название таблицы
#define TABLE_FNAME "FirstName" // Вторая колонка
#define TABLE_SNAME "SurName" // Третья колонка
#define TABLE_PHONE "Phone" // Четвертая колонка

class DataBase : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();
    /* Методы для непосредственной работы с классом
* Подключение к базе данных и вставка записей в таблицу
* */
    void connectToDataBase();
private:
    // Сам объект базы данных, с которым будет производиться работа
    QSqlDatabase db;
private:
    /* Внутренние методы для работы с базой данных
* */
    bool openDataBase(); // Открытие базы данных
    bool restoreDataBase(); // Восстановление базы данных
    void closeDataBase(); // Закрытие базы данных
    bool createTable(); // Создание таблицы в базе данных

public slots:
    bool inserIntoTable(const QVariantList &data); // Добавление записей в таблицу
    bool inserIntoTable(const QString &fname, const QString &sname, const
                       QString &phone);
    bool removeRecord(const int id); // Удаление записи из таблицы по ее id
};

#endif // DATABASE_H
