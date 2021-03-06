/*
 * Note: this file originally auto-generated by mib2c using
 *       : mib2c.array-user.conf,v 5.15.2.1 2003/02/27 05:59:41 rstory Exp $
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
 *     http://www.net-snmp.org/tutorial/
 *
 *
 * You can also join the #net-snmp channel on irc.openprojects.net
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

#include "saHpiSensorsTable.h"

static netsnmp_handler_registration *my_handler = NULL;
static netsnmp_table_array_callbacks cb;

oid             saHpiSensorsTable_oid[] = { saHpiSensorsTable_TABLE_OID };
size_t          saHpiSensorsTable_oid_len =
OID_LENGTH(saHpiSensorsTable_oid);


#ifdef saHpiSensorsTable_IDX2
/************************************************************
 * keep binary tree to find context by name
 */
static int      saHpiSensorsTable_cmp(const void *lhs, const void *rhs);

/************************************************************
 * compare two context pointers here. Return -1 if lhs < rhs,
 * 0 if lhs == rhs, and 1 if lhs > rhs.
 */
static int
saHpiSensorsTable_cmp(const void *lhs, const void *rhs)
{
    saHpiSensorsTable_context *context_l =
        (saHpiSensorsTable_context *) lhs;
    saHpiSensorsTable_context *context_r =
        (saHpiSensorsTable_context *) rhs;

    /*
     * check primary key, then secondary. Add your own code if
     * there are more than 2 indexes
     */
    int             rc;

    /*
     * TODO: implement compare. Remove this ifdef code and
     * add your own code here.
     */
#ifdef TABLE_CONTAINER_TODO
    snmp_log(LOG_ERR,
             "saHpiSensorsTable_compare not implemented! Container order undefined\n");
    return 0;
#endif

    /*
     * EXAMPLE:
     *   
     * rc = strcmp( context_l->xxName, context_r->xxName);
     *
     * if(rc)
     *   return rc;
     *
     * TODO: fix secondary keys (or delete if there are none)
     *
     * if(context_l->yy < context_r->yy) 
     *   return -1;
     *
     * return (context_l->yy == context_r->yy) ? 0 : 1;
     */
}

/************************************************************
 * search tree
 */
/** TODO: set additional indexes as parameters */
saHpiSensorsTable_context *
saHpiSensorsTable_get(const char *name, int len)
{
    saHpiSensorsTable_context tmp;

    /** we should have a secondary index */
    netsnmp_assert(cb.container->next != NULL);

    /*
     * TODO: implement compare. Remove this ifdef code and
     * add your own code here.
     */
#ifdef TABLE_CONTAINER_TODO
    snmp_log(LOG_ERR, "saHpiSensorsTable_get not implemented!\n");
    return NULL;
#endif

    /*
     * EXAMPLE:
     *
     * if(len > sizeof(tmp.xxName))
     *   return NULL;
     *
     * strncpy( tmp.xxName, name, sizeof(tmp.xxName) );
     * tmp.xxName_len = len;
     *
     * return CONTAINER_FIND(cb.container->next, &tmp);
     */
}
#endif


/************************************************************
 * Initializes the saHpiSensorsTable module
 */
void
init_saHpiSensorsTable(void)
{
    initialize_table_saHpiSensorsTable();

    /*
     * TODO: perform any startup stuff here
     */
}

/************************************************************
 * the *_row_copy routine
 */
