/**************************************************************************
*
* Copyright (C) 2005 Steve Karg <skarg@users.sourceforge.net>
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
*********************************************************************/
#include <stddef.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include "config.h"
#include "txbuf.h"
#include "bacdef.h"
#include "bacdcode.h"
#include "address.h"
#include "tsm.h"
#include "npdu.h"
#include "apdu.h"
#include "device.h"
#include "datalink.h"
#include "dcc.h"
#include "whois.h"
#include "bacenum.h"
/* some demo stuff needed */
#include "handlers.h"
#include "txbuf.h"
#include "client.h"

/** @file s_whois.c  Send a Who-Is request. */

/** Send a Who-Is request to a remote network for a specific device, a range,
 * or any device.
 * If low_limit and high_limit both are -1, then the range is unlimited.
 * If low_limit and high_limit have the same non-negative value, then only
 * that device will respond.
 * Otherwise, low_limit must be less than high_limit.
 * @param target_address [in] BACnet address of target router
 * @param low_limit [in] Device Instance Low Range, 0 - 4,194,303 or -1
 * @param high_limit [in] Device Instance High Range, 0 - 4,194,303 or -1
 */
void Send_WhoIs_To_Network(
    BACNET_ROUTE * dest,
    int32_t low_limit,
    int32_t high_limit)
{
    int len = 0;
    int pdu_len = 0;
    int bytes_sent = 0;
    BACNET_NPCI_DATA npci_data;
    BACNET_ADDRESS my_address;

	DLCB *dlcb = alloc_dlcb_response('t', dest );
	if (dlcb == NULL) return;

    datalink_get_my_address(&my_address);
    /* encode the NPDU portion of the packet */
    npdu_setup_npci_data(&npci_data, false, MESSAGE_PRIORITY_NORMAL);

    pdu_len =
        npdu_encode_pdu(&dlcb->Handler_Transmit_Buffer[0], target_address,
        &my_address, &npci_data);
    /* encode the APDU portion of the packet */
    len =
        whois_encode_apdu(&dlcb->Handler_Transmit_Buffer[pdu_len], low_limit,
                          high_limit);
    pdu_len += len;
    bytes_sent =
        datalink_send_pdu(target_address, &npci_data, dlcb );
#if PRINT_ENABLED
    if (bytes_sent <= 0)
        fprintf(stderr, "Failed to Send Who-Is Request (%s)!\n",
            strerror(errno));
#endif
}

/** Send a global Who-Is request for a specific device, a range, or any device.
 * If low_limit and high_limit both are -1, then the range is unlimited.
 * If low_limit and high_limit have the same non-negative value, then only
 * that device will respond.
 * Otherwise, low_limit must be less than high_limit.
 * @param low_limit [in] Device Instance Low Range, 0 - 4,194,303 or -1
 * @param high_limit [in] Device Instance High Range, 0 - 4,194,303 or -1
 */
void Send_WhoIs_Global(
    PORT_SUPPORT  *portParams,
    int32_t low_limit,
    int32_t high_limit)
{
    BACNET_ROUTE dest;

    if (!dcc_communication_enabled())
        return;

    dest.portParams = portParams;
    /* Who-Is is a global broadcast */
    // todo2 - why not return a pointer, less copying...
    // portParams->get_broadcast_address(portParams, &dest);
    bacnet_path_set_broadcast_global(&dest.bacnetPath );

    Send_WhoIs_To_Network(&dest, low_limit, high_limit);
}

/** Send a local Who-Is request for a specific device, a range, or any device.
 * If low_limit and high_limit both are -1, then the range is unlimited.
 * If low_limit and high_limit have the same non-negative value, then only
 * that device will respond.
 * Otherwise, low_limit must be less than high_limit.
 * @param low_limit [in] Device Instance Low Range, 0 - 4,194,303 or -1
 * @param high_limit [in] Device Instance High Range, 0 - 4,194,303 or -1
 */
void Send_WhoIs_Local(
    PORT_SUPPORT  *portParams,
    int32_t low_limit,
    int32_t high_limit)
{
    BACNET_ROUTE dest;
    char temp[6];
    int loop;

    if (!dcc_communication_enabled())
        return;

    /* Who-Is is a global broadcast */
    datalink_get_broadcast_address(&dest);
    dest.portParams = portParams;
    bacnet_path_set_broadcast_local(&dest.bacnetPath );


    Send_WhoIs_To_Network(&dest, low_limit, high_limit);
}

/** Send a Who-Is request to a remote network for a specific device, a range,
 * or any device.
 * @ingroup DMDDB
 * If low_limit and high_limit both are -1, then the range is unlimited.
 * If low_limit and high_limit have the same non-negative value, then only
 * that device will respond.
 * Otherwise, low_limit must be less than high_limit.
 * @param target_address [in] BACnet address of target router
 * @param low_limit [in] Device Instance Low Range, 0 - 4,194,303 or -1
 * @param high_limit [in] Device Instance High Range, 0 - 4,194,303 or -1
 */
void Send_WhoIs_Remote(
    PORT_SUPPORT  *portParams,
    BACNET_PATH * target_address,
    int32_t low_limit,
    int32_t high_limit)
{
    BACNET_ROUTE dest;
    if (!dcc_communication_enabled())
        return;

    dest.portParams = portParams;
    bacnet_path_copy(&dest.bacnetPath, target_address);
    Send_WhoIs_To_Network(target_address, low_limit, high_limit);
}

/** Send a global Who-Is request for a specific device, a range, or any device.
 * @ingroup DMDDB
 * This was the original Who-Is broadcast but the code was moved to the more
 * descriptive Send_WhoIs_Global when Send_WhoIs_Local and Send_WhoIsRemote was
 * added.
 * If low_limit and high_limit both are -1, then the range is unlimited.
 * If low_limit and high_limit have the same non-negative value, then only
 * that device will respond.
 * Otherwise, low_limit must be less than high_limit.
 * @param low_limit [in] Device Instance Low Range, 0 - 4,194,303 or -1
 * @param high_limit [in] Device Instance High Range, 0 - 4,194,303 or -1
 */
void Send_WhoIs(
    int32_t low_limit,
    int32_t high_limit)
{
    Send_WhoIs_Global(low_limit, high_limit);
}
