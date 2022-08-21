#ifndef EXPENSEMODEL_H
#define EXPENSEMODEL_H

#include "Class/Expense.h"
#include "Database/DatabaseManager.h"

#include <vector>
#include <QAbstractTableModel>
#include <QHash>

class ExpenseModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Roles {
        ID_ROLE = Qt::UserRole + 1, DATE_ROLE, CATEGORY_ROLE, EXPENSE_ROLE,
        SHOP_NAME_ROLE
    };

    enum ColumnName {
        ID = 0, DATE, CATEGORY, EXPENSE, SHOP_NAME
    };

    explicit ExpenseModel(QObject* parent = nullptr);
    QModelIndex add(const Expense& expense);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    bool removeRows(int row, int count, const QModelIndex& parent) override;
    QHash<int, QByteArray> roleNames() const override;

private:
    bool isValidIndex(const QModelIndex& index) const;

    DatabaseManager& m_database;
    std::vector<Expense> m_expenses;
};

#endif