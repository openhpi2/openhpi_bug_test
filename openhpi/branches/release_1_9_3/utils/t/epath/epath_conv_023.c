/* -*- linux-c -*-
 * 
 * (C) Copyright IBM Corp. 2004
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  This
 * file and program are licensed under a BSD style license.  See
 * the Copying file included with the OpenHPI distribution for
 * full licensing terms.
 */

/******************************************************************* 
 * WARNING! This file is auto-magically generated by:
 *          gen_tests.pl.
 *          Do not change this file manually. Update script instead
 *******************************************************************/

#include <string.h>

#include <SaHpi.h>
#include <oh_utils.h>

/**
 * main: 
 * epathstr -> epath test
 * 
 * Test if an entity path string is converted properly into an entity path.
 **/
int main(int argc, char **argv) 
{
        char *test_string = "{ADD_IN_CARD,16}{POWER_MGMNT,6}";
        oh_big_textbuffer bigbuf;
	SaErrorT err;
        SaHpiEntityPathT ep;
        
	err = oh_encode_entitypath(test_string, &ep);
	if (err) {
		printf("  Error! Testcase failed. Line=%d\n", __LINE__);
		printf("  Received error=%s\n", oh_lookup_error(err));
		return -1;
	}
         
        if (ep.Entry[0].EntityType != SAHPI_ENT_POWER_MGMNT) {
	    printf("  Error! Testcase failed. Line=%d\n", __LINE__);
	    printf("  Received=%d; Expected=%d\n", ep.Entry[0].EntityType, SAHPI_ENT_POWER_MGMNT);
	    return -1;
	}
                
        if (ep.Entry[0].EntityLocation != 6) {
	    printf("  Error! Testcase failed. Line=%d\n", __LINE__);
	    printf("  Received=%d; Expected=%d\n", ep.Entry[0].EntityLocation, 6);
	    return -1;
	}
        
        if (ep.Entry[1].EntityType != SAHPI_ENT_ADD_IN_CARD) {
	    printf("  Error! Testcase failed. Line=%d\n", __LINE__);
	    printf("  Received=%d; Expected=%d\n", ep.Entry[1].EntityType, SAHPI_ENT_ADD_IN_CARD);
	    return -1;
	}
        
        if (ep.Entry[1].EntityLocation != 16) {
	    printf("  Error! Testcase failed. Line=%d\n", __LINE__);
	    printf("  Received=%d; Expected=%d\n", ep.Entry[1].EntityLocation, 16);
	    return -1;
	}

	oh_init_bigtext(&bigbuf);
	err = oh_decode_entitypath(&ep, &bigbuf);
	if (err) {
		printf("  Error! Testcase failed. Line=%d\n", __LINE__);
		printf("  Received error=%s\n", oh_lookup_error(err));
		return -1;
	}

	if (strcmp(bigbuf.Data, test_string)) {
		printf("  Error! Testcase failed. Line=%d\n", __LINE__);
		printf("  Received Entity Path=%s.\n", bigbuf.Data);
		return -1;
	}

        return 0;
}