static int
saHpiSensorsTable_row_copy(saHpiSensorsTable_context * dst,
                           saHpiSensorsTable_context * src)
{
    if (!dst || !src)
        return 1;

    /*
     * copy index, if provided
     */
    if (dst->index.oids)
        free(dst->index.oids);
    if (snmp_clone_mem((void *) &dst->index.oids, src->index.oids,
                       src->index.len * sizeof(oid))) {
        dst->index.oids = NULL;
        return 1;
    }
    dst->index.len = src->index.len;


    /*
     * copy components into the context structure
     */
    dst->saHpiSensorsIndex = src->saHpiSensorsIndex;

    dst->saHpiSensorsType = src->saHpiSensorsType;

    dst->saHpiSensorsCategory = src->saHpiSensorsCategory;

    dst->saHpiSensorsEventsCategoryControl =
        src->saHpiSensorsEventsCategoryControl;

    dst->saHpiSensorsEventsState = src->saHpiSensorsEventsState;

    memcpy(dst->saHpiSensorsIgnore, src->saHpiSensorsIgnore,
           src->saHpiSensorsIgnore_len);
    dst->saHpiSensorsIgnore_len = src->saHpiSensorsIgnore_len;

    dst->saHpiSensorsReadingFormats = src->saHpiSensorsReadingFormats;

    memcpy(dst->saHpiSensorsIsNumeric, src->saHpiSensorsIsNumeric,
           src->saHpiSensorsIsNumeric_len);
    dst->saHpiSensorsIsNumeric_len = src->saHpiSensorsIsNumeric_len;

    dst->saHpiSensorsSignFormat = src->saHpiSensorsSignFormat;

    dst->saHpiSensorsBaseUnits = src->saHpiSensorsBaseUnits;

    dst->saHpiSensorsModifierUnits = src->saHpiSensorsModifierUnits;

    dst->saHpiSensorsModifierUse = src->saHpiSensorsModifierUse;

    memcpy(dst->saHpiSensorsFactorsStatic, src->saHpiSensorsFactorsStatic,
           src->saHpiSensorsFactorsStatic_len);
    dst->saHpiSensorsFactorsStatic_len =
        src->saHpiSensorsFactorsStatic_len;

    memcpy(dst->saHpiSensorsFactors, src->saHpiSensorsFactors,
           src->saHpiSensorsFactors_len);
    dst->saHpiSensorsFactors_len = src->saHpiSensorsFactors_len;

    dst->saHpiSensorsFactorsLinearization =
        src->saHpiSensorsFactorsLinearization;

    memcpy(dst->saHpiSensorsPercentage, src->saHpiSensorsPercentage,
           src->saHpiSensorsPercentage_len);
    dst->saHpiSensorsPercentage_len = src->saHpiSensorsPercentage_len;

    dst->saHpiSensorsRangeFlags = src->saHpiSensorsRangeFlags;

    memcpy(dst->saHpiSensorsRangeReadingValuesPresent,
           src->saHpiSensorsRangeReadingValuesPresent,
           src->saHpiSensorsRangeReadingValuesPresent_len);
    dst->saHpiSensorsRangeReadingValuesPresent_len =
        src->saHpiSensorsRangeReadingValuesPresent_len;

    memcpy(dst->saHpiSensorsRangeReadingRaw,
           src->saHpiSensorsRangeReadingRaw,
           src->saHpiSensorsRangeReadingRaw_len);
    dst->saHpiSensorsRangeReadingRaw_len =
        src->saHpiSensorsRangeReadingRaw_len;

    memcpy(dst->saHpiSensorsRangeReadingInterpreted,
           src->saHpiSensorsRangeReadingInterpreted,
           src->saHpiSensorsRangeReadingInterpreted_len);
    dst->saHpiSensorsRangeReadingInterpreted_len =
        src->saHpiSensorsRangeReadingInterpreted_len;

    memcpy(dst->saHpiSensorsRangeReadingEventSensor,
           src->saHpiSensorsRangeReadingEventSensor,
           src->saHpiSensorsRangeReadingEventSensor_len);
    dst->saHpiSensorsRangeReadingEventSensor_len =
        src->saHpiSensorsRangeReadingEventSensor_len;

    memcpy(dst->saHpiSensorsThresholdDefnIsThreshold,
           src->saHpiSensorsThresholdDefnIsThreshold,
           src->saHpiSensorsThresholdDefnIsThreshold_len);
    dst->saHpiSensorsThresholdDefnIsThreshold_len =
        src->saHpiSensorsThresholdDefnIsThreshold_len;

    memcpy(dst->saHpiSensorsThresholdDefnTholdCapabilities,
           src->saHpiSensorsThresholdDefnTholdCapabilities,
           src->saHpiSensorsThresholdDefnTholdCapabilities_len);
    dst->saHpiSensorsThresholdDefnTholdCapabilities_len =
        src->saHpiSensorsThresholdDefnTholdCapabilities_len;

    dst->saHpiSensorsThresholdDefnReadThold =
        src->saHpiSensorsThresholdDefnReadThold;

    dst->saHpiSensorsThresholdDefnWriteThold =
        src->saHpiSensorsThresholdDefnWriteThold;

    dst->saHpiSensorsThresholdDefnFixedThold =
        src->saHpiSensorsThresholdDefnFixedThold;

    memcpy(dst->saHpiSensorsThresholdRaw, src->saHpiSensorsThresholdRaw,
           src->saHpiSensorsThresholdRaw_len);
    dst->saHpiSensorsThresholdRaw_len = src->saHpiSensorsThresholdRaw_len;

    memcpy(dst->saHpiSensorsThresholdInterpreted,
           src->saHpiSensorsThresholdInterpreted,
           src->saHpiSensorsThresholdInterpreted_len);
    dst->saHpiSensorsThresholdInterpreted_len =
        src->saHpiSensorsThresholdInterpreted_len;

    dst->saHpiSensorsOEM = src->saHpiSensorsOEM;

    return 0;
}

