#pragma once

#include <QObject>
#include <QSortFilterProxyModel>
#include <git2.h>


class CommitHandler;
class CommitsByAuthor;
class CommitsByAuthorProxy;
class CommitsPerDay;

class Repository : public QObject
{
    Q_OBJECT

public:
    Repository(QObject *parent = nullptr);
    ~Repository();

    Q_PROPERTY(bool open READ isOpen NOTIFY openChanged);
    Q_PROPERTY(QString branch READ branch NOTIFY branchChanged);
    Q_PROPERTY(QString commitId READ commitId NOTIFY commitIdChanged);

    bool isOpen() const;
    QString branch() const;
    QString commitId() const;

public slots:
    bool chooseRepository();
    
    QAbstractListModel*    getCommitsByAuthor();
    QSortFilterProxyModel* getTopAuthors(int number = 5);
    QAbstractListModel*    getCommitsPerDay();

protected slots:
    void pollHead();

signals:
    void openChanged(bool isOpen);
    void branchChanged(const QString& newBranch);
    void commitIdChanged(const QString& newId);

private:
    bool openRepo(const std::string& repo);    
    void walk();

    QString m_branch;
    QString m_commitId;

    git_repository *m_repo;
    git_reference  *m_head;
    git_commit     *m_commit;

    CommitsByAuthor *m_commitsByAuthor;
    CommitsPerDay *m_commitsPerDay;
    std::vector<CommitHandler*> m_handlers;
};