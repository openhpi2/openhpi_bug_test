/*
 * (C) Copyright IBM Corp. 2003
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  This
 * file and program are licensed under a BSD style license.  See
 * the Copying file included with the OpenHPI distribution for
 * full licensing terms.
 *
 * Authors:
 *   Konrad Rzeszutek <konradr@us.ibm.com>
 *
 * Note: this file originally auto-generated by mib2c using
 *       : mib2c.array-user.conf,v 5.15.2.1 2003/02/27 05:59:41 rstory Exp $
 *
 * $Id$
 *
 */
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <net-snmp/library/snmp_assert.h>

#include "epath_utils.h"
#include <SaHpi.h>

#include <hpiSubagent.h>
#include <saHpiTable.h>
#include <saHpiRdrTable.h>

#include <saHpiSensorTable.h>
#include <saHpiCtrlTable.h>
#include <saHpiInventoryTable.h>
#include <saHpiWatchdogTable.h>


static netsnmp_handler_registration *my_handler = NULL;
static netsnmp_table_array_callbacks cb;

extern  int send_traps_on_startup;

oid             saHpiRdrTable_oid[] = { saHpiRdrTable_TABLE_OID };
size_t          saHpiRdrTable_oid_len = OID_LENGTH(saHpiRdrTable_oid);
//   { 1, 3, 6, 1, 3, 90, 3, 1, 0 };
oid      saHpiRdrCount_oid[] = { hpiResources_OID, SCALAR_COLUMN_SAHPIRDRCOUNT, 0 };

//  { 1, 3, 6, 1, 3, 90, 4, 7, 0 };
oid saHpiResourceDataRecordNotification[] = { hpiNotifications_OID, 7, 0};

static u_long rdr_count = 0;



/************************************************************
 * keep binary tree to find context by name
 */
static int      saHpiRdrTable_cmp(const void *lhs, const void *rhs);

/************************************************************
 * compare two context pointers here. Return -1 if lhs < rhs,
 * 0 if lhs == rhs, and 1 if lhs > rhs.
 */
static int
saHpiRdrTable_cmp(const void *lhs, const void *rhs)
{
    saHpiRdrTable_context *context_l = (saHpiRdrTable_context *) lhs;
    saHpiRdrTable_context *context_r = (saHpiRdrTable_context *) rhs;
   
    int             rc;

    if (context_l->saHpiResourceID < context_r->saHpiResourceID) 
      return -1;

    rc = (context_l->saHpiResourceID == context_r->saHpiResourceID) ? 0 : 1;

    if (rc==0)
      return rc;

    if (context_l->saHpiRdrRecordId < context_r->saHpiRdrRecordId)
      return -1;
    rc = (context_l->saHpiRdrRecordId == context_r->saHpiRdrRecordId) ? 0 : 1;

    if (rc==0)
      return rc;

    if (context_l->saHpiRdrType < context_r->saHpiRdrType)
      return -1;
    return (context_l->saHpiRdrType == context_r->saHpiRdrType) ? 0 : 1;

}





