/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.array-user.conf,v 5.18.2.2 2004/02/09 18:21:47 rstory Exp $
 *
 * $Id$
 *
 * Yes, there is lots of code here that you might not use. But it is much
 * easier to remove code than to add it!
 */
#ifndef SAHPIANNUNCIATORTABLE_H
#define SAHPIANNUNCIATORTABLE_H

#ifdef __cplusplus
extern "C" {
#endif


#include <net-snmp/net-snmp-config.h>
#include <net-snmp/library/container.h>
#include <net-snmp/agent/table_array.h>

/** Index saHpiDomainId is external */
/** Index saHpiResourceId is external */
/** Index saHpiResourceIsHistorical is external */
/** Index saHpiAnnunciatorNum is internal */

typedef struct saHpiAnnunciatorTable_context_s {
        netsnmp_index index; /** THIS MUST BE FIRST!!! */

        /*************************************************************
         * You can store data internally in this structure.
         *
         * TODO: You will probably have to fix a few types here...
         */
        /** TODO: add storage for external index(s)! */
        /** SaHpiInstrumentId = ASN_UNSIGNED */
        unsigned long saHpiAnnunciatorNum;

        /** INTEGER = ASN_INTEGER */
        long saHpiAnnunciatorType;

        /** TruthValue = ASN_INTEGER */
        long saHpiAnnunciatorModeReadOnly;

        /** UNSIGNED32 = ASN_UNSIGNED */
        unsigned long saHpiAnnunciatorMaxConditions;

        /** INTEGER = ASN_INTEGER */
        long saHpiAnnunciatorMode;

        /** UNSIGNED32 = ASN_UNSIGNED */
        unsigned long saHpiAnnunciatorOem;

        /** RowPointer = ASN_OBJECT_ID */
        oid saHpiAnnunciatorRDR[MAX_OID_LEN];
        long saHpiAnnunciatorRDR_len;


        /*
         * OR
         *
         * Keep a pointer to your data
         */
        void * data;

        /*
         *add anything else you want here
         */

} saHpiAnnunciatorTable_context;

/*************************************************************
 * function declarations
 */
SaErrorT populate_annunciator(SaHpiSessionIdT sessionid, 
                                      SaHpiRdrT *rdr_entry,
                                      SaHpiRptEntryT *rpt_entry,
                                      oid *full_oid, size_t full_oid_len,
                                      oid *child_oid, size_t *child_oid_len);
int set_table_annun_mode (saHpiAnnunciatorTable_context *row_ctx);

/*************************************************************
 * function declarations
 */
void init_saHpiAnnunciatorTable(void);
void initialize_table_saHpiAnnunciatorTable(void);
const saHpiAnnunciatorTable_context * saHpiAnnunciatorTable_get_by_idx(netsnmp_index *);
const saHpiAnnunciatorTable_context * saHpiAnnunciatorTable_get_by_idx_rs(netsnmp_index *,
                                                                          int row_status);
int saHpiAnnunciatorTable_get_value(netsnmp_request_info *, netsnmp_index *, netsnmp_table_request_info *);


/*************************************************************
 * oid declarations
 */
extern oid saHpiAnnunciatorTable_oid[];
extern size_t saHpiAnnunciatorTable_oid_len;

#define saHpiAnnunciatorTable_TABLE_OID 1,3,6,1,4,1,18568,2,1,1,4,6

/* Number of table Indexes */
#define ANNUNCIATOR_INDEX_NR 4 
#define saHpiDomainId_INDEX 0
#define saHpiResourceEntryId_INDEX 1
#define saHpiResourceIsHistorical_INDEX 2
#define saHpiAnnunciatorNum_INDEX 3

/*************************************************************
 * column number definitions for table saHpiAnnunciatorTable
 */
#define COLUMN_SAHPIANNUNCIATORNUM 1
#define COLUMN_SAHPIANNUNCIATORTYPE 2
#define COLUMN_SAHPIANNUNCIATORMODEREADONLY 3
#define COLUMN_SAHPIANNUNCIATORMAXCONDITIONS 4
#define COLUMN_SAHPIANNUNCIATORMODE 5
#define COLUMN_SAHPIANNUNCIATOROEM 6
#define COLUMN_SAHPIANNUNCIATORRDR 7
#define saHpiAnnunciatorTable_COL_MIN 2
#define saHpiAnnunciatorTable_COL_MAX 7


int saHpiAnnunciatorTable_extract_index( saHpiAnnunciatorTable_context * ctx, netsnmp_index * hdr );

void saHpiAnnunciatorTable_set_reserve1( netsnmp_request_group * );
void saHpiAnnunciatorTable_set_reserve2( netsnmp_request_group * );
void saHpiAnnunciatorTable_set_action( netsnmp_request_group * );
void saHpiAnnunciatorTable_set_commit( netsnmp_request_group * );
void saHpiAnnunciatorTable_set_free( netsnmp_request_group * );
void saHpiAnnunciatorTable_set_undo( netsnmp_request_group * );

saHpiAnnunciatorTable_context * saHpiAnnunciatorTable_duplicate_row( saHpiAnnunciatorTable_context* );
netsnmp_index * saHpiAnnunciatorTable_delete_row( saHpiAnnunciatorTable_context* );

int saHpiAnnunciatorTable_can_activate(saHpiAnnunciatorTable_context *undo_ctx,
                                       saHpiAnnunciatorTable_context *row_ctx,
                                       netsnmp_request_group * rg);
int saHpiAnnunciatorTable_can_deactivate(saHpiAnnunciatorTable_context *undo_ctx,
                                         saHpiAnnunciatorTable_context *row_ctx,
                                         netsnmp_request_group * rg);
int saHpiAnnunciatorTable_can_delete(saHpiAnnunciatorTable_context *undo_ctx,
                                     saHpiAnnunciatorTable_context *row_ctx,
                                     netsnmp_request_group * rg);


saHpiAnnunciatorTable_context * saHpiAnnunciatorTable_create_row( netsnmp_index* );

saHpiAnnunciatorTable_context * saHpiAnnunciatorTable_get( const char *name, int len );

#ifdef __cplusplus
};
#endif

#endif /** SAHPIANNUNCIATORTABLE_H */
