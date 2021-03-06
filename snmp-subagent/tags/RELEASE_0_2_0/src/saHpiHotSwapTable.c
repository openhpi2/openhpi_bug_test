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

#include <saHpiHotSwapTable.h>
#include <SaHpi.h>
#include <hpiSubagent.h>

static netsnmp_handler_registration *my_handler = NULL;
static netsnmp_table_array_callbacks cb;

static oid saHpiHotSwapTable_oid[] = { saHpiHotSwapTable_TABLE_OID };
static size_t saHpiHotSwapTable_oid_len = OID_LENGTH (saHpiHotSwapTable_oid);

static int
saHpiHotSwapTable_modify_context (SaHpiRptEntryT * rpt_entry,
				  oid * rpt_oid, size_t rpt_oid_len,
				  saHpiHotSwapTable_context * ctx);


int
populate_hotswap (SaHpiRptEntryT * rpt_entry,
		  oid * rpt_oid, size_t rpt_oid_len)
{

  SaHpiSessionIdT session_id;
  int rc = AGENT_ERR_NOERROR;

  oid index_oid[HOTSWAP_INDEX_NR];


  netsnmp_index hotswap_index;
  saHpiHotSwapTable_context *hotswap_context;

  DEBUGMSGTL ((AGENT, "\n\t--- populate_hotswap. Entry\n"));
  if ((rc = getSaHpiSession (&session_id)) == AGENT_ERR_NOERROR)
    {


      index_oid[0] = rpt_entry->DomainId;
      index_oid[1] = rpt_entry->ResourceId;

      hotswap_index.oids = (oid *) & index_oid;
      hotswap_index.len = HOTSWAP_INDEX_NR;
      hotswap_context = CONTAINER_FIND (cb.container, &hotswap_index);

      if (!hotswap_context)
	{
	  // Couldn't find it. Add new entry.
	  hotswap_context = saHpiHotSwapTable_create_row (&hotswap_index);
	}

      if (!hotswap_context)
	{
	  snmp_log (LOG_ERR, "Not enough memory for a HotSwap row!\n");
	  return AGENT_ERR_MEMORY_FAULT;
	}

      if (saHpiHotSwapTable_modify_context (rpt_entry,
					    rpt_oid,
					    rpt_oid_len,
					    hotswap_context)
	  == AGENT_NEW_ENTRY)
	{

	  CONTAINER_INSERT (cb.container, hotswap_context);
	}

    }

  DEBUGMSGTL ((AGENT, "\n\t--- populate_hotswap: Exit (rc: %d).\n", rc));
  return rc;
}

static int
saHpiHotSwapTable_modify_context (SaHpiRptEntryT * rpt_entry,
				  oid * rpt_oid, size_t rpt_oid_len,
				  saHpiHotSwapTable_context * ctx)
{
  unsigned int update_entry = MIB_FALSE;
  long hash = 0;
  int rc;
  SaHpiSessionIdT session_id;
  SaHpiHsIndicatorStateT indication_state;
  SaHpiHsPowerStateT power_state;
  SaHpiResetActionT reset_action;
  SaHpiHsStateT state;
  // These are 64-bite
  SaHpiTimeoutT insert_t;
  SaHpiTimeoutT extract_t;

  if (rpt_entry)
    {
      hash = calculate_hash_value (rpt_entry, sizeof (SaHpiRptEntryT)
				   - sizeof (SaHpiTextBufferT));
    }
  if (ctx)
    {
      if (ctx->hash != 0)
	{
	  DEBUGMSGTL ((AGENT, "Updating HotSwap entry [%d, %d]\n",
		       ctx->domain_id, ctx->resource_id));
	  update_entry = MIB_TRUE;

	}

      if (hash == 0)
	hash = 1;
      ctx->hash = hash;

      if (rpt_entry)
	{
	  ctx->resource_id = rpt_entry->ResourceId;
	  ctx->domain_id = rpt_entry->DomainId;
	  ctx->saHpiHotSwapEventSeverity = rpt_entry->ResourceSeverity + 1;
	}
      // Get the seesion_id
      rc = getSaHpiSession (&session_id);
      if (rc != AGENT_ERR_NOERROR)
	{
	  DEBUGMSGTL ((AGENT, "Call to getSaHpiSession failed with rc: %d\n",
		       rc));
	  return rc;
	}

      // Indicator
      DEBUGMSGTL ((AGENT, "Calling saHpiHotSwapIndicatorStateGet with %d\n",
		   ctx->resource_id));

      rc = saHpiHotSwapIndicatorStateGet (session_id,
					  ctx->resource_id,
					  &indication_state);
      if (rc != SA_OK)
	{
	  DEBUGMSGTL ((AGENT,
		       "Call to saHpiHotSwapIndicatorStateGet failed with rc: %s\n",
		       get_error_string (rc)));
	}
      else
	ctx->saHpiHotSwapIndicator = indication_state + 1;


      // PowerState
      DEBUGMSGTL ((AGENT, "Calling saHpiResourcePowerStateGet with %d\n",
		   ctx->resource_id));

      rc = saHpiResourcePowerStateGet (session_id,
				       ctx->resource_id, &power_state);

      if (rc != SA_OK)
	{
	  DEBUGMSGTL ((AGENT,
		       "Call to saHpiResourcePowerStateGet failed with %s\n",
		       get_error_string (rc)));
	}
      else
	ctx->saHpiHotSwapPowerState = power_state + 1;

      // ResetState
      DEBUGMSGTL ((AGENT, "Calling saHpiResourceResetStateGet with %d\n",
		   ctx->resource_id));

      rc = saHpiResourceResetStateGet (session_id,
				       ctx->resource_id, &reset_action);

      if (rc != SA_OK)
	{
	  DEBUGMSGTL ((AGENT,
		       "Call to saHpiResourceResetStateGet failed with %s\n",
		       get_error_string (rc)));
	}
      else
	ctx->saHpiHotSwapResetState = reset_action + 1;


      // State
      DEBUGMSGTL ((AGENT, "Calling saHpiHotSwapStateGet with %d\n",
		   ctx->resource_id));

      rc = saHpiHotSwapStateGet (session_id, ctx->resource_id, &state);

      if (rc != SA_OK)
	{
	  DEBUGMSGTL ((AGENT, "Call to saHpiHotSwapStateGet failed with %s\n",
		       get_error_string (rc)));
	}
      else
	{
	  ctx->saHpiHotSwapState = state + 1;
	  // We don't know the previous state?
	  ctx->saHpiHotSwapPreviousState = 0;
	}


      // InsertTimeout
      DEBUGMSGTL ((AGENT, "Calling saHpiAutoInsertTimeoutGet \n"));

      rc = saHpiAutoInsertTimeoutGet (session_id, &insert_t);

      if (rc != SA_OK)
	{
	  DEBUGMSGTL ((AGENT,
		       "Call to saHpiAutoInsertTimeoutGet failed with %s\n",
		       get_error_string (rc)));
	}
      else
	// IBM-KR: TODO, saHpiTimeT is 64bit, long is 32bit-
	// Should we make it 64-bit? Endian
	ctx->saHpiHotSwapInsertTimeout = insert_t;

      // Extract timeout
      DEBUGMSGTL ((AGENT, "Calling saHpiAutoExtractTimeoutGet with %d\n",
		   ctx->resource_id));

      rc = saHpiAutoExtractTimeoutGet (session_id,
				       ctx->resource_id, &extract_t);

      if (rc != SA_OK)
	{
	  DEBUGMSGTL ((AGENT,
		       "Call to saHpiAutoExtractTimeoutGet failed with %s\n",
		       get_error_string (rc)));
	}
      else
	{
	  // IBM-KR: TODO, saHpiTimeT is 64bit, long is 32bit-
	  // Should we make it 64-bit? Endian
	  //       
	  ctx->saHpiHotSwapExtractTimeout = extract_t;
	}
      ctx->saHpiHotSwapActionRequest = 0;

      // Copy the RPT OID.
      if (rpt_oid) {
      ctx->saHpiHotSwapRTP_len = rpt_oid_len * sizeof (oid);
      memcpy (ctx->saHpiHotSwapRTP, rpt_oid, ctx->saHpiHotSwapRTP_len);
      }
      if (update_entry == MIB_TRUE)
	return AGENT_ENTRY_EXIST;
      return AGENT_NEW_ENTRY;
    }
  return AGENT_ERR_NULL_DATA;
}

