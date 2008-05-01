//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003-2004 Andras Varga
// Copyright (C) 2005 Ahmet Sekercioglu
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//
// $Id: modules.ned,v 1.2 2007/05/13 11:07:28 ahmet Exp $

simple AppGen
    parameters:
        destAddresses: string,
        pkSize: numeric,
        iaTime: numeric;
    gates:
        out: out;
endsimple

simple AppSink
    gates:
        in: in;
endsimple

simple NetworkLayer
    gates:
        in: in[];
        out: out[];
        in: localIn;
        out: localOut;
endsimple

simple PDropTailQueue
    parameters:
       pkCapacity: numeric const;
    gates:
       in: in;
       out: out;
endsimple

simple Server
    gates:
       in: in;
       out: out;
endsimple

