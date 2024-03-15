/*
 * File:   newmainXC16.c
 * Author: RFI1
 *
 * Created on 8 de febrero de 2024, 18:23
 */

#include "inc/mesh.h"

#include <xc.h>

#include "inc/nr_constants.h"
#include "inc/x16.h"
#include "inc/common.h"
#include "inc/phy.h"
#include "inc/nx_common.h"
#include "inc/nf.h"

#include "inc/systemTimer.h"


void init_meshDriver() {
    
    /*[NR_COMMON]
max_retries=5
ticks_max_route=300
ticks_max_ack=5
ticks_max_broadcast=60
count_lost_adv=3
max_ticks_wait_next=100
max_ticks_jump_delay=100
max_ticks_rsvd=5
max_ticks_backoff=10
max_ticks_calm=0
se_host_bits=2
     */
    
    NF_CONFIG nf_config = { 
        .local = 1,                     //mi direccion 
    };
    
    NF_CALLBACKS nf_callbacks = {
        
        .get_current_ticks = getSystemMilis , // USHORT(*GET_CURRENT_TICKS)(USHORT *max_ticks);   
        
        // capa fisica
        .phy_listen_start  = NULL,  //
        .phy_listen_stop   = NULL,  //
        .phy_send          = NULL,  //
        .phy_status        = NULL,  //
    };
    
    if (nf_init(NX_LOG_OFF,&nf_config, &nf_callbacks) != NF_ERROR_NO_ERROR) { }
    
}
void poll_meshDriver()
{
        nf_poll();
}
    
