#include "widget.h"
#include "taskstorage.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    taskInput = new QLineEdit(this);
    btnAdd = new QPushButton("Добавить");
    btnDelete = new QPushButton("Удалить");
    taskList = new QListWidget(this);

    vbox = new QVBoxLayout(this);
    hboxButtons = new QHBoxLayout();

    hboxButtons->addWidget(taskInput);
    hboxButtons->addWidget(btnAdd);
    hboxButtons->addWidget(btnDelete);

    vbox->addLayout(hboxButtons);
    vbox->addWidget(taskList);
    setLayout(vbox);
    applyStyles();

    //signals for buttons and enter
    connect(btnAdd, SIGNAL(clicked()),
            this, SLOT(on_btnAdd_clicked()));
    connect(btnDelete, SIGNAL(clicked()),
            this, SLOT(on_btnDelete_clicked()));
    connect(taskInput, &QLineEdit::returnPressed, this, &Widget::on_btnAdd_clicked);

    //delete shortcut
    QShortcut *deleteShortcut = new QShortcut(QKeySequence(Qt::Key_Delete), taskList);
    connect(deleteShortcut, &QShortcut::activated, this, [=]() {
        delete taskList->takeItem(taskList->currentRow());
    });

    //complete task checkbox with double-click
    connect(taskList, &QListWidget::itemDoubleClicked, this, &Widget::toggleTaskCompleted);

    //context menu
    taskList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(taskList, &QListWidget::customContextMenuRequested,
            this, &Widget::showContextMenu);

    //change foreground while checkbox changing
    connect(taskList, &QListWidget::itemChanged, this, &Widget::onItemChanged);

    TaskStorage::loadTasks(taskList, "data/tasks.txt");
}

void Widget::on_btnAdd_clicked()
{
    QString text = taskInput->text();

    if (text.isEmpty())
        return;

    QListWidgetItem *item = new QListWidgetItem(text);
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Unchecked);

    taskList->addItem(item);
    taskInput->clear();
}

void Widget::on_btnDelete_clicked()
{
    delete taskList->takeItem(taskList->currentRow());
}

void Widget::toggleTaskCompleted()
{
    QListWidgetItem *item = taskList->currentItem();
    if(!item) return;

    if(item->checkState() == Qt::Unchecked)
    {
        item->setCheckState(Qt::Checked);
    }
    else
    {
        item->setCheckState(Qt::Unchecked);
    }
}

void Widget::closeEvent(QCloseEvent *event)
{
    TaskStorage::saveTasks(taskList, "data/tasks.txt");
    QWidget::closeEvent(event);
}

//context menu for right button click (edit and delete tasks)
void Widget::showContextMenu(const QPoint &pos)
{
    QListWidgetItem *item = taskList->itemAt(pos);
    if(!item)
        return;

    QMenu menu(this);
    QAction *editAction = menu.addAction("Редактировать");
    QAction *deleteAction = menu.addAction("Удалить");

    QAction *selectedAction = menu.exec(taskList->viewport()->mapToGlobal(pos));
    if(!selectedAction)
        return;

    if(selectedAction == editAction)
    {
        bool ok;
        QString newText = QInputDialog::getText(this, "Редактировать задачу", "Введите новый текст", QLineEdit::Normal, item->text(), &ok);
        if(ok && !newText.trimmed().isEmpty())
        {
            item->setText(newText.trimmed());
        }
    }
    else if(selectedAction == deleteAction)
    {
        delete taskList->takeItem(taskList->row(item));
    }
}

void Widget::onItemChanged(QListWidgetItem *item)
{
    if(!item)
        return;

    QFont font = item->font();
    if(item->checkState() == Qt::Checked)
    {
        font.setStrikeOut(true);
        font.setItalic(true);
        item->setForeground(Qt::gray);
    }
    else if(item->checkState() == Qt::Unchecked)
    {
        font.setStrikeOut(false);
        font.setItalic(false);
        item->setForeground(Qt::black);
    }
    item->setFont(font);
}

//changing styles for buttons and taskList
void Widget::applyStyles()
{
    btnAdd->setStyleSheet(
        "QPushButton {"
        "  background-color: #4CAF50;"
        "  color: white;"
        "  border-radius: 8px;"
        "  padding: 6px 12px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #45a049;"
        "}"
    );

    btnDelete->setStyleSheet(
        "QPushButton {"
        "  background-color: #f00024;"
        "  color: white;"
        "  border-radius: 8px;"
        "  padding: 6px 12px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #a30018;"
        "}"
        );

    /*taskList->setStyleSheet(
        "QListWidget {"
        "  background-color: #f9f9f9;"
        "  border: 1px solid #ddd;"
        "  border-radius: 6px;"
        "}"
        "QListWidget::item:selected {"
        "  background-color: #cce5ff;"
        "}"
        );
*/



}

Widget::~Widget() {}