int
set_hotswap_indicator (saHpiHotSwapTable_context * ctx)
{


  SaHpiSessionIdT session_id;
  SaErrorT rc;
  SaHpiHsIndicatorStateT indication_state;

  if (ctx)
    {
      indication_state = ctx->saHpiHotSwapIndicator - 1;
      // Get the seesion_id
      rc = getSaHpiSession (&session_id);
      if (rc != AGENT_ERR_NOERROR)
	{
	  DEBUGMSGTL ((AGENT, "Call to getSaHpiSession failed with rc: %d\n",
		       rc));
	  return rc;
	}

      // Set the new value
      DEBUGMSGTL ((AGENT, "Calling with saHpiHotSwapIndicatorStateSet%d\n",
		   ctx->resource_id));

      rc = saHpiHotSwapIndicatorStateSet (session_id,
					  ctx->resource_id, indication_state);


      if (rc != SA_OK)
	{
	  snmp_log (LOG_ERR,
		    "Call to saHpiHotSwapIndicatorStateSet failed with return code: %s\n",
		    get_error_string (rc));
	  DEBUGMSGTL ((AGENT,
		       "Call saHpiHotSwapIndicatorStateSet failed with return code: %s\n",
		       get_error_string (rc)));
	  return AGENT_ERR_OPERATION;
	}

      // Get the new value
      DEBUGMSGTL ((AGENT, "Calling saHpiHotSwapIndicatorStateGet with %d\n",
		   ctx->resource_id));

      rc = saHpiHotSwapIndicatorStateGet (session_id,
					  ctx->resource_id,
					  &indication_state);


      if (rc != SA_OK)
	{
	  snmp_log (LOG_ERR,
		    "Call to saHpiHotSwapIndicatorStateGet failed with rc: %s\n",
		    get_error_string (rc));
	  DEBUGMSGTL ((AGENT,
		       "Call to  saHpiHotSwapIndicatorStateGet failed with rc: %s\n",
		       get_error_string (rc)));
	  return AGENT_ERR_OPERATION;
	}
      // Update the new value to ctx.
      ctx->saHpiHotSwapIndicator = indication_state + 1;
      return AGENT_ERR_NOERROR;
    }
  return AGENT_ERR_NULL_DATA;
}

