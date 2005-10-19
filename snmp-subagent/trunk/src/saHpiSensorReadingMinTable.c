/*
 * (C) Copyright IBM Corp. 2005
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  This
 * file and program are licensed under a BSD style license.  See
 * the Copying file included with the OpenHPI distribution for
 * full licensing terms.
 *
 * Authors:
 *   David Judkovics  <djudkovi@us.ibm.com>
 *   Daniel de Araujo <ddearauj@us.ibm.com>
 *
 * Note: this file originally auto-generated by mib2c using
 *       : mib2c.array-user.conf,v 5.18.2.2 2004/02/09 18:21:47 rstory Exp $
 *
 * $Id$
 *
 *
 * For help understanding NET-SNMP in general, please check the 
 *     documentation and FAQ at:
 *
 *     http://www.net-snmp.org/
 *
 *
 * For help understanding this code, the agent and how it processes
 *     requests, please check the following references.
 *
 *     http://www.net-snmp.org/tutorial-5/
 *
 *
 * You can also join the #net-snmp channel on irc.freenode.net
 *     and ask for help there.
 *
 *
 * And if all else fails, send a detailed message to the developers
 *     describing the problem you are having to:
 *
 *    net-snmp-coders@lists.sourceforge.net
 *
 *
 * Yes, there is lots of code here that you might not use. But it is much
 * easier to remove code than to add it!
 */
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

#include <net-snmp/library/snmp_assert.h>

#include <SaHpi.h>
#include "saHpiSensorReadingMinTable.h"
#include <hpiSubagent.h>
#include <hpiCheckIndice.h>
#include <session_info.h>

#include <oh_utils.h>


static     netsnmp_handler_registration *my_handler = NULL;
static     netsnmp_table_array_callbacks cb;

oid saHpiSensorReadingMinTable_oid[] = { saHpiSensorReadingMinTable_TABLE_OID};
size_t saHpiSensorReadingMinTable_oid_len = OID_LENGTH(saHpiSensorReadingMinTable_oid);

/************************************************************/
/************************************************************/
/************************************************************/
/************************************************************/

/*
 * SaErrorT populate_ctrl_text()
 */
SaErrorT populate_sensor_min(SaHpiSessionIdT sessionid, 
			     SaHpiRdrT *rdr_entry,
			     SaHpiRptEntryT *rpt_entry)
{

	DEBUGMSGTL ((AGENT, "populate_sensor_max, called\n"));

	SaErrorT rv = SA_OK;
        int new_row = MIB_FALSE;

	oid sensor_min_oid[SENSOR_READING_MIN_INDEX_NR];
	netsnmp_index sensor_min_index;
	saHpiSensorReadingMinTable_context *sensor_min_context;

	/* check for NULL pointers */
	if (!rdr_entry) {
		DEBUGMSGTL ((AGENT, 
			     "ERROR: populate_ctrl_text() passed NULL rdr_entry pointer\n"));
		return AGENT_ERR_INTERNAL_ERROR;
	}
	if (!rpt_entry) {
		DEBUGMSGTL ((AGENT, 
			     "ERROR: populate_ctrl_text() passed NULL rdr_entry pointer\n"));
		return AGENT_ERR_INTERNAL_ERROR;
	}

	/* BUILD oid for new row */
	/* assign the number of indices */
	sensor_min_index.len = SENSOR_READING_MIN_INDEX_NR;
	/** Index saHpiDomainId is external */
	sensor_min_oid[0] = get_domain_id(sessionid);
	/** Index saHpiResourceId is external */
	sensor_min_oid[1] = rpt_entry->ResourceId;
	/** Index saHpiResourceIsHistorical is external */
	sensor_min_oid[2] = MIB_FALSE;
	/** Index saHpiSensorNum */
	sensor_min_oid[3] = rdr_entry->RdrTypeUnion.SensorRec.Num;
	/* assign the indices to the index */
	sensor_min_index.oids = (oid *) & sensor_min_oid;

	/* See if Row exists. */
	sensor_min_context = NULL;
	sensor_min_context = CONTAINER_FIND(cb.container, &sensor_min_index);

	if (!sensor_min_context) {
		// New entry. Add it
		sensor_min_context = 
		saHpiSensorReadingMinTable_create_row(&sensor_min_index);
                new_row = MIB_TRUE;
	}
	if (!sensor_min_context) {
		snmp_log (LOG_ERR, "Not enough memory for a Max row!");
		return AGENT_ERR_INTERNAL_ERROR;
	}

	/** TruthValue = ASN_INTEGER */
	sensor_min_context->saHpiSensorReadingMinIsSupported =
	(rdr_entry->RdrTypeUnion.SensorRec.DataFormat.Range.Min.IsSupported
	 == SAHPI_TRUE) ? MIB_TRUE : MIB_FALSE;

	/** SaHpiSensorReadingType = ASN_INTEGER */
	sensor_min_context->saHpiSensorReadingMinType = 
	rdr_entry->RdrTypeUnion.SensorRec.DataFormat.Range.Min.Type + 1;

	/** SaHpiSensorReadingValue = ASN_OCTET_STR */
	sensor_min_context->saHpiSensorReadingMinValue_len =
	set_sensor_reading_value(
				&rdr_entry->RdrTypeUnion.SensorRec.DataFormat.Range.Min,
				sensor_min_context->saHpiSensorReadingMinValue);

	if (new_row == MIB_TRUE)
                CONTAINER_INSERT (cb.container, sensor_min_context);

	return rv;
}

