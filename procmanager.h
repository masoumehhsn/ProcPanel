#ifndef PROCMANAGER_H
#define PROCMANAGER_H
#include <processmodel.h>
#include <QTimer>
#include "resourceusage.h"

class ProcManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ProcessModel* procModel READ procModel WRITE setProcModel NOTIFY procModelChanged FINAL)
    Q_PROPERTY(double cpuUsage READ cpuUsage WRITE setCpuUsage NOTIFY cpuUsageChanged FINAL)
    Q_PROPERTY(double memUsage READ memUsage WRITE setMemUsage NOTIFY memUsageChanged FINAL)
public:
    explicit ProcManager(QObject* parent = nullptr);
    Q_INVOKABLE void stopProc(int pid);
    Q_INVOKABLE void resumeProc(int pid);
    Q_INVOKABLE void terminateProc(int pid);
    Q_INVOKABLE void sort(int column, Qt::SortOrder order);
    ProcessModel* procModel() const;
    double cpuUsage() const;
    double memUsage() const;
    void setProcModel(ProcessModel* model);
    void setCpuUsage(double cpu);
    void setMemUsage(double memory);

signals:
    void procModelChanged();
    void cpuUsageChanged();
    void memUsageChanged();

private:
    ProcessModel* m_procModel;
    QTimer m_detailsTimer;
    QTimer m_cpuUsageTimer;
    QTimer m_memUsageTimer;

    ResourceUsage m_resUsage;
    double m_cpuUsage;
    double m_memUsage;    

};

#endif // PROCMANAGER_H