int
populate_rdr(SaHpiRptEntryT *rpt_entry, 
	     SaHpiResourceIdT resource_id,
	     oid *rpt_oid, size_t rpt_oid_len) 
{

  SaErrorT       err;
  SaHpiEntryIdT  current_rdr;
  SaHpiEntryIdT  next_rdr;
  SaHpiRdrT      rdr_entry;
  SaHpiSessionIdT session_id;

  long backup_count = rdr_count;
  int rc = AGENT_ERR_NOERROR;

   oid			rdr_oid[3];
   oid                  full_oid[MAX_OID_LEN];
   oid                  child_oid[MAX_OID_LEN];
   size_t                  child_oid_len;
   oid                  column[2];
   int                  column_len = 2;
   int                  full_oid_len;

   unsigned long child_id = 0xDEADBEEF;

   netsnmp_index	rdr_index;
   saHpiRdrTable_context	*rdr_context; 

   DEBUGMSGTL((AGENT,"\n\t--- populate_rdr: Entry.\n"));
  if (getSaHpiSession(&session_id) == AGENT_ERR_NOERROR) {
    rdr_index.len = 3;
    next_rdr= SAHPI_FIRST_ENTRY;
    do {
      current_rdr = next_rdr;
      err = saHpiRdrGet(session_id, resource_id,
			current_rdr, &next_rdr, &rdr_entry);
      
      if (SA_OK == err) {
	// Look at the MIB to find out what the indexs are
	rdr_oid[0]=resource_id;
	rdr_oid[1]=rdr_entry.RecordId;
	rdr_oid[2]=rdr_entry.RdrType;
	
	rdr_index.oids = (oid *)&rdr_oid;	
	DEBUGMSGTL((AGENT,"\nIndex for this entry is: \n"));
	DEBUGMSGOID((AGENT,rdr_oid, rdr_index.len));
	if (backup_count == 0) {
	  rdr_context = saHpiRdrTable_create_row(&rdr_index);
	} else {
	  // We are re-populating. Check for existing entries
	   DEBUGMSGTL((AGENT,"Searching for index: %d.%d\n", 
		       rdr_entry.RecordId,
		       rdr_entry.RdrType));
	   DEBUGMSGTL((AGENT,"\n"));	 
	   // See if it exists.
	   rdr_context = NULL;
	   rdr_context = CONTAINER_FIND(cb.container, &rdr_index);
	   // If we don't find it - we create it.
	     
	   if (!rdr_context) {
	     // New entry. Add it
	     DEBUGMSGTL((AGENT,"Couldn't find it\n"));
	     rdr_context = saHpiRdrTable_create_row(&rdr_index);
	   } 
	}
      
	
	column[0] = 1;
	column[1] =  COLUMN_SAHPIRDRRESOURCEID;	     
	build_full_oid(saHpiRdrTable_oid, saHpiRdrTable_oid_len,
		       column, column_len,
		       &rdr_index,
		       full_oid, MAX_OID_LEN, &full_oid_len);
			    
	DEBUGMSGTL((AGENT,"Our first OBJECT OID for RDR row is: "));
	DEBUGMSGOID((AGENT, full_oid, full_oid_len));
	
	if (rdr_entry.RdrType == SAHPI_SENSOR_RDR) {
	  child_id = rdr_entry.RdrTypeUnion.SensorRec.Num;
	  DEBUGMSGTL((AGENT,"CHILD ID: %d\n", child_id));
	  rc = populate_sensor(&rdr_entry.RdrTypeUnion.SensorRec, 
			       resource_id,
			       full_oid, full_oid_len, 
			       child_oid, &child_oid_len);
	}
	if (rdr_entry.RdrType == SAHPI_CTRL_RDR) {
	  child_id = rdr_entry.RdrTypeUnion.CtrlRec.Num;
	  DEBUGMSGTL((AGENT,"CHILD ID: %d\n", child_id));
	  rc =populate_control(&rdr_entry.RdrTypeUnion.CtrlRec,
			       full_oid, full_oid_len,
			       child_oid, &child_oid_len);
	}
	if (rdr_entry.RdrType == SAHPI_INVENTORY_RDR) {
	  child_id = rdr_entry.RdrTypeUnion.InventoryRec.EirId;
	  rc =populate_inventory(&rdr_entry.RdrTypeUnion.InventoryRec,
				 resource_id,
				 full_oid, full_oid_len,
				 child_oid, &child_oid_len);
	}
	if (rdr_entry.RdrType == SAHPI_WATCHDOG_RDR) {
	  child_id = rdr_entry.RdrTypeUnion.WatchdogRec.WatchdogNum;
	  rc =populate_watchdog(&rdr_entry.RdrTypeUnion.WatchdogRec,
				resource_id,
				full_oid, full_oid_len,
				child_oid, &child_oid_len);
	}
	
	DEBUGMSGTL((AGENT,"rc is %d", rc));
	if (rc != AGENT_ERR_NOERROR)
	  break;
	
	// By this stage, rdr_context surely has something in it.
	// '*_modify_context' does a checksum check to see if 
	// the record needs to be altered, and if so populates with
	// information from RDR and the OIDs passed.

	if (saHpiRdrTable_modify_context(resource_id,
					 &rdr_entry, 
					 rdr_context,
					 rpt_oid,
					 rpt_oid_len,
					 child_oid,
					 child_oid_len,
					 child_id)
	    == AGENT_NEW_ENTRY) {
	  DEBUGMSGTL((AGENT,"Adding it in\n"));
	  CONTAINER_INSERT(cb.container, rdr_context);	  
	  rdr_count = CONTAINER_SIZE(cb.container);

	  if (send_traps_on_startup == TRUE) {
	    send_saHpiRdrTable_notification(rdr_context);
	  }

	}
      } else { // Bail out.
	rc = AGENT_ERR_OPERATION;
	break;
      }
    } while ( next_rdr != SAHPI_LAST_ENTRY);
    
    // Now check to see if we need to delete any entry.
  }

  DEBUGMSGTL((AGENT,"\n\t--- populate_rdr. Exit\n"));
  return rc;
}


