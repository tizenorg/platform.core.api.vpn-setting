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

#ifndef __TIZEN_NETWORK_VPN_H__
#define __TIZEN_NETWORK_VPN_H__

#include <tizen.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @addtogroup CAPI_NETWORK_VPN_MANAGER_MODULE
* @{
*/

/**
 * @brief The handle for vpn.
 */
typedef void *vpn_h;
typedef void *vpn_settings_h;

/**
* @brief The VPN error type
*/
typedef enum {
	VPN_ERROR_NONE = TIZEN_ERROR_NONE, /**< Successful */
	VPN_ERROR_INVALID_PARAMETER = TIZEN_ERROR_INVALID_PARAMETER, /**< Invalid parameter */
	VPN_ERROR_OUT_OF_MEMORY = TIZEN_ERROR_OUT_OF_MEMORY, /**< Out of memory error */
	VPN_ERROR_INVALID_OPERATION = TIZEN_ERROR_INVALID_OPERATION, /**< Invalid operation */
	VPN_ERROR_ADDRESS_FAMILY_NOT_SUPPORTED = TIZEN_ERROR_ADDRESS_FAMILY_NOT_SUPPORTED, /**< Address family not supported */
	VPN_ERROR_OPERATION_FAILED = TIZEN_ERROR_NETWORK_CLASS|0x0301, /**< Operation failed */
	VPN_ERROR_NO_CONNECTION = TIZEN_ERROR_NETWORK_CLASS|0x0302, /**< There is no connected AP */
	VPN_ERROR_NOW_IN_PROGRESS = TIZEN_ERROR_NOW_IN_PROGRESS, /** Now in progress */
	VPN_ERROR_ALREADY_EXISTS = TIZEN_ERROR_NETWORK_CLASS|0x0303, /**< Already exists */
	VPN_ERROR_OPERATION_ABORTED = TIZEN_ERROR_NETWORK_CLASS|0x0304, /**< Operation is aborted */
	VPN_ERROR_DHCP_FAILED = TIZEN_ERROR_NETWORK_CLASS|0x0306, /**< DHCP failed */
	VPN_ERROR_INVALID_KEY = TIZEN_ERROR_NETWORK_CLASS|0x0307, /**< Invalid key */
	VPN_ERROR_NO_REPLY = TIZEN_ERROR_NETWORK_CLASS|0x0308, /**< No reply */
	VPN_ERROR_SECURITY_RESTRICTED = TIZEN_ERROR_NETWORK_CLASS|0x0309, /**< Restricted by security system policy */
} vpn_error_e;

/**
* @}
*/

/**
* @addtogroup CAPI_NETWORK_VPN_MODULE
* @{
*/

/**
* @brief Initializes VPN
* @return 0 on success, otherwise negative error value.
* @retval #VPN_ERROR_NONE  Successful
* @retval #VPN_ERROR_INVALID_OPERATION  Invalid operation
* @retval #VPN_ERROR_OPERATION_FAILED  Operation failed
*/
int vpn_initialize(void);

/**
* @brief Deinitializes VPN
* @return 0 on success, otherwise negative error value.
* @retval #VPN_ERROR_NONE  Successful
* @retval #VPN_ERROR_INVALID_OPERATION  Invalid operation
* @retval #VPN_ERROR_OPERATION_FAILED  Operation failed
*/
int vpn_deinitialize(void);

/**
* @}
*/

/**
* @addtogroup CAPI_NETWORK_VPN_SETTINGS
* @{
*/

/**
* @brief Initializes VPN Settings
* @return 0 on success, otherwise negative error value.
* @retval #VPN_ERROR_NONE  Successful
* @retval #VPN_ERROR_INVALID_OPERATION  Invalid operation
* @retval #VPN_ERROR_OPERATION_FAILED  Operation failed
* @see vpn_settings_deinit()
*/
int vpn_settings_init();

/**
* @brief De-Initializes VPN Settings
* @return 0 on success, otherwise negative error value.
* @retval #VPN_ERROR_NONE  Successful
* @retval #VPN_ERROR_INVALID_OPERATION  Invalid operation
* @retval #VPN_ERROR_OPERATION_FAILED  Operation failed
* @pre vpn_settings_init() Must be called before deinit
* @see vpn_settings_deinit()
*/
int vpn_settings_deinit();

/**
* @brief Sets VPN Specific Settings
* @param[in] key  The Key for the Settings
* @param[in] value The Value for the Settings
* @return 0 on success, otherwise negative error value.
* @retval #VPN_ERROR_NONE  Successful
* @retval #VPN_ERROR_INVALID_OPERATION  Invalid operation
* @pre vpn_settings_init() must be  called before calling this API
* @retval #VPN_ERROR_OPERATION_FAILED  Operation failed
* @see vpn_settings_deinit()
*/
int vpn_settings_set_specific(const char *key, const char *value);

/**
* @}
*/

#ifdef __cplusplus
}
#endif

#endif /* __TIZEN_NETWORK_VPN_H__ */
