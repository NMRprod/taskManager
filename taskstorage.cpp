#include "taskstorage.h"

void TaskStorage::saveTasks(QListWidget *list, const QString &filePath)
{
    QFile file(filePath);
    QFileInfo info(filePath);
    QDir().mkpath(info.path());

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for(int i = 0; i < list->count(); ++i)
    {
        QListWidgetItem *item = list->item(i);
        int state = (item->checkState() == Qt::Checked) ? 1 : 0;
        out << state << "|" << item->text() << "\n";
    }
}

void TaskStorage::loadTasks(QListWidget *list, const QString &filePath)
{
    QFile file(filePath);
    if (!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList parts = line.split("|");
        if (parts.size() != 2)
            continue;

        QListWidgetItem *item = new QListWidgetItem(parts[1]);
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
        item->setCheckState(parts[0] == "1" ? Qt::Checked : Qt::Unchecked);
        list->addItem(item);
    }
}
