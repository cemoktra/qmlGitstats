#include "commitsbyauthor.h"
#include <string>
#include <iterator>

CommitsByAuthor::CommitsByAuthor(QObject *parent) 
    : CommitHandler(parent) 
    , m_commits(0)
    , m_maxCommits(0)
{
}

void CommitsByAuthor::start()
{    
    beginResetModel();
    m_data.clear();
    m_commits = 0;
    m_maxCommits = 0;
}

void CommitsByAuthor::handleCommit(git_repository *repo, git_commit *commit)
{
    m_commits++;
    std::string author = std::string(git_commit_author(commit)->name) + " (" + std::string(git_commit_author(commit)->email) + ")";

    auto find_result = std::find_if(m_data.begin(), m_data.end(), [&](const std::pair<int, std::string> &data) { return 0 == data.second.compare(author);});
    if (find_result != m_data.end()) {
        auto newCount = find_result->first + 1;
        m_maxCommits = std::max(m_maxCommits, newCount);
        m_data.erase(find_result);
        m_data.insert(std::make_pair(newCount, author));
    } else{
        m_maxCommits = std::max(m_maxCommits, 1);
        m_data.insert(std::make_pair(1, author));
    }
}

void CommitsByAuthor::finished()
{
    endResetModel();
}

QVariant CommitsByAuthor::data(const QModelIndex &index, int role) const
{
    auto iter = std::next(m_data.begin(), index.row());
    if (role == CommitsByAuthorRoles::authorRole)
        return QString::fromStdString(iter->second);
    else if (role == CommitsByAuthorRoles::commitsRole)
        return iter->first;
    else if (role == CommitsByAuthorRoles::totalCommitsRole)
        return m_commits;
    else if (role == CommitsByAuthorRoles::maxCommitsRole)
        return m_maxCommits;
    return QVariant();
}

int CommitsByAuthor::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

QHash<int, QByteArray> CommitsByAuthor::roleNames() const
{
    auto defaultNames = QAbstractItemModel::roleNames();
    defaultNames.insert(CommitsByAuthorRoles::authorRole, QString("author").toLatin1());
    defaultNames.insert(CommitsByAuthorRoles::commitsRole, QString("commits").toLatin1());
    defaultNames.insert(CommitsByAuthorRoles::totalCommitsRole, QString("totalCommits").toLatin1());
    defaultNames.insert(CommitsByAuthorRoles::maxCommitsRole, QString("maxCommits").toLatin1());
    return defaultNames;
}



CommitsByAuthorProxy::CommitsByAuthorProxy(int filterTop, QObject *parent)
    : QSortFilterProxyModel(parent)
    , m_filterTop(filterTop)
{
}

bool CommitsByAuthorProxy::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    return sourceRow < m_filterTop;
}