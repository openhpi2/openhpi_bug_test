/*      -*- linux-c -*-
 *
 * (C) Copyright IBM Corp. 2003, 2004
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  This
 * file and program are licensed under a BSD style license.  See
 * the Copying file included with the OpenHPI distribution for
 * full licensing terms.
 *
 * Author(s):
 *      Steve Sherman <stevees@us.ibm.com>
 *      Renier Morales <renierm@users.sf.net>
 *      Thomas Kanngieser <thomas.kanngieser@fci.com>
 *      Chris Chia <cchia@users.sf.net.com>
 */

/******************************************************************************
 * DESCRIPTION:
 * Module contains functions to convert between HPI's SaHpiEntityPathT
 * structure and an OpenHPI canonical string. The canonical string is formed
 * by removing the "SAHPI_ENT_" prefix from the HPI types, and creating 
 * tuples for the entity types. Order of significance is inverted to make 
 * entity paths look more like Unix directory structure. It is also assumed 
 * that {ROOT,0} exists implicitly before all of these entries. For example:
 *
 * {SYSTEM_CHASSIS,2}{PROCESSOR_BOARD,0}
 *
 * FUNCTIONS:
 * string2entitypath - Coverts canonical entity path string to HPI entity path
 * entitypath2string - Coverts HPI entity path to canonical entity path string
 * ep_concat         - Concatenates two SaHpiEntityPathT together.
 *
 * NOTES:
 *   - SAHPI_ENT_ROOT is used to identify end element of an entity path
 *     fully populated entity path may not have a SAHPI_ENT_ROOT.
 *   - Duplicate names in SaHPIEntityTypeT enumeration aren't handled
 *     Names below won't be preserved across conversion calls:
 *       - IPMI_GROUP              - IPMI_GROUP + 0x90
 *       - IPMI_GROUP + 0xB0       - IPMI_GROUP + 0xD0
 *       - ROOT_VALUE              - SAFHPI_GROUP
 *****************************************************************************/
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <oh_utils.h>

static unsigned int index2entitytype(unsigned int i);
static int entitytype2index(unsigned int i);

static gchar *eshort_names[] = {
	"UNSPECIFIED",
	"OTHER",
	"UNKNOWN",
	"PROCESSOR",
	"DISK_BAY",
	"PERIPHERAL_BAY",
	"SYS_MGMNT_MODULE",
	"SYSTEM_BOARD",
	"MEMORY_MODULE",
	"PROCESSOR_MODULE",
	"POWER_SUPPLY",
	"ADD_IN_CARD",
	"FRONT_PANEL_BOARD",
	"BACK_PANEL_BOARD",
	"POWER_SYSTEM_BOARD",
	"DRIVE_BACKPLANE",
	"SYS_EXPANSION_BOARD",
	"OTHER_SYSTEM_BOARD",
	"PROCESSOR_BOARD",
	"POWER_UNIT",
	"POWER_MODULE",
	"POWER_MGMNT",
	"CHASSIS_BACK_PANEL_BOARD",
	"SYSTEM_CHASSIS",
	"SUB_CHASSIS",
	"OTHER_CHASSIS_BOARD",
	"DISK_DRIVE_BAY",
	"PERIPHERAL_BAY_2",
	"DEVICE_BAY",
	"COOLING_DEVICE",
	"COOLING_UNIT",
	"INTERCONNECT",
	"MEMORY_DEVICE",
	"SYS_MGMNT_SOFTWARE",
	"BIOS",
	"OPERATING_SYSTEM",
	"SYSTEM_BUS",
	"GROUP",
	"REMOTE",
	"EXTERNAL_ENVIRONMENT",
	"BATTERY",
	"CHASSIS_SPECIFIC",     /* Jumps to 144 */
	"BOARD_SET_SPECIFIC",   /* Jumps to 176 */
	"OEM_SYSINT_SPECIFIC",  /* Jumps to 208 */
	"ROOT",                 /* Jumps to 65535 and continues from there... */
	"RACK",
	"SUBRACK",
	"COMPACTPCI_CHASSIS",
	"ADVANCEDTCA_CHASSIS",
	"RACK_MOUNTED_SERVER",
        "SYSTEM_BLADE",
        "SWITCH",
        "SWITCH_BLADE",
	"SBC_BLADE",
	"IO_BLADE",
	"DISK_BLADE",
	"DISK_DRIVE",
	"FAN",
	"POWER_DISTRIBUTION_UNIT",
	"SPEC_PROC_BLADE",
	"IO_SUBBOARD",
	"SBC_SUBBOARD",
	"ALARM_MANAGER",
	"SHELF_MANAGER",
       	"DISPLAY_PANEL",
	"SUBBOARD_CARRIER_BLADE",
        "PHYSICAL_SLOT"
};

