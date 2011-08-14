/*
 * Ascent MMORPG Server
 * Copyright (C) 2005-2008 Ascent Team <http://www.ascentemu.com/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author:		Luck
 *
 */

#ifndef _ASCENT_H
#define _ASCENT_H

#include "AscentConfig.h"
#include "Common.h"
#include "CrashHandler.h"


#include "crc32.h"
#include "DebugTools.h"
#include "Singleton.h"
#include "Log.h"
#include "NGLog.h"
#include "Timer.h"

#include "StackWalker.h"


#include "PacketLog.h"
#include "Config/ConfigEnv.h"
#include <ctype.h>
#include "MersenneTwister.h"
#include "Threading/Mutex.h"
#include "Timer.h"
#include "MemoryLeaks.h"
#include <mysql.h>
#include "CrashHandler.h"

#include "CThreads.h"

//not sure if these are needed
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#pragma comment(lib, "version.lib")  // for "VerQueryValue"


//Config Includes
#include "Config/Config.h"
#include "Config/ConfigEnv.h"

//Threading Includes
#include "Threading/Threading.h"
#include "Threading/RWLock.h"
#include "Threading/ThreadPool.h"

//Database Includes
#include "Database/Field.h"
#include "Database/Database.h"
#include "Database/DatabaseEnv.h"

#if defined(ENABLE_DATABASE_MYSQL)
#  pragma message("[DATABASE LAYER] MySql")
#  include "Database/MySQLDatabase.h"
#endif

#if defined(ENABLE_DATABASE_POSTGRES)
#  pragma message("[DATABASE LAYER] PostgreSql - WARNING: BETA")
#  include "Database/PostgresDatabase.h"
#endif

#if defined(ENABLE_DATABASE_SQLITE)
#  pragma message("[DATABASE LAYER] Sqlite 3 - WARNING: BETA")
#  include "Database/SQLiteDatabase.h"
#endif

//HeapUtils Includes
#include "HeapUtils/ContainersInl.h"
#include "HeapUtils/DbgHeap.h"
#include "HeapUtils/GObjBase.h"
#include "HeapUtils/GuardObjs.h"

//Network Includes
#include "Network/Network.h"



// util fast queue
#include "FastQueue.h"
#include "ByteBuffer.h"
#include "string_map.h"

#ifdef __DragonFly__                                                            
#  include <pthread.h>                                                            
#endif//__DragonFly__

#include <fcntl.h>

#include <errno.h>

//#include "ascent_getopt.h"
















// database





#endif // _ASCENT_H