int
set_hotswap_powerstate (saHpiHotSwapTable_context * ctx)
{


  SaHpiSessionIdT session_id;
  SaErrorT rc;
  SaHpiHsPowerStateT power_state;

  if (ctx)
    {
      power_state = ctx->saHpiHotSwapPowerState - 1;
      // Get the seesion_id
      rc = getSaHpiSession (&session_id);
      if (rc != AGENT_ERR_NOERROR)
	{
	  DEBUGMSGTL ((AGENT, "Call to getSaHpiSession failed with rc: %d\n",
		       rc));
	  return rc;
	}

      // Set the new value
      DEBUGMSGTL ((AGENT, "Calling  saHpiResourcePowerStateSet with %d\n",
		   ctx->resource_id));
      rc =
	saHpiResourcePowerStateSet (session_id, ctx->resource_id,
				    power_state);


      if (rc != SA_OK)
	{
	  snmp_log (LOG_ERR,
		    "Call to saHpiResourcePowerStateSet failed with return code: %s\n",
		    get_error_string (rc));
	  DEBUGMSGTL ((AGENT,
		       "Call to saHpiResourcePowerStateSet  failed with return code: %s\n",
		       get_error_string (rc)));
	  return AGENT_ERR_OPERATION;
	}

      // Get the new value
      DEBUGMSGTL ((AGENT, "Calling with saHpiResourcePowerStateGet %d\n",
		   ctx->resource_id));

      rc = saHpiResourcePowerStateGet (session_id, ctx->resource_id,
				       &power_state);


      if (rc != SA_OK)
	{
	  snmp_log (LOG_ERR,
		    "Call to saHpiResourcePowerStateGet failed with rc: %s\n",
		    get_error_string (rc));
	  DEBUGMSGTL ((AGENT,
		       "Call to saHpiResourcePowerStateGet failed with rc: %s\n",
		       get_error_string (rc)));
	  return AGENT_ERR_OPERATION;
	}
      // Update the new value to ctx.
      ctx->saHpiHotSwapPowerState = power_state - 1;
      return AGENT_ERR_NOERROR;
    }
  return AGENT_ERR_NULL_DATA;
}

int
set_hotswap_reset_state (saHpiHotSwapTable_context * ctx)
{


  SaHpiSessionIdT session_id;
  SaErrorT rc;
  SaHpiResetActionT reset_action;
  if (ctx)
    {
      reset_action = ctx->saHpiHotSwapResetState - 1;
      // Get the seesion_id
      rc = getSaHpiSession (&session_id);
      if (rc != AGENT_ERR_NOERROR)
	{
	  DEBUGMSGTL ((AGENT, "Call to getSaHpiSession failed with rc: %d\n",
		       rc));
	  return rc;
	}

      // Set the new value
      DEBUGMSGTL ((AGENT, "Calling saHpiResourceResetStateSet with %d\n",
		   ctx->resource_id));
      rc =
	saHpiResourceResetStateSet (session_id, ctx->resource_id,
				    reset_action);


      if (rc != SA_OK)
	{
	  snmp_log (LOG_ERR,
		    "Call to  saHpiResourceResetStateSetfailed with return code: %s\n",
		    get_error_string (rc));
	  DEBUGMSGTL ((AGENT,
		       "Call saHpiResourceResetStateSet failed with return code: %s\n",
		       get_error_string (rc)));
	  return AGENT_ERR_OPERATION;
	}

      // Get the new value
      DEBUGMSGTL ((AGENT, "Calling saHpiResourceResetStateGet with %d\n",
		   ctx->resource_id));

      rc = saHpiResourceResetStateGet (session_id, ctx->resource_id,
				       &reset_action);


      if (rc != SA_OK)
	{
	  snmp_log (LOG_ERR,
		    "Call to saHpiResourceResetStateGet failed with rc: %s\n",
		    get_error_string (rc));
	  DEBUGMSGTL ((AGENT,
		       "Call to  saHpiResourceResetStateGet failed with rc: %s\n",
		       get_error_string (rc)));
	  return AGENT_ERR_OPERATION;
	}
      // Update the new value to ctx.
      ctx->saHpiHotSwapResetState = reset_action + 1;
      return AGENT_ERR_NOERROR;
    }
  return AGENT_ERR_NULL_DATA;
}

int
set_hotswap_insert_t (saHpiHotSwapTable_context * ctx)
{


  SaHpiSessionIdT session_id;
  SaErrorT rc;
  SaHpiTimeoutT time;

  if (ctx)
    {
      time = ctx->saHpiHotSwapInsertTimeout;

      // Get the seesion_id
      rc = getSaHpiSession (&session_id);
      if (rc != AGENT_ERR_NOERROR)
	{
	  DEBUGMSGTL ((AGENT, "Call to getSaHpiSession failed with rc: %d\n",
		       rc));
	  return rc;
	}

      // Set the new value
      DEBUGMSGTL ((AGENT, "Calling saHpiAutoInsertTimeoutSet  with %d\n",
		   ctx->resource_id));
      rc = saHpiAutoInsertTimeoutSet (session_id, time);


      if (rc != SA_OK)
	{
	  snmp_log (LOG_ERR,
		    "Call to saHpiAutoInsertTimeoutSet  failed with return code: %s\n",
		    get_error_string (rc));
	  DEBUGMSGTL ((AGENT,
		       "Call saHpiAutoInsertTimeoutSet failed with return code: %s\n",
		       get_error_string (rc)));
	  return AGENT_ERR_OPERATION;
	}

      // Get the new value
      DEBUGMSGTL ((AGENT, "Calling saHpiAutoInsertTimeoutGet  with %d\n",
		   ctx->resource_id));

      rc = saHpiAutoInsertTimeoutGet (session_id, &time);


      if (rc != SA_OK)
	{
	  snmp_log (LOG_ERR,
		    "Call to saHpiAutoInsertTimeoutGet failed with rc: %s\n",
		    get_error_string (rc));
	  DEBUGMSGTL ((AGENT,
		       "Call to saHpiAutoInsertTimeoutGet  failed with rc: %s\n",
		       get_error_string (rc)));
	  return AGENT_ERR_OPERATION;
	}
      // Update the new value to ctx.
      ctx->saHpiHotSwapInsertTimeout = time;
      return AGENT_ERR_NOERROR;
    }
  return AGENT_ERR_NULL_DATA;
}