static unsigned int eshort_num_names = sizeof( eshort_names ) / sizeof( gchar * );

static unsigned int index2entitytype(unsigned int i)
{
        if(i <= ESHORTNAMES_BEFORE_JUMP) {
                return i;
        } else if(i == ESHORTNAMES_FIRST_JUMP) {
                return (unsigned int)SAHPI_ENT_CHASSIS_SPECIFIC;
        } else if(i == ESHORTNAMES_SECOND_JUMP) {
                return (unsigned int)SAHPI_ENT_BOARD_SET_SPECIFIC;
        } else if(i == ESHORTNAMES_THIRD_JUMP) {
                return (unsigned int)SAHPI_ENT_OEM_SYSINT_SPECIFIC;
        } else {
                assert(i >= ESHORTNAMES_LAST_JUMP);
                return (i - ESHORTNAMES_LAST_JUMP + (unsigned int)SAHPI_ENT_ROOT);
        }
}

static int entitytype2index(unsigned int i)
{
        if(i <= ESHORTNAMES_BEFORE_JUMP)
                return i;
        else if (i == (unsigned int)SAHPI_ENT_CHASSIS_SPECIFIC)
                return ESHORTNAMES_FIRST_JUMP;
        else if (i == (unsigned int)SAHPI_ENT_BOARD_SET_SPECIFIC)
                return ESHORTNAMES_SECOND_JUMP;
        else if (i == (unsigned int)SAHPI_ENT_OEM_SYSINT_SPECIFIC)
                return ESHORTNAMES_THIRD_JUMP;
        else if (i >= (unsigned int)SAHPI_ENT_ROOT &&
                 i-(unsigned int)SAHPI_ENT_ROOT < eshort_num_names-ESHORTNAMES_LAST_JUMP)
                return i-(unsigned int)SAHPI_ENT_ROOT+ESHORTNAMES_LAST_JUMP;

        return -1;
}

/**
 * string2entitypath
 * @epathstr: IN. Pointer to canonical entity path string
 * @epathptr: OUT. Pointer to HPI's entity path structure
 *
 * Converts an entity path canonical string into a
 * SaHpiEntityPathT structure.
 * 
 * Returns: 0 Successful return, -1 Error return
 */
