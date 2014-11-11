﻿// cmdsubject.cpp
// Copyright (c) 2004-2013, Zhang Yungui
// License: LGPL, https://github.com/rhcad/touchvg

#include "mgcmdmgr_.h"
#include "cmdsubject.h"
#include <vector>

class CmdSubjectImpl : public CmdSubject
{
public:
    CmdSubjectImpl() {}

private:
    virtual void registerObserver(CmdObserver* observer) {
        if (observer) {
            unregisterObserver(observer);
            _arr.push_back(observer);
        }
    }
    virtual void unregisterObserver(CmdObserver* observer) {
        for (Iterator it = _arr.begin(); it != _arr.end(); ++it) {
            if (*it == observer) {
                _arr.erase(it);
                break;
            }
        }
    }
    virtual void onDocLoaded(const MgMotion* sender, bool forUndo) {
        for (Iterator it = _arr.begin(); it != _arr.end(); ++it) {
            (*it)->onDocLoaded(sender, forUndo);
        }
    }
    virtual void onEnterSelectCommand(const MgMotion* sender) {
        for (Iterator it = _arr.begin(); it != _arr.end(); ++it) {
            (*it)->onEnterSelectCommand(sender);
        }
    }
    virtual void onUnloadCommands(MgCmdManager* sender) {
        Observers arr(_arr);
        _arr.clear();
        for (Iterator it = arr.begin(); it != arr.end(); ++it) {
            (*it)->onUnloadCommands(sender);
        }
    }
    virtual bool selectActionsNeedHided(const MgMotion* sender) {
        for (Iterator it = _arr.begin(); it != _arr.end(); ++it) {
            if ((*it)->selectActionsNeedHided(sender)) {
                return true;
            }
        }
        return false;
    }
    virtual int addShapeActions(const MgMotion* sender,
        mgvector<int>& actions, int n, const MgShape* shape) {
        for (Iterator it = _arr.begin(); it != _arr.end(); ++it) {
            n = (*it)->addShapeActions(sender, actions, n, shape);
        }
        return n;
    }
    virtual bool doAction(const MgMotion* sender, int action) {
        for (Iterator it = _arr.begin(); it != _arr.end(); ++it) {
            if ((*it)->doAction(sender, action))
                return true;
        }
        return false;
    }
    virtual bool doEndAction(const MgMotion* sender, int action) {
        for (Iterator it = _arr.begin(); it != _arr.end(); ++it) {
            if ((*it)->doEndAction(sender, action))
                return true;
        }
        return false;
    }
    virtual void drawInShapeCommand(const MgMotion* sender, 
        MgCommand* cmd, GiGraphics* gs) {
        for (Iterator it = _arr.begin(); it != _arr.end(); ++it) {
            (*it)->drawInShapeCommand(sender, cmd, gs);
        }
    }
    virtual void drawInSelectCommand(const MgMotion* sender, 
        const MgShape* shape, int handleIndex, GiGraphics* gs) {
        for (Iterator it = _arr.begin(); it != _arr.end(); ++it) {
            (*it)->drawInSelectCommand(sender, shape, handleIndex, gs);
        }
    }
    virtual void onSelectTouchEnded(const MgMotion* sender, int shapeid,
        int handleIndex, int snapid, int snapHandle,
        int count, const int* ids)
    {
        for (Iterator it = _arr.begin(); it != _arr.end(); ++it) {
            (*it)->onSelectTouchEnded(sender, shapeid, 
                handleIndex, snapid, snapHandle, count, ids);
        }
    }
    virtual void onGatherSnapIgnoredID(const MgMotion* sender, const MgShape* sp,
                                       int* ids, int& i, int n) {
        for (Iterator it = _arr.begin(); it != _arr.end(); ++it) {
            (*it)->onGatherSnapIgnoredID(sender, sp, ids, i, n);
        }
    }

