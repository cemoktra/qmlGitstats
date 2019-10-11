#pragma once

#include "commithandler.h"
#include <QSortFilterProxyModel>
#include <set>

class CommitsByAuthor : public CommitHandler
{ 
    Q_OBJECT

public:
    enum CommitsByAuthorRoles {
        authorRole = Qt::UserRole + 1,
        commitsRole,
        totalCommitsRole,
        maxCommitsRole,
    };

    CommitsByAuthor(QObject *parent = nullptr);
    ~CommitsByAuthor() = default;

    void start() override;
    void handleCommit(git_repository *repo, git_commit *commit) override;
    void finished() override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QHash<int, QByteArray> roleNames() const;

private:
    std::set<std::pair<int, std::string>, std::greater<std::pair<int, std::string>>> m_data;
    
    int m_commits;
    int m_maxCommits;
};

class CommitsByAuthorProxy : public QSortFilterProxyModel
{
public:
    CommitsByAuthorProxy(int filterTop, QObject *parent = nullptr);
    ~CommitsByAuthorProxy() = default;

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private:
    int m_filterTop;
};