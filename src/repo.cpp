#include "repo.h"
#include "commitsbyauthor.h"
#include "commitsperday.h"
#include <QFileDialog>
#include <QString>
#include <QTimer>
#include <iostream>

Repository::Repository(QObject *parent)
    : QObject(parent)
    , m_repo(nullptr)
    , m_branch("<unknown>")
    , m_head(nullptr)
    , m_commit(nullptr)
    , m_commitsByAuthor(new CommitsByAuthor(this))
    , m_commitsPerDay(new CommitsPerDay(this))
{
    m_handlers.push_back(m_commitsByAuthor);
    m_handlers.push_back(m_commitsPerDay);

    git_libgit2_init();

    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, Repository::pollHead);
    timer->start(2000);

    // TODO: remove
    //openRepo("C:\\Users\\bscb\\Documents\\QmlMemory");
    openRepo("C:\\Users\\bscb\\Documents\\gitstats\\libgit2");
}

Repository::~Repository()
{
    git_reference_free(m_head);
    git_commit_free(m_commit);
    git_repository_free(m_repo);
    git_libgit2_shutdown();
}

bool Repository::isOpen() const
{
    return m_repo != nullptr;
}

QString Repository::branch() const
{
    return m_branch;
}

QString Repository::commitId() const
{
    return m_commitId;
}

bool Repository::chooseRepository()
{
    return openRepo(QFileDialog::getExistingDirectory(nullptr, tr("Open Directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks).toStdString());    
}

QAbstractListModel* Repository::getCommitsByAuthor()
{
    return m_commitsByAuthor;
}

QSortFilterProxyModel* Repository::getTopAuthors(int number)
{
    auto proxy = new CommitsByAuthorProxy(number, this);
    proxy->setSourceModel(m_commitsByAuthor);
    return proxy;
}

QAbstractListModel* Repository::getCommitsPerDay()
{
    return m_commitsPerDay;
}

bool Repository::openRepo(const std::string& repo)
{  
    if (0 != git_repository_open(&m_repo, repo.c_str())) {
        emit openChanged(false);
        return false;
    }
    emit openChanged(true);
    
    pollHead();

    return true;    
}

void Repository::pollHead()
{
    const char *branchName;

    if (!m_repo) 
        return;

    git_reference *head = nullptr;
    if (0 == git_repository_head(&head, m_repo)) {
        // get branch name
        if (0 == git_branch_name(&branchName, head)) {
            QString qBranchName = branchName;
            
            if (qBranchName != m_branch) {
                git_reference_free(m_head);
                m_head = head;
                m_branch = qBranchName;
                emit branchChanged(m_branch);
                walk();
            }
        }

        // get head commit
        git_commit *commit = nullptr;
        if (0 == git_commit_lookup(&commit, m_repo, git_reference_target(m_head))) {
            if (commit != m_commit) {
                git_commit_free(m_commit);
                m_commit = commit;
                QString commitId = git_oid_tostr_s(git_commit_id(m_commit));
                if (commitId != m_commitId) {
                    m_commitId = commitId;
                    emit commitIdChanged(m_commitId);
                }
            }
        }
    }
}

void Repository::walk()
{
    git_revwalk *walk  = nullptr;
    git_commit  *commit = nullptr;
    git_oid      oid;

    std::for_each(m_handlers.begin(), m_handlers.end(), [](CommitHandler *handler) { handler->start(); });
    if (0 == git_revwalk_new(&walk, m_repo)) {
        git_revwalk_sorting(walk, GIT_SORT_TOPOLOGICAL | GIT_SORT_TIME);
        git_revwalk_push_head(walk);

        
        while (git_revwalk_next(&oid, walk) == 0) {
            git_commit_lookup(&commit, m_repo, &oid);
            std::for_each(m_handlers.begin(), m_handlers.end(), [&](CommitHandler *handler) { handler->handleCommit(m_repo, commit); });
            git_commit_free(commit);
        }
    }
    std::for_each(m_handlers.begin(), m_handlers.end(), [&](CommitHandler *handler) { handler->finished(); });

    git_revwalk_free(walk);
}