    virtual void onSelectionChanged(const MgMotion* sender) {
        for (Iterator it = _arr.begin(); it != _arr.end(); ++it) {
            (*it)->onSelectionChanged(sender);
        }
    }
    virtual bool onShapeWillAdded(const MgMotion* sender, MgShape* shape) {
        for (Iterator it = _arr.begin(); it != _arr.end(); ++it) {
            if (!(*it)->onShapeWillAdded(sender, shape)) {
                return false;
            }
        }
        return true;
    }
    virtual void onShapeAdded(const MgMotion* sender, MgShape* shape) {
        for (Iterator it = _arr.begin(); it != _arr.end(); ++it) {
            (*it)->onShapeAdded(sender, shape);
        }
    }
    virtual bool onShapeWillDeleted(const MgMotion* sender, const MgShape* shape) {
        for (Iterator it = _arr.begin(); it != _arr.end(); ++it) {
            if (!(*it)->onShapeWillDeleted(sender, shape)) {
                return false;
            }
        }
        return true;
    }
    virtual void onShapeDeleted(const MgMotion* sender, const MgShape* shape) {
        for (Iterator it = _arr.begin(); it != _arr.end(); ++it) {
            (*it)->onShapeDeleted(sender, shape);
        }
    }
    virtual bool onShapeCanRotated(const MgMotion* sender, const MgShape* shape) {
        for (Iterator it = _arr.begin(); it != _arr.end(); ++it) {
            if (!(*it)->onShapeCanRotated(sender, shape)) {
                return false;
            }
        }
        return true;
    }
    virtual bool onShapeCanTransform(const MgMotion* sender, const MgShape* shape) {
        for (Iterator it = _arr.begin(); it != _arr.end(); ++it) {
            if (!(*it)->onShapeCanTransform(sender, shape)) {
                return false;
            }
        }
        return true;
    }
    virtual bool onShapeCanUnlock(const MgMotion* sender, const MgShape* shape) {
        for (Iterator it = _arr.begin(); it != _arr.end(); ++it) {
            if (!(*it)->onShapeCanUnlock(sender, shape)) {
                return false;
            }
        }
        return true;
    }
    virtual bool onShapeCanUngroup(const MgMotion* sender, const MgShape* shape) {
        for (Iterator it = _arr.begin(); it != _arr.end(); ++it) {
            if (!(*it)->onShapeCanUngroup(sender, shape)) {
                return false;
            }
        }
        return true;
    }
    virtual bool onShapeCanMovedHandle(const MgMotion* sender, const MgShape* sp, int index) {
        for (Iterator it = _arr.begin(); it != _arr.end(); ++it) {
            if (!(*it)->onShapeCanMovedHandle(sender, sp, index)) {
                return false;
            }
        }
        return true;
    }
    virtual void onShapeMoved(const MgMotion* sender, MgShape* shape, int segment) {
        for (Iterator it = _arr.begin(); it != _arr.end(); ++it) {
            (*it)->onShapeMoved(sender, shape, segment);
        }
    }
    virtual bool onShapeWillChanged(const MgMotion* sender, MgShape* sp, const MgShape* oldsp) {
        for (Iterator it = _arr.begin(); it != _arr.end(); ++it) {
            if (!(*it)->onShapeWillChanged(sender, sp, oldsp)) {
                return false;
            }
        }
        return true;
    }
    virtual void onShapeChanged(const MgMotion* sender, MgShape* shape) {
        for (Iterator it = _arr.begin(); it != _arr.end(); ++it) {
            (*it)->onShapeChanged(sender, shape);
        }
    }

    virtual MgBaseShape* createShape(const MgMotion* sender, int type) {
        MgBaseShape* sp = (MgBaseShape*)0;
        for (Iterator it = _arr.begin(); !sp && it != _arr.end(); ++it) {
            sp = (*it)->createShape(sender, type);
        }
        return sp;
    }

    virtual MgCommand* createCommand(const MgMotion* sender, const char* name) {
        MgCommand* cmd = (MgCommand*)0;
        for (Iterator it = _arr.begin(); !cmd && it != _arr.end(); ++it) {
            cmd = (*it)->createCommand(sender, name);
        }
        return cmd;
    }
    
    virtual bool onPreGesture(MgMotion* sender) {
        for (Iterator it = _arr.begin(); it != _arr.end(); ++it) {
            if (!(*it)->onPreGesture(sender)) {
                return false;
            }
        }
        return true;
    }
    
    virtual void onPostGesture(const MgMotion* sender) {
        for (Iterator it = _arr.begin(); it != _arr.end(); ++it) {
            (*it)->onPostGesture(sender);
        }
    }
    
    virtual void onPointSnapped(const MgMotion* sender, const MgShape* sp) {
        for (Iterator it = _arr.begin(); it != _arr.end(); ++it) {
            (*it)->onPointSnapped(sender, sp);
        }
    }

private:
    typedef std::vector<CmdObserver*> Observers;
    typedef Observers::iterator Iterator;
    Observers _arr;
};

CmdSubject* MgCmdManagerImpl::getCmdSubject()
{
    if (!_subject) {
        _subject = new CmdSubjectImpl();
    }
    return _subject;
}

void MgCmdManagerImpl::freeSubject()
{
    if (_subject) {
        delete _subject;
        _subject = NULL;
    }
}