int string2entitypath(const gchar *epathstr, SaHpiEntityPathT *epathptr)
{

	gchar  **epathdefs = NULL, **epathvalues = NULL;
	gchar  *gstr = NULL, *etype = NULL, *einstance = NULL, *endptr = NULL;
        gint rtncode = 0;
	guint   i, j, match, instance, num_valid_entities = 0;
        GSList *epath_list = NULL, *lst = NULL;
	SaHpiEntityT  *entityptr = NULL;
        gint num = 0;
        int is_numeric = 0;
        
	if (epathstr == NULL || epathstr[0] == '\0') {
		dbg("Input entity path string is NULL"); 
		return -1;
	}

        /* Split out {xxx,yyy} definition pairs */
       	gstr = g_strstrip(g_strdup(epathstr));
	if (gstr == NULL || gstr[0] == '\0') {
		dbg("Stripped entity path string is NULL"); 
		rtncode = -1;
		goto CLEANUP;
	}

	epathdefs = g_strsplit(gstr, EPATHSTRING_END_DELIMITER, -1);
	if (epathdefs == NULL) {
		dbg("Could not split entity path string.");
		rtncode = -1;
		goto CLEANUP;
        }

	/* Split out HPI entity type and instance strings */
	for (i=0; epathdefs[i] != NULL && epathdefs[i][0] != '\0'; i++) {

		epathdefs[i] = g_strstrip(epathdefs[i]);
		/* Check format - for starting delimiter and a comma */
		if ((epathdefs[i][0] != EPATHSTRING_START_DELIMITER_CHAR) || 
		    (strpbrk(epathdefs[i], EPATHSTRING_VALUE_DELIMITER) == NULL)) {
			dbg("Invalid entity path format.");
			rtncode = -1;
			goto CLEANUP;
		}

		epathvalues = g_strsplit(epathdefs[i],
                                         EPATHSTRING_VALUE_DELIMITER,
                                         ELEMENTS_IN_SaHpiEntityT);
		epathvalues[0] = g_strdelimit(epathvalues[0], EPATHSTRING_START_DELIMITER, ' ');

		etype = g_strstrip(epathvalues[0]);
		einstance = g_strstrip(epathvalues[1]);

		instance = strtol(einstance, &endptr, 10);
		if (endptr[0] != '\0') { 
			dbg("Invalid instance character"); 
			rtncode = -1; 
			goto CLEANUP;
                }

		for (match=0, j=0; j < eshort_num_names; j++) {
			if (!strcmp(eshort_names[j], etype)) {
				match = 1;
				break;
			}
		}
                
                is_numeric = 0;

		if (!match) { 
                        // check for numeric type
                        num = strtol(etype,&endptr, 0);

                        if (num <= 0 || endptr[0] != '\0') {
                                dbg("Invalid entity type string"); 
                                rtncode = -1; 
                                goto CLEANUP;
                        }
                        
                        is_numeric = 1;
		}

		/* Save entity path definitions; reverse order */
		if (num_valid_entities < SAHPI_MAX_ENTITY_PATH) {
			entityptr = (SaHpiEntityT *)g_malloc0(sizeof(*entityptr));
			if (entityptr == NULL) { 
				dbg("Out of memory"); 
				rtncode = -1; 
				goto CLEANUP;
			}

                        if (is_numeric)
                                entityptr->EntityType = num;
                        else
                                entityptr->EntityType = index2entitytype(j);

			entityptr->EntityLocation = instance;
			epath_list = g_slist_prepend(epath_list, (gpointer)entityptr);
		}

		num_valid_entities++; 
	}  
  
	/* Initialize and write HPI entity path structure */
	ep_init(epathptr);

	for (i = 0; epath_list != NULL; i++) {
                lst = epath_list;
                if (i < SAHPI_MAX_ENTITY_PATH) {
                        epathptr->Entry[i].EntityType = 
                                ((SaHpiEntityT *)(lst->data))->EntityType;
                        epathptr->Entry[i].EntityLocation = 
                                ((SaHpiEntityT *)(lst->data))->EntityLocation;
                }
                epath_list = g_slist_remove_link(epath_list,lst);
                g_free(lst->data);
		g_slist_free(lst);
	}

	if (num_valid_entities > SAHPI_MAX_ENTITY_PATH) {
		dbg("Too many entity defs");
		rtncode = -1;
	}

 CLEANUP:
	g_free(gstr);
	g_strfreev(epathdefs);
	g_strfreev(epathvalues);
	g_slist_free(epath_list);

	return(rtncode);
} /* End string2entitypath */

/**
 * entitypath2string
 * @epathptr: IN. Pointer to HPI's entity path structure
 * @epathstr: OUT. Pointer to canonical entity path string
 * @strsize: IN. Canonical string length
 *
 * Converts an entity path structure into its
 * canonical string version. 
 *
 * Returns: >0 Number of characters written to canonical entity path string, 
 * -1 Error return. -2 Entity path has invalid entity types.
 */
