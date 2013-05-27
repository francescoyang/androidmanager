#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "jptypes.h"
#include "manager_api.h"
#include "common_api.h"

#include "dbinterface.h"
#include "gps_api.h"
#include "net_api.h"
#include "fingerprint_api.h"
#include "download_api.h"
#include "jpcard_api.h"
#include "env.h"
#include "photoresponse_api.h"
#include "spi_manager_api.h"
#include "softwareconfig.h"
#include "spi_manager_api.h"
#include "pwm_api.h"
#include "data_update.h"
#include "gpio_api.h"
#include "debug_out.h"
#include <sys/time.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __managermod{
	void *managerp;
	pthread_t tid;
	pthread_attr_t tattr;
}managermod_t;

static managermod_t managermod;
static struct timeval timelast = {-1, -1};
static int timeremain;

static int open_jpsystem_init(void)
{
	int i;
	int voltage = 0;
	struct timespec rem = { 0, 5000000};
	for (i = 0; i < 4; i++) {
		voltage = read_voltage();
		nanosleep(&rem, &rem);
		DEBUG_OUT(DEBUG_GZQ, "read voltage = %d\n", voltage);
	}
	
	operation_lm2(1);
	operation_12v(1);

	open_key();
	return 0;
}


void* manager_pthread(void* arg) 
{
	//creat gps pthread
	uartdev_t udev;
	netdev_t ndev;
	peripheral_t peridev;
	pwmdev_t curpwm;
	struct timeval timecur;
	//parseparam_init
	char buf_file[128];
	memset(buf_file,0,128);
	sprintf(buf_file,"%s/%s",jpsys_config_base,"config");
 	softwareconfig_mode_init(buf_file);

	devid = get_devid_bydb();

	//if (!get_jpcarddevname_bydb(&udev)) {
//		gpiomode_init(udev.name);
//	}

	gpiomode_init("/dev/gpio");



	if (!get_fingerdevname_bydb(&udev)) {
		finger_pthread_modulse_init(&udev);
		jpcard_pthread_modulse_init(&udev);
		fingersetbaute();
	}
	

	if (!get_gpsdevname_bydb(&udev)) {
		gps_pthread_modules_init(&udev);
	}

	if (!get_netdevname_bydb(&ndev)) {
		net_pthread_env_init();
		net_pthread_modules_init(&ndev);
		download_pthread_modules_init();
	}

	mediaconfig config;
	memset(&config,0,sizeof(mediaconfig));
	config.device_id = devid;
	memcpy(config.server_ip, "192.168.1.249", 13);
	config.server_port = (short)7303;
	config.encode_type = (short)0;
	memcpy(config.path, "/opt/jpsystem/content", strlen("/opt/jpsystem/content")+1);	
	jpsys_configure(&config);


	if (!get_peridevname_bydb(&peridev)) {

		// spi
		spi_modules_init(&peridev.spidev);  
		open_jpsystem_init();

		// pho
		photoresponse_modules_init(&peridev.phodev);
		photoresponse_readval();
		
		// pwm
		pwm_module_init(&peridev.pwmdev);
	}

	if (!get_dataupdev_bydb(&ndev)){
		dataup_pthread_modules_init(&ndev);
	}
	
	timeremain = (ndev.reconnect==0?5:ndev.reconnect);
	gettimeofday(&timelast,0);
	DEBUG_OUT(DEBUG_GZQ, "manage thread: timeremain = %d\n",timeremain);

	while ( 1 ) {
		//read spi
		if (test_poweroff_status()) {
			DEBUG_OUT(DEBUG_GZQ, "test_poweroff_status close\n");
			break;
		}
	if (test_restart_status()) {
			break;
		}



		if (!get_pwmdevname_bydb(&curpwm)) {
			autoconctl_backlight(&curpwm);
		}

		gettimeofday(&timecur,0);
		if(timecur.tv_sec-timelast.tv_sec < 5 || timeremain < 0) continue;	
#if 0
		if (!get_gpsdevname_bydb(&udev)) {
			if (PTHREAD_ERROR == test_gps_pthread_status()) {
				gps_pthread_modules_init(&udev);	
			}
		}
#endif
		//creat wifi pthread
		if (!get_netdevname_bydb(&ndev)) {
			if (PTHREAD_ERROR == test_net_pthread_status()) {
				net_pthread_modules_init(&ndev);
				timeremain--;
				DEBUG_OUT(DEBUG_GZQ, "manage thread: restart net_pthread...remain = %d\n",timeremain);
			}
		}
		gettimeofday(&timelast,0);

		usleep(800000);
		jp_exec("/bin/sync",NULL,NULL);
	}


	if (!get_gpsdevname_bydb(&udev)) {
		if (PTHREAD_OK == test_gps_pthread_status()) {
			gps_pthread_modules_kill();
		}
	}

		//creat wifi pthread
	if (!get_netdevname_bydb(&ndev)) {
		if (PTHREAD_OK == test_net_pthread_status()) {
			net_pthread_modules_kill();
		}
	}
// save data
//save data ok send perweroff now
	poweroff_now();
	pthread_exit(NULL);
}

int manager_modulse_init(void)
{

	if (!pthread_attr_init(&managermod.tattr)) {
		if (!pthread_attr_setdetachstate(&managermod.tattr, PTHREAD_CREATE_DETACHED)) {
			pthread_create(&managermod.tid, &managermod.tattr, manager_pthread, NULL);
			pthread_attr_destroy(&managermod.tattr);
		} else {
			return -1;
		}	
	} else {
		return -1;
	}

	return 0;
}


#ifdef __cplusplus
}
#endif

