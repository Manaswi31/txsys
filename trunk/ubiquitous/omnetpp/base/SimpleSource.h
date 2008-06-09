//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2005 Andras Varga
// Copyright (C) 2005-2007 Ahmet Sekercioglu
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//
// $Id: app_gen.h,v 1.1 2007/05/13 11:07:28 ahmet Exp $";

#ifndef __SimpleSource_H
#define __SimpleSource_H

class SimpleSource : public cSimpleModule
{
  private:
    int pkSize;
    double iaTime;

    // Statistics
    long numSent;

    cMessage *timeToGenerateAPacket;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

#endif

