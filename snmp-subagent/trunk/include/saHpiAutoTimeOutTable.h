/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.array-user.conf,v 5.18.2.2 2004/02/09 18:21:47 rstory Exp $
 *
 * $Id$
 *
 * Yes, there is lots of code here that you might not use. But it is much
 * easier to remove code than to add it!
 */
#ifndef SAHPIAUTOTIMEOUTTABLE_H
#define SAHPIAUTOTIMEOUTTABLE_H

#ifdef __cplusplus
extern "C" {
#endif

    
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/library/container.h>
#include <net-snmp/agent/table_array.h>

        /** Index saHpiDomainId is external */

typedef struct saHpiAutoTimeOutTable_context_s {
    netsnmp_index index; /** THIS MUST BE FIRST!!! */

    /*************************************************************
     * You can store data internally in this structure.
     *
     * TODO: You will probably have to fix a few types here...
     */
    /** TODO: add storage for external index(s)! */
        /** SaHpiTime = ASN_COUNTER64 */
    /** TODO: Is this type correct? */
            long saHpiAutoTimeoutForInsert;


    /*
     * OR
     *
     * Keep a pointer to your data
     */
    void * data;

    /*
     *add anything else you want here
     */

} saHpiAutoTimeOutTable_context;

/*************************************************************
 * function declarations
 */
void init_saHpiAutoTimeOutTable(void);
void initialize_table_saHpiAutoTimeOutTable(void);
const saHpiAutoTimeOutTable_context * saHpiAutoTimeOutTable_get_by_idx(netsnmp_index *);
const saHpiAutoTimeOutTable_context * saHpiAutoTimeOutTable_get_by_idx_rs(netsnmp_index *,
                                        int row_status);
int saHpiAutoTimeOutTable_get_value(netsnmp_request_info *, netsnmp_index *, netsnmp_table_request_info *);


/*************************************************************
 * oid declarations
 */
extern oid saHpiAutoTimeOutTable_oid[];
extern size_t saHpiAutoTimeOutTable_oid_len;

#define saHpiAutoTimeOutTable_TABLE_OID 1,3,6,1,4,1,18568,1,1,1,6,1,11,1
    
/*************************************************************
 * column number definitions for table saHpiAutoTimeOutTable
 */
#define COLUMN_SAHPIAUTOTIMEOUTFORINSERT 1
#define saHpiAutoTimeOutTable_COL_MIN 1
#define saHpiAutoTimeOutTable_COL_MAX 1

/* comment out the following line if you don't handle SET-REQUEST for saHpiAutoTimeOutTable */
#define saHpiAutoTimeOutTable_SET_HANDLING

/* comment out the following line if you can't create new rows */
#define saHpiAutoTimeOutTable_ROW_CREATION

/* comment out the following line if you don't want the secondary index */
#define saHpiAutoTimeOutTable_IDX2

/* uncommend the following line if you allow modifications to an
 * active row */
/** define saHpiAutoTimeOutTable_CAN_MODIFY_ACTIVE_ROW */

#ifdef saHpiAutoTimeOutTable_SET_HANDLING

int saHpiAutoTimeOutTable_extract_index( saHpiAutoTimeOutTable_context * ctx, netsnmp_index * hdr );

void saHpiAutoTimeOutTable_set_reserve1( netsnmp_request_group * );
void saHpiAutoTimeOutTable_set_reserve2( netsnmp_request_group * );
void saHpiAutoTimeOutTable_set_action( netsnmp_request_group * );
void saHpiAutoTimeOutTable_set_commit( netsnmp_request_group * );
void saHpiAutoTimeOutTable_set_free( netsnmp_request_group * );
void saHpiAutoTimeOutTable_set_undo( netsnmp_request_group * );

saHpiAutoTimeOutTable_context * saHpiAutoTimeOutTable_duplicate_row( saHpiAutoTimeOutTable_context* );
netsnmp_index * saHpiAutoTimeOutTable_delete_row( saHpiAutoTimeOutTable_context* );

int saHpiAutoTimeOutTable_can_activate(saHpiAutoTimeOutTable_context *undo_ctx,
                      saHpiAutoTimeOutTable_context *row_ctx,
                      netsnmp_request_group * rg);
int saHpiAutoTimeOutTable_can_deactivate(saHpiAutoTimeOutTable_context *undo_ctx,
                        saHpiAutoTimeOutTable_context *row_ctx,
                        netsnmp_request_group * rg);
int saHpiAutoTimeOutTable_can_delete(saHpiAutoTimeOutTable_context *undo_ctx,
                    saHpiAutoTimeOutTable_context *row_ctx,
                    netsnmp_request_group * rg);
    
    
#ifdef saHpiAutoTimeOutTable_ROW_CREATION
saHpiAutoTimeOutTable_context * saHpiAutoTimeOutTable_create_row( netsnmp_index* );
#endif
#endif

#ifdef saHpiAutoTimeOutTable_IDX2
saHpiAutoTimeOutTable_context * saHpiAutoTimeOutTable_get( const char *name, int len );
#endif

#ifdef __cplusplus
};
#endif

#endif /** SAHPIAUTOTIMEOUTTABLE_H */
