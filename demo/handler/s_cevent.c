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
#include "event.h"
#include "device.h"
#include "datalink.h"
#include "tsm.h"
#include "dcc.h"
#include "address.h"
/* some demo stuff needed */
#include "handlers.h"
#include "txbuf.h"
#include "client.h"

/** @file s_cevent.c  Send a ConfirmedEventNotification Request. */

/** Sends an Confirmed Alarm/Event Notification.
 * @ingroup EVNOTFCN
 *
 * @param device_id [in] ID of the destination device
 * @param data [in] The information about the Event to be sent.
 * @return invoke id of outgoing message, or 0 if communication is disabled,
 *         or no tsm slot is available.
 */
uint8_t Send_CEvent_Notify(
	PORT_SUPPORT *portParams,
    uint32_t device_id,
    BACNET_EVENT_NOTIFICATION_DATA * data)
{
    int len = 0;
    int pdu_len = 0;
    int bytes_sent = 0;
    BACNET_NPCI_DATA npci_data;
    BACNET_PATH dest;
    //BACNET_GLOBAL_ADDRESS my_address;
    unsigned max_apdu = 0;
    bool status = false;
    uint8_t invoke_id = 0;

    if (!dcc_communication_enabled())
        return 0;

    /* is the device bound? */
    status = address_get_by_device(device_id, &max_apdu, &dest);
    /* is there a tsm available? */
    if (status)
        invoke_id = tsm_next_free_invokeID();
    if (invoke_id) {
        /* encode the NPDU portion of the packet */
        datalink_get_my_address(&my_address);
        npdu_setup_npci_data(&npci_data, true, MESSAGE_PRIORITY_NORMAL);
        pdu_len =
            npdu_encode_pdu(&dlcb->Handler_Transmit_Buffer[0], &dest->bacnetPath.glAdr, NULL, // &my_address,
                            &npci_data);
        /* encode the APDU portion of the packet */
        len =
            cevent_notify_encode_apdu(&dlcb->Handler_Transmit_Buffer[pdu_len],
                                      invoke_id, data);
        pdu_len += len;
        /* will it fit in the sender?
           note: if there is a bottleneck router in between
           us and the destination, we won't know unless
           we have a way to check for that and update the
           max_apdu in the address binding table. */
        if ((unsigned) pdu_len < max_apdu) {
            dlcb->optr = pdu_len;
            tsm_set_confirmed_unsegmented_transaction(invoke_id, &dest,
                &npci_data, dlcb );
            bytes_sent =
                datalink_send_pdu(&dest, &npci_data,
                dlcb );
#if PRINT_ENABLED
            if (bytes_sent <= 0) {
                fprintf(stderr,
                    "Failed to Send ConfirmedEventNotification Request (%s)!\n",
                    strerror(errno));
            }
#endif
        } else {
            tsm_free_invoke_id(invoke_id);
            invoke_id = 0;
#if PRINT_ENABLED
            fprintf(stderr,
                "Failed to Send ConfirmedEventNotification Request "
                "(exceeds destination maximum APDU)!\n");
#endif
        }
    }

    return invoke_id;
}
