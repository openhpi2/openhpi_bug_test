/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.array-user.conf,v 5.18 2003/11/07 17:03:52 rstory Exp $
 *
 * $Id$
 *
 * Yes, there is lots of code here that you might not use. But it is much
 * easier to remove code than to add it!
 */
#ifndef SAHPIHOTSWAPTABLE_H
#define SAHPIHOTSWAPTABLE_H

#ifdef __cplusplus
extern "C" {
#endif

    
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/library/container.h>
#include <net-snmp/agent/table_array.h>

        /** Index saHpiDomainId is external */
        /** Index saHpiResourceId is external */

typedef struct saHpiHotSwapTable_context_s {
    netsnmp_index index; /** THIS MUST BE FIRST!!! */

    /*************************************************************
     * You can store data internally in this structure.
     *
     * TODO: You will probably have to fix a few types here...
     */
    /** TODO: add storage for external index(s)! */
        /** INTEGER = ASN_INTEGER */
            long saHpiHotSwapIndicator;

        /** SaHpiHotSwapState = ASN_INTEGER */
            long saHpiHotSwapState;

        /** SaHpiHotSwapState = ASN_INTEGER */
            long saHpiHotSwapPreviousState;

        /** SaHpiTime = ASN_COUNTER64 */
    /** TODO: Is this type correct? */
            long saHpiHotSwapExtractTimeout;

        /** INTEGER = ASN_INTEGER */
            long saHpiHotSwapActionRequest;

        /** INTEGER = ASN_INTEGER */
            long saHpiHotSwapPolicyCancel;

        /** INTEGER = ASN_INTEGER */
            long saHpiHotSwapResourceRequest;

        /** INTEGER = ASN_INTEGER */
            long saHpiHotSwapResetAction;

        /** INTEGER = ASN_INTEGER */
            long saHpiHotSwapPowerAction;

        /** RowPointer = ASN_OBJECT_ID */
            oid saHpiHotSwapRTP[MAX_OID_LEN];
            long saHpiHotSwapRTP_len;


    /*
     * OR
     *
     * Keep a pointer to your data
     */
    void * data;

    /*
     *add anything else you want here
     */

} saHpiHotSwapTable_context;

/*************************************************************
 * function declarations
 */
void init_saHpiHotSwapTable(void);
void initialize_table_saHpiHotSwapTable(void);
const saHpiHotSwapTable_context * saHpiHotSwapTable_get_by_idx(netsnmp_index *);
const saHpiHotSwapTable_context * saHpiHotSwapTable_get_by_idx_rs(netsnmp_index *,
                                        int row_status);
int saHpiHotSwapTable_get_value(netsnmp_request_info *, netsnmp_index *, netsnmp_table_request_info *);


/*************************************************************
 * oid declarations
 */
extern oid saHpiHotSwapTable_oid[];
extern size_t saHpiHotSwapTable_oid_len;

#define saHpiHotSwapTable_TABLE_OID 1,3,6,1,4,1,18568,1,1,1,6,1,11,3
    
/*************************************************************
 * column number definitions for table saHpiHotSwapTable
 */
#define COLUMN_SAHPIHOTSWAPINDICATOR 1
#define COLUMN_SAHPIHOTSWAPSTATE 2
#define COLUMN_SAHPIHOTSWAPPREVIOUSSTATE 3
#define COLUMN_SAHPIHOTSWAPEXTRACTTIMEOUT 4
#define COLUMN_SAHPIHOTSWAPACTIONREQUEST 5
#define COLUMN_SAHPIHOTSWAPPOLICYCANCEL 6
#define COLUMN_SAHPIHOTSWAPRESOURCEREQUEST 7
#define COLUMN_SAHPIHOTSWAPRESETACTION 8
#define COLUMN_SAHPIHOTSWAPPOWERACTION 9
#define COLUMN_SAHPIHOTSWAPRTP 10
#define saHpiHotSwapTable_COL_MIN 1
#define saHpiHotSwapTable_COL_MAX 10

/* comment out the following line if you don't handle SET-REQUEST for saHpiHotSwapTable */
#define saHpiHotSwapTable_SET_HANDLING

/* comment out the following line if you can't create new rows */
#define saHpiHotSwapTable_ROW_CREATION

/* comment out the following line if you don't want the secondary index */
#define saHpiHotSwapTable_IDX2

/* uncommend the following line if you allow modifications to an
 * active row */
/** define saHpiHotSwapTable_CAN_MODIFY_ACTIVE_ROW */

#ifdef saHpiHotSwapTable_SET_HANDLING

int saHpiHotSwapTable_extract_index( saHpiHotSwapTable_context * ctx, netsnmp_index * hdr );

void saHpiHotSwapTable_set_reserve1( netsnmp_request_group * );
void saHpiHotSwapTable_set_reserve2( netsnmp_request_group * );
void saHpiHotSwapTable_set_action( netsnmp_request_group * );
void saHpiHotSwapTable_set_commit( netsnmp_request_group * );
void saHpiHotSwapTable_set_free( netsnmp_request_group * );
void saHpiHotSwapTable_set_undo( netsnmp_request_group * );

saHpiHotSwapTable_context * saHpiHotSwapTable_duplicate_row( saHpiHotSwapTable_context* );
netsnmp_index * saHpiHotSwapTable_delete_row( saHpiHotSwapTable_context* );

int saHpiHotSwapTable_can_activate(saHpiHotSwapTable_context *undo_ctx,
                      saHpiHotSwapTable_context *row_ctx,
                      netsnmp_request_group * rg);
int saHpiHotSwapTable_can_deactivate(saHpiHotSwapTable_context *undo_ctx,
                        saHpiHotSwapTable_context *row_ctx,
                        netsnmp_request_group * rg);
int saHpiHotSwapTable_can_delete(saHpiHotSwapTable_context *undo_ctx,
                    saHpiHotSwapTable_context *row_ctx,
                    netsnmp_request_group * rg);
    
    
#ifdef saHpiHotSwapTable_ROW_CREATION
saHpiHotSwapTable_context * saHpiHotSwapTable_create_row( netsnmp_index* );
#endif
#endif

#ifdef saHpiHotSwapTable_IDX2
saHpiHotSwapTable_context * saHpiHotSwapTable_get( const char *name, int len );
#endif

#ifdef __cplusplus
};
#endif

#endif /** SAHPIHOTSWAPTABLE_H */
