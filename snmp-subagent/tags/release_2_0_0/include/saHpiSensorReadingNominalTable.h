/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.array-user.conf,v 5.18.2.2 2004/02/09 18:21:47 rstory Exp $
 *
 * $Id$
 *
 * Yes, there is lots of code here that you might not use. But it is much
 * easier to remove code than to add it!
 */
#ifndef SAHPISENSORREADINGNOMINALTABLE_H
#define SAHPISENSORREADINGNOMINALTABLE_H

#ifdef __cplusplus
extern "C" {
#endif


#include <net-snmp/net-snmp-config.h>
#include <net-snmp/library/container.h>
#include <net-snmp/agent/table_array.h>

/** Index saHpiDomainId is external */
/** Index saHpiResourceId is external */
/** Index saHpiResourceIsHistorical is external */
/** Index saHpiSensorNum is external */

typedef struct saHpiSensorReadingNominalTable_context_s {
	netsnmp_index index; /** THIS MUST BE FIRST!!! */

	/*************************************************************
	 * You can store data internally in this structure.
	 *
	 * TODO: You will probably have to fix a few types here...
	 */
	/** TODO: add storage for external index(s)! */
	/** TruthValue = ASN_INTEGER */
	long saHpiSensorReadingNominalIsSupported;

	/** SaHpiSensorReadingType = ASN_INTEGER */
	long saHpiSensorReadingNominalType;

	/** SaHpiSensorReadingValue = ASN_OCTET_STR */
	unsigned char saHpiSensorReadingNominalValue[SAHPI_SENSOR_BUFFER_LENGTH];
	long saHpiSensorReadingNominalValue_len;


	/*
	 * OR
	 *
	 * Keep a pointer to your data
	 */
	void * data;

	/*
	 *add anything else you want here
	 */

} saHpiSensorReadingNominalTable_context;

/*
 * SaErrorT populate_sensor_nominal()
 */
	SaErrorT populate_sensor_nominal(SaHpiSessionIdT sessionid, 
					 SaHpiRdrT *rdr_entry,
					 SaHpiRptEntryT *rpt_entry);

/*************************************************************
 * function declarations
 */
void init_saHpiSensorReadingNominalTable(void);
void initialize_table_saHpiSensorReadingNominalTable(void);
const saHpiSensorReadingNominalTable_context * saHpiSensorReadingNominalTable_get_by_idx(netsnmp_index *);
const saHpiSensorReadingNominalTable_context * saHpiSensorReadingNominalTable_get_by_idx_rs(netsnmp_index *,
											    int row_status);
int saHpiSensorReadingNominalTable_get_value(netsnmp_request_info *, netsnmp_index *, netsnmp_table_request_info *);


/*************************************************************
 * oid declarations
 */
extern oid saHpiSensorReadingNominalTable_oid[];
extern size_t saHpiSensorReadingNominalTable_oid_len;

#define saHpiSensorReadingNominalTable_TABLE_OID 1,3,6,1,4,1,18568,2,1,1,4,9,6

/* Number of table Indexes */
#define SENSOR_READING_NOMINAL_INDEX_NR 4 

/*************************************************************
 * column number definitions for table saHpiSensorReadingNominalTable
 */
#define COLUMN_SAHPISENSORREADINGNOMINALISSUPPORTED 1
#define COLUMN_SAHPISENSORREADINGNOMINALTYPE 2
#define COLUMN_SAHPISENSORREADINGNOMINALVALUE 3
#define saHpiSensorReadingNominalTable_COL_MIN 1
#define saHpiSensorReadingNominalTable_COL_MAX 3


int saHpiSensorReadingNominalTable_extract_index( saHpiSensorReadingNominalTable_context * ctx, netsnmp_index * hdr );

void saHpiSensorReadingNominalTable_set_reserve1( netsnmp_request_group * );
void saHpiSensorReadingNominalTable_set_reserve2( netsnmp_request_group * );
void saHpiSensorReadingNominalTable_set_action( netsnmp_request_group * );
void saHpiSensorReadingNominalTable_set_commit( netsnmp_request_group * );
void saHpiSensorReadingNominalTable_set_free( netsnmp_request_group * );
void saHpiSensorReadingNominalTable_set_undo( netsnmp_request_group * );

saHpiSensorReadingNominalTable_context * saHpiSensorReadingNominalTable_duplicate_row( saHpiSensorReadingNominalTable_context* );
netsnmp_index * saHpiSensorReadingNominalTable_delete_row( saHpiSensorReadingNominalTable_context* );

int saHpiSensorReadingNominalTable_can_activate(saHpiSensorReadingNominalTable_context *undo_ctx,
						saHpiSensorReadingNominalTable_context *row_ctx,
						netsnmp_request_group * rg);
int saHpiSensorReadingNominalTable_can_deactivate(saHpiSensorReadingNominalTable_context *undo_ctx,
						  saHpiSensorReadingNominalTable_context *row_ctx,
						  netsnmp_request_group * rg);
int saHpiSensorReadingNominalTable_can_delete(saHpiSensorReadingNominalTable_context *undo_ctx,
					      saHpiSensorReadingNominalTable_context *row_ctx,
					      netsnmp_request_group * rg);


saHpiSensorReadingNominalTable_context * saHpiSensorReadingNominalTable_create_row( netsnmp_index* );

saHpiSensorReadingNominalTable_context * saHpiSensorReadingNominalTable_get( const char *name, int len );

#ifdef __cplusplus
};
#endif

#endif /** SAHPISENSORREADINGNOMINALTABLE_H */
