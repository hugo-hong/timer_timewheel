#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include "x_utils.h"
#include "timewheel.h"

/*******************************************************************************
 *                      Macros & Type Define
 *******************************************************************************/
#define TAG    "MAIN"



/*******************************************************************************
 *                      Structures
 *******************************************************************************/
struct request_para{
    void *timer;
    int val;
};

/*******************************************************************************
 *                      Internal Function Declarations
 *******************************************************************************/

/*******************************************************************************
 *                      External Function Declarations
 *******************************************************************************/

/*******************************************************************************
 *                      Variable Definitions
 *******************************************************************************/



/*******************************************************************************
 *                      External Variable Declaration
 *******************************************************************************/

/*******************************************************************************
 *                      Function Definitions
 *******************************************************************************/


void mytimer(unsigned long arg)
{
    struct request_para *para = (struct request_para *)arg;

    LOG_DBG(TAG, "%d", para->val);

    ti_mod_timer(para->timer, 3000);

	sleep(10);

    // DELETE TIMER
    //ti_del_timer(para->timer);
}

void main() {
    LOG_DBG(TAG, "hello timewheel demo \n");

    void *tw = NULL;
    void *te  = NULL;
    struct request_para *para;


    para = (struct request_para *)X_MALLOC( sizeof(struct request_para) );
    X_ASSERT(TAG, para != NULL);

    // CREATE TIMEWHEEL
    tw = ti_timewheel_create();
    X_ASSERT(TAG, tw != NULL);

    // ADD TIMER
    para->val = 100;
    para->timer = ti_add_timer(tw, 3000, &mytimer, (unsigned long)para);

    while(1)
    {
        sleep(2);
    }

    // RELEASE TIMEWHEEL
    ti_timewheel_release(tw);

    X_FREE(para);

}