/**
 * 
 * @domainId
 * @resourceId
 * 
 * @return 
 */
SaErrorT clear_sensor_min(SaHpiDomainIdT domainId, SaHpiResourceIdT resourceId)

{
        SaErrorT rv = SA_OK;
        netsnmp_index *row_idx;
        saHpiSensorReadingMinTable_context *sen_min_ctx;

	DEBUGMSGTL ((AGENT, "clear_sensor_min, called\n"));	
	DEBUGMSGTL ((AGENT, "           domainId   [%d]\n", domainId));	
	DEBUGMSGTL ((AGENT, "           resourceId [%d]\n", resourceId));

        row_idx = CONTAINER_FIRST(cb.container);
        if (row_idx) //At least one entry was found.
        {
                do {
                        /* based on the found row_idx get the pointer   */
                        /* to its context (row data)                    */
                        sen_min_ctx = CONTAINER_FIND(cb.container, row_idx);

                        /* before we delete the context we should get the  */
                        /* next row (context) if any before we delete this */ 
                        /* one.                                            */
                        row_idx = CONTAINER_NEXT(cb.container, row_idx);

                        if ((sen_min_ctx->index.oids[saHpiSenMinDomainId_INDEX] ==
                             domainId) &&

                            (sen_min_ctx->index.oids[saHpiSenMinResourceId_INDEX] ==
                             resourceId)) {

                                /* all conditions met remove row */
                                CONTAINER_REMOVE (cb.container, sen_min_ctx);
                                saHpiSensorReadingMinTable_delete_row (sen_min_ctx);
                                DEBUGMSGTL ((AGENT, "clear_sensor_min: "
                                                    "found row: removing\n"));

                        }

                } while (row_idx);
        } 

        return rv;
}


/************************************************************/
/************************************************************/
/************************************************************/

/************************************************************
 * keep binary tree to find context by name
 */
static int saHpiSensorReadingMinTable_cmp( const void *lhs, const void *rhs );

/************************************************************
 * compare two context pointers here. Return -1 if lhs < rhs,
 * 0 if lhs == rhs, and 1 if lhs > rhs.
 */
static int
saHpiSensorReadingMinTable_cmp( const void *lhs, const void *rhs )
{
	saHpiSensorReadingMinTable_context *context_l =
	(saHpiSensorReadingMinTable_context *)lhs;
	saHpiSensorReadingMinTable_context *context_r =
	(saHpiSensorReadingMinTable_context *)rhs;

	/*
	 * check primary key, then secondary. Add your own code if
	 * there are more than 2 indexes
	 */
	DEBUGMSGTL ((AGENT, "saHpiSensorReadingMinTable_cmp, called\n"));

	/* check for NULL pointers */
	if (lhs == NULL || rhs == NULL ) {
		DEBUGMSGTL((AGENT,"saHpiSensorReadingMinTable_cmp() NULL pointer ERROR\n" ));
		return 0;
	}
	/* CHECK FIRST INDEX,  saHpiDomainId */
	if ( context_l->index.oids[0] < context_r->index.oids[0])
		return -1;

	if ( context_l->index.oids[0] > context_r->index.oids[0])
		return 1;

	if ( context_l->index.oids[0] == context_r->index.oids[0]) {
		/* If saHpiDomainId index is equal sort by second index */
		/* CHECK SECOND INDEX,  saHpiResourceEntryId */
		if ( context_l->index.oids[1] < context_r->index.oids[1])
			return -1;

		if ( context_l->index.oids[1] > context_r->index.oids[1])
			return 1;

		if ( context_l->index.oids[1] == context_r->index.oids[1]) {
			/* If saHpiResourceEntryId index is equal sort by third index */
			/* CHECK THIRD INDEX,  saHpiResourceIsHistorical */
			if ( context_l->index.oids[2] < context_r->index.oids[2])
				return -1;

			if ( context_l->index.oids[2] > context_r->index.oids[2])
				return 1;

			if ( context_l->index.oids[2] == context_r->index.oids[2]) {
				/* If saHpiResourceIsHistorical index is equal sort by forth index */
				/* CHECK FORTH INDEX,  saHpiSensorNum */
				if ( context_l->index.oids[3] < context_r->index.oids[3])
					return -1;

				if ( context_l->index.oids[3] > context_r->index.oids[3])
					return 1;

				if ( context_l->index.oids[3] == context_r->index.oids[3])
					return 0;
			}
		}
	}

	return 0;
}


