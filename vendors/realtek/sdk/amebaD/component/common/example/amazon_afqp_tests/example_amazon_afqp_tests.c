
#include <platform_opts.h>

#if (CONFIG_EXAMPLE_AMAZON_AFQP_TESTS)

#include "FreeRTOS.h"
#include "task.h"
#include "diag.h"

#include "unity_fixture.h"
#include "unity.h"
#include "jsmn.h"
#include "aws_iot_ota_types.h"




#if !defined(configSUPPORT_STATIC_ALLOCATION) || (configSUPPORT_STATIC_ALLOCATION != 1)
/* #define configSUPPORT_STATIC_ALLOCATION 1 */
#error configSUPPORT_STATIC_ALLOCATION must be defined in FreeRTOSConfig.h as 1. 
#endif

#if !defined(CONFIG_USE_MBEDTLS) || (CONFIG_USE_MBEDTLS != 1)
#error CONFIG_USE_MBEDTLS must be defined in platform_opts.h as 1. 
#endif

extern int aws_test_main(void);

static void example_amazon_afqp_tests_thread(void *pvParameters)
{
    aws_test_main();
#if !defined(configUSE_DAEMON_TASK_STARTUP_HOOK) || (configUSE_DAEMON_TASK_STARTUP_HOOK == 0)
    vApplicationDaemonTaskStartupHook();
#endif
    vTaskDelete(NULL);
    return;
}

void example_amazon_afqp_tests(void)
{    
    if(xTaskCreate(example_amazon_afqp_tests_thread, ((const char*)"example_amazon_afqp_tests_thread"), 512, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
        printf("\n\r%s xTaskCreate(example_amazon_afqp_tests_thread) failed", __FUNCTION__);
}

#endif // #if (CONFIG_EXAMPLE_AMAZON_AFQP_TESTS)
