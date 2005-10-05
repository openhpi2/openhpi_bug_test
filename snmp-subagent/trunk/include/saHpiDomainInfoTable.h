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
 *        : mib2c.array-user.conf,v 5.18.2.2 2004/02/09 18:21:47 rstory Exp $
 *
 * $Id$
 *
 * Yes, there is lots of code here that you might not use. But it is much
 * easier to remove code than to add it!
 */
#ifndef SAHPIDOMAININFOTABLE_H
#define SAHPIDOMAININFOTABLE_H

#ifdef __cplusplus
extern "C" {
#endif

    
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/library/container.h>
#include <net-snmp/agent/table_array.h>

#include <SaHpi.h>

/* Number of table Indexes */
#define DOMAIN_INFO_INDEX_NR 1        

typedef struct saHpiDomainInfoTable_context_s {
    netsnmp_index index; /** THIS MUST BE FIRST!!! */

    /*************************************************************
     * You can store data internally in this structure.
     */
        /** SaHpiDomainId = ASN_UNSIGNED */
            unsigned long saHpiDomainId;

        /** BITS = ASN_OCTET_STR */
            unsigned char saHpiDomainCapabilities[65535];
            long saHpiDomainCapabilities_len;

        /** TruthValue = ASN_INTEGER */
            long saHpiDomainIsPeer;

        /** SaHpiTextType = ASN_INTEGER */
            long saHpiDomainTagTextType;

        /** SaHpiTextLanguage = ASN_INTEGER */
            long saHpiDomainTagTextLanguage;

        /** SaHpiText = ASN_OCTET_STR */
            unsigned char saHpiDomainTag[SAHPI_MAX_TEXT_BUFFER_LENGTH];
            long saHpiDomainTag_len;

        /** UNSIGNED32 = ASN_UNSIGNED */
            unsigned long saHpiDomainReferenceUpdateCount;

        /** SaHpiTime = ASN_COUNTER64 */
            struct counter64 saHpiDomainReferenceUpdateTimestamp;

        /** UNSIGNED32 = ASN_UNSIGNED */
            unsigned long saHpiDomainResourcePresenceUpdateCount;

        /** SaHpiTime = ASN_COUNTER64 */
            struct counter64 saHpiDomainResourcePresenceUpdateTimestamp;

        /** UNSIGNED32 = ASN_UNSIGNED */
            unsigned long saHpiDomainAlarmUpdateCount;

        /** SaHpiTime = ASN_COUNTER64 */
            struct counter64 saHpiDomainAlarmUpdateTimestamp;

        /** UNSIGNED32 = ASN_UNSIGNED */
            unsigned long saHpiDomainActiveAlarms;

        /** UNSIGNED32 = ASN_UNSIGNED */
            unsigned long saHpiDomainCriticalAlarms;

        /** UNSIGNED32 = ASN_UNSIGNED */
            unsigned long saHpiDomainMajorAlarms;

        /** UNSIGNED32 = ASN_UNSIGNED */
            unsigned long saHpiDomainMinorAlarms;

        /** UNSIGNED32 = ASN_UNSIGNED */
            unsigned long saHpiDomainAlarmUserLimit;

        /** TruthValue = ASN_INTEGER */
            long saHpiDomainAlarmOverflow;

        /** SaHpiGuid = ASN_OCTET_STR */
            unsigned char saHpiDomainGuid[ sizeof(SaHpiGuidT) ];
            long saHpiDomainGuid_len;


    /*
     * OR
     *
     * Keep a pointer to your data
     */
    void * data;

    /*
     *add anything else you want here
     */

} saHpiDomainInfoTable_context;

/*************************************************************
 * function declarations: OpenHpi
 */
int populate_saHpiDomainInfoTable(SaHpiSessionIdT sessionid);
SaErrorT async_domain_add(SaHpiSessionIdT sessionid, SaHpiEventT *event, 
                          SaHpiRdrT *rdr, SaHpiRptEntryT *rpt_entry);
SaErrorT clear_domain_info_entry(SaHpiDomainIdT domain_id); 

/*************************************************************
 * function declarations
 */
void init_saHpiDomainInfoTable(void);
void initialize_table_saHpiDomainInfoTable(void);
const saHpiDomainInfoTable_context * saHpiDomainInfoTable_get_by_idx(netsnmp_index *);
const saHpiDomainInfoTable_context * saHpiDomainInfoTable_get_by_idx_rs(netsnmp_index *,
                                        int row_status);
int saHpiDomainInfoTable_get_value(netsnmp_request_info *, netsnmp_index *, netsnmp_table_request_info *);

int set_table_domain_tag (saHpiDomainInfoTable_context *row_ctx);

/*************************************************************
 * oid declarations table
 */
extern oid saHpiDomainInfoTable_oid[];
extern size_t saHpiDomainInfoTable_oid_len;

#define saHpiDomainInfoTable_TABLE_OID 1,3,6,1,4,1,18568,2,1,1,2,2
    
/*************************************************************
 * column number definitions for table saHpiDomainInfoTable
 */
#define saHpiDomainId_INDEX 0 
 
#define COLUMN_SAHPIDOMAINID 1
#define COLUMN_SAHPIDOMAINCAPABILITIES 2
#define COLUMN_SAHPIDOMAINISPEER 3
#define COLUMN_SAHPIDOMAINTAGTEXTTYPE 4
#define COLUMN_SAHPIDOMAINTAGTEXTLANGUAGE 5
#define COLUMN_SAHPIDOMAINTAG 6
#define COLUMN_SAHPIDOMAINREFERENCEUPDATECOUNT 7
#define COLUMN_SAHPIDOMAINREFERENCEUPDATETIMESTAMP 8
#define COLUMN_SAHPIDOMAINRESOURCEPRESENCEUPDATECOUNT 9
#define COLUMN_SAHPIDOMAINRESOURCEPRESENCEUPDATETIMESTAMP 10
#define COLUMN_SAHPIDOMAINALARMUPDATECOUNT 11
#define COLUMN_SAHPIDOMAINALARMUPDATETIMESTAMP 12
#define COLUMN_SAHPIDOMAINACTIVEALARMS 13
#define COLUMN_SAHPIDOMAINCRITICALALARMS 14
#define COLUMN_SAHPIDOMAINMAJORALARMS 15
#define COLUMN_SAHPIDOMAINMINORALARMS 16
#define COLUMN_SAHPIDOMAINALARMUSERLIMIT 17
#define COLUMN_SAHPIDOMAINALARMOVERFLOW 18
#define COLUMN_SAHPIDOMAINGUID 19
#define saHpiDomainInfoTable_COL_MIN 1
#define saHpiDomainInfoTable_COL_MAX 19

/* comment out the following line if you don't handle SET-REQUEST for saHpiDomainInfoTable */
#define saHpiDomainInfoTable_SET_HANDLING

/* comment out the following line if you can't create new rows */
#define saHpiDomainInfoTable_ROW_CREATION

/* comment out the following line if you don't want the secondary index */
#define saHpiDomainInfoTable_IDX2

/* uncommend the following line if you allow modifications to an
 * active row */
/** define saHpiDomainInfoTable_CAN_MODIFY_ACTIVE_ROW */



int saHpiDomainInfoTable_extract_index( saHpiDomainInfoTable_context * ctx, netsnmp_index * hdr );

void saHpiDomainInfoTable_set_reserve1( netsnmp_request_group * );
void saHpiDomainInfoTable_set_reserve2( netsnmp_request_group * );
void saHpiDomainInfoTable_set_action( netsnmp_request_group * );
void saHpiDomainInfoTable_set_commit( netsnmp_request_group * );
void saHpiDomainInfoTable_set_free( netsnmp_request_group * );
void saHpiDomainInfoTable_set_undo( netsnmp_request_group * );

saHpiDomainInfoTable_context * saHpiDomainInfoTable_duplicate_row( saHpiDomainInfoTable_context* );
netsnmp_index * saHpiDomainInfoTable_delete_row( saHpiDomainInfoTable_context* );

int saHpiDomainInfoTable_can_activate(saHpiDomainInfoTable_context *undo_ctx,
                      saHpiDomainInfoTable_context *row_ctx,
                      netsnmp_request_group * rg);
int saHpiDomainInfoTable_can_deactivate(saHpiDomainInfoTable_context *undo_ctx,
                        saHpiDomainInfoTable_context *row_ctx,
                        netsnmp_request_group * rg);
int saHpiDomainInfoTable_can_delete(saHpiDomainInfoTable_context *undo_ctx,
                    saHpiDomainInfoTable_context *row_ctx,
                    netsnmp_request_group * rg);
    
    

saHpiDomainInfoTable_context * saHpiDomainInfoTable_create_row( netsnmp_index* );


#ifdef __cplusplus
};
#endif

#endif /** SAHPIDOMAININFOTABLE_H */
