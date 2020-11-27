#pragma once

#include <MyLogger.h>

#define LOG_GEN_ITEM(msg, instanceId, descId)\
LOG_INFO("[P{0:d} {1:s}] new instance id: {2:d} for desc id: {3:d}", playerId, #msg, instanceId, descId)

#define LOG_ERROR_SIMPLE(desc)\
LOG_ERROR("[P{0:d} {1:s}] {2:s}", playerId, message, desc)
#define LOG_ERROR_SIMPLE_C(charId, desc)\
LOG_ERROR("[C{0:d} {1:s}] {2:s}", charId, message, desc)

#define LOG_DB_GET_ERROR(domain)\
LOG_ERROR("[P{0:d} {1:s}] get({2:s}) error - [{3:d}] {4:s}", playerId, message, #domain, getRes.status().errcode(), getRes.status().description()); \
if(getRes.status().isNetworkError())\
	w["error"] = "DB_NETWORK_ERROR"

#define LOG_DB_SET_ERROR(domain)\
LOG_ERROR("[P{0:d} {1:s}] set({2:s}) error - [{3:d}] {4:s}", playerId, message, #domain, storeRes.status().errcode(), storeRes.status().description());

#define LOG_DB_GET_ERROR_C(charId, domain)\
LOG_ERROR("[C{0:d} {1:s}] get({2:s}) error - [{3:d}] {4:s}", charId, message, #domain, getRes.status().errcode(), getRes.status().description()); \
if(getRes.status().isNetworkError())\
	w["error"] = "DB_NETWORK_ERROR"

#define LOG_DB_SET_ERROR_C(charId, domain)\
LOG_ERROR("[C{0:d} {1:s}] set({2:s}) error - [{3:d}] {4:s}", charId, message, #domain, storeRes.status().errcode(), storeRes.status().description());
