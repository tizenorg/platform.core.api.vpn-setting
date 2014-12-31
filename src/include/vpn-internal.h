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

#ifndef __VPN_CONNECTION_PRIVATE_H__
#define __VPN_CONNECTION_PRIVATE_H__

#include <connman-lib-common.h>

#include "vpn.h"
#include "common.h"

#define LOGI(fmt, arg...) printf("%s:%d %s() " fmt "\n",  \
				__FILE__, __LINE__, __func__, ## arg)
#define LOGW(fmt, arg...) printf("warning %s:%d %s() " fmt "\n", \
				__FILE__, __LINE__, __func__, ## arg)
#define LOGE(fmt, arg...) printf("error %s:%d %s() " fmt "\n", \
				__FILE__, __LINE__, __func__, ## arg)

#undef LOG_TAG
#define LOG_TAG "CAPI_NETWORK_VPN"

#define VPN_INFO	1
#define VPN_ERROR	2
#define VPN_WARN	3

#define VPN_LOG(log_level, format, args...) \
	do { \
		switch (log_level) { \
		case VPN_ERROR: \
			LOGE(format, ## args); \
			break; \
		case VPN_WARN: \
			LOGW(format, ## args); \
			break; \
		default: \
			LOGI(format, ## args); \
		} \
	} while (0)

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

bool _vpn_init(void);
bool _vpn_deinit(void);

int _vpn_settings_init();
int _vpn_settings_deinit();
int _vpn_settings_set_specific(const char *key, const char *value);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
