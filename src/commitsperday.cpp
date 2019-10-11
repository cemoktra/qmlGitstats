#include "commitsperday.h"
#include <iterator>


CommitsPerDay::CommitsPerDay(QObject *parent) 
    : CommitHandler(parent) 
    , m_commits(0)
    , m_maxCommits(0)
{
}

void CommitsPerDay::start()
{
    beginResetModel();
    m_commits = 0;
    m_maxCommits = 0;
    m_data.clear();
}

void CommitsPerDay::handleCommit(git_repository *repo, git_commit *commit)
{
    m_commits++;

    std::time_t time = git_commit_author(commit)->when.time;
    const std::tm *time_out = std::localtime(&time);

    auto find_result = std::find_if(m_data.begin(), m_data.end(), [&](const std::pair<int, int> &data) { return data.first == time_out->tm_wday;});
    if (find_result != m_data.end()) {
        auto newCount = find_result->second + 1;
        m_maxCommits = std::max(m_maxCommits, newCount);
        m_data.erase(find_result);
        m_data.insert(std::make_pair(time_out->tm_wday, newCount));
    } else {
        m_maxCommits = std::max(m_maxCommits, 1);
        m_data.insert(std::make_pair(time_out->tm_wday, 1));
    }
    
}

void CommitsPerDay::finished()
{
    endResetModel();
}

QVariant CommitsPerDay::data(const QModelIndex &index, int role) const
{
    auto iter = std::next(m_data.begin(), index.row());
    if (role == CommitsPerDayRoles::commitsRole) {
        return iter->second;
    } else if (role == CommitsPerDayRoles::weekdayRole) {
        switch(iter->first)
        {
            case 0: return QString("Sunday");
            case 1: return QString("Monday");
            case 2: return QString("Tuesday");
            case 3: return QString("Wednesday");
            case 4: return QString("Thursday");
            case 5: return QString("Friday");
            case 6: return QString("Saturday");
            default:return QVariant();
        }
    } else if (role == CommitsPerDayRoles::totalCommitsRole)
        return m_commits;
    else if (role == CommitsPerDayRoles::maxCommitsRole)
        return m_maxCommits;
    return QVariant();
}

int CommitsPerDay::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

QHash<int, QByteArray> CommitsPerDay::roleNames() const
{
    auto defaultNames = QAbstractItemModel::roleNames();
    defaultNames.insert(CommitsPerDayRoles::weekdayRole, QString("weekday").toLatin1());
    defaultNames.insert(CommitsPerDayRoles::commitsRole, QString("commits").toLatin1());
    defaultNames.insert(CommitsPerDayRoles::totalCommitsRole, QString("totalCommits").toLatin1());
    defaultNames.insert(CommitsPerDayRoles::maxCommitsRole, QString("maxCommits").toLatin1());
    return defaultNames;
}