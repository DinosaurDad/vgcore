// GcShapeDoc.cpp
// Copyright (c) 2012-2013, https://github.com/rhcad/touchvg

#include "GcShapeDoc.h"
#include "GcBaseView.h"

GcShapeDoc::GcShapeDoc()
{
}

GcShapeDoc::~GcShapeDoc()
{
}

bool GcShapeDoc::addView(GcBaseView* view)
{
    if (view && view->deviceView() && view->cmdView()->document() == this
        && !findView(view->deviceView())) {
        _views.push_back(view);
        return true;
    }
    return false;
}

bool GcShapeDoc::removeView(GcBaseView* view)
{
    std::vector<GcBaseView*>::iterator it;
    
    for (it = _views.begin(); it != _views.end(); ++it) {
        if (*it == view) {
            _views.erase(it);
            return true;
        }
    }
    return false;
}

GcBaseView* GcShapeDoc::findView(GiView* view) const
{
    std::vector<GcBaseView*>::const_iterator it;
    
    for (it = _views.begin(); it != _views.end(); ++it) {
        if ((*it)->deviceView() == view) {
            return *it;
        }
    }
    return NULL;
}

GcBaseView* GcShapeDoc::getView(int index) const
{
    return index >= 0 && index < getViewCount() ? _views[index] : NULL;
}

int GcShapeDoc::getViewCount() const
{
    return (int)_views.size();
}

GcBaseView* GcShapeDoc::firstView() const
{
    return !_views.empty() ? _views.front() : NULL;
}
