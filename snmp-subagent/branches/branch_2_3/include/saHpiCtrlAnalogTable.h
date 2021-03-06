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
#ifndef SAHPICTRLANALOGTABLE_H
#define SAHPICTRLANALOGTABLE_H

#ifdef __cplusplus
extern "C" {
#endif


#include <net-snmp/net-snmp-config.h>
#include <net-snmp/library/container.h>
#include <net-snmp/agent/table_array.h>

#include <SaHpi.h>
#include <oh_utils.h>

	/** Index saHpiDomainId is external */
	/** Index saHpiResourceId is external */
	/** Index saHpiResourceIsHistorical is external */
	/** Index saHpiCtrlAnalogEntryId is internal */

	typedef struct saHpiCtrlAnalogTable_context_s {
		netsnmp_index index; /** THIS MUST BE FIRST!!! */

		/*************************************************************
		 * You can store data internally in this structure.
		 *
		 * TODO: You will probably have to fix a few types here...
		 */
		/** TODO: add storage for external index(s)! */
		/** SaHpiEntryId = ASN_UNSIGNED */
		unsigned long saHpiCtrlAnalogEntryId;

		/** SaHpiInstrumentId = ASN_UNSIGNED */
		unsigned long saHpiCtrlAnalogNum;

		/** SaHpiCtrlOutputType = ASN_INTEGER */
		long saHpiCtrlAnalogOutputType;

		/** SaHpiCtrlMode = ASN_INTEGER */
		long saHpiCtrlAnalogDefaultMode;

		/** SaHpiCtrlMode = ASN_INTEGER */
		long saHpiCtrlAnalogMode;

		/** TruthValue = ASN_INTEGER */
		long saHpiCtrlAnalogIsReadOnly;

		/** TruthValue = ASN_INTEGER */
		long saHpiCtrlAnalogIsWriteOnly;

		/** INTEGER = ASN_INTEGER */
		long saHpiCtrlAnalogDefaultMinState;

		/** INTEGER = ASN_INTEGER */
		long saHpiCtrlAnalogDefaultMaxState;

		/** INTEGER = ASN_INTEGER */
		long saHpiCtrlAnalogDefaultState;

		/** INTEGER = ASN_INTEGER */
		long saHpiCtrlAnalogState;

		/** UNSIGNED32 = ASN_UNSIGNED */
		unsigned long saHpiCtrlAnalogOem;

		/** RowPointer = ASN_OBJECT_ID */
		oid saHpiCtrlAnalogRDR[MAX_OID_LEN];
		long saHpiCtrlAnalogRDR_len;


		/*
		 * OR
		 *
		 * Keep a pointer to your data
		 */
		void * data;

		/*
		 *add anything else you want here
		 */

	} saHpiCtrlAnalogTable_context;


/*************************************************************
 * set funtions
 */
int set_table_ctrl_analog_mode (saHpiCtrlAnalogTable_context *row_ctx);
int set_table_ctrl_analog_state (saHpiCtrlAnalogTable_context *row_ctx);


/*************************************************************
 * function declarations
 */
SaErrorT populate_ctrl_analog(SaHpiSessionIdT sessionid, 
			      SaHpiRdrT *rdr_entry,
			      SaHpiRptEntryT *rpt_entry,
			      oid *full_oid, size_t full_oid_len,
			      oid *child_oid, size_t *child_oid_len);
SaErrorT clear_ctrl_analog(SaHpiDomainIdT domainId, 
                           SaHpiResourceIdT resourceId);


/*************************************************************
 * function declarations
 */
void init_saHpiCtrlAnalogTable(void);
void initialize_table_saHpiCtrlAnalogTable(void);
const saHpiCtrlAnalogTable_context * saHpiCtrlAnalogTable_get_by_idx(netsnmp_index *);
const saHpiCtrlAnalogTable_context * saHpiCtrlAnalogTable_get_by_idx_rs(netsnmp_index *,
										int row_status);
int saHpiCtrlAnalogTable_get_value(netsnmp_request_info *, netsnmp_index *, netsnmp_table_request_info *);


/*************************************************************
 * oid declarations
 */
extern oid saHpiCtrlAnalogTable_oid[];
extern size_t saHpiCtrlAnalogTable_oid_len;

#define saHpiCtrlAnalogTable_TABLE_OID 1,3,6,1,4,1,18568,2,1,1,4,7,7

/* Number of table Indexes */
#define CTRL_ANALOG_INDEX_NR 4 
#define saHpiCtrlAnalogDomainId_INDEX 0
#define saHpiCtrlAnalogResourceEntryId_INDEX 1
#define saHpiCtrlAnalogResourceIsHistorical_INDEX 2
#define saHpiCtrlAnalogEntryId_INDEX 3

/*************************************************************
 * column number definitions for table saHpiCtrlAnalogTable
 */
#define COLUMN_SAHPICTRLANALOGENTRYID 1
#define COLUMN_SAHPICTRLANALOGNUM 2
#define COLUMN_SAHPICTRLANALOGOUTPUTTYPE 3
#define COLUMN_SAHPICTRLANALOGDEFAULTMODE 4
#define COLUMN_SAHPICTRLANALOGMODE 5
#define COLUMN_SAHPICTRLANALOGISREADONLY 6
#define COLUMN_SAHPICTRLANALOGISWRITEONLY 7
#define COLUMN_SAHPICTRLANALOGDEFAULTMINSTATE 8
#define COLUMN_SAHPICTRLANALOGDEFAULTMAXSTATE 9
#define COLUMN_SAHPICTRLANALOGDEFAULTSTATE 10
#define COLUMN_SAHPICTRLANALOGSTATE 11
#define COLUMN_SAHPICTRLANALOGOem 12
#define COLUMN_SAHPICTRLANALOGRDR 13
#define saHpiCtrlAnalogTable_COL_MIN 2
#define saHpiCtrlAnalogTable_COL_MAX 13

/* comment out the following line if you don't handle SET-REQUEST for saHpiCtrlAnalogTable */
#define saHpiCtrlAnalogTable_SET_HANDLING

/* comment out the following line if you can't create new rows */
#define saHpiCtrlAnalogTable_ROW_CREATION

/* comment out the following line if you don't want the secondary index */
#define saHpiCtrlAnalogTable_IDX2

/* uncommend the following line if you allow modifications to an
 * active row */
/** define saHpiCtrlAnalogTable_CAN_MODIFY_ACTIVE_ROW */

	int saHpiCtrlAnalogTable_extract_index( saHpiCtrlAnalogTable_context * ctx, netsnmp_index * hdr );

	void saHpiCtrlAnalogTable_set_reserve1( netsnmp_request_group * );
	void saHpiCtrlAnalogTable_set_reserve2( netsnmp_request_group * );
	void saHpiCtrlAnalogTable_set_action( netsnmp_request_group * );
	void saHpiCtrlAnalogTable_set_commit( netsnmp_request_group * );
	void saHpiCtrlAnalogTable_set_free( netsnmp_request_group * );
	void saHpiCtrlAnalogTable_set_undo( netsnmp_request_group * );

	saHpiCtrlAnalogTable_context * saHpiCtrlAnalogTable_duplicate_row( saHpiCtrlAnalogTable_context* );
	netsnmp_index * saHpiCtrlAnalogTable_delete_row( saHpiCtrlAnalogTable_context* );

	int saHpiCtrlAnalogTable_can_activate(saHpiCtrlAnalogTable_context *undo_ctx,
					      saHpiCtrlAnalogTable_context *row_ctx,
					      netsnmp_request_group * rg);
	int saHpiCtrlAnalogTable_can_deactivate(saHpiCtrlAnalogTable_context *undo_ctx,
						saHpiCtrlAnalogTable_context *row_ctx,
						netsnmp_request_group * rg);
	int saHpiCtrlAnalogTable_can_delete(saHpiCtrlAnalogTable_context *undo_ctx,
					    saHpiCtrlAnalogTable_context *row_ctx,
					    netsnmp_request_group * rg);

	saHpiCtrlAnalogTable_context * saHpiCtrlAnalogTable_create_row( netsnmp_index* );
	saHpiCtrlAnalogTable_context * saHpiCtrlAnalogTable_get( const char *name, int len );

#ifdef __cplusplus
};
#endif

#endif /** SAHPICTRLANALOGTABLE_H */
