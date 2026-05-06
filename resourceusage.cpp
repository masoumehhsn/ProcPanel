#include "resourceusage.h"

ResourceUsage::ResourceUsage() {}

void ResourceUsage::refresh()
{
    getCpuUsage();
}

double ResourceUsage::getCpuUsage() {

    static long long lastIdle = 0;
    static long long lastTotal = 0;

    int fd = open("/proc/stat", O_RDONLY);
    if (fd < 0)
        return 0.0;

    char buf[512] = {0};
    ssize_t n = read(fd, buf, sizeof(buf) - 1);
    close(fd);

    if (n <= 0)
        return 0.0;

    long long user, nice, system, idle;
    if (sscanf(buf, "cpu %lld %lld %lld %lld",
               &user, &nice, &system, &idle) != 4)
        return 0.0;

    long long total = user + nice + system + idle;

    long long totalDiff = total - lastTotal;
    long long idleDiff = idle - lastIdle;

    lastTotal = total;
    lastIdle = idle;

    if (totalDiff == 0)
        return 0.0;

    return 100.0 * (1.0 - (double)idleDiff / totalDiff);

}

double ResourceUsage::getMemoryUsage() {
    int fd = open("/proc/meminfo", O_RDONLY);
    if (fd < 0)
        return 0.0;

    char buf[1024] = {0};
    ssize_t n = read(fd, buf, sizeof(buf) - 1);
    close(fd);

    if (n <= 0)
        return 0.0;

    long long memTotal = 0;
    long long memAvailable = 0;

    const char* ptr = buf;

    while (*ptr) {
        if (sscanf(ptr, "MemTotal: %lld kB", &memTotal) == 1) {
            // found total
        } else if (sscanf(ptr, "MemAvailable: %lld kB", &memAvailable) == 1) {
            // found available
        }

        // move to next line
        while (*ptr && *ptr != '\n') ptr++;
        if (*ptr == '\n') ptr++;
    }

    if (memTotal == 0)
        return 0.0;

    long long used = memTotal - memAvailable;

    return 100.0 * (double)used / memTotal;
}