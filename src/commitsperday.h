#pragma once

#include "commithandler.h"
#include <set>

class CommitsPerDay : public CommitHandler
{ 
    Q_OBJECT

public:
    enum CommitsPerDayRoles {
        weekdayRole = Qt::UserRole + 1,
        commitsRole,
        totalCommitsRole,
        maxCommitsRole,
    };

    CommitsPerDay(QObject *parent = nullptr);
    ~CommitsPerDay() = default;

    int totalCommits() const;

    void start() override;
    void handleCommit(git_repository *repo, git_commit *commit) override;
    void finished() override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QHash<int, QByteArray> roleNames() const;

private:
    std::set<std::pair<int, int>> m_data;
    int m_commits;
    int m_maxCommits;
};