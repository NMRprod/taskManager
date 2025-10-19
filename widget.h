#ifndef WIDGET_H
#define WIDGET_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLineEdit>
#include <QShortcut>
#include <QKeySequence>
#include <QMenu>
#include <QInputDialog>
#include <QContextMenuEvent>


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnAdd_clicked();
    void on_btnDelete_clicked();
    void toggleTaskCompleted();
    void showContextMenu(const QPoint &pos);
    void onItemChanged(QListWidgetItem *item);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    QLineEdit *taskInput;

    QPushButton *btnAdd;
    QPushButton *btnDelete;

    QVBoxLayout *vbox;
    QHBoxLayout *hboxButtons;

    QListWidget *taskList;

    QShortcut *deleteShortcut;

    void applyStyles();

};
#endif // WIDGET_H