int
set_hotswap_extract_t (saHpiHotSwapTable_context * ctx)
{


  SaHpiSessionIdT session_id;
  SaErrorT rc;
  SaHpiTimeoutT time;

  if (ctx)
    {
      time = ctx->saHpiHotSwapExtractTimeout;

      // Get the seesion_id
      rc = getSaHpiSession (&session_id);
      if (rc != AGENT_ERR_NOERROR)
	{
	  DEBUGMSGTL ((AGENT, "Call to getSaHpiSession failed with rc: %d\n",
		       rc));
	  return rc;
	}

      // Set the new value
      DEBUGMSGTL ((AGENT, "Calling saHpiAutoExtractTimeoutSet  with %d\n",
		   ctx->resource_id));
      rc = saHpiAutoExtractTimeoutSet (session_id, ctx->resource_id, time);


      if (rc != SA_OK)
	{
	  snmp_log (LOG_ERR,
		    "Call to saHpiAutoExtractTimeoutSet  failed with return code: %s\n",
		    get_error_string (rc));
	  DEBUGMSGTL ((AGENT,
		       "Call saHpiAutoExtractTimeoutSet failed with return code: %s\n",
		       get_error_string (rc)));
	  return AGENT_ERR_OPERATION;
	}

      // Get the new value
      DEBUGMSGTL ((AGENT, "Calling saHpiAutoExtractTimeoutGet  with %d\n",
		   ctx->resource_id));

      rc = saHpiAutoExtractTimeoutGet (session_id, ctx->resource_id, &time);


      if (rc != SA_OK)
	{
	  snmp_log (LOG_ERR,
		    "Call to saHpiAutoExtractTimeoutGet failed with rc: %s\n",
		    get_error_string (rc));
	  DEBUGMSGTL ((AGENT,
		       "Call to saHpiAutoExtractTimeoutGet  failed with rc: %s\n",
		       get_error_string (rc)));
	  return AGENT_ERR_OPERATION;
	}
      // Update the new value to ctx.
      ctx->saHpiHotSwapExtractTimeout = time;
      return AGENT_ERR_NOERROR;
    }
  return AGENT_ERR_NULL_DATA;
}

int
set_hotswap_action_request (saHpiHotSwapTable_context * ctx)
{


  SaHpiSessionIdT session_id;
  SaErrorT rc;
  SaHpiHsActionT action;

  if (ctx)
    {
      action = ctx->saHpiHotSwapActionRequest - 1;
      // Get the seesion_id
      rc = getSaHpiSession (&session_id);
      if (rc != AGENT_ERR_NOERROR)
	{
	  DEBUGMSGTL ((AGENT, "Call to getSaHpiSession failed with rc: %d\n",
		       rc));
	  return rc;
	}

      // Set the new value
      DEBUGMSGTL ((AGENT, "Calling saHpiHotSwapActionRequest with %d\n",
		   ctx->resource_id));
      rc = saHpiHotSwapActionRequest (session_id, ctx->resource_id, action);


      if (rc != SA_OK)
	{
	  snmp_log (LOG_ERR,
		    "Call to  saHpiHotSwapActionRequest failed with return code: %s\n",
		    get_error_string (rc));
	  DEBUGMSGTL ((AGENT,
		       "Call to saHpiHotSwapActionRequest failed with return code: %s\n",
		       get_error_string (rc)));
	  return AGENT_ERR_OPERATION;
	}

      ctx->saHpiHotSwapActionRequest = action + 1;
      return AGENT_ERR_NOERROR;
    }
  return AGENT_ERR_NULL_DATA;
}


int
delete_hotswap_row (SaHpiDomainIdT domain_id, SaHpiResourceIdT resource_id)
{

  saHpiHotSwapTable_context *ctx;
  oid hotswap_oid[HOTSWAP_INDEX_NR];
  netsnmp_index hotswap_index;
  int rc = AGENT_ERR_NOT_FOUND;

  DEBUGMSGTL ((AGENT, "delete_hotswap_row (%d, %d). Entry\n",
	       domain_id, resource_id));

  hotswap_oid[0] = domain_id;
  hotswap_oid[1] = resource_id;


  // Possible more indexs?
  hotswap_index.oids = (oid *) & hotswap_oid;
  hotswap_index.len = HOTSWAP_INDEX_NR;

  ctx = CONTAINER_FIND (cb.container, &hotswap_index);

  if (ctx)
    {
      CONTAINER_REMOVE (cb.container, ctx);
      saHpiHotSwapTable_delete_row (ctx);
      rc = AGENT_ERR_NOERROR;
    }
  DEBUGMSGTL ((AGENT, "delete_hotswap_row. Exit (rc: %d).\n", rc));
  return rc;
}

int
update_hotswap_event (SaHpiDomainIdT domain_id,
		      SaHpiResourceIdT resource_id,
		      SaHpiHotSwapEventT * event)
{

  saHpiHotSwapTable_context *ctx;
  oid hotswap_oid[HOTSWAP_INDEX_NR];
  netsnmp_index hotswap_index;
  int rc = AGENT_ERR_NOT_FOUND;

  hotswap_oid[0] = domain_id;
  hotswap_oid[1] = resource_id;

  // Possible more indexs?
  hotswap_index.oids = (oid *) & hotswap_oid;
  hotswap_index.len = HOTSWAP_INDEX_NR;

  ctx = CONTAINER_FIND (cb.container, &hotswap_index);

  if (ctx)
    {
      ctx->saHpiHotSwapState = event->HotSwapState + 1;
      ctx->saHpiHotSwapPreviousState = event->PreviousHotSwapState + 1;
      rc = AGENT_ERR_NOERROR;
    }

  return rc;
}

/************************************************************
 * the *_row_copy routine
 */