int  
saHpiRdrTable_modify_context(SaHpiResourceIdT resource_id,
			     SaHpiRdrT *entry,
			     saHpiRdrTable_context *ctx,
			     oid *rpt_oid,
			     size_t rpt_oid_len,
			     oid *child_oid, 
			     size_t child_oid_len,
			     unsigned long child_id) {

  long hash;
  int len;

  // Make sure they are valid.
  if (entry && ctx) {
    
    // We are subtracting SaHpiTextBufferT b/c the underlaying HPI
    // library is not zeroing out the memory for not used entries -
    // thus garbage in SaHpiTextBufferT exist,
    hash = calculate_hash_value(entry, sizeof(SaHpiRdrTypeT)+
				sizeof(SaHpiEntityPathT)+
				sizeof(SaHpiEntryIdT));
    
    DEBUGMSGTL((AGENT," Hash value: %d, in ctx: %d\n", hash, ctx->hash));

    if (ctx->hash != 0) {
      // Only do the check if the hash value is something else than zero.
      // 'zero' value is only for newly created records, and in some
      // rare instances when the hash has rolled to zero - in which
      // case we will just consider the worst-case scenario and update
      // the record and not trust the hash value.
      if (hash == ctx->hash) {
	// The same data. No need to change.
	return AGENT_ENTRY_EXIST;
      }
    }

    ctx->hash = hash;

    DEBUGMSGTL((AGENT,"Creating columns for: %d\n", entry->RecordId));

    ctx->saHpiResourceID = resource_id;
    ctx->saHpiRdrRecordId = entry->RecordId;
    ctx->saHpiRdrType = entry->RdrType;

    len = entitypath2string(
			    &entry->Entity, 
			    (gchar *)&ctx->saHpiRdrEntityPath, 
			    SNMP_MAX_MSG_SIZE);
    if (len < 0) {
      // Bummer, EntityPath too long to fit in the SNMP_MAX_MSG_SIZE.
      len = 0;
    }
    DEBUGMSGTL((AGENT,"EntityPath: %s\n", ctx->saHpiRdrEntityPath));
    // Possible buffer overflow here?
    ctx->saHpiRdrEntityPath_len = len;

    ctx->saHpiRdr_len = child_oid_len*sizeof(oid);
    memcpy(ctx->saHpiRdr, child_oid, ctx->saHpiRdr_len);


    ctx->saHpiRdrRTP_len = rpt_oid_len*sizeof(oid);
    memcpy(ctx->saHpiRdrRTP, rpt_oid, ctx->saHpiRdrRTP_len);

    ctx->saHpiRdrId = child_id;

    return AGENT_NEW_ENTRY;
  }
  
  return AGENT_ERR_NULL_DATA;
}

