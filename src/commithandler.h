#pragma once

#include <QAbstractListModel>
#include "git2.h"

class CommitHandler : public QAbstractListModel
{
    Q_OBJECT

public:
    CommitHandler(QObject *parent = nullptr) : QAbstractListModel(parent) {}
    ~CommitHandler() = default;

    virtual void start() = 0;
    virtual void handleCommit(git_repository *repo, git_commit *commit) = 0;
    virtual void finished() = 0;
};