static int
saHpiHotSwapTable_row_copy (saHpiHotSwapTable_context * dst,
			    saHpiHotSwapTable_context * src)
{
  if (!dst || !src)
    return 1;

  /*
   * copy index, if provided
   */
  if (dst->index.oids)
    free (dst->index.oids);
  if (snmp_clone_mem ((void *) &dst->index.oids, src->index.oids,
		      src->index.len * sizeof (oid)))
    {
      dst->index.oids = NULL;
      return 1;
    }
  dst->index.len = src->index.len;


  /*
   * copy components into the context structure
   */

  dst->saHpiHotSwapIndicator = src->saHpiHotSwapIndicator;

  dst->saHpiHotSwapPowerState = src->saHpiHotSwapPowerState;

  dst->saHpiHotSwapResetState = src->saHpiHotSwapResetState;

  dst->saHpiHotSwapState = src->saHpiHotSwapState;

  dst->saHpiHotSwapPreviousState = src->saHpiHotSwapPreviousState;

  dst->saHpiHotSwapEventSeverity = src->saHpiHotSwapEventSeverity;

  dst->saHpiHotSwapInsertTimeout = src->saHpiHotSwapInsertTimeout;

  dst->saHpiHotSwapExtractTimeout = src->saHpiHotSwapExtractTimeout;

  dst->saHpiHotSwapActionRequest = src->saHpiHotSwapActionRequest;

  memcpy (src->saHpiHotSwapRTP, dst->saHpiHotSwapRTP,
	  src->saHpiHotSwapRTP_len);
  dst->saHpiHotSwapRTP_len = src->saHpiHotSwapRTP_len;

  dst->domain_id = src->domain_id;
  dst->hash = src->hash;
  dst->resource_id = src->resource_id;
  return 0;
}


/*
 * the *_extract_index routine
 */
