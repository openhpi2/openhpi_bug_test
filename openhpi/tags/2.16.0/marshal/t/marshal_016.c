/*
 * Copyright (c) 2004 by FORCE Computers.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  This
 * file and program are licensed under a BSD style license.  See
 * the Copying file included with the OpenHPI distribution for
 * full licensing terms.
 *
 * Authors:
 *     Thomas Kanngieser <thomas.kanngieser@fci.com>
 */

#include <glib.h>
#include "marshal.h"
#include <glib.h>


int
main( int argc, char *argv[] )
{
  tInt16 value = 0x42aa;
  tInt16 swap = GUINT16_SWAP_LE_BE( value );
  tInt16  result;

  unsigned int s = Demarshal( G_BYTE_ORDER == G_LITTLE_ENDIAN ? G_BIG_ENDIAN : G_LITTLE_ENDIAN,
                              &Marshal_Int16Type, &result, &swap );

  if ( s != sizeof( tInt16 ) )
       return 1;

  if ( value != result )
       return 1;

  return 0;
}
