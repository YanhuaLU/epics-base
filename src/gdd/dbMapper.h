#ifndef DB_MAPPER_H
#define DB_MAPPER_H

/*
 * Author: Jim Kowalkowski
 * Date: 2/96
 *
 * $Id$
 *
 * $Log$
 * Revision 1.2  1997/04/10 19:59:25  jhill
 * api changes
 *
 * Revision 1.1  1996/06/25 19:11:36  jbk
 * new in EPICS base
 *
 *
 * *Revision 1.1  1996/05/31 13:15:24  jbk
 * *add new stuff
 *
 */

#include "shareLib.h"
#include "aitTypes.h"
#include "gdd.h"

extern "C" {
#include "db_access.h"
#include "cadef.h"
}

class gddApplicationTypeTable;

// Function proto to convert from a db_struct to a gdd.  The gdd will
// reference the data in the db_struct if the db_struct points to an
// array.  The second argument is the number of elements if db_struct
// represents an array, or zero if the db_struct is a scaler.
typedef gdd* (*to_gdd)(void* db_struct, aitIndex element_count);

// Function proto to convert from a gdd to a dbr structure, returns the
// number of elements that the value field of db_struct points to if the
// gdd points to an array.  The db_struct will reference the data
// contained within the gdd (which is probably also referenced from the user).
typedef int (*to_dbr)(void* db_struct, gdd*);

struct gddDbrMapFuncTable {
	to_gdd	conv_gdd;
	to_dbr	conv_dbr;
};
typedef struct gddDbrMapFuncTable gddDbrMapFuncTable;

struct gddDbrToAitTable {
	aitEnum		type;
	aitUint16	app;
	char*		app_name;
};
typedef struct gddDbrToAitTable gddDbrToAitTable;

epicsShareExtern gddDbrToAitTable gddDbrToAit[];
epicsShareExtern const chtype gddAitToDbr[];
epicsShareExtern gddDbrMapFuncTable gddMapDbr[];
epicsShareExtern void gddMakeMapDBR(gddApplicationTypeTable& tt);
epicsShareExtern void gddMakeMapDBR(gddApplicationTypeTable* tt);

#endif

