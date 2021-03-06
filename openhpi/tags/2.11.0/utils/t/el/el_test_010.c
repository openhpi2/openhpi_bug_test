/*      -*- linux-c -*-
 *
 * (C) Copyright IBM Corp. 2004
 * Copyright (c) 2004 by Intel Corp.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  This
 * file and program are licensed under a BSD style license.  See
 * the Copying file included with the OpenHPI distribution for
 * full licensing terms.
 *
 * Authors:
 *      Christina Hernandez<hernanc@us.ibm.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>

#include <SaHpi.h>
#include <openhpi.h>
#include <oh_utils.h>
#include <el_utils.h>


#include "el_test.h"

/**
 * main: EL test
 *
 * This test verifies oh_el_prepend by reading an
 * existing EL from a file, then prepending 5 events to the EL.
 *
 * Return value: 0 on success, 1 on failure
 **/


int main(int argc, char **argv)
{
        oh_el *el;
        SaErrorT retc;
	int x;
	SaHpiEventT event;
	static char *data[5] = {
        	"Test data one",
		"Test data two",
		"Test data three",
		"Test data four",
		"Test data five"
	};


	/* test oh_el_prepend with existing EL*/
	el = oh_el_create(20);


        /* get EL from file (el) */
        retc = oh_el_map_from_file(el, "./elTest.data");
        if (retc != SA_OK) {
                err("ERROR: oh_el_map_from_file failed.");
                return 1;
        }

	/* add 5 more events to el */
	for(x=0;x<5;x++){
        	event.Source = 1;
        	event.EventType = SAHPI_ET_USER;
        	event.Timestamp = SAHPI_TIME_UNSPECIFIED;
        	event.Severity = SAHPI_DEBUG;
		strcpy((char *) &event.EventDataUnion.UserEvent.UserEventData.Data, data[x]);


        	retc = oh_el_prepend(el, &event, NULL, NULL);
        	if (retc != SA_OK) {
              	  err("ERROR: oh_el_append failed.");
               	  return 1;
        	}       
	}

        /* close el */
        retc = oh_el_close(el);
        if (retc != SA_OK) {
                err("ERROR: oh_el_close on el failed.");
                return 1;
        }


        return 0;
}

