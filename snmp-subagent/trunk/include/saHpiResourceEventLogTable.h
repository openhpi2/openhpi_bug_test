/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.array-user.conf,v 5.18.2.2 2004/02/09 18:21:47 rstory Exp $
 *
 * $Id$
 *
 * Yes, there is lots of code here that you might not use. But it is much
 * easier to remove code than to add it!
 */
#ifndef SAHPIRESOURCEEVENTLOGTABLE_H
#define SAHPIRESOURCEEVENTLOGTABLE_H

#ifdef __cplusplus
extern "C" {
#endif

    
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/library/container.h>
#include <net-snmp/agent/table_array.h>

        /** Index saHpiDomainId is external */
        /** Index saHpiResourceId is external */
        /** Index saHpiEventSeverity is external */
        /** Index saHpiResourceEventLogEntryId is internal */

typedef struct saHpiResourceEventLogTable_context_s {
    netsnmp_index index; /** THIS MUST BE FIRST!!! */

    /*************************************************************
     * You can store data internally in this structure.
     *
     * TODO: You will probably have to fix a few types here...
     */
    /** TODO: add storage for external index(s)! */
        /** SaHpiEntryId = ASN_UNSIGNED */
            unsigned long saHpiResourceEventLogEntryId;

        /** SaHpiTime = ASN_COUNTER64 */
    /** TODO: Is this type correct? */
            long saHpiResourceEventLogTimestamp;

        /** INTEGER = ASN_INTEGER */
            long saHpiResourceEventLogType;


    /*
     * OR
     *
     * Keep a pointer to your data
     */
    void * data;

    /*
     *add anything else you want here
     */

} saHpiResourceEventLogTable_context;

/*************************************************************
 * function declarations
 */
void init_saHpiResourceEventLogTable(void);
void initialize_table_saHpiResourceEventLogTable(void);
const saHpiResourceEventLogTable_context * saHpiResourceEventLogTable_get_by_idx(netsnmp_index *);
const saHpiResourceEventLogTable_context * saHpiResourceEventLogTable_get_by_idx_rs(netsnmp_index *,
                                        int row_status);
int saHpiResourceEventLogTable_get_value(netsnmp_request_info *, netsnmp_index *, netsnmp_table_request_info *);

/*************************************************************
 * function declarations
 */
SaErrorT populate_saHpiResourceEventLogTable(SaHpiSessionIdT sessionid, 
                                             SaHpiEventLogEntryT *event,
                                             oid * this_child_oid, 
                                             size_t *this_child_oid_len);

SaErrorT resource_event_log_clear(SaHpiSessionIdT session_id, 
                                  SaHpiResourceIdT resource_id,  
                                  oid *saHpiEventLogRowPointer, 
                                  size_t saHpiEventLogRowPointer_len);


/*************************************************************
 * oid declarations
 */
extern oid saHpiResourceEventLogTable_oid[];
extern size_t saHpiResourceEventLogTable_oid_len;

#define saHpiResourceEventLogTable_TABLE_OID 1,3,6,1,4,1,18568,2,1,1,3,2,5
    
/*************************************************************
 * column number definitions for table saHpiResourceEventLogTable
 */
#define RESOURCE_EVENT_LOG_INDEX_NR 4
#define COLUMN_SAHPIRESOURCEEVENTLOGENTRYID 1
#define COLUMN_SAHPIRESOURCEEVENTLOGTIMESTAMP 2
#define COLUMN_SAHPIRESOURCEEVENTLOGTYPE 3
#define saHpiResourceEventLogTable_COL_MIN 2
#define saHpiResourceEventLogTable_COL_MAX 3

int saHpiResourceEventLogTable_extract_index( saHpiResourceEventLogTable_context * ctx, netsnmp_index * hdr );

void saHpiResourceEventLogTable_set_reserve1( netsnmp_request_group * );
void saHpiResourceEventLogTable_set_reserve2( netsnmp_request_group * );
void saHpiResourceEventLogTable_set_action( netsnmp_request_group * );
void saHpiResourceEventLogTable_set_commit( netsnmp_request_group * );
void saHpiResourceEventLogTable_set_free( netsnmp_request_group * );
void saHpiResourceEventLogTable_set_undo( netsnmp_request_group * );

saHpiResourceEventLogTable_context * saHpiResourceEventLogTable_duplicate_row( saHpiResourceEventLogTable_context* );
netsnmp_index * saHpiResourceEventLogTable_delete_row( saHpiResourceEventLogTable_context* );

int saHpiResourceEventLogTable_can_activate(saHpiResourceEventLogTable_context *undo_ctx,
                      saHpiResourceEventLogTable_context *row_ctx,
                      netsnmp_request_group * rg);
int saHpiResourceEventLogTable_can_deactivate(saHpiResourceEventLogTable_context *undo_ctx,
                        saHpiResourceEventLogTable_context *row_ctx,
                        netsnmp_request_group * rg);
int saHpiResourceEventLogTable_can_delete(saHpiResourceEventLogTable_context *undo_ctx,
                    saHpiResourceEventLogTable_context *row_ctx,
                    netsnmp_request_group * rg);
    
    
saHpiResourceEventLogTable_context * saHpiResourceEventLogTable_create_row( netsnmp_index* );

saHpiResourceEventLogTable_context * saHpiResourceEventLogTable_get( const char *name, int len );

#ifdef __cplusplus
};
#endif

#endif /** SAHPIRESOURCEEVENTLOGTABLE_H */
