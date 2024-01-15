#include "listmodel.h"
#include "database.h"
#include <QSqlQueryModel>

ListModel::ListModel(QObject *parent) : QSqlQueryModel(parent)
{
    this->updateModel();
}


QVariant ListModel::data(const QModelIndex &index, int role) const {
    // Определяем номер колонки, адрес так сказать, по номеру роли
    int columnId = role - Qt::UserRole - 1;
    // Создаем индекс с помощью новоиспеченного ID колонки
    QModelIndex modelIndex = this->index(index.row(), columnId);
    /* И с помощью уже метода data() базового класса
* берем данные для таблицы из модели
* */
    return QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
}

QHash<int, QByteArray> ListModel::roleNames() const {
    /* Сохраняем в хеш-таблицу названия ролей
* по их номеру
* */
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[FNameRole] = "FirstName";
    roles[SNameRole] = "SurName";
    roles[PhoneRole] = "Phone";
    return roles;
}

// Метод обновления таблицы в модели представления данных
void ListModel::updateModel()
{
    // Обновление производится SQL-запросом к базе данных
    this->setQuery("SELECT id, " TABLE_FNAME ", " TABLE_SNAME ", "
                   TABLE_PHONE " FROM " TABLE);
}
// Получение id из строки в модели представления данных
int ListModel::getId(int row)
{
    return this->data(this->index(row, 0), IdRole).toInt();
}
