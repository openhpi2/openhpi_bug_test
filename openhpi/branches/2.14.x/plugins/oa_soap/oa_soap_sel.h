/*
 * Copyright (C) 2007-2008, Hewlett-Packard Development Company, LLP
 *                     All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in
 * the documentation and/or other materials provided with the distribution.
 *
 * Neither the name of the Hewlett-Packard Corporation, nor the names
 * of its contributors may be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Author(s)
 *      Raghavendra M.S. <raghavendra.ms@hp.com>
 */

#ifndef _OA_SOAP_SEL_H
#define _OA_SOAP_SEL_H

/* Include files */
#include <SaHpi.h>
#include <oh_error.h>

SaErrorT oa_soap_get_sel_info(void *oh_handler,
                             SaHpiResourceIdT resource_id,
                             SaHpiEventLogInfoT *info);

SaErrorT oa_soap_set_sel_time(void *oh_handler,
                             SaHpiResourceIdT resource_id,
                             SaHpiTimeT time);

SaErrorT oa_soap_add_sel_entry(void *oh_handler,
                              SaHpiResourceIdT resource_id,
                              const SaHpiEventT *Event);

SaErrorT oa_soap_clear_sel(void *oh_handler,
                          SaHpiResourceIdT id);

SaErrorT oa_soap_reset_sel_overflow(void *oh_handler,
                                   SaHpiResourceIdT resource_id);

SaErrorT oa_soap_get_sel_entry(void *oh_handler,
                              SaHpiResourceIdT resource_id,
                              SaHpiEventLogEntryIdT current,
                              SaHpiEventLogEntryIdT *prev,
                              SaHpiEventLogEntryIdT *next,
                              SaHpiEventLogEntryT *entry,
                              SaHpiRdrT *rdr,
                              SaHpiRptEntryT  *rpt);

SaErrorT oa_soap_sel_state_set(void *oh_handler,
                              SaHpiResourceIdT id,
                              SaHpiBoolT enable);

#endif