int entitypath2string(const SaHpiEntityPathT *epathptr, gchar *epathstr, const gint strsize)
{
     
	gchar  *instance_str, *catstr, *tmpstr;
	gint   err, i, strcount = 0, rtncode = 0;
        int tidx;
        gchar *type_str;
        gchar type_str_buffer[20];

	if (epathstr == NULL || strsize <= 0) { 
		dbg("Null string or invalid string size"); 
		return -1;
	}

        if (epathptr == NULL) {
                *epathstr = '\0';
                return 0;
        }

        /*if (validate_ep(epathptr)) {
                dbg("Entity path contains invalid types. Unable to convert to string.");
                return -2;
        }*/

	instance_str = (gchar *)g_malloc0(OH_MAX_LOCATION_DIGITS + 1);
	tmpstr = (gchar *)g_malloc0(strsize);
	if (instance_str == NULL || tmpstr == NULL) { 
		dbg("Out of memory"); 
		rtncode = -1; 
		goto CLEANUP;
	}
        
        /* Find last element of structure. Disregard ROOT element
         * and count as last in entity path.
         */
        for (i = 0; i < SAHPI_MAX_ENTITY_PATH; i++) {
                if (epathptr->Entry[i].EntityType == SAHPI_ENT_ROOT) {                            
                            break;
                }
        }

        /* Parse entity path into a string */
	for (i--; i >= 0; i--) {
                guint num_digits, work_instance_num;
                
		/* Validate and convert data */
                work_instance_num = epathptr->Entry[i].EntityLocation;
                for (num_digits = 1; (work_instance_num = work_instance_num/10) > 0; num_digits++);
		
		if (num_digits > OH_MAX_LOCATION_DIGITS) { 
                        dbg("Instance value too big");
                        rtncode = -1; 
			goto CLEANUP;
		}
                memset(instance_str, 0, OH_MAX_LOCATION_DIGITS + 1);
                err = snprintf(instance_str, OH_MAX_LOCATION_DIGITS + 1,
                               "%d", epathptr->Entry[i].EntityLocation);

                /* Find string for current entity type */
                tidx = entitytype2index(epathptr->Entry[i].EntityType);
                if ( tidx >= 0 )
                        type_str = eshort_names[tidx];
                else { /* String for entity type not found. */
                        err = snprintf(type_str_buffer, 20, "%d",
                                       epathptr->Entry[i].EntityType);
                        type_str = type_str_buffer;
                }                
                
		strcount = strcount + 
			strlen(EPATHSTRING_START_DELIMITER) + 
			strlen(type_str) + 
			strlen(EPATHSTRING_VALUE_DELIMITER) + 
			strlen(instance_str) + 
			strlen(EPATHSTRING_END_DELIMITER);

		if (strcount > strsize - 1) {
			dbg("Not enough space allocated for string");
			rtncode = -1;
			goto CLEANUP;
		}

		catstr = g_strconcat(EPATHSTRING_START_DELIMITER,
				     type_str,
				     EPATHSTRING_VALUE_DELIMITER,
				     instance_str, 
				     EPATHSTRING_END_DELIMITER, 
				     NULL);

		strcat(tmpstr, catstr);
		g_free(catstr);
	}
        rtncode = strcount;
	/* Write string */
	memset(epathstr, 0 , strsize);
	strcpy(epathstr, tmpstr);

 CLEANUP:
	g_free(instance_str);
	g_free(tmpstr);

	return(rtncode);
} /* End entitypath2string */

/**
 * ep_init
 * @ep: Pointer to SaHpiEntityPathT structure to initialize.
 *
 * Initializes the given entity path to all {ROOT,0} elements.
 *
 * Returns: void.
 **/
 void ep_init(SaHpiEntityPathT *ep) {
	 int i;

         if (!ep) return;
         
         for (i = 0; i < SAHPI_MAX_ENTITY_PATH; i++) {
                 ep->Entry[i].EntityType = SAHPI_ENT_ROOT;
                 ep->Entry[i].EntityLocation = 0;
         }
 }

/**
 * ep_concat
 * @dest: IN,OUT Left-hand entity path. Gets appended with @append.
 * @append: IN Right-hand entity path. Pointer entity path to be appended.
 *
 * Concatenate two entity path structures (SaHpiEntityPathT).
 * @dest is assumed to be the least significant entity path in the operation.
 * append will be truncated into @dest, if it doesn't fit completely in the space
 * that @dest has available relative to SAHPI_MAX_ENTITY_PATH.
 *
 * Returns: 0 on Success, -1 if dest is NULL.
 **/
int ep_concat(SaHpiEntityPathT *dest, const SaHpiEntityPathT *append)
{
        unsigned int i, j;

        if (!dest) return -1;
        if (!append) return 0;

        for (i = 0; i < SAHPI_MAX_ENTITY_PATH; i++) {
                if (dest->Entry[i].EntityType == SAHPI_ENT_ROOT) {
                        break;
                }
        }

        for (j = 0; i < SAHPI_MAX_ENTITY_PATH; i++) {                
                dest->Entry[i].EntityLocation = append->Entry[j].EntityLocation;
                dest->Entry[i].EntityType = append->Entry[j].EntityType;
                if (append->Entry[j].EntityType == SAHPI_ENT_ROOT) break;
                j++;
        }

        return 0;
}

