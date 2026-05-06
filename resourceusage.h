#ifndef RESOURCEUSAGE_H
#define RESOURCEUSAGE_H
#include <QObject>
#include <unistd.h>
#include <cstdio>
#include <fcntl.h>

class ResourceUsage
{
public:
    ResourceUsage();
    void refresh();
    double getCpuUsage();
    double getMemoryUsage();
};

#endif // RESOURCEUSAGE_H