#ifdef saHpiSensorsTable_SET_HANDLING

/*
 * the *_extract_index routine
 */
int
saHpiSensorsTable_extract_index(saHpiSensorsTable_context * ctx,
                                netsnmp_index * hdr)
{
    /*
     * temporary local storage for extracting oid index
     */
    netsnmp_variable_list var_saHpiSensorsIndex;
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
    memset(&var_saHpiSensorsIndex, 0x00, sizeof(var_saHpiSensorsIndex));
    var_saHpiSensorsIndex.type = ASN_UNSIGNED;
       /** TODO: link this index to the next, or NULL for the last one */
#ifdef TABLE_CONTAINER_TODO
    snmp_log(LOG_ERR,
             "saHpiSensorsTable_extract_index index list not implemented!\n");
    return 0;
#else
    var_saHpiSensorsIndex.next_variable = &var_XX;
#endif


    /*
     * parse the oid into the individual components
     */
    err = parse_oid_indexes(hdr->oids, hdr->len, &var_saHpiSensorsIndex);
    if (err == SNMP_ERR_NOERROR) {
        /*
         * copy components into the context structure
         */
        ctx->saHpiSensorsIndex = *var_saHpiSensorsIndex.val.integer;


        /*
         * TODO: check index for valid values. For EXAMPLE:
         *
         * if ( *var_saHpiSensorsIndex.val.integer != XXX ) {
         *    err = -1;
         * }
         */
    }

    /*
     * parsing may have allocated memory. free it.
     */
    snmp_reset_var_buffers(&var_saHpiSensorsIndex);

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
saHpiSensorsTable_can_delete(saHpiSensorsTable_context * undo_ctx,
                             saHpiSensorsTable_context * row_ctx,
                             netsnmp_request_group * rg)
{

    /*
     * TODO: check for other deletion requirements here
     */
    return 1;
}

#ifdef saHpiSensorsTable_ROW_CREATION
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
 * returns a newly allocated saHpiSensorsTable_context
 *   structure if the specified indexes are not illegal
 * returns NULL for errors or illegal index values.
 */
saHpiSensorsTable_context *
saHpiSensorsTable_create_row(netsnmp_index * hdr)
{
    saHpiSensorsTable_context *ctx =
        SNMP_MALLOC_TYPEDEF(saHpiSensorsTable_context);
    if (!ctx)
        return NULL;

    /*
     * TODO: check indexes, if necessary.
     */
    if (saHpiSensorsTable_extract_index(ctx, hdr)) {
        free(ctx->index.oids);
        free(ctx);
        return NULL;
    }

    /*
     * netsnmp_mutex_init(ctx->lock);
     * netsnmp_mutex_lock(ctx->lock); 
     */

    /*
     * TODO: initialize any default values here. This is also
     * first place you really should allocate any memory for
     * yourself to use.  If you allocated memory earlier,
     * make sure you free it for earlier error cases!
     */
    /**
     ctx->saHpiSensorsThresholdRaw = 0;
     ctx->saHpiSensorsThresholdInterpreted = 0;
    */

    return ctx;
}
#endif

/************************************************************
 * the *_duplicate row routine
 */
saHpiSensorsTable_context *
saHpiSensorsTable_duplicate_row(saHpiSensorsTable_context * row_ctx)
{
    saHpiSensorsTable_context *dup;

    if (!row_ctx)
        return NULL;

    dup = SNMP_MALLOC_TYPEDEF(saHpiSensorsTable_context);
    if (!dup)
        return NULL;

    if (saHpiSensorsTable_row_copy(dup, row_ctx)) {
        free(dup);
        dup = NULL;
    }

    return dup;
}

/************************************************************
 * the *_delete_row method is called to delete a row.
 */
netsnmp_index  *
saHpiSensorsTable_delete_row(saHpiSensorsTable_context * ctx)
{
    /*
     * netsnmp_mutex_destroy(ctx->lock); 
     */

    if (ctx->index.oids)
        free(ctx->index.oids);

    /*
     * TODO: release any memory you allocated here...
     */

    /*
     * release header
     */
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
saHpiSensorsTable_set_reserve1(netsnmp_request_group * rg)
{
    saHpiSensorsTable_context *row_ctx =
        (saHpiSensorsTable_context *) rg->existing_row;
    saHpiSensorsTable_context *undo_ctx =
        (saHpiSensorsTable_context *) rg->undo_info;
    netsnmp_variable_list *var;
    netsnmp_request_group_item *current;
    int             rc;


    /*
     * TODO: loop through columns, check syntax and lengths. For
     * columns which have no dependencies, you could also move
     * the value/range checking here to attempt to catch error
     * cases as early as possible.
     */
    for (current = rg->list; current; current = current->next) {

        var = current->ri->requestvb;
        rc = SNMP_ERR_NOERROR;

        switch (current->tri->colnum) {

        case COLUMN_SAHPISENSORSTHRESHOLDRAW:
            /** OCTETSTR = ASN_OCTET_STR */
            rc = netsnmp_check_vb_type_and_size(var, ASN_OCTET_STR,
                                                sizeof(row_ctx->
                                                       saHpiSensorsThresholdRaw));
            break;

        case COLUMN_SAHPISENSORSTHRESHOLDINTERPRETED:
            /** OCTETSTR = ASN_OCTET_STR */
            rc = netsnmp_check_vb_type_and_size(var, ASN_OCTET_STR,
                                                sizeof(row_ctx->
                                                       saHpiSensorsThresholdInterpreted));
            break;

        default:/** We shouldn't get here */
            rc = SNMP_ERR_GENERR;
            snmp_log(LOG_ERR, "unknown column in "
                     "saHpiSensorsTable_set_reserve1\n");
        }

        if (rc)
            netsnmp_set_mode_request_error(MODE_SET_BEGIN, current->ri,
                                           rc);
        rg->status = SNMP_MAX(rg->status, current->ri->status);
    }

    /*
     * done with all the columns. Could check row related
     * requirements here.
     */
}

void
saHpiSensorsTable_set_reserve2(netsnmp_request_group * rg)
{
    saHpiSensorsTable_context *row_ctx =
        (saHpiSensorsTable_context *) rg->existing_row;
    saHpiSensorsTable_context *undo_ctx =
        (saHpiSensorsTable_context *) rg->undo_info;
    netsnmp_request_group_item *current;
    netsnmp_variable_list *var;
    int             rc;

    rg->rg_void = rg->list->ri;

    /*
     * TODO: loop through columns, check for valid
     * values and any range constraints.
     */
    for (current = rg->list; current; current = current->next) {

        var = current->ri->requestvb;
        rc = SNMP_ERR_NOERROR;

        switch (current->tri->colnum) {

        case COLUMN_SAHPISENSORSTHRESHOLDRAW:
            /** OCTETSTR = ASN_OCTET_STR */
            /*
             * TODO: routine to check valid values
             *
             * EXAMPLE:
             *
             * if ( XXX_check_value( var->val.string, XXX ) ) {
             *    rc = SNMP_ERR_INCONSISTENTVALUE;
             *    rc = SNMP_ERR_BADVALUE;
             * }
             */
            break;

        case COLUMN_SAHPISENSORSTHRESHOLDINTERPRETED:
            /** OCTETSTR = ASN_OCTET_STR */
            /*
             * TODO: routine to check valid values
             *
             * EXAMPLE:
             *
             * if ( XXX_check_value( var->val.string, XXX ) ) {
             *    rc = SNMP_ERR_INCONSISTENTVALUE;
             *    rc = SNMP_ERR_BADVALUE;
             * }
             */
            break;

        default:/** We shouldn't get here */
            netsnmp_assert(0); /** why wasn't this caught in reserve1? */
        }

        if (rc)
            netsnmp_set_mode_request_error(MODE_SET_BEGIN, current->ri,
                                           rc);
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
void
saHpiSensorsTable_set_action(netsnmp_request_group * rg)
{
    netsnmp_variable_list *var;
    saHpiSensorsTable_context *row_ctx =
        (saHpiSensorsTable_context *) rg->existing_row;
    saHpiSensorsTable_context *undo_ctx =
        (saHpiSensorsTable_context *) rg->undo_info;
    netsnmp_request_group_item *current;


    /*
     * TODO: loop through columns, copy varbind values
     * to context structure for the row.
     */
    for (current = rg->list; current; current = current->next) {

        var = current->ri->requestvb;

        switch (current->tri->colnum) {

        case COLUMN_SAHPISENSORSTHRESHOLDRAW:
            /** OCTETSTR = ASN_OCTET_STR */
            memcpy(row_ctx->saHpiSensorsThresholdRaw, var->val.string,
                   var->val_len);
            row_ctx->saHpiSensorsThresholdRaw_len = var->val_len;
            break;

        case COLUMN_SAHPISENSORSTHRESHOLDINTERPRETED:
            /** OCTETSTR = ASN_OCTET_STR */
            memcpy(row_ctx->saHpiSensorsThresholdInterpreted,
                   var->val.string, var->val_len);
            row_ctx->saHpiSensorsThresholdInterpreted_len = var->val_len;
            break;

        default:/** We shouldn't get here */
            netsnmp_assert(0); /** why wasn't this caught in reserve1? */
        }
    }

    /*
     * done with all the columns. Could check row related
     * requirements here.
     */
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
void
saHpiSensorsTable_set_commit(netsnmp_request_group * rg)
{
    netsnmp_variable_list *var;
    saHpiSensorsTable_context *row_ctx =
        (saHpiSensorsTable_context *) rg->existing_row;
    saHpiSensorsTable_context *undo_ctx =
        (saHpiSensorsTable_context *) rg->undo_info;
    netsnmp_request_group_item *current;

    /*
     * loop through columns
     */
    for (current = rg->list; current; current = current->next) {

        var = current->ri->requestvb;

        switch (current->tri->colnum) {

        case COLUMN_SAHPISENSORSTHRESHOLDRAW:
            /** OCTETSTR = ASN_OCTET_STR */
            break;

        case COLUMN_SAHPISENSORSTHRESHOLDINTERPRETED:
            /** OCTETSTR = ASN_OCTET_STR */
            break;

        default:/** We shouldn't get here */
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
void
saHpiSensorsTable_set_free(netsnmp_request_group * rg)
{
    netsnmp_variable_list *var;
    saHpiSensorsTable_context *row_ctx =
        (saHpiSensorsTable_context *) rg->existing_row;
    saHpiSensorsTable_context *undo_ctx =
        (saHpiSensorsTable_context *) rg->undo_info;
    netsnmp_request_group_item *current;

    /*
     * loop through columns
     */
    for (current = rg->list; current; current = current->next) {

        var = current->ri->requestvb;

        switch (current->tri->colnum) {

        case COLUMN_SAHPISENSORSTHRESHOLDRAW:
            /** OCTETSTR = ASN_OCTET_STR */
            break;

        case COLUMN_SAHPISENSORSTHRESHOLDINTERPRETED:
            /** OCTETSTR = ASN_OCTET_STR */
            break;

        default:/** We shouldn't get here */
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
void
saHpiSensorsTable_set_undo(netsnmp_request_group * rg)
{
    netsnmp_variable_list *var;
    saHpiSensorsTable_context *row_ctx =
        (saHpiSensorsTable_context *) rg->existing_row;
    saHpiSensorsTable_context *undo_ctx =
        (saHpiSensorsTable_context *) rg->undo_info;
    netsnmp_request_group_item *current;

    /*
     * loop through columns
     */
    for (current = rg->list; current; current = current->next) {

        var = current->ri->requestvb;

        switch (current->tri->colnum) {

        case COLUMN_SAHPISENSORSTHRESHOLDRAW:
            /** OCTETSTR = ASN_OCTET_STR */
            break;

        case COLUMN_SAHPISENSORSTHRESHOLDINTERPRETED:
            /** OCTETSTR = ASN_OCTET_STR */
            break;

        default:/** We shouldn't get here */
            netsnmp_assert(0); /** why wasn't this caught in reserve1? */
        }
    }

    /*
     * done with all the columns. Could check row related
     * requirements here.
     */
}

#endif /** saHpiSensorsTable_SET_HANDLING */


/************************************************************
 *
 * Initialize the saHpiSensorsTable table by defining its contents and how it's structured
 */
void
initialize_table_saHpiSensorsTable(void)
{
    netsnmp_table_registration_info *table_info;

    if (my_handler) {
        snmp_log(LOG_ERR,
                 "initialize_table_saHpiSensorsTable_handler called again\n");
        return;
    }

    memset(&cb, 0x00, sizeof(cb));

    /** create the table structure itself */
    table_info = SNMP_MALLOC_TYPEDEF(netsnmp_table_registration_info);

    /*
     * if your table is read only, it's easiest to change the
     * HANDLER_CAN_RWRITE definition below to HANDLER_CAN_RONLY 
     */
    my_handler = netsnmp_create_handler_registration("saHpiSensorsTable",
                                                     netsnmp_table_array_helper_handler,
                                                     saHpiSensorsTable_oid,
                                                     saHpiSensorsTable_oid_len,
                                                     HANDLER_CAN_RWRITE);

    if (!my_handler || !table_info) {
        snmp_log(LOG_ERR, "malloc failed in "
                 "initialize_table_saHpiSensorsTable_handler\n");
        return; /** mallocs failed */
    }

    /***************************************************
     * Setting up the table's definition
     */
    /*
     * TODO: add any external indexes here.
     */

    /*
     * internal indexes
     */
        /** index: saHpiSensorsIndex */
    netsnmp_table_helper_add_index(table_info, ASN_UNSIGNED);

    table_info->min_column = saHpiSensorsTable_COL_MIN;
    table_info->max_column = saHpiSensorsTable_COL_MAX;

    /***************************************************
     * registering the table with the master agent
     */
    cb.get_value = saHpiSensorsTable_get_value;
    cb.container = netsnmp_container_find("saHpiSensorsTable_primary:"
                                          "saHpiSensorsTable:"
                                          "table_container");
#ifdef saHpiSensorsTable_IDX2
    netsnmp_container_add_index(cb.container,
                                netsnmp_container_find
                                ("saHpiSensorsTable_secondary:"
                                 "saHpiSensorsTable:" "table_container"));
    cb.container->next->compare = saHpiSensorsTable_cmp;
#endif
#ifdef saHpiSensorsTable_SET_HANDLING
    cb.can_set = 1;
#ifdef saHpiSensorsTable_ROW_CREATION
    cb.create_row = (UserRowMethod *) saHpiSensorsTable_create_row;
#endif
    cb.duplicate_row = (UserRowMethod *) saHpiSensorsTable_duplicate_row;
    cb.delete_row = (UserRowMethod *) saHpiSensorsTable_delete_row;
    cb.row_copy =
        (Netsnmp_User_Row_Operation *) saHpiSensorsTable_row_copy;

    cb.can_delete =
        (Netsnmp_User_Row_Action *) saHpiSensorsTable_can_delete;

    cb.set_reserve1 = saHpiSensorsTable_set_reserve1;
    cb.set_reserve2 = saHpiSensorsTable_set_reserve2;
    cb.set_action = saHpiSensorsTable_set_action;
    cb.set_commit = saHpiSensorsTable_set_commit;
    cb.set_free = saHpiSensorsTable_set_free;
    cb.set_undo = saHpiSensorsTable_set_undo;
#endif
    DEBUGMSGTL(("initialize_table_saHpiSensorsTable",
                "Registering table saHpiSensorsTable "
                "as a table array\n"));
    netsnmp_table_container_register(my_handler, table_info, &cb,
                                     cb.container, 1);
}

/************************************************************
 * saHpiSensorsTable_get_value
 */
int
saHpiSensorsTable_get_value(netsnmp_request_info *request,
                            netsnmp_index * item,
                            netsnmp_table_request_info *table_info)
{
    netsnmp_variable_list *var = request->requestvb;
    saHpiSensorsTable_context *context =
        (saHpiSensorsTable_context *) item;

    switch (table_info->colnum) {

    case COLUMN_SAHPISENSORSINDEX:
            /** UNSIGNED32 = ASN_UNSIGNED */
        snmp_set_var_typed_value(var, ASN_UNSIGNED,
                                 (char *) &context->saHpiSensorsIndex,
                                 sizeof(context->saHpiSensorsIndex));
        break;

    case COLUMN_SAHPISENSORSTYPE:
            /** INTEGER = ASN_INTEGER */
        snmp_set_var_typed_value(var, ASN_INTEGER,
                                 (char *) &context->saHpiSensorsType,
                                 sizeof(context->saHpiSensorsType));
        break;

    case COLUMN_SAHPISENSORSCATEGORY:
            /** INTEGER = ASN_INTEGER */
        snmp_set_var_typed_value(var, ASN_INTEGER,
                                 (char *) &context->saHpiSensorsCategory,
                                 sizeof(context->saHpiSensorsCategory));
        break;

    case COLUMN_SAHPISENSORSEVENTSCATEGORYCONTROL:
            /** INTEGER = ASN_INTEGER */
        snmp_set_var_typed_value(var, ASN_INTEGER,
                                 (char *) &context->
                                 saHpiSensorsEventsCategoryControl,
                                 sizeof(context->
                                        saHpiSensorsEventsCategoryControl));
        break;

    case COLUMN_SAHPISENSORSEVENTSSTATE:
            /** UNSIGNED32 = ASN_UNSIGNED */
        snmp_set_var_typed_value(var, ASN_UNSIGNED,
                                 (char *) &context->
                                 saHpiSensorsEventsState,
                                 sizeof(context->saHpiSensorsEventsState));
        break;

    case COLUMN_SAHPISENSORSIGNORE:
            /** BITS = ASN_OCTET_STR */
        snmp_set_var_typed_value(var, ASN_OCTET_STR,
                                 (char *) &context->saHpiSensorsIgnore,
                                 context->saHpiSensorsIgnore_len);
        break;

    case COLUMN_SAHPISENSORSREADINGFORMATS:
            /** UNSIGNED32 = ASN_UNSIGNED */
        snmp_set_var_typed_value(var, ASN_UNSIGNED,
                                 (char *) &context->
                                 saHpiSensorsReadingFormats,
                                 sizeof(context->
                                        saHpiSensorsReadingFormats));
        break;

    case COLUMN_SAHPISENSORSISNUMERIC:
            /** BITS = ASN_OCTET_STR */
        snmp_set_var_typed_value(var, ASN_OCTET_STR,
                                 (char *) &context->saHpiSensorsIsNumeric,
                                 context->saHpiSensorsIsNumeric_len);
        break;

    case COLUMN_SAHPISENSORSSIGNFORMAT:
            /** INTEGER = ASN_INTEGER */
        snmp_set_var_typed_value(var, ASN_INTEGER,
                                 (char *) &context->saHpiSensorsSignFormat,
                                 sizeof(context->saHpiSensorsSignFormat));
        break;

    case COLUMN_SAHPISENSORSBASEUNITS:
            /** INTEGER = ASN_INTEGER */
        snmp_set_var_typed_value(var, ASN_INTEGER,
                                 (char *) &context->saHpiSensorsBaseUnits,
                                 sizeof(context->saHpiSensorsBaseUnits));
        break;

    case COLUMN_SAHPISENSORSMODIFIERUNITS:
            /** INTEGER = ASN_INTEGER */
        snmp_set_var_typed_value(var, ASN_INTEGER,
                                 (char *) &context->
                                 saHpiSensorsModifierUnits,
                                 sizeof(context->
                                        saHpiSensorsModifierUnits));
        break;

    case COLUMN_SAHPISENSORSMODIFIERUSE:
            /** INTEGER = ASN_INTEGER */
        snmp_set_var_typed_value(var, ASN_INTEGER,
                                 (char *) &context->
                                 saHpiSensorsModifierUse,
                                 sizeof(context->saHpiSensorsModifierUse));
        break;

    case COLUMN_SAHPISENSORSFACTORSSTATIC:
            /** BITS = ASN_OCTET_STR */
        snmp_set_var_typed_value(var, ASN_OCTET_STR,
                                 (char *) &context->
                                 saHpiSensorsFactorsStatic,
                                 context->saHpiSensorsFactorsStatic_len);
        break;

    case COLUMN_SAHPISENSORSFACTORS:
            /** OCTETSTR = ASN_OCTET_STR */
        snmp_set_var_typed_value(var, ASN_OCTET_STR,
                                 (char *) &context->saHpiSensorsFactors,
                                 context->saHpiSensorsFactors_len);
        break;

    case COLUMN_SAHPISENSORSFACTORSLINEARIZATION:
            /** INTEGER = ASN_INTEGER */
        snmp_set_var_typed_value(var, ASN_INTEGER,
                                 (char *) &context->
                                 saHpiSensorsFactorsLinearization,
                                 sizeof(context->
                                        saHpiSensorsFactorsLinearization));
        break;

    case COLUMN_SAHPISENSORSPERCENTAGE:
            /** BITS = ASN_OCTET_STR */
        snmp_set_var_typed_value(var, ASN_OCTET_STR,
                                 (char *) &context->saHpiSensorsPercentage,
                                 context->saHpiSensorsPercentage_len);
        break;

    case COLUMN_SAHPISENSORSRANGEFLAGS:
            /** UNSIGNED32 = ASN_UNSIGNED */
        snmp_set_var_typed_value(var, ASN_UNSIGNED,
                                 (char *) &context->saHpiSensorsRangeFlags,
                                 sizeof(context->saHpiSensorsRangeFlags));
        break;

    case COLUMN_SAHPISENSORSRANGEREADINGVALUESPRESENT:
            /** OCTETSTR = ASN_OCTET_STR */
        snmp_set_var_typed_value(var, ASN_OCTET_STR,
                                 (char *) &context->
                                 saHpiSensorsRangeReadingValuesPresent,
                                 context->
                                 saHpiSensorsRangeReadingValuesPresent_len);
        break;

    case COLUMN_SAHPISENSORSRANGEREADINGRAW:
            /** OCTETSTR = ASN_OCTET_STR */
        snmp_set_var_typed_value(var, ASN_OCTET_STR,
                                 (char *) &context->
                                 saHpiSensorsRangeReadingRaw,
                                 context->saHpiSensorsRangeReadingRaw_len);
        break;

    case COLUMN_SAHPISENSORSRANGEREADINGINTERPRETED:
            /** OCTETSTR = ASN_OCTET_STR */
        snmp_set_var_typed_value(var, ASN_OCTET_STR,
                                 (char *) &context->
                                 saHpiSensorsRangeReadingInterpreted,
                                 context->
                                 saHpiSensorsRangeReadingInterpreted_len);
        break;

    case COLUMN_SAHPISENSORSRANGEREADINGEVENTSENSOR:
            /** OCTETSTR = ASN_OCTET_STR */
        snmp_set_var_typed_value(var, ASN_OCTET_STR,
                                 (char *) &context->
                                 saHpiSensorsRangeReadingEventSensor,
                                 context->
                                 saHpiSensorsRangeReadingEventSensor_len);
        break;

    case COLUMN_SAHPISENSORSTHRESHOLDDEFNISTHRESHOLD:
            /** BITS = ASN_OCTET_STR */
        snmp_set_var_typed_value(var, ASN_OCTET_STR,
                                 (char *) &context->
                                 saHpiSensorsThresholdDefnIsThreshold,
                                 context->
                                 saHpiSensorsThresholdDefnIsThreshold_len);
        break;

    case COLUMN_SAHPISENSORSTHRESHOLDDEFNTHOLDCAPABILITIES:
            /** BITS = ASN_OCTET_STR */
        snmp_set_var_typed_value(var, ASN_OCTET_STR,
                                 (char *) &context->
                                 saHpiSensorsThresholdDefnTholdCapabilities,
                                 context->
                                 saHpiSensorsThresholdDefnTholdCapabilities_len);
        break;

    case COLUMN_SAHPISENSORSTHRESHOLDDEFNREADTHOLD:
            /** UNSIGNED32 = ASN_UNSIGNED */
        snmp_set_var_typed_value(var, ASN_UNSIGNED,
                                 (char *) &context->
                                 saHpiSensorsThresholdDefnReadThold,
                                 sizeof(context->
                                        saHpiSensorsThresholdDefnReadThold));
        break;

    case COLUMN_SAHPISENSORSTHRESHOLDDEFNWRITETHOLD:
            /** UNSIGNED32 = ASN_UNSIGNED */
        snmp_set_var_typed_value(var, ASN_UNSIGNED,
                                 (char *) &context->
                                 saHpiSensorsThresholdDefnWriteThold,
                                 sizeof(context->
                                        saHpiSensorsThresholdDefnWriteThold));
        break;

    case COLUMN_SAHPISENSORSTHRESHOLDDEFNFIXEDTHOLD:
            /** UNSIGNED32 = ASN_UNSIGNED */
        snmp_set_var_typed_value(var, ASN_UNSIGNED,
                                 (char *) &context->
                                 saHpiSensorsThresholdDefnFixedThold,
                                 sizeof(context->
                                        saHpiSensorsThresholdDefnFixedThold));
        break;

    case COLUMN_SAHPISENSORSTHRESHOLDRAW:
            /** OCTETSTR = ASN_OCTET_STR */
        snmp_set_var_typed_value(var, ASN_OCTET_STR,
                                 (char *) &context->
                                 saHpiSensorsThresholdRaw,
                                 context->saHpiSensorsThresholdRaw_len);
        break;

    case COLUMN_SAHPISENSORSTHRESHOLDINTERPRETED:
            /** OCTETSTR = ASN_OCTET_STR */
        snmp_set_var_typed_value(var, ASN_OCTET_STR,
                                 (char *) &context->
                                 saHpiSensorsThresholdInterpreted,
                                 context->
                                 saHpiSensorsThresholdInterpreted_len);
        break;

    case COLUMN_SAHPISENSORSOEM:
            /** UNSIGNED32 = ASN_UNSIGNED */
        snmp_set_var_typed_value(var, ASN_UNSIGNED,
                                 (char *) &context->saHpiSensorsOEM,
                                 sizeof(context->saHpiSensorsOEM));
        break;

    default:/** We shouldn't get here */
        snmp_log(LOG_ERR, "unknown column in "
                 "saHpiSensorsTable_get_value\n");
        return SNMP_ERR_GENERR;
    }
    return SNMP_ERR_NOERROR;
}

/************************************************************
 * saHpiSensorsTable_get_by_idx
 */
const saHpiSensorsTable_context *
saHpiSensorsTable_get_by_idx(netsnmp_index * hdr)
{
    return (const saHpiSensorsTable_context *)
        CONTAINER_FIND(cb.container, hdr);
}