int
saHpiHotSwapTable_extract_index (saHpiHotSwapTable_context * ctx,
				 netsnmp_index * hdr)
{
  /*
   * temporary local storage for extracting oid index
   */
  netsnmp_variable_list var_saHpiDomainID;
  netsnmp_variable_list var_saHpiResourceID;
  int err;

  /*
   * copy index, if provided
   */
  if (hdr)
    {
      netsnmp_assert (ctx->index.oids == NULL);
      if (snmp_clone_mem ((void *) &ctx->index.oids, hdr->oids,
			  hdr->len * sizeof (oid)))
	{
	  return -1;
	}
      ctx->index.len = hdr->len;
    }

    /**
     * Create variable to hold each component of the index
     */
  memset (&var_saHpiDomainID, 0x00, sizeof (var_saHpiDomainID));
  var_saHpiDomainID.type = ASN_UNSIGNED;
  var_saHpiDomainID.next_variable = &var_saHpiResourceID;

  memset (&var_saHpiResourceID, 0x00, sizeof (var_saHpiResourceID));
  var_saHpiResourceID.type = ASN_UNSIGNED;
  var_saHpiResourceID.next_variable = NULL;

  /*
   * parse the oid into the individual components
   */
  err = parse_oid_indexes (hdr->oids, hdr->len, &var_saHpiDomainID);


  /*
   * parsing may have allocated memory. free it.
   */
  snmp_reset_var_buffers (&var_saHpiDomainID);

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
saHpiHotSwapTable_can_delete (saHpiHotSwapTable_context * undo_ctx,
			      saHpiHotSwapTable_context * row_ctx,
			      netsnmp_request_group * rg)
{

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
 * returns a newly allocated saHpiHotSwapTable_context
 *   structure if the specified indexes are not illegal
 * returns NULL for errors or illegal index values.
 */
saHpiHotSwapTable_context *
saHpiHotSwapTable_create_row (netsnmp_index * hdr)
{
  saHpiHotSwapTable_context *ctx =
    SNMP_MALLOC_TYPEDEF (saHpiHotSwapTable_context);
  if (!ctx)
    return NULL;


  if (saHpiHotSwapTable_extract_index (ctx, hdr))
    {
      free (ctx->index.oids);
      free (ctx);
      return NULL;
    }

  ctx->saHpiHotSwapIndicator = 0;
  ctx->saHpiHotSwapPowerState = 0;
  ctx->saHpiHotSwapResetState = 0;
  ctx->saHpiHotSwapState = 0;
  ctx->saHpiHotSwapPreviousState = 0;
  ctx->saHpiHotSwapInsertTimeout = 0;
  ctx->saHpiHotSwapExtractTimeout = 0;
  ctx->saHpiHotSwapActionRequest = 0;
  ctx->hash = 0;

  return ctx;
}


/************************************************************
 * the *_duplicate row routine
 */
saHpiHotSwapTable_context *
saHpiHotSwapTable_duplicate_row (saHpiHotSwapTable_context * row_ctx)
{
  saHpiHotSwapTable_context *dup;

  if (!row_ctx)
    return NULL;

  dup = SNMP_MALLOC_TYPEDEF (saHpiHotSwapTable_context);
  if (!dup)
    return NULL;

  if (saHpiHotSwapTable_row_copy (dup, row_ctx))
    {
      free (dup);
      dup = NULL;
    }

  return dup;
}

/************************************************************
 * the *_delete_row method is called to delete a row.
 */
netsnmp_index *
saHpiHotSwapTable_delete_row (saHpiHotSwapTable_context * ctx)
{

  if (ctx->index.oids)
    free (ctx->index.oids);

  free (ctx);

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
saHpiHotSwapTable_set_reserve1 (netsnmp_request_group * rg)
{
  saHpiHotSwapTable_context *row_ctx =
    (saHpiHotSwapTable_context *) rg->existing_row;

  netsnmp_variable_list *var;
  netsnmp_request_group_item *current;
  int rc;


  DEBUGMSGTL ((AGENT, "saHpiHotSwapTable_set_reserve1: Entry.\n"));
  for (current = rg->list; current; current = current->next)
    {

      var = current->ri->requestvb;
      rc = SNMP_ERR_NOERROR;

      switch (current->tri->colnum)
	{

	case COLUMN_SAHPIHOTSWAPINDICATOR:
	    /** INTEGER = ASN_INTEGER */
	  rc = netsnmp_check_vb_type_and_size (var, ASN_INTEGER,
					       sizeof (row_ctx->
						       saHpiHotSwapIndicator));
	  break;

	case COLUMN_SAHPIHOTSWAPPOWERSTATE:
	    /** INTEGER = ASN_INTEGER */
	  rc = netsnmp_check_vb_type_and_size (var, ASN_INTEGER,
					       sizeof (row_ctx->
						       saHpiHotSwapPowerState));
	  break;

	case COLUMN_SAHPIHOTSWAPRESETSTATE:
	    /** INTEGER = ASN_INTEGER */
	  rc = netsnmp_check_vb_type_and_size (var, ASN_INTEGER,
					       sizeof (row_ctx->
						       saHpiHotSwapResetState));
	  break;

	case COLUMN_SAHPIHOTSWAPSTATE:
	    /** INTEGER = ASN_INTEGER */
	case COLUMN_SAHPIHOTSWAPPREVIOUSSTATE:
	    /** INTEGER = ASN_INTEGER */
	case COLUMN_SAHPIHOTSWAPEVENTSEVERITY:
	  rc = SNMP_ERR_NOTWRITABLE;
	  break;
	case COLUMN_SAHPIHOTSWAPINSERTTIMEOUT:
	    /** UNSIGNED32 = ASN_UNSIGNED */
	  rc = netsnmp_check_vb_type_and_size (var, ASN_UNSIGNED,
					       sizeof (row_ctx->
						       saHpiHotSwapInsertTimeout));
	  break;

	case COLUMN_SAHPIHOTSWAPEXTRACTTIMEOUT:
	    /** UNSIGNED32 = ASN_UNSIGNED */
	  rc = netsnmp_check_vb_type_and_size (var, ASN_UNSIGNED,
					       sizeof (row_ctx->
						       saHpiHotSwapExtractTimeout));
	  break;

	case COLUMN_SAHPIHOTSWAPACTIONREQUEST:
	    /** INTEGER = ASN_INTEGER */
	  rc = netsnmp_check_vb_type_and_size (var, ASN_INTEGER,
					       sizeof (row_ctx->
						       saHpiHotSwapActionRequest));
	  break;
	case COLUMN_SAHPIHOTSWAPRTP:
	  rc = SNMP_ERR_NOTWRITABLE;
	  break;
	default:
		/** We shouldn't get here */
	  rc = SNMP_ERR_GENERR;
	  snmp_log (LOG_ERR, "unknown column in "
		    "saHpiHotSwapTable_set_reserve1\n");
	}

      if (rc)
	netsnmp_set_mode_request_error (MODE_SET_BEGIN, current->ri, rc);
      rg->status = SNMP_MAX (rg->status, current->ri->status);
    }
  for (current = rg->list; current; current = current->next)
    {

      // The nice thing about this API is that _row_copy() is called
      // for this row - if the API has matched the index with an
      // already existing entry. We check the 'hash' value. If its
      // 0 the API couldn't find the right context.

      if (row_ctx->hash == 0)
	{
	  netsnmp_set_mode_request_error (MODE_SET_BEGIN, current->ri,
					  SNMP_ERR_NOSUCHNAME);
	}
    }
  DEBUGMSGTL ((AGENT, "saHpiHotSwapTable_set_reserve1: Exit.\n"));
}

void
saHpiHotSwapTable_set_reserve2 (netsnmp_request_group * rg)
{

  netsnmp_request_group_item *current;
  netsnmp_variable_list *var;
  int rc;

  rg->rg_void = rg->list->ri;
  DEBUGMSGTL ((AGENT, "saHpiHotSwapTable_set_reserve2: Entry.\n"));

  for (current = rg->list; current; current = current->next)
    {

      var = current->ri->requestvb;
      rc = SNMP_ERR_NOERROR;

      switch (current->tri->colnum)
	{

	case COLUMN_SAHPIHOTSWAPINDICATOR:
	  if ((*var->val.integer < 1) || (*var->val.integer > 2))
	    rc = SNMP_ERR_BADVALUE;

	  break;

	case COLUMN_SAHPIHOTSWAPPOWERSTATE:
	  if ((*var->val.integer < 1) || (*var->val.integer > 3))
	    rc = SNMP_ERR_BADVALUE;
	  break;

	case COLUMN_SAHPIHOTSWAPRESETSTATE:
	  if ((*var->val.integer < 1) || (*var->val.integer > 4))
	    rc = SNMP_ERR_BADVALUE;

	  break;

	case COLUMN_SAHPIHOTSWAPSTATE:
	    /** INTEGER = ASN_INTEGER */
	  if ((*var->val.integer < 1) || (*var->val.integer > 6))
	    rc = SNMP_ERR_BADVALUE;
	  break;

	case COLUMN_SAHPIHOTSWAPPREVIOUSSTATE:
	    /** INTEGER = ASN_INTEGER */
	  // Its  read-only object.
	  break;

	case COLUMN_SAHPIHOTSWAPINSERTTIMEOUT:
	    /** UNSIGNED32 = ASN_UNSIGNED */

	  break;

	case COLUMN_SAHPIHOTSWAPEXTRACTTIMEOUT:
	    /** UNSIGNED32 = ASN_UNSIGNED */

	  break;

	case COLUMN_SAHPIHOTSWAPACTIONREQUEST:
	    /** INTEGER = ASN_INTEGER */
	  if ((*var->val.integer < 1) || (*var->val.integer > 2))
	    rc = SNMP_ERR_BADVALUE;
	  break;

	default:
		/** We shouldn't get here */
	  netsnmp_assert (0);  /** why wasn't this caught in reserve1? */
	}

      if (rc)
	netsnmp_set_mode_request_error (MODE_SET_BEGIN, current->ri, rc);
    }

  /*
   * done with all the columns. Could check row related
   * requirements here.
   */
  DEBUGMSGTL ((AGENT, "saHpiHotSwapTable_set_reserve2: Exit.\n"));
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
saHpiHotSwapTable_set_action (netsnmp_request_group * rg)
{
  netsnmp_variable_list *var;
  saHpiHotSwapTable_context *row_ctx =
    (saHpiHotSwapTable_context *) rg->existing_row;

  netsnmp_request_group_item *current;

  int rc = SNMP_ERR_NOERROR;

  DEBUGMSGTL ((AGENT, "saHpiHotSwapTable_set_reserve: Entry.\n"));

  for (current = rg->list; current; current = current->next)
    {

      var = current->ri->requestvb;

      switch (current->tri->colnum)
	{
	case COLUMN_SAHPIHOTSWAPINDICATOR:
	    /** INTEGER = ASN_INTEGER */
	  row_ctx->saHpiHotSwapIndicator = *var->val.integer;
	  if (set_hotswap_indicator (row_ctx) != AGENT_ERR_NOERROR)
	    rc = SNMP_ERR_INCONSISTENTVALUE;

	  break;

	case COLUMN_SAHPIHOTSWAPPOWERSTATE:
	    /** INTEGER = ASN_INTEGER */
	  row_ctx->saHpiHotSwapPowerState = *var->val.integer;
	  if (set_hotswap_powerstate (row_ctx) != AGENT_ERR_NOERROR)
	    rc = SNMP_ERR_INCONSISTENTVALUE;
	  break;

	case COLUMN_SAHPIHOTSWAPRESETSTATE:
	    /** INTEGER = ASN_INTEGER */
	  row_ctx->saHpiHotSwapResetState = *var->val.integer;
	  if (set_hotswap_reset_state (row_ctx) != AGENT_ERR_NOERROR)
	    rc = SNMP_ERR_INCONSISTENTVALUE;
	  break;

	case COLUMN_SAHPIHOTSWAPINSERTTIMEOUT:
	    /** UNSIGNED32 = ASN_UNSIGNED */
	  row_ctx->saHpiHotSwapInsertTimeout = *var->val.integer;
	  if (set_hotswap_insert_t (row_ctx) != AGENT_ERR_NOERROR)
	    rc = SNMP_ERR_INCONSISTENTVALUE;
	  break;

	case COLUMN_SAHPIHOTSWAPEXTRACTTIMEOUT:
	    /** UNSIGNED32 = ASN_UNSIGNED */
	  row_ctx->saHpiHotSwapExtractTimeout = *var->val.integer;
	  if (set_hotswap_extract_t (row_ctx) != AGENT_ERR_NOERROR)
	    rc = SNMP_ERR_INCONSISTENTVALUE;
	  break;

	case COLUMN_SAHPIHOTSWAPACTIONREQUEST:
	    /** INTEGER = ASN_INTEGER */
	  row_ctx->saHpiHotSwapActionRequest = *var->val.integer;
	  if (set_hotswap_action_request (row_ctx) != AGENT_ERR_NOERROR)
	    rc = SNMP_ERR_INCONSISTENTVALUE;
	  break;

	default:
		/** We shouldn't get here */
	  netsnmp_assert (0);  /** why wasn't this caught in reserve1? */
	}

      if (rc)
	netsnmp_set_mode_request_error (MODE_SET_BEGIN, current->ri, rc);
    }
  DEBUGMSGTL ((AGENT, "saHpiHotSwapTable_set_action: Exit.\n"));
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
saHpiHotSwapTable_set_commit (netsnmp_request_group * rg)
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
saHpiHotSwapTable_set_free (netsnmp_request_group * rg)
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
saHpiHotSwapTable_set_undo (netsnmp_request_group * rg)
{

}




/************************************************************
 *
 * Initialize the saHpiHotSwapTable table by defining its contents and how it's structured
 */
void
initialize_table_saHpiHotSwapTable (void)
{
  netsnmp_table_registration_info *table_info;

  if (my_handler)
    {
      snmp_log (LOG_ERR,
		"initialize_table_saHpiHotSwapTable_handler called again\n");
      return;
    }

  memset (&cb, 0x00, sizeof (cb));

    /** create the table structure itself */
  table_info = SNMP_MALLOC_TYPEDEF (netsnmp_table_registration_info);

  /*
   * if your table is read only, it's easiest to change the
   * HANDLER_CAN_RWRITE definition below to HANDLER_CAN_RONLY 
   */
  my_handler = netsnmp_create_handler_registration ("saHpiHotSwapTable",
						    netsnmp_table_array_helper_handler,
						    saHpiHotSwapTable_oid,
						    saHpiHotSwapTable_oid_len,
						    HANDLER_CAN_RWRITE);

  if (!my_handler || !table_info)
    {
      snmp_log (LOG_ERR, "malloc failed in "
		"initialize_table_saHpiHotSwapTable_handler\n");
      return;	/** mallocs failed */
    }

    /***************************************************
     * Setting up the table's definition
     */

  /*
   * internal indexes
   */
	/** index: saHpiDomainID */
  netsnmp_table_helper_add_index (table_info, ASN_UNSIGNED);
	/** index: saHpiResourceID */
  netsnmp_table_helper_add_index (table_info, ASN_UNSIGNED);

  table_info->min_column = saHpiHotSwapTable_COL_MIN;
  table_info->max_column = saHpiHotSwapTable_COL_MAX;

    /***************************************************
     * registering the table with the master agent
     */
  cb.get_value = saHpiHotSwapTable_get_value;
  cb.container = netsnmp_container_find ("saHpiHotSwapTable_primary:"
					 "saHpiHotSwapTable:"
					 "table_container");



  cb.create_row = (UserRowMethod *) saHpiHotSwapTable_create_row;

  cb.duplicate_row = (UserRowMethod *) saHpiHotSwapTable_duplicate_row;
  cb.delete_row = (UserRowMethod *) saHpiHotSwapTable_delete_row;
  cb.row_copy = (Netsnmp_User_Row_Operation *) saHpiHotSwapTable_row_copy;


  cb.can_delete = (Netsnmp_User_Row_Action *) saHpiHotSwapTable_can_delete;

  cb.set_reserve1 = saHpiHotSwapTable_set_reserve1;
  cb.set_reserve2 = saHpiHotSwapTable_set_reserve2;
  cb.set_action = saHpiHotSwapTable_set_action;
  cb.set_commit = saHpiHotSwapTable_set_commit;
  cb.set_free = saHpiHotSwapTable_set_free;
  cb.set_undo = saHpiHotSwapTable_set_undo;

  DEBUGMSGTL (("initialize_table_saHpiHotSwapTable",
	       "Registering table saHpiHotSwapTable " "as a table array\n"));
  netsnmp_table_container_register (my_handler, table_info, &cb,
				    cb.container, 1);
}

/************************************************************
 * saHpiHotSwapTable_get_value
 */
int
saHpiHotSwapTable_get_value (netsnmp_request_info * request,
			     netsnmp_index * item,
			     netsnmp_table_request_info * table_info)
{
  netsnmp_variable_list *var = request->requestvb;
  saHpiHotSwapTable_context *context = (saHpiHotSwapTable_context *) item;

#ifdef GET_ROUTINE_CALLS_SNMP_GET
saHpiHotSwapTable_modify_context (NULL,
				NULL, -1,
			        context);
#endif
  switch (table_info->colnum)
    {

    case COLUMN_SAHPIHOTSWAPINDICATOR:
	    /** INTEGER = ASN_INTEGER */
      snmp_set_var_typed_value (var, ASN_INTEGER,
				(char *) &context->saHpiHotSwapIndicator,
				sizeof (context->saHpiHotSwapIndicator));
      break;

    case COLUMN_SAHPIHOTSWAPPOWERSTATE:
	    /** INTEGER = ASN_INTEGER */
      snmp_set_var_typed_value (var, ASN_INTEGER,
				(char *) &context->saHpiHotSwapPowerState,
				sizeof (context->saHpiHotSwapPowerState));
      break;

    case COLUMN_SAHPIHOTSWAPRESETSTATE:
	    /** INTEGER = ASN_INTEGER */
      snmp_set_var_typed_value (var, ASN_INTEGER,
				(char *) &context->saHpiHotSwapResetState,
				sizeof (context->saHpiHotSwapResetState));
      break;

    case COLUMN_SAHPIHOTSWAPSTATE:
	    /** INTEGER = ASN_INTEGER */
      snmp_set_var_typed_value (var, ASN_INTEGER,
				(char *) &context->saHpiHotSwapState,
				sizeof (context->saHpiHotSwapState));
      break;

    case COLUMN_SAHPIHOTSWAPPREVIOUSSTATE:
	    /** INTEGER = ASN_INTEGER */
      snmp_set_var_typed_value (var, ASN_INTEGER,
				(char *) &context->
				saHpiHotSwapPreviousState,
				sizeof (context->saHpiHotSwapPreviousState));
      break;

    case COLUMN_SAHPIHOTSWAPEVENTSEVERITY:
	    /** INTEGER = ASN_INTEGER */
      snmp_set_var_typed_value (var, ASN_INTEGER,
				(char *) &context->
				saHpiHotSwapEventSeverity,
				sizeof (context->saHpiHotSwapEventSeverity));
      break;

    case COLUMN_SAHPIHOTSWAPINSERTTIMEOUT:
	    /** UNSIGNED32 = ASN_UNSIGNED */
      snmp_set_var_typed_value (var, ASN_UNSIGNED,
				(char *) &context->
				saHpiHotSwapInsertTimeout,
				sizeof (context->saHpiHotSwapInsertTimeout));
      break;

    case COLUMN_SAHPIHOTSWAPEXTRACTTIMEOUT:
	    /** UNSIGNED32 = ASN_UNSIGNED */
      snmp_set_var_typed_value (var, ASN_UNSIGNED,
				(char *) &context->
				saHpiHotSwapExtractTimeout,
				sizeof (context->saHpiHotSwapExtractTimeout));
      break;

    case COLUMN_SAHPIHOTSWAPACTIONREQUEST:
	    /** INTEGER = ASN_INTEGER */
      snmp_set_var_typed_value (var, ASN_INTEGER,
				(char *) &context->
				saHpiHotSwapActionRequest,
				sizeof (context->saHpiHotSwapActionRequest));
      break;

    case COLUMN_SAHPIHOTSWAPRTP:
	    /** RowPointer = ASN_OBJECT_ID */
      snmp_set_var_typed_value (var, ASN_OBJECT_ID,
				(char *) &context->saHpiHotSwapRTP,
				context->saHpiHotSwapRTP_len);
      break;

    default:
	    /** We shouldn't get here */
      snmp_log (LOG_ERR, "unknown column in "
		"saHpiHotSwapTable_get_value\n");
      return SNMP_ERR_GENERR;
    }
  return SNMP_ERR_NOERROR;
}