/************************************************************
 * Initializes the saHpiSensorReadingMinTable module
 */
void
init_saHpiSensorReadingMinTable(void)
{
	initialize_table_saHpiSensorReadingMinTable();

}

/************************************************************
 * the *_row_copy routine
 */
static int saHpiSensorReadingMinTable_row_copy(saHpiSensorReadingMinTable_context * dst,
					       saHpiSensorReadingMinTable_context * src)
{
	if (!dst||!src)
		return 1;

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingMinTable_row_copy, called\n"));

	/*
	 * copy index, if provided
	 */
	if (dst->index.oids)
		free(dst->index.oids);
	if (snmp_clone_mem( (void*)&dst->index.oids, src->index.oids,
			    src->index.len * sizeof(oid) )) {
		dst->index.oids = NULL;
		return 1;
	}
	dst->index.len = src->index.len;


	/*
	 * copy components into the context structure
	 */
	/** TODO: add code for external index(s)! */
	dst->saHpiSensorReadingMinIsSupported = src->saHpiSensorReadingMinIsSupported;

	dst->saHpiSensorReadingMinType = src->saHpiSensorReadingMinType;

	memcpy( dst->saHpiSensorReadingMinValue, src->saHpiSensorReadingMinValue, src->saHpiSensorReadingMinValue_len );
	dst->saHpiSensorReadingMinValue_len = src->saHpiSensorReadingMinValue_len;

	return 0;
}


/**
 * the *_extract_index routine
 *
 * This routine is called when a set request is received for an index
 * that was not found in the table container. Here, we parse the oid
 * in the the individual index components and copy those indexes to the
 * context. Then we make sure the indexes for the new row are valid.
 */
int
saHpiSensorReadingMinTable_extract_index( saHpiSensorReadingMinTable_context * ctx, netsnmp_index * hdr )
{
	/*
	 * temporary local storage for extracting oid index
	 *
	 * extract index uses varbinds (netsnmp_variable_list) to parse
	 * the index OID into the individual components for each index part.
	 */
	/** TODO: add storage for external index(s)! */
	netsnmp_variable_list var_saHpiDomainId;
	netsnmp_variable_list var_saHpiResourceId;
	netsnmp_variable_list var_saHpiResourceIsHistorical;
	netsnmp_variable_list var_saHpiSensorNum;
	int err;

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingMinTable_extract_index, called\n"));

	/*
	 * copy index, if provided
	 */
	if (hdr) {
		netsnmp_assert(ctx->index.oids == NULL);
		if (snmp_clone_mem( (void*)&ctx->index.oids, hdr->oids,
				    hdr->len * sizeof(oid) )) {
			return -1;
		}
		ctx->index.len = hdr->len;
	}

	/*
	 * initialize variable that will hold each component of the index.
	 * If there are multiple indexes for the table, the variable_lists
	 * need to be linked together, in order.
	 */
	/** TODO: add code for external index(s)! */
	memset( &var_saHpiDomainId, 0x00, sizeof(var_saHpiDomainId) );
	var_saHpiDomainId.type = ASN_UNSIGNED; /* type hint for parse_oid_indexes */
	/** TODO: link this index to the next, or NULL for the last one */
	var_saHpiDomainId.next_variable = &var_saHpiResourceId;

	memset( &var_saHpiResourceId, 0x00, sizeof(var_saHpiResourceId) );
	var_saHpiResourceId.type = ASN_UNSIGNED; /* type hint for parse_oid_indexes */
	/** TODO: link this index to the next, or NULL for the last one */
	var_saHpiResourceId.next_variable = &var_saHpiResourceIsHistorical;

	memset( &var_saHpiResourceIsHistorical, 0x00, sizeof(var_saHpiResourceIsHistorical) );
	var_saHpiResourceIsHistorical.type = ASN_INTEGER; /* type hint for parse_oid_indexes */
	/** TODO: link this index to the next, or NULL for the last one */
	var_saHpiResourceIsHistorical.next_variable = &var_saHpiSensorNum;

	memset( &var_saHpiSensorNum, 0x00, sizeof(var_saHpiSensorNum) );
	var_saHpiSensorNum.type = ASN_UNSIGNED;	/* type hint for parse_oid_indexes */
	/** TODO: link this index to the next, or NULL for the last one */
	var_saHpiSensorNum.next_variable = NULL;


	/*
	 * parse the oid into the individual index components
	 */
	err = parse_oid_indexes( hdr->oids, hdr->len, &var_saHpiDomainId );
	if (err == SNMP_ERR_NOERROR) {
		/*
		 * copy index components into the context structure
		 */
		/** skipping external index saHpiDomainId */

		/** skipping external index saHpiResourceId */

		/** skipping external index saHpiResourceIsHistorical */

		/** skipping external index saHpiSensorNum */

		err = saHpiDomainId_check_index(
					       *var_saHpiDomainId.val.integer);
		err = saHpiResourceEntryId_check_index(
						      *var_saHpiResourceId.val.integer);  
		err = saHpiResourceIsHistorical_check_index(
							   *var_saHpiResourceIsHistorical.val.integer);
		err = saHpiSensorNum_check_index(
						*var_saHpiSensorNum.val.integer);
	}

	/*
	 * parsing may have allocated memory. free it.
	 */
	snmp_reset_var_buffers( &var_saHpiDomainId );

	return err;
}

