#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QObject>
#include <QQmlEngine>
#include <QSqlQueryModel>

class ListModel : public QSqlQueryModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    // Перечисляем все роли, которые будут использоваться в TableView
    enum Roles {
        IdRole = Qt::UserRole + 1, // id
        FNameRole, // имя
        SNameRole, // фамилия
        PhoneRole // телефон
    };
    // Объявляем конструктор класса
    explicit ListModel(QObject *parent = nullptr);
    // Переопределяем метод, который будет возвращать данные
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole)
        const;

protected:
    QHash<int, QByteArray> roleNames() const;

public slots:
    void updateModel();
    int getId(int row);

};
#endif // LISTMODEL_H