int
send_saHpiRdrTable_notification(saHpiRdrTable_context *ctx) {

  netsnmp_variable_list *notification_vars = NULL;
  oid snmptrap[] = { snmptrap_oid };
  DEBUGMSGTL((AGENT,"--- send_saHpiRdrTable_notification: Entry.\n"));  

  snmp_varlist_add_variable(&notification_vars,
			    snmptrap, OID_LENGTH(snmptrap),
			    ASN_OBJECT_ID,
			    (u_char *)saHpiResourceDataRecordNotification,
			    OID_LENGTH(saHpiResourceDataRecordNotification)* sizeof(oid));


  make_SaHpiRdrTable_trap_msg(notification_vars,
			      &ctx->index,
			      COLUMN_SAHPIRDRRESOURCEID,
			      ASN_UNSIGNED,
			      (char *)&ctx->saHpiResourceID,
			      sizeof(ctx->saHpiResourceID));

  make_SaHpiRdrTable_trap_msg(notification_vars,
			      &ctx->index,
			      COLUMN_SAHPIRDRRECORDID,
			      ASN_UNSIGNED,
			      (char *)&ctx->saHpiRdrRecordId,
			      sizeof(ctx->saHpiRdrRecordId));
  
  make_SaHpiRdrTable_trap_msg(notification_vars,
		&ctx->index,
		COLUMN_SAHPIRDRTYPE,
		ASN_INTEGER,
		(char *)&ctx->saHpiRdrType,
		sizeof(ctx->saHpiRdrType));

 make_SaHpiRdrTable_trap_msg(notification_vars,
	       &ctx->index,
	       COLUMN_SAHPIRDRENTITYPATH,
	       ASN_OCTET_STR,
	       ctx->saHpiRdrEntityPath,
	       ctx->saHpiRdrEntityPath_len);

 make_SaHpiRdrTable_trap_msg(notification_vars,
		&ctx->index,
		COLUMN_SAHPIRDR,
		ASN_OBJECT_ID,
		(char *)ctx->saHpiRdr,
		ctx->saHpiRdr_len);

  make_SaHpiRdrTable_trap_msg(notification_vars,
		&ctx->index,
		COLUMN_SAHPIRDRRTP,
		ASN_OBJECT_ID,
		(char *)ctx->saHpiRdrRTP,
		ctx->saHpiRdrRTP_len);

  oid rdr_count_oid[] = 
    {hpiResources_OID , SCALAR_COLUMN_SAHPIRDRCOUNT , 0 };

 snmp_varlist_add_variable(&notification_vars,
			   rdr_count_oid, OID_LENGTH(rdr_count_oid),
			   ASN_COUNTER,
			   (char *)&rdr_count,
			   sizeof(rdr_count));

  send_v2trap(notification_vars);

  snmp_free_varbind(notification_vars);
  DEBUGMSGTL((AGENT,"--- send_saHpiRdrTable_notification: Exit.\n"));
  return 0;
}
void
make_SaHpiRdrTable_trap_msg(netsnmp_variable_list *list, 
	      netsnmp_index *index,
	      int col, 
	      u_char type,
	      const u_char *value, 
	      const size_t value_len) {

  oid entries[MAX_OID_LEN];
  int len;
  oid column[2];


  column[0] = 1; // wonder where this comes from? Look at the HPI MIB
  column[1] = col;

  build_full_oid(saHpiRdrTable_oid, saHpiRdrTable_oid_len,
		 column, 2,
		 index,
		 entries, MAX_OID_LEN, &len);
  DEBUGMSGTL((AGENT,"\n"));
  DEBUGMSGOID((AGENT,entries, len));
  DEBUGMSGTL((AGENT,"\n"));

 snmp_varlist_add_variable(&list,
			   entries, len,
			   type,
			   value,
			   value_len);
			
  
}

/************************************************************
 * the *_row_copy routine
 */

