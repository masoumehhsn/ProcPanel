#include "processmodel.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>

long long ProcessModel::readProcessCPUTime(int pid)
{
    QString path = QString("/proc/%1/stat").arg(pid);

    int fd = open(path.toStdString().c_str(), O_RDONLY);
    if (fd < 0) return 0;

    char buf[1024] = {0};
    read(fd, buf, sizeof(buf) - 1);
    close(fd);

    char *ptr = strrchr(buf, ')');
    if (!ptr) return 0;

    ptr += 2;

    long long utime = 0, stime = 0;

    sscanf(ptr,
           "%*c "        // state
           "%*d %*d %*d %*d %*d "
           "%*u %*u %*u %*u %*u "
           "%lld %lld",
           &utime, &stime);
    return utime + stime;
}

void ProcessModel::setSortingParams(int column, Qt::SortOrder order)
{
    m_sortColumn = column;
    m_order = order;
}

void ProcessModel::sort()
{
    if (m_sortColumn < 0 || m_processes.isEmpty())
        return;
    std::sort(m_processes.begin(), m_processes.end(),
              [this](const ProcessInfo &a, const ProcessInfo &b) {

                  switch (m_sortColumn) {
                  case 0: return m_order == Qt::AscendingOrder ? a.pid < b.pid : a.pid > b.pid;
                  case 1: return m_order == Qt::AscendingOrder ? a.name < b.name : a.name > b.name;
                  case 2: return m_order == Qt::AscendingOrder ? a.state < b.state : a.state > b.state;
                  case 3: return m_order == Qt::AscendingOrder ? a.memory < b.memory : a.memory > b.memory;
                  case 4: return m_order == Qt::AscendingOrder ? a.cpu < b.cpu : a.cpu > b.cpu;
                  default: return false;
                  }
    });

}

long long ProcessModel::readTotalCPUTime()
{
    int fd = open("/proc/stat", O_RDONLY);
    if (fd < 0) return 0;

    char buf[512] = {0};
    int n = read(fd, buf, sizeof(buf) - 1);
    close(fd);

    long long user, nice, system, idle;
    sscanf(buf, "cpu %lld %lld %lld %lld",
           &user, &nice, &system, &idle);

    return user + nice + system + idle;
}

