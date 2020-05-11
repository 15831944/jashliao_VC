/*---------------------------------------------------------------------------*
 |              PDFlib - A library for generating PDF on the fly             |
 +---------------------------------------------------------------------------+
 | Copyright (c) 1997-2005 Thomas Merz and PDFlib GmbH. All rights reserved. |
 +---------------------------------------------------------------------------+
 |                                                                           |
 |    This software is subject to the PDFlib license. It is NOT in the       |
 |    public domain. Extended versions and commercial licenses are           |
 |    available, please check http://www.pdflib.com.                         |
 |                                                                           |
 *---------------------------------------------------------------------------*/

/* $Id: pc_crypt.c,v 1.48.2.10 2006/02/27 17:16:38 york Exp $
 *
 * Routines for PDF encryption and decryption
 *
 */

#include "pc_util.h"
#include "pc_md5.h"
#include "pc_arc4.h"
#include "pc_crypt.h"


static void pdc_pd_crypt_c(void) {}