/************************************************************
 * the *_can_activate routine is called
 * when a row is changed to determine if all the values
 * set are consistent with the row's rules for a row status
 * of ACTIVE.
 *
 * return 1 if the row could be ACTIVE
 * return 0 if the row is not ready for the ACTIVE state
 */
int saHpiSensorReadingMinTable_can_activate(saHpiSensorReadingMinTable_context *undo_ctx,
					    saHpiSensorReadingMinTable_context *row_ctx,
					    netsnmp_request_group * rg)
{

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingMinTable_can_activate, called\n"));

	/*
	 * TODO: check for activation requirements here
	 */


	/*
	 * be optimistic.
	 */
	return 1;
}

/************************************************************
 * the *_can_deactivate routine is called when a row that is
 * currently ACTIVE is set to a state other than ACTIVE. If
 * there are conditions in which a row should not be allowed
 * to transition out of the ACTIVE state (such as the row being
 * referred to by another row or table), check for them here.
 *
 * return 1 if the row can be set to a non-ACTIVE state
 * return 0 if the row must remain in the ACTIVE state
 */
int saHpiSensorReadingMinTable_can_deactivate(saHpiSensorReadingMinTable_context *undo_ctx,
					      saHpiSensorReadingMinTable_context *row_ctx,
					      netsnmp_request_group * rg)
{

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingMinTable_can_deactivate, called\n"));

	/*
	 * TODO: check for deactivation requirements here
	 */
	return 1;
}

/************************************************************
 * the *_can_delete routine is called to determine if a row
 * can be deleted.
 *
 * return 1 if the row can be deleted
 * return 0 if the row cannot be deleted
 */
int saHpiSensorReadingMinTable_can_delete(saHpiSensorReadingMinTable_context *undo_ctx,
					  saHpiSensorReadingMinTable_context *row_ctx,
					  netsnmp_request_group * rg)
{

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingMinTable_can_delete, called\n"));

	/*
	 * probably shouldn't delete a row that we can't
	 * deactivate.
	 */
	if (saHpiSensorReadingMinTable_can_deactivate(undo_ctx,row_ctx,rg) != 1)
		return 0;

	/*
	 * TODO: check for other deletion requirements here
	 */
	return 1;
}

/************************************************************
 * the *_create_row routine is called by the table handler
 * to create a new row for a given index. If you need more
 * information (such as column values) to make a decision
 * on creating rows, you must create an initial row here
 * (to hold the column values), and you can examine the
 * situation in more detail in the *_set_reserve1 or later
 * states of set processing. Simple check for a NULL undo_ctx
 * in those states and do detailed creation checking there.
 *
 * returns a newly allocated saHpiSensorReadingMinTable_context
 *   structure if the specified indexes are not illegal
 * returns NULL for errors or illegal index values.
 */