static int
saHpiRdrTable_row_copy(saHpiRdrTable_context * dst,
                       saHpiRdrTable_context * src)
{
  DEBUGMSGTL((AGENT,"--- saHpiRdrTable_row_copy: Entry.\n"));

  if (!dst || !src)
    return 1;


    if (dst->index.oids)
        free(dst->index.oids);
    if (snmp_clone_mem((void *) &dst->index.oids, src->index.oids,
                       src->index.len * sizeof(oid))) {
        dst->index.oids = NULL;
        return 1;
    }
    dst->index.len = src->index.len;



    dst->saHpiResourceID = src->saHpiResourceID;
    dst->saHpiRdrRecordId = src->saHpiRdrRecordId;

    dst->saHpiRdrType = src->saHpiRdrType;

    memcpy(dst->saHpiRdrEntityPath, src->saHpiRdrEntityPath,
           src->saHpiRdrEntityPath_len);
    dst->saHpiRdrEntityPath_len = src->saHpiRdrEntityPath_len;

    memcpy(src->saHpiRdr, dst->saHpiRdr, src->saHpiRdr_len);
    dst->saHpiRdr_len = src->saHpiRdr_len;

    dst->saHpiRdrId = src->saHpiRdrId;

    memcpy(src->saHpiRdrRTP, dst->saHpiRdrRTP, src->saHpiRdrRTP_len);
    dst->saHpiRdrRTP_len = src->saHpiRdrRTP_len;

    return 0;
}



/*
 * the *_extract_index routine
 */
int
saHpiRdrTable_extract_index(saHpiRdrTable_context * ctx,
                            netsnmp_index * hdr)
{
    /*
     * temporary local storage for extracting oid index
     */
    netsnmp_variable_list var_saHpiResourceID;
    netsnmp_variable_list var_saHpiRdrRecordId;
    netsnmp_variable_list var_saHpiRdrType;
    int             err;

    /*
     * copy index, if provided
     */
    if (hdr) {
        netsnmp_assert(ctx->index.oids == NULL);
        if (snmp_clone_mem((void *) &ctx->index.oids, hdr->oids,
                           hdr->len * sizeof(oid))) {
            return -1;
        }
        ctx->index.len = hdr->len;
    }

    /**
     * Create variable to hold each component of the index
     */
    memset(&var_saHpiResourceID, 0x00, sizeof(var_saHpiResourceID));
    var_saHpiResourceID.type = ASN_UNSIGNED;
    var_saHpiResourceID.next_variable = &var_saHpiRdrRecordId;

    memset(&var_saHpiRdrRecordId, 0x00, sizeof(var_saHpiRdrRecordId));
    var_saHpiRdrRecordId.type = ASN_UNSIGNED;
    var_saHpiRdrRecordId.next_variable = &var_saHpiRdrType;

    memset(&var_saHpiRdrType, 0x00, sizeof(var_saHpiRdrType));
    var_saHpiRdrType.type = ASN_INTEGER;
    var_saHpiRdrType.next_variable = NULL;

    /*
     * parse the oid into the individual components
     */
    err = parse_oid_indexes(hdr->oids, hdr->len, &var_saHpiResourceID);
    if (err == SNMP_ERR_NOERROR) {
        /*
         * copy components into the context structure
         */
      ctx->saHpiResourceID = *var_saHpiResourceID.val.integer;
        ctx->saHpiRdrRecordId = *var_saHpiRdrRecordId.val.integer;

        ctx->saHpiRdrType = *var_saHpiRdrType.val.integer;

        /*
         * TODO: check index for valid values. For EXAMPLE:
         *
         * if ( *var_saHpiRdrType.val.integer != XXX ) {
         *    err = -1;
         * }
         */
    }

    /*
     * parsing may have allocated memory. free it.
     */
    snmp_reset_var_buffers(&var_saHpiRdrRecordId);

    return err;
}

/************************************************************
 * the *_can_delete routine is called to determine if a row
 * can be deleted.
 *
 * return 1 if the row can be deleted
 * return 0 if the row cannot be deleted
 */
