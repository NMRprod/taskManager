#ifndef TASKSTORAGE_H
#define TASKSTORAGE_H

#pragma once
#include <QString>
#include <QListWidget>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDir>

class TaskStorage
{
public:
    static void saveTasks(QListWidget *list, const QString &filePath);
    static void loadTasks(QListWidget *list, const QString &filePath);
};

#endif // TASKSTORAGE_H