saHpiSensorReadingMinTable_context *
saHpiSensorReadingMinTable_create_row( netsnmp_index* hdr)
{
	saHpiSensorReadingMinTable_context * ctx =
	SNMP_MALLOC_TYPEDEF(saHpiSensorReadingMinTable_context);

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingMinTable_create_row, called\n"));

	if (!ctx)
		return NULL;

	/*
	 * TODO: check indexes, if necessary.
	 */
	if (saHpiSensorReadingMinTable_extract_index( ctx, hdr )) {
		free(ctx->index.oids);
		free(ctx);
		return NULL;
	}

	/* netsnmp_mutex_init(ctx->lock);
	   netsnmp_mutex_lock(ctx->lock); */

	/*
	 * TODO: initialize any default values here. This is also
	 * first place you really should allocate any memory for
	 * yourself to use.  If you allocated memory earlier,
	 * make sure you free it for earlier error cases!
	 */
	/**
	*/

	return ctx;
}

/************************************************************
 * the *_duplicate row routine
 */
saHpiSensorReadingMinTable_context *
saHpiSensorReadingMinTable_duplicate_row( saHpiSensorReadingMinTable_context * row_ctx)
{
	saHpiSensorReadingMinTable_context * dup;

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingMinTable_duplicate_row, called\n"));

	if (!row_ctx)
		return NULL;

	dup = SNMP_MALLOC_TYPEDEF(saHpiSensorReadingMinTable_context);
	if (!dup)
		return NULL;

	if (saHpiSensorReadingMinTable_row_copy(dup,row_ctx)) {
		free(dup);
		dup = NULL;
	}

	return dup;
}

/************************************************************
 * the *_delete_row method is called to delete a row.
 */
netsnmp_index * saHpiSensorReadingMinTable_delete_row( saHpiSensorReadingMinTable_context * ctx )
{
	/* netsnmp_mutex_destroy(ctx->lock); */

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingMinTable_delete_row, called\n"));

	if (ctx->index.oids)
		free(ctx->index.oids);

	/*
	 * TODO: release any memory you allocated here...
	 */

	/*
	 * release header
	 */
	free( ctx );

	return NULL;
}


/************************************************************
 * RESERVE is used to check the syntax of all the variables
 * provided, that the values being set are sensible and consistent,
 * and to allocate any resources required for performing the SET.
 * After this stage, the expectation is that the set ought to
 * succeed, though this is not guaranteed. (In fact, with the UCD
 * agent, this is done in two passes - RESERVE1, and
 * RESERVE2, to allow for dependancies between variables).
 *
 * BEFORE calling this routine, the agent will call duplicate_row
 * to create a copy of the row (unless this is a new row; i.e.
 * row_created == 1).
 *
 * next state -> SET_RESERVE2 || SET_FREE
 */
void saHpiSensorReadingMinTable_set_reserve1( netsnmp_request_group *rg )
{
//    saHpiSensorReadingMinTable_context *row_ctx =
//            (saHpiSensorReadingMinTable_context *)rg->existing_row;
//    saHpiSensorReadingMinTable_context *undo_ctx =
//            (saHpiSensorReadingMinTable_context *)rg->undo_info;
	netsnmp_variable_list *var;
	netsnmp_request_group_item *current;
	int rc;

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingMinTable_set_reserve1, called\n"));

	/*
	 * TODO: loop through columns, check syntax and lengths. For
	 * columns which have no dependencies, you could also move
	 * the value/range checking here to attempt to catch error
	 * cases as early as possible.
	 */
	for ( current = rg->list; current; current = current->next ) {

		var = current->ri->requestvb;
		rc = SNMP_ERR_NOERROR;

		switch (current->tri->colnum) {

		default: /** We shouldn't get here */
			rc = SNMP_ERR_GENERR;
			snmp_log(LOG_ERR, "unknown column in "
				 "saHpiSensorReadingMinTable_set_reserve1\n");
		}

		if (rc)
			netsnmp_request_set_error( current->ri, rc );
		rg->status = SNMP_MAX( rg->status, current->ri->status );
	}

	/*
	 * done with all the columns. Could check row related
	 * requirements here.
	 */
}