int
saHpiRdrTable_can_delete(saHpiRdrTable_context * undo_ctx,
                         saHpiRdrTable_context * row_ctx,
                         netsnmp_request_group * rg)
{


    return 0;
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
 * returns a newly allocated saHpiRdrTable_context
 *   structure if the specified indexes are not illegal
 * returns NULL for errors or illegal index values.
 */
saHpiRdrTable_context *
saHpiRdrTable_create_row(netsnmp_index * hdr)
{
    saHpiRdrTable_context *ctx =
        SNMP_MALLOC_TYPEDEF(saHpiRdrTable_context);
    if (!ctx)
        return NULL;

      if (saHpiRdrTable_extract_index(ctx, hdr)) {
        free(ctx->index.oids);
        free(ctx);
        return NULL;
    }

    ctx->hash = 0;
    return ctx;
}


/************************************************************
 * the *_duplicate row routine
 */
saHpiRdrTable_context *
saHpiRdrTable_duplicate_row(saHpiRdrTable_context * row_ctx)
{
    saHpiRdrTable_context *dup;

    if (!row_ctx)
        return NULL;

    dup = SNMP_MALLOC_TYPEDEF(saHpiRdrTable_context);
    if (!dup)
        return NULL;

    if (saHpiRdrTable_row_copy(dup, row_ctx)) {
        free(dup);
        dup = NULL;
    }

    return dup;
}

/************************************************************
 * the *_delete_row method is called to delete a row.
 */
netsnmp_index  *
saHpiRdrTable_delete_row(saHpiRdrTable_context * ctx)
{

    if (ctx->index.oids)
        free(ctx->index.oids);

    free(ctx);

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
void
saHpiRdrTable_set_reserve1(netsnmp_request_group * rg)
{
 
}

void
saHpiRdrTable_set_reserve2(netsnmp_request_group * rg)
{


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
void
saHpiRdrTable_set_action(netsnmp_request_group * rg)
{
   
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
void
saHpiRdrTable_set_commit(netsnmp_request_group * rg)
{
  
}

/************************************************************
 * If either of the RESERVE calls fail, the write routines
 * are called again with the FREE action, to release any resources
 * that have been allocated. The agent will then return a failure
 * response to the requesting application.
 *
 * AFTER calling this routine, the agent will delete undo_info.
 */
void
saHpiRdrTable_set_free(netsnmp_request_group * rg)
{
 
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
void
saHpiRdrTable_set_undo(netsnmp_request_group * rg)
{
  
}




/************************************************************
 *
 * Initialize the saHpiRdrTable table by defining its contents and how it's structured
 */
void
initialize_table_saHpiRdrTable(void)
{
    netsnmp_table_registration_info *table_info;

    if (my_handler) {
        snmp_log(LOG_ERR,
                 "initialize_table_saHpiRdrTable_handler called again\n");
        return;
    }

    memset(&cb, 0x00, sizeof(cb));

    /** create the table structure itself */
    table_info = SNMP_MALLOC_TYPEDEF(netsnmp_table_registration_info);

    /*
     * if your table is read only, it's easiest to change the
     * HANDLER_CAN_RWRITE definition below to HANDLER_CAN_RONLY 
     */
    my_handler = netsnmp_create_handler_registration("saHpiRdrTable",
                                                     netsnmp_table_array_helper_handler,
                                                     saHpiRdrTable_oid,
                                                     saHpiRdrTable_oid_len,
                                                     HANDLER_CAN_RONLY);

    if (!my_handler || !table_info) {
        snmp_log(LOG_ERR, "malloc failed in "
                 "initialize_table_saHpiRdrTable_handler\n");
        return; /** mallocs failed */
    }

  
        /** index: saHpiRdrRecordId */
    netsnmp_table_helper_add_index(table_info, ASN_UNSIGNED);
    netsnmp_table_helper_add_index(table_info, ASN_UNSIGNED);
        /** index: saHpiRdrType */
    netsnmp_table_helper_add_index(table_info, ASN_INTEGER);

    table_info->min_column = saHpiRdrTable_COL_MIN;
    table_info->max_column = saHpiRdrTable_COL_MAX;

    /***************************************************
     * registering the table with the master agent
     */
    cb.get_value = saHpiRdrTable_get_value;
    cb.container = netsnmp_container_find("saHpiRdrTable_primary:"
                                          "saHpiRdrTable:"
                                          "table_container");

    netsnmp_container_add_index(cb.container,
                                netsnmp_container_find
                                ("saHpiRdrTable_secondary:"
                                 "saHpiRdrTable:" "table_container"));
    cb.container->next->compare = saHpiRdrTable_cmp;

    cb.create_row = (UserRowMethod *) saHpiRdrTable_create_row;

   
    cb.duplicate_row = (UserRowMethod *) saHpiRdrTable_duplicate_row;
    cb.delete_row = (UserRowMethod *) saHpiRdrTable_delete_row;
   
    cb.row_copy = (Netsnmp_User_Row_Operation *) saHpiRdrTable_row_copy;
   
    cb.can_delete = (Netsnmp_User_Row_Action *) saHpiRdrTable_can_delete;
   /* 
    cb.set_reserve1 = saHpiRdrTable_set_reserve1;
    cb.set_reserve2 = saHpiRdrTable_set_reserve2;
    cb.set_action = saHpiRdrTable_set_action;
    cb.set_commit = saHpiRdrTable_set_commit;
    cb.set_free = saHpiRdrTable_set_free;
    cb.set_undo = saHpiRdrTable_set_undo;
   */ 

    DEBUGMSGTL(("initialize_table_saHpiRdrTable",
                "Registering table saHpiRdrTable " "as a table array\n"));

    netsnmp_table_container_register(my_handler, table_info, &cb,
                                     cb.container, 1);

    netsnmp_register_read_only_counter32_instance("rdr_count",
						  saHpiRdrCount_oid,
						  OID_LENGTH(saHpiRdrCount_oid),
						  &rdr_count,
						  NULL);

}

/************************************************************
 * saHpiRdrTable_get_value
 */
int
saHpiRdrTable_get_value(netsnmp_request_info *request,
                        netsnmp_index * item,
                        netsnmp_table_request_info *table_info)
{
    netsnmp_variable_list *var = request->requestvb;
    saHpiRdrTable_context *context = (saHpiRdrTable_context *) item;


    DEBUGMSGTL((AGENT,"--- saHpiRdrTable_get_value: Entry\n"));
    switch (table_info->colnum) {

   
   

    case COLUMN_SAHPIRDRRECORDID:
            /** UNSIGNED32 = ASN_UNSIGNED */
        snmp_set_var_typed_value(var, ASN_UNSIGNED,
                                 (char *) &context->saHpiRdrRecordId,
                                 sizeof(context->saHpiRdrRecordId));
        break;

    case COLUMN_SAHPIRDRTYPE:
            /** INTEGER = ASN_INTEGER */
        snmp_set_var_typed_value(var, ASN_INTEGER,
                                 (char *) &context->saHpiRdrType,
                                 sizeof(context->saHpiRdrType));
        break;

    case COLUMN_SAHPIRDRENTITYPATH:
            /** OCTETSTR = ASN_OCTET_STR */
        snmp_set_var_typed_value(var, ASN_OCTET_STR,
                                 (char *) &context->saHpiRdrEntityPath,
                                 context->saHpiRdrEntityPath_len);
        break;

    case COLUMN_SAHPIRDR:
            /** RowPointer = ASN_OBJECT_ID */
        snmp_set_var_typed_value(var, ASN_OBJECT_ID,
                                 (char *) &context->saHpiRdr,
                                 context->saHpiRdr_len);
        break;

    case COLUMN_SAHPIRDRID:
            /** COUNTER = ASN_COUNTER */
        snmp_set_var_typed_value(var, ASN_COUNTER,
                                 (char *) &context->saHpiRdrId,
                                 sizeof(context->saHpiRdrId));
        break;

    case COLUMN_SAHPIRDRRTP:
            /** RowPointer = ASN_OBJECT_ID */
        snmp_set_var_typed_value(var, ASN_OBJECT_ID,
                                 (char *) &context->saHpiRdrRTP,
                                 context->saHpiRdrRTP_len);
        break;

    default:/** We shouldn't get here */
        snmp_log(LOG_ERR, "unknown column in "
                 "saHpiRdrTable_get_value\n");
        return SNMP_ERR_GENERR;
    }

    DEBUGMSGTL((AGENT,"--- saHpiRdrTable_get_value: Exit\n"));
    return SNMP_ERR_NOERROR;
}

/************************************************************
 * saHpiRdrTable_get_by_idx
 */
/*
const saHpiRdrTable_context *
saHpiRdrTable_get_by_idx(netsnmp_index * hdr)
{
    return (const saHpiRdrTable_context *)
        CONTAINER_FIND(cb.container, hdr);
}
*/
