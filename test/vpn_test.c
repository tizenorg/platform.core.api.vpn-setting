/*
 * Copyright (c) 2014-2015 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <sys/un.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <assert.h>
#include <vpn.h>
#include <tizen_error.h>

gboolean test_thread(GIOChannel *source, GIOCondition condition,
							gpointer data);

static const char *__test_convert_error_to_string(vpn_error_e err_type)
{
	switch (err_type) {
	case VPN_ERROR_NONE:
		return "NONE";
	case VPN_ERROR_INVALID_PARAMETER:
		return "INVALID_PARAMETER";
	case VPN_ERROR_OUT_OF_MEMORY:
		return "OUT_OF_MEMORY";
	case VPN_ERROR_INVALID_OPERATION:
		return "INVALID_OPERATION";
	case VPN_ERROR_ADDRESS_FAMILY_NOT_SUPPORTED:
		return "ADDRESS_FAMILY_NOT_SUPPORTED";
	case VPN_ERROR_OPERATION_FAILED:
		return "OPERATION_FAILED";
	case VPN_ERROR_NO_CONNECTION:
		return "NO_CONNECTION";
	case VPN_ERROR_NOW_IN_PROGRESS:
		return "NOW_IN_PROGRESS";
	case VPN_ERROR_ALREADY_EXISTS:
		return "ALREADY_EXISTS";
	case VPN_ERROR_OPERATION_ABORTED:
		return "OPERATION_ABORTED";
	case VPN_ERROR_DHCP_FAILED:
		return "DHCP_FAILED";
	case VPN_ERROR_INVALID_KEY:
		return "INVALID_KEY";
	case VPN_ERROR_NO_REPLY:
		return "NO_REPLY";
	case VPN_ERROR_SECURITY_RESTRICTED:
		return "SECURITY_RESTRICTED";
	}

	return "UNKNOWN";
}

int test_vpn_init(void)
{
	int rv = vpn_initialize();

	if (rv == VPN_ERROR_NONE) {
		printf("Register Callbacks if Initialize is Successful\n");
	} else {
		printf("VPN init failed [%s]\n", __test_convert_error_to_string(rv));
		return -1;
	}

	printf("VPN init succeeded\n");
	return 1;
}

int test_vpn_deinit(void)
{
	int rv = vpn_deinitialize();

	if (rv != VPN_ERROR_NONE) {
		printf("VPN init failed [%s]\n", __test_convert_error_to_string(rv));
		return -1;
	}

	printf("VPN deinit succeeded\n");
	return 1;
}

int main(int argc, char **argv)
{
	GMainLoop *mainloop;
	mainloop = g_main_loop_new (NULL, FALSE);

	GIOChannel *channel = g_io_channel_unix_new(0);
	g_io_add_watch(channel, (G_IO_IN|G_IO_ERR|G_IO_HUP|G_IO_NVAL), test_thread, NULL);

	printf("Test Thread created...\n");

	g_main_loop_run (mainloop);

	return 0;
}

gboolean test_thread(GIOChannel *source, GIOCondition condition, gpointer data)
{
	int rv;
	char a[10];

	printf("Event received from stdin\n");

	rv = read(0, a, 10);

	if (rv <= 0 || a[0] == '0') {
		rv = vpn_deinitialize();

		if (rv != VPN_ERROR_NONE)
			printf("Fail to deinitialize.\n");

		exit(1);
	}

	if (a[0] == '\n' || a[0] == '\r') {
		printf("\n\n Network Connection API Test App\n\n");
		printf("Options..\n");
		printf("1 	- VPN init and set callbacks\n");
		printf("2 	- VPN deinit(unset callbacks automatically)\n");
		printf("0 	- Exit \n");

		printf("ENTER  - Show options menu.......\n");
	}

	switch (a[0]) {
	case '1':
		rv = test_vpn_init();
		break;
	case '2':
		rv = test_vpn_deinit();
		break;
	default:
		break;
	}

	if (rv == 1)
		printf("Operation succeeded!\n");
	else
		printf("Operation failed!\n");

	return TRUE;
}