void saHpiSensorReadingMinTable_set_reserve2( netsnmp_request_group *rg )
{
//    saHpiSensorReadingMinTable_context *row_ctx = (saHpiSensorReadingMinTable_context *)rg->existing_row;
//    saHpiSensorReadingMinTable_context *undo_ctx = (saHpiSensorReadingMinTable_context *)rg->undo_info;
	netsnmp_request_group_item *current;
	netsnmp_variable_list *var;
	int rc;

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingMinTable_set_reserve2, called\n"));

	rg->rg_void = rg->list->ri;

	/*
	 * TODO: loop through columns, check for valid
	 * values and any range constraints.
	 */
	for ( current = rg->list; current; current = current->next ) {

		var = current->ri->requestvb;
		rc = SNMP_ERR_NOERROR;

		switch (current->tri->colnum) {

		default: /** We shouldn't get here */
			netsnmp_assert(0); /** why wasn't this caught in reserve1? */
		}

		if (rc)
			netsnmp_request_set_error( current->ri, rc);
	}

	/*
	 * done with all the columns. Could check row related
	 * requirements here.
	 */
}

/************************************************************
 * Assuming that the RESERVE phases were successful, the next
 * stage is indicated by the action value ACTION. This is used
 * to actually implement the set operation. However, this must
 * either be done into temporary (persistent) storage, or the
 * previous value stored similarly, in case any of the subsequent
 * ACTION calls fail.
 *
 * In your case, changes should be made to row_ctx. A copy of
 * the original row is in undo_ctx.
 */
void saHpiSensorReadingMinTable_set_action( netsnmp_request_group *rg )
{
	netsnmp_variable_list *var;
//    saHpiSensorReadingMinTable_context *row_ctx = (saHpiSensorReadingMinTable_context *)rg->existing_row;
//    saHpiSensorReadingMinTable_context *undo_ctx = (saHpiSensorReadingMinTable_context *)rg->undo_info;
	netsnmp_request_group_item *current;

	int            row_err = 0;

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingMinTable_set_action, called\n"));

	/*
	 * TODO: loop through columns, copy varbind values
	 * to context structure for the row.
	 */
	for ( current = rg->list; current; current = current->next ) {

		var = current->ri->requestvb;

		switch (current->tri->colnum) {

		default: /** We shouldn't get here */
			netsnmp_assert(0); /** why wasn't this caught in reserve1? */
		}
	}

	if (row_err) {
		netsnmp_request_set_error((netsnmp_request_info*)rg->rg_void,
					       row_err);
		return;
	}

	/*
	 * TODO: if you have dependencies on other tables, this would be
	 * a good place to check those, too.
	 */
}

/************************************************************
 * Only once the ACTION phase has completed successfully, can
 * the final COMMIT phase be run. This is used to complete any
 * writes that were done into temporary storage, and then release
 * any allocated resources. Note that all the code in this phase
 * should be "safe" code that cannot possibly fail (cue
 * hysterical laughter). The whole intent of the ACTION/COMMIT
 * division is that all of the fallible code should be done in
 * the ACTION phase, so that it can be backed out if necessary.
 *
 * BEFORE calling this routine, the agent will update the
 * container (inserting a row if row_created == 1, or removing
 * the row if row_deleted == 1).
 *
 * AFTER calling this routine, the agent will delete the
 * undo_info.
 */
void saHpiSensorReadingMinTable_set_commit( netsnmp_request_group *rg )
{
	netsnmp_variable_list *var;
//    saHpiSensorReadingMinTable_context *row_ctx = (saHpiSensorReadingMinTable_context *)rg->existing_row;
//    saHpiSensorReadingMinTable_context *undo_ctx = (saHpiSensorReadingMinTable_context *)rg->undo_info;
	netsnmp_request_group_item *current;

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingMinTable_set_commit, called\n"));

	/*
	 * loop through columns
	 */
	for ( current = rg->list; current; current = current->next ) {

		var = current->ri->requestvb;

		switch (current->tri->colnum) {

		default: /** We shouldn't get here */
			netsnmp_assert(0); /** why wasn't this caught in reserve1? */
		}
	}

	/*
	 * done with all the columns. Could check row related
	 * requirements here.
	 */
}

/************************************************************
 * If either of the RESERVE calls fail, the write routines
 * are called again with the FREE action, to release any resources
 * that have been allocated. The agent will then return a failure
 * response to the requesting application.
 *
 * AFTER calling this routine, the agent will delete undo_info.
 */
