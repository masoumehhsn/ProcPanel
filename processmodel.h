#ifndef PROCESSMODEL_H
#define PROCESSMODEL_H

#include <QObject>
#include <QString>
#include <QAbstractTableModel>

struct ProcessInfo {
    int pid = 1;
    QString name = "";
    QString state = "";
    long memory = 0; // in KB
    double cpu = 0.0;
};

class ProcessModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum Columns {
        PID,
        Name,
        State,
        Memory,
        Cpu,
        ColumnCount
    };
    enum Roles {
        PidRole = Qt::UserRole + 1,
        NameRole,
        StateRole,
        MemoryRole,
        CpuRole
    };

    QHash<int, QByteArray> roleNames() const override {
        return {
            {Qt::DisplayRole, "display"},
            {PidRole, "pid"},
            {NameRole, "name"},
            {StateRole, "state"},
            {MemoryRole, "memory"},
            {CpuRole, "cpu"}

        };
    }
    int rowCount(const QModelIndex &) const override {
        return m_processes.size();
    }

    int columnCount(const QModelIndex &) const override {
        return ColumnCount;
    }

    QVariant data(const QModelIndex &index, int role) const override {
        const auto &item = m_processes[index.row()];

        if (role == PidRole)
            return item.pid;
        if (role == NameRole)
            return item.name;
        if (role == StateRole)
            return item.state;
        if (role == MemoryRole)
            return QVariant::fromValue(static_cast<qlonglong>(item.memory));
        if(role == Cpu)
            return QString::number(item.cpu, 'f', 1);
;

        if (role == Qt::DisplayRole) {
            switch (index.column()) {
            case 0: return item.pid;
            case 1: return item.name;
            case 2: return item.state;
            case 3: return QVariant::fromValue(static_cast<qlonglong>(item.memory));
            case 4: return QString::number(item.cpu, 'f', 1);
;
            }
        }

        return {};
    }
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const override
    {
        if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
            return {};

        switch (section) {
        case 0: return "PID";
        case 1: return "Name";
        case 2: return "State";
        case 3: return "Memory";
        case 4: return "Cpu%";
        }

        return {};
    }

    QVector<ProcessInfo> readProcesses()
    {
        QVector<ProcessInfo> list;

        DIR *dir = opendir("/proc");
        if (!dir) return list;

        struct dirent *entry;

        while ((entry = readdir(dir)) != nullptr) {
            int pid = atoi(entry->d_name);
            if (pid <= 0) continue;

            ProcessInfo p;
            p.pid = pid;

            QString commPath = QString("/proc/%1/comm").arg(pid);
            int fd = open(commPath.toStdString().c_str(), O_RDONLY);
            if (fd >= 0) {
                char buf[256] = {0};
                read(fd, buf, sizeof(buf));
                p.name = QString(buf).trimmed();
                close(fd);
            }

            QString statusPath = QString("/proc/%1/status").arg(pid);
            fd = open(statusPath.toStdString().c_str(), O_RDONLY);
            if (fd >= 0) {
                char buf[4096] = {0};
                int n = read(fd, buf, sizeof(buf) - 1);
                close(fd);

                QString content = QString::fromUtf8(buf, n);
                QStringList lines = content.split("\n");

                for (const auto &line : lines) {

                    if (line.startsWith("State:")) {
                        p.state = line.section(":", 1).trimmed();
                    }

                    if (line.startsWith("VmRSS:")) {
                        p.memory = line.section(":", 1)
                        .simplified()
                            .split(" ")
                            .first()
                            .toLong(); // KB
                    }
                }
            }

            list.append(p);
        }

        closedir(dir);
        return list;
    }
    long long readTotalCPUTime();
    long long readProcessCPUTime(int pid);
    void setSortingParams(int column, Qt::SortOrder order);

public slots:
    void refresh()
    {
        long long totalTime = readTotalCPUTime();

        beginResetModel();
        m_processes = readProcesses();

        long long deltaTotal = totalTime - m_prevTotalTime;

        for (auto &p : m_processes) {
            // qDebug()<<"pid: "<<p.pid;
            long long procTime = readProcessCPUTime(p.pid);
            if(!m_prevProcTime.contains(p.pid)){
                // qDebug()<<"first initialization";
                m_prevProcTime[p.pid] = procTime;
                continue;
            }
            else{
                auto prevProc = m_prevProcTime[p.pid];
                long long deltaProc = procTime - prevProc;

                if (deltaTotal > 0) {
                    p.cpu = (double(deltaProc) / deltaTotal) * 100.0;
                } else {
                    p.cpu = 0.0;
                }

                m_prevProcTime[p.pid] = procTime;
            }
        }

        m_prevTotalTime = totalTime;
        if(m_sortColumn != 0 || m_order != Qt::AscendingOrder)
        {
            sort();
        }
        endResetModel();
    }
private:
    void sort();
    QVector<ProcessInfo> m_processes;
    QHash<int, long long> m_prevProcTime;
    long long m_prevTotalTime = 0;
    int m_sortColumn = 0;
    Qt::SortOrder m_order = Qt::AscendingOrder;
};


#endif // PROCESSMODEL_H
