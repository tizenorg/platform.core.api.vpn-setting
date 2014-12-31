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
#include <ctype.h>
#include <glib.h>

#include <connman-vpn.h>
#include <connman-vpn-manager.h>

#include "vpn-internal.h"

static GHashTable *settings_hash;

/*
 * Utility Functions
 */

vpn_error_e _vpn_lib_error2vpn_error(enum connman_lib_err err_type)
{
	switch (err_type) {
	case CONNMAN_LIB_ERR_NONE:
		return VPN_ERROR_NONE;
	case CONNMAN_LIB_ERR_ALREADY_EXISTS:
		return VPN_ERROR_INVALID_OPERATION;
	case CONNMAN_LIB_ERR_NOT_REGISTERED:
		return VPN_ERROR_INVALID_OPERATION;
	case CONNMAN_LIB_ERR_NOT_CONNECTED:
		return VPN_ERROR_NO_CONNECTION;
	case CONNMAN_LIB_ERR_ALREADY_CONNECTED:
		return VPN_ERROR_ALREADY_EXISTS;
	case CONNMAN_LIB_ERR_IN_PROGRESS:
		return VPN_ERROR_NOW_IN_PROGRESS;
	case CONNMAN_LIB_ERR_OPERATION_ABORTED:
		return VPN_ERROR_OPERATION_ABORTED;
	case CONNMAN_LIB_ERR_OPERATION_TIMEOUT:
	case CONNMAN_LIB_ERR_TIMEOUT:
		return VPN_ERROR_NO_REPLY;
	default:
		return VPN_ERROR_OPERATION_FAILED;
	}
}

/*
 *Functions Actually use Connman VPN Library
 */

bool _vpn_init(void)
{
	int rv;

	rv = connman_vpn_init();

	if (rv != 0)
		return false;

	return true;
}

bool _vpn_deinit(void)
{
	connman_vpn_deinit();
	return true;
}

int _vpn_settings_init()
{
	if (settings_hash != NULL) {
		VPN_LOG(VPN_INFO,
			"Settings Hash: %p Already present!", settings_hash);
		return VPN_ERROR_INVALID_OPERATION;
	}

	settings_hash = g_hash_table_new_full(
				g_str_hash, g_str_equal,
				g_free, g_free);
	VPN_LOG(VPN_INFO, "Settings Hash: %p", settings_hash);

	return VPN_ERROR_NONE;
}

int _vpn_settings_deinit()
{
	if (settings_hash == NULL)
		return VPN_ERROR_INVALID_OPERATION;

	VPN_LOG(VPN_INFO, "Settings Hash: %p Destroyed", settings_hash);
	g_hash_table_destroy(settings_hash);
	settings_hash = NULL;

	return VPN_ERROR_NONE;
}

int _vpn_settings_set_specific(const char *key, const char *value)
{
	VPN_LOG(VPN_INFO,
		"Settings Hash: %p {%s=%s}", settings_hash, key, value);

	if (key == NULL)
		return VPN_ERROR_INVALID_PARAMETER;

	if (g_hash_table_contains(settings_hash, key)) {
		if (value == NULL) {
			VPN_LOG(VPN_INFO, "Settings Hash: %p {%s=%s} (Removed)",
				settings_hash, key,
				(gchar *)g_hash_table_lookup(
					settings_hash, key));
			g_hash_table_remove(settings_hash, key);
			return VPN_ERROR_NONE;
		}
	}

	g_hash_table_replace(settings_hash,
			(gpointer)g_strdup(key),
			(gpointer)g_strdup(value));

	return VPN_ERROR_NONE;
}