void saHpiSensorReadingMinTable_set_free( netsnmp_request_group *rg )
{
	netsnmp_variable_list *var;
//    saHpiSensorReadingMinTable_context *row_ctx = (saHpiSensorReadingMinTable_context *)rg->existing_row;
//    saHpiSensorReadingMinTable_context *undo_ctx = (saHpiSensorReadingMinTable_context *)rg->undo_info;
	netsnmp_request_group_item *current;

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingMinTable_set_free, called\n"));

	/*
	 * loop through columns
	 */
	for ( current = rg->list; current; current = current->next ) {

		var = current->ri->requestvb;

		switch (current->tri->colnum) {

		default: 
			break;/** We shouldn't get here */
			/** should have been logged in reserve1 */
		}
	}

	/*
	 * done with all the columns. Could check row related
	 * requirements here.
	 */
}

/************************************************************
 * If the ACTION phase does fail (for example due to an apparently
 * valid, but unacceptable value, or an unforeseen problem), then
 * the list of write routines are called again, with the UNDO
 * action. This requires the routine to reset the value that was
 * changed to its previous value (assuming it was actually changed),
 * and then to release any resources that had been allocated. As
 * with the FREE phase, the agent will then return an indication
 * of the error to the requesting application.
 *
 * BEFORE calling this routine, the agent will update the container
 * (remove any newly inserted row, re-insert any removed row).
 *
 * AFTER calling this routing, the agent will call row_copy
 * to restore the data in existing_row from the date in undo_info.
 * Then undo_info will be deleted (or existing row, if row_created
 * == 1).
 */
void saHpiSensorReadingMinTable_set_undo( netsnmp_request_group *rg )
{
	netsnmp_variable_list *var;
//    saHpiSensorReadingMinTable_context *row_ctx = (saHpiSensorReadingMinTable_context *)rg->existing_row;
//    saHpiSensorReadingMinTable_context *undo_ctx = (saHpiSensorReadingMinTable_context *)rg->undo_info;
	netsnmp_request_group_item *current;

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingMinTable_set_undo, called\n"));

	/*
	 * loop through columns
	 */
	for ( current = rg->list; current; current = current->next ) {

		var = current->ri->requestvb;

		switch (current->tri->colnum) {

		default: /** We shouldn't get here */
			netsnmp_assert(0); /** why wasn't this caught in reserve1? */
		}
	}

	/*
	 * done with all the columns. Could check row related
	 * requirements here.
	 */
}


/************************************************************
 *
 * Initialize the saHpiSensorReadingMinTable table by defining its contents and how it's structured
 */
void
initialize_table_saHpiSensorReadingMinTable(void)
{
	netsnmp_table_registration_info *table_info;

	DEBUGMSGTL ((AGENT, "initialize_table_saHpiSensorReadingMinTable, called\n"));

	if (my_handler) {
		snmp_log(LOG_ERR, "initialize_table_saHpiSensorReadingMinTable_handler called again\n");
		return;
	}

	memset(&cb, 0x00, sizeof(cb));

	/** create the table structure itself */
	table_info = SNMP_MALLOC_TYPEDEF(netsnmp_table_registration_info);

	/* if your table is read only, it's easiest to change the
	   HANDLER_CAN_RWRITE definition below to HANDLER_CAN_RONLY */
	my_handler = netsnmp_create_handler_registration("saHpiSensorReadingMinTable",
							 netsnmp_table_array_helper_handler,
							 saHpiSensorReadingMinTable_oid,
							 saHpiSensorReadingMinTable_oid_len,
							 HANDLER_CAN_RWRITE);

	if (!my_handler || !table_info) {
		snmp_log(LOG_ERR, "malloc failed in "
			 "initialize_table_saHpiSensorReadingMinTable_handler\n");
		return;	/** mallocs failed */
	}

	/***************************************************
	 * Setting up the table's definition
	 */
	/*
	 * TODO: add any external indexes here.
	 */
	/** TODO: add code for external index(s)! */

	/*
	 * internal indexes
	 */
	/** index: saHpiDomainId */
	netsnmp_table_helper_add_index(table_info, ASN_UNSIGNED);
	/** index: saHpiResourceId */
	netsnmp_table_helper_add_index(table_info, ASN_UNSIGNED);
	/** index: saHpiResourceIsHistorical */
	netsnmp_table_helper_add_index(table_info, ASN_INTEGER);
	/** index: saHpiSensorNum */
	netsnmp_table_helper_add_index(table_info, ASN_UNSIGNED);

	table_info->min_column = saHpiSensorReadingMinTable_COL_MIN;
	table_info->max_column = saHpiSensorReadingMinTable_COL_MAX;

	/***************************************************
	 * registering the table with the master agent
	 */
	cb.get_value = saHpiSensorReadingMinTable_get_value;
	cb.container = netsnmp_container_find("saHpiSensorReadingMinTable_primary:"
					      "saHpiSensorReadingMinTable:"
					      "table_container");

	netsnmp_container_add_index(cb.container,
				    netsnmp_container_find("saHpiSensorReadingMinTable_secondary:"
							   "saHpiSensorReadingMinTable:"
							   "table_container"));
	cb.container->next->compare = saHpiSensorReadingMinTable_cmp;


	cb.can_set = 1;

	cb.create_row = (UserRowMethod*)saHpiSensorReadingMinTable_create_row;

	cb.duplicate_row = (UserRowMethod*)saHpiSensorReadingMinTable_duplicate_row;
	cb.delete_row = (UserRowMethod*)saHpiSensorReadingMinTable_delete_row;
	cb.row_copy = (Netsnmp_User_Row_Operation *)saHpiSensorReadingMinTable_row_copy;

	cb.can_activate = (Netsnmp_User_Row_Action *)saHpiSensorReadingMinTable_can_activate;
	cb.can_deactivate = (Netsnmp_User_Row_Action *)saHpiSensorReadingMinTable_can_deactivate;
	cb.can_delete = (Netsnmp_User_Row_Action *)saHpiSensorReadingMinTable_can_delete;

	cb.set_reserve1 = saHpiSensorReadingMinTable_set_reserve1;
	cb.set_reserve2 = saHpiSensorReadingMinTable_set_reserve2;
	cb.set_action = saHpiSensorReadingMinTable_set_action;
	cb.set_commit = saHpiSensorReadingMinTable_set_commit;
	cb.set_free = saHpiSensorReadingMinTable_set_free;
	cb.set_undo = saHpiSensorReadingMinTable_set_undo;

	DEBUGMSGTL(("initialize_table_saHpiSensorReadingMinTable",
		    "Registering table saHpiSensorReadingMinTable "
		    "as a table array\n"));
	netsnmp_table_container_register(my_handler, table_info, &cb,
					 cb.container, 1);
}

