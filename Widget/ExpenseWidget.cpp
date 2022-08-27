#include "ExpenseWidget.h"
#include "ui_ExpenseWidget.h"
#include "Dialog/ExpenseDialog.h"
#include "Model/ExpenseModel.h"

#include <QMessageBox>

ExpenseWidget::ExpenseWidget(QWidget* parent):
    QWidget(parent),
    ui(new Ui::ExpenseWidget),
    m_expenseModel(new ExpenseModel(this))
{
    ui->setupUi(this);
    connect(ui->btnAdd, &QPushButton::clicked, this, &ExpenseWidget::add);
    connect(ui->btnDelete, &QPushButton::clicked, this, &ExpenseWidget::remove);
    setModel(m_expenseModel);
    setDesign();
}

ExpenseWidget::~ExpenseWidget()
{
    delete ui;
}

void ExpenseWidget::setModel(ExpenseModel* model)
{
    ui->tabExpenses->setModel(model);
}

void ExpenseWidget::setDesign()
{
    ui->tabExpenses->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tabExpenses->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tabExpenses->setTextElideMode(Qt::ElideRight);
    ui->tabExpenses->horizontalHeader()->setVisible(true);
    ui->tabExpenses->resizeColumnsToContents();
    ui->tabExpenses->setCurrentIndex(ui->tabExpenses->model()->index(0,0));
    ui->tabExpenses->show();
}

void ExpenseWidget::add()
{
    Expense expense;
    ExpenseDialog dialog(expense);
    auto dialogCode = dialog.exec();
    if(dialogCode == QDialog::Accepted)
    {
        QModelIndex createdIndex = m_expenseModel->add(expense);
        ui->tabExpenses->setCurrentIndex(createdIndex);
    }
}

void ExpenseWidget::edit()
{

}

void ExpenseWidget::remove()
{
    unsigned int currentRow = ui->tabExpenses->currentIndex().row();
    !m_expenseModel->removeRows(currentRow, 1) ?
                QMessageBox::warning(this, tr("Delete current row"),
                    tr("Current row could not be deleted!"), QMessageBox::Ok) :
                QMessageBox::information(this, tr("Delete current row"),
                    tr("Current row has been deleted!"), QMessageBox::Ok);
}
