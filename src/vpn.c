/*
* Network VPN library
*
* Copyright (c) 2014-2015 Samsung Electronics. All rights reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*              http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/

#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <vconf/vconf.h>

#include "vpn-internal.h"

static bool is_init = false;

EXPORT_API int vpn_initialize(void)
{
	if (is_init) {
		VPN_LOG(VPN_ERROR, "Already initialized\n");
		return VPN_ERROR_INVALID_OPERATION;
	}

	if (_vpn_init() == false) {
		VPN_LOG(VPN_ERROR, "Init failed!\n");
		return VPN_ERROR_OPERATION_FAILED;
	}

	is_init = true;

	VPN_LOG(VPN_INFO, "VPN successfully initialized!\n");

	return VPN_ERROR_NONE;
}

EXPORT_API int vpn_deinitialize(void)
{
	if (is_init == false) {
		VPN_LOG(VPN_ERROR, "Not initialized\n");
		return VPN_ERROR_INVALID_OPERATION;
	}

	if (_vpn_deinit() == false) {
		VPN_LOG(VPN_ERROR, "Deinit failed!\n");
		return VPN_ERROR_OPERATION_FAILED;
	}

	is_init = false;
	VPN_LOG(VPN_INFO, "VPN successfully de-initialized!\n");

	return VPN_ERROR_NONE;
}
