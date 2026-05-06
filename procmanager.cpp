#include "procmanager.h"
#include <stdlib.h>
#include <dirent.h>
#include <signal.h>
#include <sys/types.h>
#include <QDebug>


void ProcManager::stopProc(int pid)
{
    kill(pid, SIGSTOP);
}

void ProcManager::resumeProc(int pid){
    kill(pid, SIGCONT);

}

void ProcManager::terminateProc(int pid)
{
    kill(pid, SIGTERM);
}

void ProcManager::sort(int col_index, Qt::SortOrder order)
{
    m_procModel->setSortingParams(col_index, order);
}

ProcessModel *ProcManager::procModel() const
{
    return m_procModel;
}

double ProcManager::cpuUsage() const
{
    return m_cpuUsage;
}

double ProcManager::memUsage() const
{
    return m_memUsage;
}

void ProcManager::setProcModel(ProcessModel *model)
{
    if (m_procModel == model)
        return;
    m_procModel = model;
    emit procModelChanged();
}

void ProcManager::setCpuUsage(double cpu)
{
    m_cpuUsage = cpu;
    emit cpuUsageChanged();
}

void ProcManager::setMemUsage(double memory)
{
    m_memUsage = memory;
    emit memUsageChanged();
}

ProcManager::ProcManager(QObject* parent) : QObject(parent), m_procModel(nullptr){
    m_procModel = new ProcessModel();
    m_procModel->refresh();
    connect(&m_detailsTimer, &QTimer::timeout, m_procModel, &ProcessModel::refresh);
    m_detailsTimer.start(2000);

    connect(&m_cpuUsageTimer, &QTimer::timeout, this, [this](){
        setCpuUsage(m_resUsage.getCpuUsage());
    });
    m_cpuUsageTimer.start(1000);

    connect(&m_memUsageTimer, &QTimer::timeout, this, [this](){
        setMemUsage(m_resUsage.getMemoryUsage());
    });
    m_memUsageTimer.start(1000);
}