/************************************************************
 * saHpiSensorReadingMinTable_get_value
 *
 * This routine is called for get requests to copy the data
 * from the context to the varbind for the request. If the
 * context has been properly maintained, you don't need to
 * change in code in this fuction.
 */
int saHpiSensorReadingMinTable_get_value(
					netsnmp_request_info *request,
					netsnmp_index *item,
					netsnmp_table_request_info *table_info )
{
	netsnmp_variable_list *var = request->requestvb;
	saHpiSensorReadingMinTable_context *context = (saHpiSensorReadingMinTable_context *)item;

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingMinTable_get_value, called\n"));

	switch (table_info->colnum) {
	
	case COLUMN_SAHPISENSORREADINGMINISSUPPORTED:
		/** TruthValue = ASN_INTEGER */
		snmp_set_var_typed_value(var, ASN_INTEGER,
					 (u_char*)&context->saHpiSensorReadingMinIsSupported,
					 sizeof(context->saHpiSensorReadingMinIsSupported) );
		break;

	case COLUMN_SAHPISENSORREADINGMINTYPE:
		/** SaHpiSensorReadingType = ASN_INTEGER */
		snmp_set_var_typed_value(var, ASN_INTEGER,
					 (u_char*)&context->saHpiSensorReadingMinType,
					 sizeof(context->saHpiSensorReadingMinType) );
		break;

	case COLUMN_SAHPISENSORREADINGMINVALUE:
		/** SaHpiSensorReadingValue = ASN_OCTET_STR */
		snmp_set_var_typed_value(var, ASN_OCTET_STR,
					 (u_char*)&context->saHpiSensorReadingMinValue,
					 context->saHpiSensorReadingMinValue_len );
		break;

	default: /** We shouldn't get here */
		snmp_log(LOG_ERR, "unknown column in "
			 "saHpiSensorReadingMinTable_get_value\n");
		return SNMP_ERR_GENERR;
	}
	return SNMP_ERR_NOERROR;
}

/************************************************************
 * saHpiSensorReadingMinTable_get_by_idx
 */
const saHpiSensorReadingMinTable_context *
saHpiSensorReadingMinTable_get_by_idx(netsnmp_index * hdr)
{
	DEBUGMSGTL ((AGENT, "saHpiSensorReadingMinTable_get_by_idx, called\n"));

	return(const saHpiSensorReadingMinTable_context *)
	CONTAINER_FIND(cb.container, hdr );
}


