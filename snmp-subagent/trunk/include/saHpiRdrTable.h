/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.array-user.conf,v 5.18 2003/11/07 17:03:52 rstory Exp $
 *
 * $Id$
 *
 * Yes, there is lots of code here that you might not use. But it is much
 * easier to remove code than to add it!
 */
#ifndef SAHPIRDRTABLE_H
#define SAHPIRDRTABLE_H

#ifdef __cplusplus
extern "C" {
#endif

    
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/library/container.h>
#include <net-snmp/agent/table_array.h>

        /** Index saHpiDomainId is external */
        /** Index saHpiResourceId is external */
        /** Index saHpiEntryId is external */
        /** Index saHpiRdrType is internal */

typedef struct saHpiRdrTable_context_s {
    netsnmp_index index; /** THIS MUST BE FIRST!!! */

    /*************************************************************
     * You can store data internally in this structure.
     *
     * TODO: You will probably have to fix a few types here...
     */
    /** TODO: add storage for external index(s)! */
        /** INTEGER = ASN_INTEGER */
            long saHpiRdrType;

        /** OCTETSTR = ASN_OCTET_STR */
            unsigned char saHpiRdrEntityPath[65535];
            long saHpiRdrEntityPath_len;

        /** TruthValue = ASN_INTEGER */
            long saHpiRdrIsFru;

        /** RowPointer = ASN_OBJECT_ID */
            oid saHpiRdr[MAX_OID_LEN];
            long saHpiRdr_len;

        /** COUNTER = ASN_COUNTER */
            unsigned long saHpiRdrId;

        /** RowPointer = ASN_OBJECT_ID */
            oid saHpiRdrRTP[MAX_OID_LEN];
            long saHpiRdrRTP_len;

        /** SaHpiTextType = ASN_INTEGER */
            long saHpiRdrTextType;

        /** SaHpiTextLanguage = ASN_INTEGER */
            long saHpiRdrTextLanguage;

        /** OCTETSTR = ASN_OCTET_STR */
            unsigned char saHpiRdrIdString[65535];
            long saHpiRdrIdString_len;


    /*
     * OR
     *
     * Keep a pointer to your data
     */
    void * data;

    /*
     *add anything else you want here
     */

} saHpiRdrTable_context;

/*************************************************************
 * function declarations
 */
void init_saHpiRdrTable(void);
void initialize_table_saHpiRdrTable(void);
const saHpiRdrTable_context * saHpiRdrTable_get_by_idx(netsnmp_index *);
const saHpiRdrTable_context * saHpiRdrTable_get_by_idx_rs(netsnmp_index *,
                                        int row_status);
int saHpiRdrTable_get_value(netsnmp_request_info *, netsnmp_index *, netsnmp_table_request_info *);


/*************************************************************
 * oid declarations
 */
extern oid saHpiRdrTable_oid[];
extern size_t saHpiRdrTable_oid_len;

#define saHpiRdrTable_TABLE_OID 1,3,6,1,4,1,18568,1,1,1,6,3,2
    
/*************************************************************
 * column number definitions for table saHpiRdrTable
 */
#define COLUMN_SAHPIRDRTYPE 1
#define COLUMN_SAHPIRDRENTITYPATH 2
#define COLUMN_SAHPIRDRISFRU 3
#define COLUMN_SAHPIRDR 4
#define COLUMN_SAHPIRDRID 5
#define COLUMN_SAHPIRDRRTP 6
#define COLUMN_SAHPIRDRTEXTTYPE 7
#define COLUMN_SAHPIRDRTEXTLANGUAGE 8
#define COLUMN_SAHPIRDRIDSTRING 9
#define saHpiRdrTable_COL_MIN 2
#define saHpiRdrTable_COL_MAX 9

/* comment out the following line if you don't handle SET-REQUEST for saHpiRdrTable */
#define saHpiRdrTable_SET_HANDLING

/* comment out the following line if you can't create new rows */
#define saHpiRdrTable_ROW_CREATION

/* comment out the following line if you don't want the secondary index */
#define saHpiRdrTable_IDX2

/* uncommend the following line if you allow modifications to an
 * active row */
/** define saHpiRdrTable_CAN_MODIFY_ACTIVE_ROW */

#ifdef saHpiRdrTable_SET_HANDLING

int saHpiRdrTable_extract_index( saHpiRdrTable_context * ctx, netsnmp_index * hdr );

void saHpiRdrTable_set_reserve1( netsnmp_request_group * );
void saHpiRdrTable_set_reserve2( netsnmp_request_group * );
void saHpiRdrTable_set_action( netsnmp_request_group * );
void saHpiRdrTable_set_commit( netsnmp_request_group * );
void saHpiRdrTable_set_free( netsnmp_request_group * );
void saHpiRdrTable_set_undo( netsnmp_request_group * );

saHpiRdrTable_context * saHpiRdrTable_duplicate_row( saHpiRdrTable_context* );
netsnmp_index * saHpiRdrTable_delete_row( saHpiRdrTable_context* );

int saHpiRdrTable_can_activate(saHpiRdrTable_context *undo_ctx,
                      saHpiRdrTable_context *row_ctx,
                      netsnmp_request_group * rg);
int saHpiRdrTable_can_deactivate(saHpiRdrTable_context *undo_ctx,
                        saHpiRdrTable_context *row_ctx,
                        netsnmp_request_group * rg);
int saHpiRdrTable_can_delete(saHpiRdrTable_context *undo_ctx,
                    saHpiRdrTable_context *row_ctx,
                    netsnmp_request_group * rg);
    
    
#ifdef saHpiRdrTable_ROW_CREATION
saHpiRdrTable_context * saHpiRdrTable_create_row( netsnmp_index* );
#endif
#endif

#ifdef saHpiRdrTable_IDX2
saHpiRdrTable_context * saHpiRdrTable_get( const char *name, int len );
#endif

#ifdef __cplusplus
};
#endif

#endif /** SAHPIRDRTABLE_H */
