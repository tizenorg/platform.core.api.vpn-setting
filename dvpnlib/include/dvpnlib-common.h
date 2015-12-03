#ifndef __COMMON_LIB_H__
#define __COMMON_LIB_H__

#include <stdbool.h>
#include <glib.h>

#ifdef __cplusplus
extern "C" {
#endif

enum dvpnlib_err {
	/* Successful */
	DVPNLIB_ERR_NONE = 0,
	/* General error */
	DVPNLIB_ERR_FAILED,
	/* Specific error */
	DVPNLIB_ERR_OPERATION_FAILED,
	DVPNLIB_ERR_INVALID_PARAMETER,
	DVPNLIB_ERR_PERMISSION_DENIED,
	DVPNLIB_ERR_PASSPHRASE_REQUIRED,
	DVPNLIB_ERR_NOT_REGISTERED,
	DVPNLIB_ERR_NOT_UNIQUE,
	DVPNLIB_ERR_NOT_SUPPORTED,
	DVPNLIB_ERR_NOT_IMPLEMENTED,
	DVPNLIB_ERR_NOT_FOUND,
	DVPNLIB_ERR_NOT_CARRIER,
	DVPNLIB_ERR_IN_PROGRESS,
	DVPNLIB_ERR_ALREADY_EXISTS,
	DVPNLIB_ERR_ALREADY_ENABLED,
	DVPNLIB_ERR_ALREADY_DISABLED,
	DVPNLIB_ERR_ALREADY_CONNECTED,
	DVPNLIB_ERR_NOT_CONNECTED,
	DVPNLIB_ERR_OPERATION_ABORTED,
	DVPNLIB_ERR_OPERATION_TIMEOUT,
	DVPNLIB_ERR_INVALID_SERVICE,
	DVPNLIB_ERR_INVALID_PROPERTY,
	/* D-Bus error */
	DVPNLIB_ERR_TIMEOUT,
	DVPNLIB_ERR_UNKNOWN_PROPERTY,
	DVPNLIB_ERR_PROPERTY_READONLY,
	DVPNLIB_ERR_UNKNOWN_METHOD,
};

/*
 * Common
 */
typedef void(*dvpnlib_reply_cb)(enum dvpnlib_err result,
							void *user_data);

#ifdef __cplusplus
}
#endif

#endif