/**
 * validate_ep
 * @ep: Pointer to an SaHpiEntityPathT structure.
 *
 * This will check the entity path to make sure it does not contain
 * any invalid entity types in it up to the root element if it has it.
 *
 * Returns: 0 if entity path is valid, -1 otherwise.
 **/
int validate_ep(const SaHpiEntityPathT *ep)
{
        int check = 0;
	int i;

        for (i = 0; i < SAHPI_MAX_ENTITY_PATH; i++) {
                if (   entitytype2index(ep->Entry[i].EntityType) < 0
                    && ep->Entry[i].EntityType > 255) {
                        check = -1;
                        break;
                } else if (ep->Entry[i].EntityType == SAHPI_ENT_ROOT) break;
        }

        return check;
}

/**
 * set_ep_instance
 * @ep: Pointer to entity path to work on
 * @et: entity type to look for
 * @ei: entity instance to set when entity type is found
 *
 * Set an instance number in the entity path given at the first
 * position (from least significant to most) the specified entity type is found.
 *
 * Returns: 0 on Success, -1 if the entity type was not found.
 **/
int set_ep_instance(SaHpiEntityPathT *ep, SaHpiEntityTypeT et, SaHpiEntityLocationT ei)
{
        int i;
        int retval = -1;

	if (!ep) return retval;

        for (i = 0; i < SAHPI_MAX_ENTITY_PATH; i++) {
                if (ep->Entry[i].EntityType == et) {
                        ep->Entry[i].EntityLocation = ei;
                        retval = 0;
                        break;                        
                } else if (ep->Entry[i].EntityType == SAHPI_ENT_ROOT) {
                        break;
                }
        }
        return retval;
}

/**
 * ep_cmp
 * @ep1: Pointer to entity path struct
 * @ep2: Pointer to entity path struct
 *
 * Compare two entity paths up to their root element.
 * To be equal, they must have the same number of elements and each element
 * (type and instance pair) must be equal to the corresponding element
 * in the other entity path.
 *
 * Returns: 0 if equal, -1 if not.
 **/
int ep_cmp(const SaHpiEntityPathT *ep1, const SaHpiEntityPathT *ep2)
{
        unsigned int i, j;
        
        if ((!ep1) || (!ep2)) {
                dbg("ep_cmp error - null pointer\n");
                return -1;
        }

        for ( i = 0; i < SAHPI_MAX_ENTITY_PATH; i++ ) {
                if (ep1->Entry[i].EntityType == SAHPI_ENT_ROOT) {
                        i++;
                        break;                                
                }
        }

        for ( j = 0; j < SAHPI_MAX_ENTITY_PATH; j++ ) {
                if (ep2->Entry[j].EntityType == SAHPI_ENT_ROOT) {
                        j++;
                        break;
                }
        }

        if ( i != j ) {
                /* dbg("ep1 element count %d != ep2 %d\n", i, j); */
                return -1;
        }

        for ( i = 0; i < j; i++ ) {
                if (ep1->Entry[i].EntityType != ep2->Entry[i].EntityType ||
                    ep1->Entry[i].EntityLocation != ep2->Entry[i].EntityLocation) {
                        /* dbg("Entity element %d: EP1 {%d,%d} != EP2 {%d,%d}", i, 
                            ep1->Entry[i].EntityType,
                            ep1->Entry[i].EntityLocation,
                            ep2->Entry[i].EntityType,
                            ep2->Entry[i].EntityLocation); */
                        return -1;
                }
        }
        
        return 0;
}

/**
 * print_ep
 * @ep: Pointer to entity path stucture.
 *
 * Print the string form of an entity path structure.
 *
 * Returns: 0 on Success, -1 on Failure.
 **/
int print_ep(const SaHpiEntityPathT *ep)
{
        const int buffer_size = 512;
        gchar epstr[buffer_size];
        int len;
	
        memset(epstr,0,buffer_size);

        if (!ep) {
		dbg("Error: null pointer \n");
                return -1;
        }
        
	len = entitypath2string(ep, epstr, sizeof(epstr));

        if (len < 0) return -1;
        /* Entity path with a sole root element will be an empty string */

	printf("Entity Path=\"%s\"\n", epstr);

        return 0;
}
