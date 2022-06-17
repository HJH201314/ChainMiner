// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA

#undef BEFORE_EXTRA

class TaskQueuePortImpl {

#define AFTER_EXTRA

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_TASKQUEUEPORTIMPL
public:
    class TaskQueuePortImpl& operator=(class TaskQueuePortImpl const &) = delete;
    TaskQueuePortImpl(class TaskQueuePortImpl const &) = delete;
#endif


public:
    /*3*/ virtual struct XTaskQueuePortObject * GetHandle();
    /*4*/ virtual long QueueItem(struct ITaskQueuePortContext *, unsigned int, void *, void ( *)(void *, bool));
    /*5*/ virtual long RegisterWaitHandle(struct ITaskQueuePortContext *, void *, void *, void ( *)(void *, bool), struct XTaskQueueRegistrationToken *);
    /*6*/ virtual void UnregisterWaitHandle(struct XTaskQueueRegistrationToken);
    /*7*/ virtual long PrepareTerminate(struct ITaskQueuePortContext *, void *, void ( *)(void *), void **);
    /*8*/ virtual void CancelTermination(void *);
    /*9*/ virtual void Terminate(void *);
    /*10*/ virtual long Attach(struct ITaskQueuePortContext *);
    /*11*/ virtual void Detach(struct ITaskQueuePortContext *);
    /*12*/ virtual bool DrainOneItem();
    /*13*/ virtual bool Wait(struct ITaskQueuePortContext *, unsigned int);
    /*14*/ virtual bool IsEmpty();
    /*15*/ virtual long SuspendTermination(struct ITaskQueuePortContext *);
    /*16*/ virtual void ResumeTermination(struct ITaskQueuePortContext *);
    /*17*/ virtual ~TaskQueuePortImpl();
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_TASKQUEUEPORTIMPL
#endif
    MCAPI long Initialize(enum XTaskQueueDispatchMode);
    MCAPI TaskQueuePortImpl();

//private:
    MCAPI bool AppendEntry(struct TaskQueuePortImpl::QueueEntry const &, unsigned __int64, bool);
    MCAPI bool AppendWaitRegistrationEntry(struct TaskQueuePortImpl::WaitRegistration *, bool);
    MCAPI void CancelPendingEntries(struct ITaskQueuePortContext *, bool);
    MCAPI long InitializeWaitRegistration(struct TaskQueuePortImpl::WaitRegistration *);
    MCAPI void ScheduleTermination(struct TaskQueuePortImpl::TerminationEntry *);
    MCAPI void SubmitPendingCallback();
    MCAPI static void EraseQueue(class LocklessQueue<struct TaskQueuePortImpl::QueueEntry> *);
    MCAPI static void WaitCallback(struct _TP_CALLBACK_INSTANCE *, void *, struct _TP_WAIT *, unsigned long);


private:


};