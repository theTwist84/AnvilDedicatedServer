#pragma once
#include "network_connection.h"
#include "..\messages\network_message_type_collection.h"
#include "..\transport\transport_address.h"
#include "..\session\network_observer.h"
#include "..\messages\network_message_gateway.h"
#include "..\messages\network_message_queue.h"

constexpr long k_network_channel_maximum_clients = 6;
constexpr long k_network_channel_maximum_base_clients = 3;
constexpr long k_network_channel_maximum_simulation_clients = 4;

enum e_network_channel_client_flags
{


	k_network_channel_client_flags_count
};

enum e_network_channel_state
{
	_network_channel_state_none,
	_network_channel_state_empty,
	_network_channel_state_closed,
	_network_channel_state_connecting,
	_network_channel_state_established,
	_network_channel_state_connected,

	k_network_channel_state_count
};

enum e_network_channel_activity
{
	k_network_channel_activity_count = 6
};

struct s_channel_configuration
{
	s_transport_address address;
};

struct s_client_iterator
{
	long required_client_flags;
	long client_designator;
	long client_index;
	long : 32;
	long : 32;
};

class c_network_channel_client
{
	void* vftable;
};

class c_network_channel_owner
{
	void* vftable;
};

struct s_client_info
{
	long flags; // e_network_channel_client_flags
	c_network_channel_client* client;
};

class c_network_channel_simulation_interface
{
	bool m_initialized;
	void* m_simulation_context;
	void* m_simulation_closure_callback;
	long m_client_count;
	s_client_info m_clients[k_network_channel_maximum_base_clients];








	//bool m_is_authority;
};

class c_network_channel_simulation_gatekeeper : c_network_channel_client
{
	void* vftable;
	bool data_available;
	bool data_expected;
};

class c_network_message_handler;
class c_network_channel
{
public:
	bool connected();
	char* get_name();
	char* get_message_type_name(e_network_message_type message_type);
	bool get_remote_address(s_transport_address* remote_address);
	// allocated()
	// allocate()
	// closed()
	// close()
	// simulation_can_be_established()
	// is_voice_only()
	// is_receive_only()
	// is_transmit_only()

private:
	c_network_link* m_link;
	c_network_observer* m_observer;
	c_network_message_gateway* m_message_gateway;
	c_network_message_handler* m_message_handler;
	s_channel_configuration* m_configuration; // g_network_configuration? s_channel_configuration?
	c_network_message_type_collection* m_type_collection;
	c_network_connection m_connection;
	c_network_message_queue m_message_queue; // 606
	c_network_channel_simulation_gatekeeper m_simulation_gatekeeper; // 631
	// above is 0x9E8 bytes
	byte unknown[0x6F0];
	// 0x9EC

	// 1,788 bytes remaining
	// 	   496 h3 debug gatekeeper size
	// 	   216
	// 
	// 632 = 
	// 633 = uint32_t m_client_count;
	// 634 = s_client_info m_clients[k_network_channel_maximum_base_clients];
	// 640 = c_network_channel_simulation_interface* m_simulation_interface;
	// 641 = m_flags
	// 642 = s_transport_unique_identifier m_remote_channel_identifier; // unique identifier inherits s_machine_identifier
	// 643 = identifier
	// 644 = e_network_channel_state m_channel_state; (_network_channel_state_none)
	// 645 = e_network_channel_closure_reason m_channel_closure_reason; (_network_channel_reason_none)
	// 646 = s_transport_address? something size 0x14?
	// 648 = unknown pointer to class/struct with s_transport_address at +4
	// 
	// 650 = char* also channel name/655?
	// 651 = s_transport_address m_remote_address;
	// 655 = char* m_channel_description; // secure address string - 0x100 size
	// 656 = init connect?
	// 657 = time related // c_network_time_statistics? size 0xD8 in h3debug
	// 658 = time related
	// 659 = 0, probably time related
	// 660 = something time related
	// 661 = time
	// 662 = array of activity time structs? struct is 16 bytes, array is k_network_channel_activity_count long
	// 663 = time
	// 664 = time
	// 665 = time
	// 666 = time
	// 
	// 668 = boolean?
	// 
	// 000 = s_channel_observer_owner m_owners[k_network_observer_owner_count];?
	// 687 = s_channel_observer m_channel_observers[k_network_maximum_observers];
	// 
	// 706 = c_network_time_statistics?
	// 
	// 729 = unknown_struct[6] // sizeof == 0x10 (first member uses network_time_get(), 3rd uses network_absolute_time_get() + 4)
	// 
	// sizeof == 0x11C0 in h3debug

	// new_channel_flags?
};
static_assert(sizeof(c_network_channel) == 0x10D8);