#include "main.hpp"

#include <unistd.h>
#include <sys/mman.h>
#include <GarrysMod/Lua/Interface.h>
#include <scanning/symbolfinder.hpp>
#include <string.h>
namespace global
{

	// Doesn't exist message!
	static const std::string bad_message_1 = "CreateFragmentsFromFile: '%s' doesn't exist.";
	// Couldn't invert rot matrix message!
	static const std::string bad_message_2 = "do_constraint_system: Couldn't invert rot matrix!";
	// File size limit message!
	static const std::string bad_message_3 = "CreateFragmentsFromFile: '%s' size exceeds net_maxfilesize limit (%i MB).";

	// Engine
	SourceSDK::ModuleLoader engine( "engine" );
	IServer *server = nullptr;

	// vPhysics
	SourceSDK::ModuleLoader vphysics( "vphysics" );

	static void Initialize( GarrysMod::Lua::ILuaBase *LUA )
	{	
		printf("Loaded hush!\n");
		SymbolFinder symfinder;
		if (!engine.IsValid( )) return;

		// First bad message
		void *patt = symfinder.FindPattern(
			engine.GetModule( ),
			reinterpret_cast<const uint8_t *>(bad_message_1.c_str( )),
			bad_message_1.length()
		);
		if( patt == nullptr ) return;
		
		size_t pagesize = sysconf(_SC_PAGESIZE);
		
		uintptr_t start = (uintptr_t) patt;
		uintptr_t end = start + bad_message_1.length();
		

		uintptr_t pagestart = start & -pagesize;

		if (mprotect((void *) pagestart, end - pagestart,
            PROT_READ | PROT_WRITE | PROT_EXEC)) {
			perror("mprotect");
			return;
		}
		
		char *buff = (char*)patt;
		buff[0] = '\0';
		printf("HUSH patched create fragements spam!\n");

		// Second bad message
		void *patt2 = symfinder.FindPattern(
			vphysics.GetModule( ),
			reinterpret_cast<const uint8_t *>(bad_message_2.c_str( )),
			bad_message_2.length()
		);
		if( patt2 == nullptr ) return;

		uintptr_t start2 = (uintptr_t) patt2;
		uintptr_t end2 = start2 + bad_message_2.length();

		uintptr_t pagestart2 = start2 & -pagesize;

		if (mprotect((void *) pagestart2, end2 - pagestart2,
			PROT_READ | PROT_WRITE | PROT_EXEC)) {
			perror("mprotect");
			return;
		}

		char *buff2 = (char*)patt2;
		buff2[0] = '\0';
		printf("HUSH patched contraint system spam2!\n");

		// Third bad message

		void *patt3 = symfinder.FindPattern(
			engine.GetModule( ),
			reinterpret_cast<const uint8_t *>(bad_message_3.c_str( )),
			bad_message_3.length()
		);
		if( patt3 == nullptr ) return;

		uintptr_t start3 = (uintptr_t) patt3;
		uintptr_t end3 = start3 + bad_message_3.length();

		uintptr_t pagestart3 = start3 & -pagesize;

		if (mprotect((void *) pagestart3, end3 - pagestart3,
			PROT_READ | PROT_WRITE | PROT_EXEC)) {
			perror("mprotect");
			return;
		}

		char *buff3 = (char*)patt3;
		buff3[0] = '\0';
		printf("HUSH patched create fragements spam2!\n");

	}

	static void Deinitialize( GarrysMod::Lua::ILuaBase *LUA )
	{
	}
}

GMOD_MODULE_OPEN( )
{
	global::Initialize( LUA );
	return 0;
}

GMOD_MODULE_CLOSE( )
{
	global::Deinitialize( LUA );
	return 0;
}
