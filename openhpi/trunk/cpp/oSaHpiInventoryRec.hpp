/*      -*- linux-c -*-
 *
 * (C) Copyright IBM Corp. 2005
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  This
 * file and program are licensed under a BSD style license.  See
 * the Copying file included with the OpenHPI distribution for
 * full licensing terms.
 *
 * Author(s):
 *    W. David Ashley <dashley@us.ibm.com>
 */


#ifndef Included_oSaHpiInventoryRec
#define Included_oSaHpiInventoryRec

#include <stdio.h>
extern "C"
{
#include <SaHpi.h>
}


class oSaHpiInventoryRec : public SaHpiInventoryRecT {
    public:
        // constructors
        oSaHpiInventoryRec();
        // copy constructor
        oSaHpiInventoryRec(const oSaHpiInventoryRec& buf);
        // destructor
        ~oSaHpiInventoryRec() {
        }
        // other methods
        bool assignField(SaHpiInventoryRecT * ptr,
                         const char *field,
                         const char *value);
        inline bool assignField(const char *field,
                                const char *value) {
            return assignField(this, field, value);
        }
        inline SaHpiInventoryRecT *getStruct(void) {
            return this;
        }
        bool fprint(FILE *stream,
                    const int indent,
                    const SaHpiInventoryRecT *buffer);
        inline bool fprint(FILE *stream,
                           const int indent) {
            return fprint(stream, indent, this);
        }
};

#endif

